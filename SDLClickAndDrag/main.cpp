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
    bool quit = false; // While loop condition initialized
    
    // Init screen and check it worked
    SDL_Surface *screen = project.init("Click and Drag");
    if (screen == NULL) return 1;
    
    // Get image loaded from file
    SDL_Surface *image = project.load_file("foo.png");
    if (image == NULL) return 1;
    
    while (!quit) {
        quit = true;
    }
    
    return 0;
}

