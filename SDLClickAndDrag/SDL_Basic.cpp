//
//  SDL_Basic.cpp
//  SDLClickAndDrag
//
//  Created by Maribeth Rauh on 3/27/13.
//  Copyright (c) 2013 Maribeth Rauh. All rights reserved.
//

#include "SDL_Basic.h"

SDL_Basic::SDL_Basic(int width, int height, int bpp) {
    SCREEN_WIDTH = width;
    SCREEN_HEIGHT = height;
    SCREEN_BPP = bpp;
}

//takes single filename, returns surface; opens a font
SDL_Surface * SDL_Basic::load_file( std::string filename ) {
    //Load the image
    SDL_Surface * newImage = load_image( filename );
    
    //Open the font
    //font = TTF_OpenFont( "RalewayThin.ttf", 20 );
    
    //If everything loaded fine
    return newImage;
}

//takes single filename, loads image, optimizes it to screen and returns it
SDL_Surface * SDL_Basic::load_image( std::string filename ) {
    SDL_Surface *loadedImage = NULL;
    SDL_Surface *optimizedImage = NULL;
    
    loadedImage = IMG_Load(filename.c_str());
    
    if (loadedImage != NULL) {
        optimizedImage = SDL_DisplayFormat(loadedImage);
        SDL_FreeSurface(loadedImage);
        
        //Map the color key
        if (optimizedImage != NULL) {
            Uint32 colorkey = SDL_MapRGB( optimizedImage->format, 0, 0xFF, 0xFF );
            
            //Set all pixels of color R 0, G 0xFF, B 0xFF to be transparent
            SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, colorkey );
        }
    }
    
    return optimizedImage;
}

//creates an SDL_Rect that corresponds to an image (SDL_Surface)
SDL_Rect SDL_Basic::createRect(SDL_Surface * image) {
    SDL_Rect rect;
    rect.w = image->w;
    rect.h = image->h;
    
    // will be updated when apply_surface called
    rect.x = NULL;
    rect.y = NULL;
    
    return rect;
}

//Parameters 1, 2: x and y coordinates indicating where image will be blitted
//Parameter 3: image to be blitted
//Parameter 4: image being blitted onto
//Parameter 5: which clip of source to blit
//blits image to destination at (x, y)
SDL_Rect SDL_Basic::apply_surface( int x, int y, SDL_Surface *source, SDL_Rect offset, SDL_Surface *destination, SDL_Rect * clip) {
    offset.x+=x;
    offset.y+=y;
    
    // changes x and y image is being blitted at if image's center point is over a snap region
    //offset = snapToLocation(offset);
    
    SDL_BlitSurface( source, clip, destination, &offset );
    return offset;
}

bool SDL_Basic::mouseOverImage(SDL_Rect imageRect, int x, int y) {
    //check if mouse coordinates are within the bounds of the rect that corresponds to the image
    if (x > imageRect.x && x < (imageRect.x + imageRect.w) && y > imageRect.y && y < (imageRect.y + imageRect.h)) {
        return true;
    }else{
        return false;
    }
}

//sets up screen and caption at at the top of the screen, returns the screen
SDL_Surface * SDL_Basic::init(std::string title) {
    //Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 ) return NULL;
    
    //Set up the screen
    SDL_Surface *screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );
    
    //If there was an error in setting up the screen
    if( screen == NULL ) return NULL;
    
    //Initialize SDL_ttf
    if( TTF_Init() == -1 ) return NULL;
    
    //Set the window caption
    SDL_WM_SetCaption( title.c_str(), NULL );
    
    //If everything initialized fine
    return screen;
}

void SDL_Basic::clean_up() {
    //Free the images in the main/another function call here
    //SDL_FreeSurface( screen );
    
    //Close the font that was used in the main/another function call here
    //TTF_CloseFont( font );
    
    //Quit SDL_ttf
    TTF_Quit();
    
    //Quit SDL
    SDL_Quit();
}