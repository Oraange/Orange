#include "GameFuncEnd.h"
#include "GameFuncPhase.h"
#include "SDL_image.h"
#include <iostream>
#include <windows.h>
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include <string>

extern SDL_Window* g_window;
extern SDL_Renderer* g_renderer;
extern bool g_flag_running;
extern int g_current_game_phase;


SDL_Rect bg_source_over_;
SDL_Rect bg_destination_over_;
SDL_Texture* bg_game_o_texture_; //  SDL_Texture variable


void Init_End()
{
	g_flag_running = true;
	
	SDL_Surface* bg_game_o_surface = IMG_Load("../Resources/over1.jpg");
	SDL_SetColorKey(bg_game_o_surface, 1, SDL_MapRGB(bg_game_o_surface->format, 255, 255, 255));
	bg_game_o_texture_ = SDL_CreateTextureFromSurface(g_renderer, bg_game_o_surface);
	SDL_FreeSurface(bg_game_o_surface);

	bg_source_over_.x = 0;
	bg_source_over_.y = 0;
	bg_source_over_.w = 650;
	bg_source_over_.h = 500;

	bg_destination_over_.x = 0;
	bg_destination_over_.y = 0;// +g_source_rect.h * 2 + 90;
	bg_destination_over_.w = 1280;//bg_source_over_.w = bg_game_o_surface->w;
	bg_destination_over_.h = 720;//bg_source_over_.h = bg_game_o_surface->h;

}

void Update_End()
{

}

void Render_End()
{
	SDL_RenderClear(g_renderer);

	SDL_RenderCopy(g_renderer, bg_game_o_texture_, &bg_source_over_, &bg_destination_over_);

	SDL_SetRenderDrawColor(g_renderer, 255, 255, 0, 0);

	//SDL_RenderCopy(g_renderer, text_re_, 0, &text_re_rect_);



	SDL_RenderPresent(g_renderer);

}

void HandleEvents_End()
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			g_flag_running = false;
			break;

		case SDL_MOUSEBUTTONDOWN:

			// If the mouse left button is pressed.  
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				g_current_game_phase = PHASE_INTRO;
			}
			break;

		default:
			break;
		}
	}
}

void ClearGame_End()
{
	SDL_DestroyTexture(bg_game_o_texture_);
}