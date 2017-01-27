#include <iostream>
#include <stdint.h>
#include <SDL.h>
#include <Rasterizer.h>
#include <glm.hpp> // This is the main GLM header
#include <matrix_transform.hpp> 
using namespace std;




//The surfaces that will be used
SDL_Surface *screen = NULL;

/*
SDL_Surface *load_image(std::string filename)
{
	//Temporary storage for the image that's loaded
	SDL_Surface* loadedImage = NULL;

	//The optimized image that will be used
	SDL_Surface* optimizedImage = NULL;

	//Load the image
	loadedImage = SDL_LoadBMP(filename.c_str());

	//If nothing went wrong in loading the image
	if (loadedImage != NULL)
	{
		//Create an optimized image
		optimizedImage = SDL_DisplayFormat(loadedImage);

		//Free the old image
		SDL_FreeSurface(loadedImage);
	}

	//Return the optimized image
	return optimizedImage;
}
*/
/*
void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination)
{
	//Make a temporary rectangle to hold the offsets
	SDL_Rect offset;

	//Give the offsets to the rectangle
	offset.x = x;
	offset.y = y;

	//Blit the surface
	SDL_BlitSurface(source, NULL, destination, &offset);
}
*/
int main(int argc, char**argv)
{

	//Initialize all SDL subsystems
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		return 1;
	}
	//Set up the screen
	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
	//If there was an error in setting up the screen
	if (screen == NULL)
	{
		return 1;
	}
	//Set the window caption
	SDL_WM_SetCaption("Hello World", NULL);
	//SDL_Surface *message = load_image("hello.bmp");
	Rasterizer rasterizer;
	rasterizer.SetFrameBuffer((uint32_t*)screen->pixels, SCREEN_WIDTH, SCREEN_HEIGHT);


	bool go = true;
	while (go)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			/* We are only worried about SDL_KEYDOWN and SDL_KEYUP events */
			switch (event.type){
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
				case SDLK_d:
					printf("d");
					break;
				case SDLK_ESCAPE:
					go = false;
					break;
				}
				break;

			case SDL_KEYUP:
				switch (event.key.keysym.sym)
				{
				case SDLK_d:
					printf("d");
					break;
				}
				break;

			default:
				break;
			}
		}
		//==============
		SDL_Rect scr;
		scr.x = 0;
		scr.y = 0;
		scr.w = SCREEN_WIDTH;
		scr.h = SCREEN_HEIGHT;
		SDL_FillRect(screen, &scr, SDL_MapRGB(screen->format, 0, 0, 0));
		//apply_surface(20, 0, message, screen);
		Color color0(1.0f, 0.0f, 0.0f, 1.0f);
		Color color1(0.0f, 1.0f, 0.0f, 1.0f);
		Color color2(0.0f, 0.0f, 1.0f, 1.0f);

		glm::vec4 v0(100.0f, 0.0f, 0.0f, 1.0f);
		glm::vec4 v1(-100.0f, -100.0f, 0.0f, 1.0f);
		glm::vec4 v2(-100.0, 100.0f, 0.0f, 1.0f);

		glm::mat4 _modelMatrix = glm::translate(glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(0.0f, 0.0f, 0.0f));
		glm::mat4 _viewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -10.0f));
		glm::mat4 _projectionMatrix = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 2000.0f);
		glm::mat4 _MVP = _projectionMatrix * _viewMatrix * _modelMatrix;

		//rasterizer.DrawLine(&color0, glm::ivec2(100, 100), &color1, glm::ivec2(200, 200));
		v0 = _MVP*v0;
		v1 = _MVP*v1;
		v2 = _MVP*v2;

		glm::vec2 p0(v0.x / v0.w + SCREEN_WIDTH / 2, v0.y / v0.w + SCREEN_HEIGHT / 2);
		glm::vec2 p1(v1.x / v1.w + SCREEN_WIDTH / 2, v1.y / v1.w + SCREEN_HEIGHT / 2);
		glm::vec2 p2(v2.x / v2.w + SCREEN_WIDTH / 2, v2.y / v2.w + SCREEN_HEIGHT / 2);

		//rasterizer.DrawWireTriangle(&color0, glm::ivec2(100, 100), &color1, glm::ivec2(200, 200), &color2, glm::ivec2(150, 300));
		//rasterizer.DrawTriangle(&color0, glm::ivec2(100, 100), &color1, glm::ivec2(200, 200), &color2, glm::ivec2(150, 300));
		rasterizer.DrawTriangle1(&color0, p0, &color1, p1, &color2, p2);
		//rasterizer.DrawTriangle1(&color0, glm::ivec2(400, 400), &color1, glm::ivec2(200, 200), &color2, glm::ivec2(100, 200));
		SDL_Flip(screen);
		SDL_Delay(10);
	}
	//Quit SDL
	SDL_Quit();
	
	return 0;
}
