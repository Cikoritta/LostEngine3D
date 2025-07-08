#include "Shader.hpp"

#include "../Debug/Debug.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <filesystem>

GLuint le::Shader::createShader(GLenum type, const std::string& source)
{
    GLuint shader = glCreateShader(type);
    const char* src = source.c_str();

    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        GLchar infoLog[512];

        glGetShaderInfoLog(shader, 512, nullptr, infoLog);

        LOG_WARN("Shader compilation failed: " + std::string(infoLog));

        glDeleteShader(shader);
    }

    return shader;
}


void le::Shader::saveProgramBinary(const std::string& filePath) const
{
    GLint length = 0;
    glGetProgramiv(m_program, GL_PROGRAM_BINARY_LENGTH, &length);
    if (length <= 0)
    {
        LOG_WARN("No program binary available to save.");
        return;
    }

    std::vector<GLubyte> binary(length);
    GLenum binaryFormat = 0;
    glGetProgramBinary(m_program, length, nullptr, &binaryFormat, binary.data());

    std::ofstream out(filePath, std::ios::binary);
    if (!out)
    {
        LOG_WARN("Failed to open file for saving shader binary: " + filePath);
        return;
    }

    out.write(reinterpret_cast<const char*>(&binaryFormat), sizeof(binaryFormat));
    out.write(reinterpret_cast<const char*>(binary.data()), length);
    out.close();

    LOG_DEBUG("Shader program binary saved to " + filePath);
}

bool le::Shader::loadProgramBinary(const std::string& filePath)
{
    std::ifstream in(filePath, std::ios::binary);
    if (!in)
    {
        LOG_DEBUG("No cached shader binary: " + filePath);
        return false;
    }

    GLenum binaryFormat;
    in.read(reinterpret_cast<char*>(&binaryFormat), sizeof(binaryFormat));
    if (in.fail())
    {
        LOG_WARN("Failed to read shader binary format.");
        return false;
    }

    std::vector<GLubyte> binaryData((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
    if (binaryData.empty())
    {
        LOG_WARN("Shader binary data is empty.");
        return false;
    }

    if (m_program != 0)
        glDeleteProgram(m_program);

    m_program = glCreateProgram();
    glProgramBinary(m_program, binaryFormat, binaryData.data(), static_cast<GLsizei>(binaryData.size()));

    GLint success = 0;
    glGetProgramiv(m_program, GL_LINK_STATUS, &success);
    if (!success)
    {
        GLchar infoLog[512];
        glGetProgramInfoLog(m_program, 512, nullptr, infoLog);
        LOG_WARN("Failed to load shader binary: " + std::string(infoLog));
        glDeleteProgram(m_program);
        m_program = 0;
        return false;
    }

    LOG_DEBUG("Loaded shader program binary from " + filePath);
    return true;
}


void le::Shader::loadFromSource(const std::string& vertexShaderSource, const std::string& fragmentShaderSource)
{
    if (m_program != 0)
    {
        glDeleteProgram(m_program);
        m_program = 0;
    }

    GLuint vs = createShader(GL_VERTEX_SHADER, vertexShaderSource);
    GLuint fs = createShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    if (vs == 0 || fs == 0)
    {
        LOG_WARN("Shader creation failed, cannot create program.");

        if (vs != 0) glDeleteShader(vs);
        if (fs != 0) glDeleteShader(fs);
    }

    m_program = glCreateProgram();

    glProgramParameteri(m_program, GL_PROGRAM_BINARY_RETRIEVABLE_HINT, GL_TRUE);

    glAttachShader(m_program, vs);
    glAttachShader(m_program, fs);
    glLinkProgram(m_program);

    GLint success;
    glGetProgramiv(m_program, GL_LINK_STATUS, &success);

    if (!success)
    {
        GLchar infoLog[512];
        glGetProgramInfoLog(m_program, 512, nullptr, infoLog);
        LOG_WARN("Shader program linking failed: " + std::string(infoLog));

        glDeleteProgram(m_program);
        m_program = 0;
    }

    glDeleteShader(vs);
    glDeleteShader(fs);
}

void le::Shader::loadFromFile(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
{
    namespace fs = std::filesystem;

    fs::path vertexPath(vertexShaderPath);
    fs::path shaderDir = vertexPath.parent_path();

    std::string binaryFileName = vertexPath.filename().string() + "_" + fs::path(fragmentShaderPath).filename().string() + ".bin";

    fs::path binaryPath = shaderDir / binaryFileName;

    if (loadProgramBinary(binaryPath.string()))
        return;
    auto readFile = [](const std::string& path) -> std::string
        {
            std::ifstream file;
            file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

            try
            {
                file.open(path);
                std::stringstream buffer;
                buffer << file.rdbuf();
                return buffer.str();
            }
            catch (const std::ifstream::failure& e)
            {
                LOG_WARN("Failed to read shader file '" + path + "': " + e.what());
                return "";
            }
        };

    std::string vertexSource = readFile(vertexShaderPath);
    std::string fragmentSource = readFile(fragmentShaderPath);

    if (vertexSource.empty() || fragmentSource.empty())
    {
        LOG_WARN("Shader source empty after reading files, aborting shader load.");
        return;
    }

    loadFromSource(vertexSource, fragmentSource);

    fs::create_directories(binaryPath.parent_path());

    saveProgramBinary(binaryPath.string());
}


void le::Shader::use() const
{
    glUseProgram(m_program);
}


void le::Shader::setUniform1i(const std::string& name, int value) const
{
    GLint location = glGetUniformLocation(m_program, name.c_str());
    if (location != -1)
        glUniform1i(location, value);
    else
        LOG_WARN("Uniform '" + name + "' not found");
}

void le::Shader::setUniform1f(const std::string& name, float value) const
{
    GLint location = glGetUniformLocation(m_program, name.c_str());
    if (location != -1)
        glUniform1f(location, value);
    else
        LOG_WARN("Uniform '" + name + "' not found");
}

void le::Shader::setUniformVec2(const std::string& name, const glm::vec2& vec) const
{
    GLint location = glGetUniformLocation(m_program, name.c_str());
    if (location != -1)
        glUniform2fv(location, 1, &vec[0]);
    else
        LOG_WARN("Uniform '" + name + "' not found");
}

void le::Shader::setUniformVec3(const std::string& name, const glm::vec3& vec) const
{
    GLint location = glGetUniformLocation(m_program, name.c_str());
    if (location != -1)
        glUniform3fv(location, 1, &vec[0]);
    else
        LOG_WARN("Uniform '" + name + "' not found");
}

void le::Shader::setUniformVec4(const std::string& name, const glm::vec4& vec) const
{
    GLint location = glGetUniformLocation(m_program, name.c_str());
    if (location != -1)
        glUniform4fv(location, 1, &vec[0]);
    else
        LOG_WARN("Uniform '" + name + "' not found");
}

void le::Shader::setUniformMat4(const std::string& name, const glm::mat4& mat) const
{
    GLint location = glGetUniformLocation(m_program, name.c_str());
    if (location != -1)
        glUniformMatrix4fv(location, 1, GL_FALSE, &mat[0][0]);
    else
        LOG_WARN("Uniform '" + name + "' not found");
}
