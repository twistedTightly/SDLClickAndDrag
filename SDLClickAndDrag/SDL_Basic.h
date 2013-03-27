//
//  SDL_Basic.h
//  SDLClickAndDrag
//
//  Created by Maribeth Rauh on 3/27/13.
//  Copyright (c) 2013 Maribeth Rauh. All rights reserved.
//
//
//  Implements many of the basic tasks needed to run an SDL program, grouped appropriately
//
//  Most of the code is taken from the LazyFoo' tutorials.  However, many methods' parameters
//  and return values were changed so they work correctly when this class is composed in another
//  or used in a main program
//
//  Could be subclassed to contain methods that group SDL functions that are commonly used together
//  for a more specific purpose (ex: mouse events). This class is meant to provide the most basic
//  functionality every SDL program will have.
//

#ifndef __SDLClickAndDrag__SDL_Basic__
#define __SDLClickAndDrag__SDL_Basic__

#include <iostream>
#include <string>
#include "SDL/SDL.h"
#include "SDL_image/SDL_image.h"
#include "SDL_ttf/SDL_ttf.h"

class SDL_Basic {
    public:
        SDL_Basic(int = 640, int = 480, int = 32);
        SDL_Surface *load_file(std::string);    //takes single filename, returns surface; opens a font
        SDL_Surface *load_image(std::string);   //takes single filename, loads image, optimizes it to screen and returns it
        void apply_surface(int, int, SDL_Surface *, SDL_Surface *, SDL_Rect *); //blits image to destination at (x, y)
        SDL_Surface *init(std::string);  //sets up screen and caption at at the top of the screen, returns the screen
        void clean_up();
    
    private:
        int SCREEN_WIDTH;
        int SCREEN_HEIGHT;
        int SCREEN_BPP;
};


#endif /* defined(__SDLClickAndDrag__SDL_Basic__) */
