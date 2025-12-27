#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

int main(int argc, char **argv)
{
	if(argc < 2)
	{
		printf("Please specify filename.\nExample:\t./iv image.ppm\n");
		return 0;
	}
	FILE *pfile = fopen(argv[1], "r");
	if(pfile == NULL)
	{
		printf("Error: Couldn't find file \"%s\"", argv[1]);
		return 0;
	}
	char *pstr = (char *)calloc(1024, sizeof(char));
	int width = 0, height = 0;
	fgets(pstr, 1024, pfile);
	fgets(pstr, 1024, pfile);
	if(pstr[0] == '#') fgets(pstr, 1024, pfile);
	sscanf(pstr, "%d %d", &width, &height);
	fgets(pstr, 1024, pfile);
	free(pstr);
	
	SDL_Window *pwindow = SDL_CreateWindow("Image Viewer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
	SDL_Surface *psurface = SDL_GetWindowSurface(pwindow);

	Uint32 color = 0;
	SDL_Rect pixel = (SDL_Rect){0, 0, 1, 1};

	for(int y = 0; y < height; y++)
		for(int x = 0; x < width; x++)
		{
			Uint8 r, g, b;
			r = (char)getc(pfile);
			g = (char)getc(pfile);
			b = (char)getc(pfile);
		       	color = SDL_MapRGB(psurface->format, r, g, b);
	
			SDL_FillRect(psurface, &pixel, color);
			pixel.x = x;
			pixel.y = y;
		}
	SDL_UpdateWindowSurface(pwindow);

	fclose(pfile);
	
	int is_app_running = 1;
	while(is_app_running)
	{
		SDL_Event event;
		while(SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT)
				is_app_running = 0;
		}
		SDL_Delay(100);
	}
	return 0;
}
