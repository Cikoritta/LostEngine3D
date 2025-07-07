#include "../Engine/LostEngine.hpp"
#include "../Engine/Debug/Debug.hpp"

int main()
{
	le::Debug::setDebugMode(le::Debug::LogMode::Console);

	le::LostEngine pokemonAgeOfDragons;


	pokemonAgeOfDragons.RunEngine();


	return 0;
}