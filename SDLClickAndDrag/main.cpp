//
//  main.cpp
//  SDLClickAndDrag
//
//  Created by Maribeth Rauh on 3/24/13.
//  Copyright (c) 2013 Maribeth Rauh. All rights reserved.
//

#include <iostream>
#include <string>
#include "SDL/SDL.h"
#include "SDL_image/SDL_image.h"
#include "SDL_ttf/SDL_ttf.h"
#include "SDL_Basic.h"           // Custom class with basic SDL functionality grouped into methods

int main( int argc, char* args[] ) // MUST use these arguments and return type for main when using SDL
{
    SDL_Basic project; // Instantiated so basic SDL methods developed in SDL_Basic can be accessed
    SDL_Event event;
    bool quit = false; // While loop condition initialized
    
    // Inits screen and checks it worked
    SDL_Surface *screen = project.init("Click and Drag");
    if (screen == NULL) return 1;
    
    // Gets image loaded from file
    SDL_Surface *image = project.load_file("foo.png");
    if (image == NULL) return 1;
    
    //Fill the screen white
    SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF ) );
    // Initial screen displayed
    if (SDL_Flip(screen) == -1) return 1;
    
    
    bool mousePressed = false;
    while (!quit) {

        // Processes events while events are in the queue
        while (SDL_PollEvent( &event )) {
            
            if (event.type == SDL_QUIT) {   // If user clicks 'x' in top left corner
                quit = true;
            }else if (event.type == SDL_MOUSEBUTTONDOWN) { //If mouse was pressed
                mousePressed = true;
            }else if (event.type == SDL_MOUSEBUTTONUP) {
                mousePressed = false;
            }else if (event.type == SDL_MOUSEMOTION && mousePressed) {
                int x = event.motion.x;
                int y = event.motion.y;
                
                project.apply_surface(x, y, image, screen, NULL);
                
                //Update Screen
                if (SDL_Flip( screen ) == -1) return 1;
            }
        }
    }
    
    
    // Clean up at end of program
    SDL_FreeSurface(image);
    SDL_FreeSurface(screen);
    project.clean_up();
    
    return 0;
}

