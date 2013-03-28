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
    
    //Fill the screen white
    SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF ) );
    
    // Gets image loaded from file
    SDL_Surface *image = project.load_file("foo.png");
    if (image == NULL) return 1;
    SDL_Rect imageRect = project.createRect(image);
    project.apply_surface(50, 50, image, imageRect, screen, NULL);

    // Create area an image will snap to if its center point enters said area
    project.setUpSnapRegion(100, 100, screen);
    
    // Initial screen displayed
    if (SDL_Flip(screen) == -1) return 1;

    
    
    bool mousePressedOnImage = false;
    while (!quit) {

        // Processes events while events are in the queue
        // Use switch case eventually?
        while (SDL_PollEvent( &event )) {
            
            if (event.type == SDL_QUIT) {   // If user clicks 'x' in top left corner
                quit = true;
                
            }else if (event.type == SDL_MOUSEBUTTONDOWN) { // If mouse was pressed down
                mousePressedOnImage = project.mouseOverImage(imageRect, event.motion.x, event.motion.y);
                
            }else if (event.type == SDL_MOUSEBUTTONUP) {
                mousePressedOnImage = false;
                
            }else if (event.type == SDL_MOUSEMOTION && mousePressedOnImage /*&& project.mouseOverImage()*/) {
                int x, y;
                SDL_GetRelativeMouseState(&x, &y); // not quite working...big x and y jump when first clicked
                //int x = event.motion.x;
                //int y = event.motion.y;
                //std::cout << x << ", " << y << std::endl;
                
                // Fill the screen white
                SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF ) );
                // Reapply snap region image
                project.applySnapRegion(screen);
                // Reapply image
                imageRect = project.apply_surface(x, y, image, imageRect, screen, NULL);
                                
                // Update Screen
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

