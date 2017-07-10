
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include <string>
#include <sstream>
#include <string>
#include <fstream>
#include <iomanip>
//Screen attributes
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 1024;
const int SCREEN_BPP = 32;

//The surfaces
SDL_Surface *image = NULL;
SDL_Surface *screen = NULL;
SDL_Surface *msg = NULL;

//The font that's going to be used
TTF_Font *font = NULL;

//The color of the font
SDL_Color textColor = { 255, 255, 255 };

SDL_Surface *load_image( std::string filename )
{
    //The image that's loaded
    SDL_Surface* loadedImage = NULL;

    //The optimized image that will be used
    SDL_Surface* optimizedImage = NULL;

    //Load the image using SDL_image
    loadedImage = IMG_Load( filename.c_str() );

    //If the image loaded
    if( loadedImage != NULL )
    {
        //Create an optimized image
        optimizedImage = SDL_DisplayFormat( loadedImage );

        //Free the old image
        SDL_FreeSurface( loadedImage );
    }

    //Return the optimized image
    return optimizedImage;
}

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination )
{
    //Rectangle to hold the offsets
    SDL_Rect offset;

    //Get offsets
    offset.x = x;
    offset.y = y;

    //Blit the surface
    SDL_BlitSurface( source, NULL, destination, &offset );
}

bool init()
{
    //Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        return false;
    }

    //Set up the screen
    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE|SDL_FULLSCREEN );

    //If there was an error in setting up the screen
    if( screen == NULL )
    {
        return false;
    }
    //Initialize SDL_ttf
    if( TTF_Init() == -1 )
    {
        return false;
    }
    //Set the window caption
    SDL_WM_SetCaption( "Points", NULL );

    //If everything initialized fine
    return true;
}

void clean_up()
{
    //Free the surface
    SDL_FreeSurface( image );
    SDL_FreeSurface( msg );
    //Close the font that was used
    TTF_CloseFont( font );

    //Quit SDL_ttf
    TTF_Quit();

    //Quit SDL
    SDL_Quit();
}

std::string format_decimal (float val)
{
    std::ostringstream oss;

    oss << std::fixed << std::setfill ('0') << std::setprecision (2) << val;

    return oss.str();
}

bool load_files()
{
    //Load the background image
    image = load_image( "myimg.png" );

    //Open the font
    font = TTF_OpenFont( "myfont.ttf", 13 );

    //If there was a problem in loading the background
    if( image == NULL )
    {
        return false;
    }

    //If there was an error in loading the font
    if( font == NULL )
    {
        return false;
    }

    //If everything loaded fine
    return true;
}


int main( int argc, char* args[] )
{
    //Quit flag
    bool quit = false;

    //Initialize
    if( init() == false )
    { 
        return 1;
    }

    //Load the files
    if( load_files() == false )
    {
        return 1;
    }



    //Apply the surface to the screen
    std::ifstream source;                    // build a read-Stream

    source.open("generatedpoints.txt");  // open data
    int multiplier=10;
    for(std::string line; std::getline(source, line); )   //read stream line by line
    {
    std::istringstream in(line);      //make a stream for the line itself

   
        int number;
        float x, y;
        in >>number >> x >> y;
        apply_surface( x*multiplier, y*multiplier, image, screen );

        std::string formx=format_decimal(x);
        std::string formy=format_decimal(y);
        std::string print = "x:"+formx+" y:"+formy+" n:"+std::to_string(number);
        msg = TTF_RenderText_Solid( font, print.c_str(), textColor );
        apply_surface( x*multiplier, y*multiplier, msg, screen );
    }


    

    //Update the screen
    if( SDL_Flip( screen ) == -1 )
    {
        return 1;
    }

    //Wait 2 seconds
    SDL_Delay( 8000 );

    //Free the surface and quit SDL
    clean_up();

    return 0;
}
