#include "SDL_load.h"

//for testing
class GameObject {
	public:
		int x, y;
		std::string name;
		SDL_Surface* surface;
		GameObject();
		void show();
		virtual void handleInput() = 0;
		void getDistance(int xPos, int yPos); //get distance between two objects
};
class MovingGameObject: public GameObject {
	public:
		int xVelocity, yVelocity;
		MovingGameObject();
		virtual void move() = 0;
};

class RectangularGameObject: public MovingGameObject {

};

class CircularGameObject: public MovingGameObject {
	public:
		int radius;
		CircularGameObject() {
			radius = 0;
		}
};

GameObject::GameObject() {
	x = 0;
	y = 0;
}

MovingGameObject::MovingGameObject() {
	xVelocity = 0;
	yVelocity = 0;
}

class Timer {
	private:
		int startTicks;
		int pausedTicks;
		bool paused;
		bool started;

	public:
		Timer();
		void start();
		void stop();
		void pause();
		void unpause();
		int getTicks();
		bool isStarted();
		bool isPaused();
};

Timer::Timer() {
	startTicks = 0;
	pausedTicks = 0;
	paused = false;
	started = false;
}

void Timer::start() {
	started = true;
	paused = false;
	startTicks = SDL_GetTicks();
}

void Timer::stop() {
	started = false;
	paused = false;
}

void Timer::pause() {
	//If the timer is running and isn't already paused
	if( ( started == true ) && ( paused == false ) ) {
		paused = true;
		//Calculate the paused ticks
		pausedTicks = SDL_GetTicks() - startTicks;
    	}
}

void Timer::unpause() {
	if( paused == true ) {
		paused = false;
		//reset ticks
		startTicks = SDL_GetTicks() - pausedTicks;
		//Reset the paused ticks
		pausedTicks = 0;
	}
}

int Timer::getTicks() {
	if( started == true ) {
		if( paused == true ) {
			//Return the number of ticks when the timer was paused
			return pausedTicks;
		} else {
			//Return the current time minus the start time
			return SDL_GetTicks() - startTicks;
		}
	}

	return 0;
}

bool Timer::isStarted() {
	return started;
}

bool Timer::isPaused() {
	return paused;
}
