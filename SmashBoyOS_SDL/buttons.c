#include "allHeaders.h"

void exitOnButton(){
	SDL_Event event;
	
	int done = 0;
	while ( !done ) {
		
		/* Check for events */
		while ( SDL_PollEvent(&event) ) {
			switch (event.type) {
					
				case SDL_MOUSEMOTION:
					break;
				case SDL_MOUSEBUTTONDOWN:
					break;
				case SDL_KEYDOWN:
					/* Any keypress quits the app... */
				case SDL_QUIT:
					done = 1;
					break;
				default:
					break;
			}
		}
	}
	
	/* Clean up the SDL library */
	SDL_Quit();
}