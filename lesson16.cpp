/*This source code copyrighted by Lazy Foo' Productions (2004-2012)
and may not be redestributed without written permission.*/

//The headers
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>
#include "sdlhelper/SDL_objects.h"
#include <iostream>

//The screen attributes
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

//The frame rate
const int FRAMES_PER_SECOND = 20;

//The dimensions of the dot
const int DOT_WIDTH = 20;
const int DOT_HEIGHT = 20;

//The surfaces
SDL_Surface *screen = NULL;

//The event structure
SDL_Event event;

class Dot : public MovingGameObject {
	public:
		virtual void handleInput();
		void move();
		void show();
};

void Dot::show() {
	applySurface(surface, screen, x, y);
}

void Dot::handleInput() {
	//If a key was pressed
	if( event.type == SDL_KEYDOWN ) {
	//Adjust the velocity
		switch( event.key.keysym.sym ) {
			case SDLK_UP: yVelocity -= DOT_HEIGHT / 2; break;
			case SDLK_DOWN: yVelocity += DOT_HEIGHT / 2; break;
			case SDLK_LEFT: xVelocity -= DOT_WIDTH / 2; break;
			case SDLK_RIGHT: xVelocity += DOT_WIDTH / 2; break;
		}
	} else if( event.type == SDL_KEYUP ) { //if a key is released
		//Adjust the velocity
		switch( event.key.keysym.sym ) {
			case SDLK_UP: yVelocity += DOT_HEIGHT / 2; break;
			case SDLK_DOWN: yVelocity -= DOT_HEIGHT / 2; break;
			case SDLK_LEFT: xVelocity += DOT_WIDTH / 2; break;
			case SDLK_RIGHT: xVelocity -= DOT_WIDTH / 2; break;
		}
	}
}

void Dot::move() {
	//Move the dot
	x += xVelocity;

	//If the dot went too far to the left or right
	if( (x < 0) || (x + DOT_WIDTH > SCREEN_WIDTH) ) {
		//move back
		x -= xVelocity;
	}

	//Move the dot up or down
	y += yVelocity;

	//If the dot went too far up or down
	if( (y < 0) || (y + DOT_HEIGHT > SCREEN_HEIGHT) ) {
		//move back
		y -= yVelocity;
	}
}

class Dot2 : public Dot {
	public:
		void handleInput();
};

void Dot2::handleInput() {
	//If a key was pressed
	if( event.type == SDL_KEYDOWN ) {
	//Adjust the velocity
		switch( event.key.keysym.sym ) {
			case 'w': yVelocity -= DOT_HEIGHT / 2; break;
			case 's': yVelocity += DOT_HEIGHT / 2; break;
			case 'a': xVelocity -= DOT_WIDTH / 2; break;
			case 'd': xVelocity += DOT_WIDTH / 2; break;
		}
	} else if( event.type == SDL_KEYUP ) { //if a key is released
		//Adjust the velocity
		switch( event.key.keysym.sym ) {
			case 'w': yVelocity += DOT_HEIGHT / 2; break;
			case 's': yVelocity -= DOT_HEIGHT / 2; break;
			case 'a': xVelocity += DOT_WIDTH / 2; break;
			case 'd': xVelocity -= DOT_WIDTH / 2; break;
		}
	}
}

bool loadFiles(Dot* dot, Dot2* dot2)
{
	//Load the dot image
	dot->surface = (SDL_Surface*)malloc(sizeof(SDL_Surface));
	dot->surface = loadKeyedOptimizedSurface("dot.bmp");

	dot2->surface = (SDL_Surface*)malloc(sizeof(SDL_Surface));
	dot2->surface = loadKeyedOptimizedSurface("dot.bmp");

	//If there was a problem in loading the dot
	if( dot == NULL ) {
		return false;
	}

	//If everything loaded fine
	return true;
}

bool init(const char* title, int SCREEN_WIDTH, int SCREEN_HEIGHT, int SCREEN_BPP) {
	//Initialize all SDL subsystems
	if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 ) {
		return false;
	}
	
	//Set up the screen
	screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );

	//If there was an error in setting up the screen
	if( screen == NULL ) {
		return false;
	}

	//Set the window caption
	SDL_WM_SetCaption( title, NULL );

	//If everything initialized fine
	return true;
}

using namespace std;

int main(int argc, char** argv) {
	bool quit = false;
	Dot myDot;
	Dot2 myDot2;
	Timer frameRateCounter;
	std::string title = "Move the Dot XD";
	cout << "initializing..." << endl;
	if(init(title.c_str(), SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP) == false) {
		return 1;
	}
	cout << "loading files..." << endl;
	if(loadFiles(&myDot, &myDot2) == false) {
		return 1;
	}

	while(quit == false) {
		cout << "starting frame rate counter..." << endl;
		frameRateCounter.start();

		cout << "starting event queue..." << endl;
		while( SDL_PollEvent( &event ) ) {
			myDot.handleInput();
			myDot2.handleInput();
			if( event.type == SDL_QUIT ) {
				quit = true;
			}
        	}
		
		myDot.move();
		myDot2.move();
		
		SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF ) );
		cout << "done!" << endl;
		myDot.show();
		myDot2.show();
		if( SDL_Flip( screen ) == -1 ) {
			return 1;
		}

		if( frameRateCounter.getTicks() < 1000 / FRAMES_PER_SECOND ) {
			SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - frameRateCounter.getTicks() );
		}
	}

	SDL_FreeSurface( myDot.surface );
	SDL_FreeSurface( myDot2.surface );
	SDL_Quit();
}
