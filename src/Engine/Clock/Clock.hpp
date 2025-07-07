#pragma once
#include <chrono>

namespace le
{
	class Clock
	{
		using ClockType = std::chrono::steady_clock;

		using TimePoint = std::chrono::time_point<ClockType>;

		TimePoint startTime{};

		TimePoint stopTime{};

		TimePoint pauseStart{};

		std::chrono::duration<double> pauseDuration{ 0 };

		bool running = false;

		bool paused = false;

	public:

        Clock() = default;

        void start();

        void stop();


        void pause();

        void reset();


		float getTime() const;
	};
}