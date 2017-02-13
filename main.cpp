#include <iostream>
#include <stdint.h>
#include <SDL.h>
#include <Rasterizer.h>
#include <glm.hpp> // This is the main GLM header
#include <matrix_transform.hpp>
#include <Obj2.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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
    Obj2 obj("cube_VT_VN.obj"/*"sphereUV.obj"*/);
    obj.loadAll();
    ////////////////
    //delta time
    clock_t lastTime = SDL_GetTicks();
    float oneSecCount = 0.0f;
    ////////////////
    float yAngle = 0.0f;
	bool go = true;
	//--------------------------------------------------------------------
	while (go)
	{
        /////////////////////////////////////
        //delta time
        clock_t currentTime = SDL_GetTicks();//clock();
        float deltaTs = (float) (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;
        printf("%f \n", deltaTs);


        //1 second event counter
        if(oneSecCount >= 1.0f)
        {
            //do stuff every 1 sec
            //yAngle += 5.0f;

            //////////////////////
            oneSecCount = 0.0f;
        }
        else
        {
            oneSecCount += deltaTs;
        }
        yAngle++;
	    /////////////////////////////////////
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
					yAngle++;
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
		///////////////////////////////////
        SDL_Rect scr;
        scr.x = 0;
        scr.y = 0;
        scr.w = SCREEN_WIDTH;
        scr.h = SCREEN_HEIGHT;
        SDL_FillRect(screen, &scr, SDL_MapRGB(screen->format, 0, 0, 0));

        Color color0(1.0f, 0.0f, 0.0f, 1.0f);
        Color color1(0.0f, 1.0f, 0.0f, 1.0f);
        Color color2(0.0f, 0.0f, 1.0f, 1.0f);

        Color color3(1.0f,1.0f,1.0f,1.0f);

//        printf("%f %f %f \n %f %f %f \n %f %f %f  \n \n",
//               obj.VRTE[0], obj.VRTE[1], obj.VRTE[2],
//               obj.VRTE[3], obj.VRTE[4], obj.VRTE[5],
//               obj.VRTE[6], obj.VRTE[7], obj.VRTE[8]);
        //Color color0(obj.VRTE[0], obj.VRTE[1], obj.VRTE[2], 1.0f);
        //Color color1(obj.VRTE[3], obj.VRTE[4], obj.VRTE[5], 1.0f);
        //Color color2(obj.VRTE[6], obj.VRTE[7], obj.VRTE[8], 1.0f);

        //glm::vec4 v0(100.0f, 0.0f, 0.0f, 1.0f);
        //glm::vec4 v1(-100.0f, -100.0f, 0.0f, 1.0f);
        //glm::vec4 v2(-100.0, 100.0f, 0.0f, 1.0f);


        glm::vec4 v0(obj.VRTE[0], obj.VRTE[1], obj.VRTE[2], 1.0f);
        glm::vec4 v1(obj.VRTE[3], obj.VRTE[4], obj.VRTE[5], 1.0f);
        glm::vec4 v2(obj.VRTE[6], obj.VRTE[7], obj.VRTE[8], 1.0f);

        glm::mat4 _modelMatrix = glm::translate(glm::scale(glm::rotate(glm::mat4(1.0f), (yAngle *glm::pi<float>() )/180.0f, glm::vec3(0.0f, 1.0f, .0f)), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(0.0f, 0.0f, 0.0f));
        glm::mat4 _viewMatrix = glm::translate( glm::rotate(glm::mat4(1.0f), (0.0f *glm::pi<float>() )/180.0f, glm::vec3(0.0f, 1.0f, .0f)), glm::vec3(0.0f, 0.0f, -5.0f));
        glm::mat4 _projectionMatrix = glm::perspectiveFov<float>(45.0f,SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 2000.0f);
        glm::mat4 _MVP = _projectionMatrix * _viewMatrix * _modelMatrix;


        //draw border
        rasterizer.DrawLine(&color3, glm::ivec2(0, 0), &color3, glm::ivec2(SCREEN_WIDTH-1, 0));
        rasterizer.DrawLine(&color3, glm::ivec2(0, SCREEN_HEIGHT-1), &color3, glm::ivec2(SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1));
        rasterizer.DrawLine(&color3, glm::ivec2(0, 0), &color3, glm::ivec2(0, SCREEN_HEIGHT-1));
        rasterizer.DrawLine(&color3, glm::ivec2(SCREEN_WIDTH-1, 0), &color3, glm::ivec2(SCREEN_WIDTH-1, SCREEN_HEIGHT-1));

        //rasterizer.DrawLine(&color3, glm::ivec2(500, 500), &color3, glm::ivec2(500, 0));

        //v0 = _MVP*v0;
        //v1 = _MVP*v1;
        //v2 = _MVP*v2;

        //glm::vec2 p0((v0.x / v0.w)*SCREEN_WIDTH/2  + SCREEN_WIDTH / 2, (v0.y / v0.w)*SCREEN_HEIGHT/2 + SCREEN_HEIGHT / 2);
        //glm::vec2 p1((v1.x / v1.w)*SCREEN_WIDTH/2  + SCREEN_WIDTH / 2, (v1.y / v1.w)*SCREEN_HEIGHT/2 + SCREEN_HEIGHT / 2);
        //glm::vec2 p2((v2.x / v2.w)*SCREEN_WIDTH/2  + SCREEN_WIDTH / 2, (v2.y / v2.w)*SCREEN_HEIGHT/2 + SCREEN_HEIGHT / 2);

        //printf("\n %f %f %f \n",v0.x,v0.y, v0.w);
        //printf("%f %f %f \n",v1.x, v1.y, v1.w);
        //printf("%f %f %f \n",v2.x, v2.y, v2.w);
        /////////////////////////////////////////
        //rasterizer.DrawTriangle1(&color0, p0, &color1, p1, &color2, p2);
        //rasterizer.DrawWireTriangle(&color0, p0, &color1, p1, &color2, p2);
        rasterizer.DrawTriangles(&obj.vertices, _MVP);

        SDL_Flip(screen);
        SDL_Delay(10);
	}
	//Quit SDL
	SDL_Quit();

	return 0;
}
