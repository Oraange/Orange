#include "GameFuncIntro.h"
#include "GameFuncPhase.h"
#include "SDL_image.h"
#include <iostream>
#include <windows.h>
#include "SDL_mixer.h"
#include "SDL_ttf.h"
//#include <atlstr.h>
#include <string>

extern SDL_Window* g_window;
extern SDL_Renderer* g_renderer;
extern bool g_flag_running;
extern int g_current_game_phase;

TTF_Font *reload_font_intro;

SDL_Rect bg_source_game_;
SDL_Rect bg_destination_game_;
SDL_Texture* bg_game_s_texture_; //  SDL_Texture variable

SDL_Rect text_re_rect_intro;
SDL_Texture *text_re_intro;

void Init_Intro()
{
	g_flag_running = true;
	reload_font_intro = TTF_OpenFont("../Resources/arose.ttf", 50);
	{/////////¹è°æ
		
		SDL_Surface* bg_game_s_surface = IMG_Load("../Resources/start.jpg");
		SDL_SetColorKey(bg_game_s_surface, 1, SDL_MapRGB(bg_game_s_surface->format, 255, 255, 255));
		bg_game_s_texture_ = SDL_CreateTextureFromSurface(g_renderer, bg_game_s_surface);
		SDL_FreeSurface(bg_game_s_surface);

		bg_source_game_.x = 0;
		bg_source_game_.y = 0;
		bg_source_game_.w = 820;
		bg_source_game_.h = 335;

		bg_destination_game_.x = 0;
		bg_destination_game_.y = 0;// +g_source_rect.h * 2 + 90;
		bg_destination_game_.w = 1280;//bg_source_game_.w=bg_game_s_surface->w;
		bg_destination_game_.h = 720;//bg_source_game_.h=bg_game_s_surface->h;
		
	}

	{
		SDL_Color green = { 0, 0, 0, 0 };
		SDL_Surface *tmp_surface = TTF_RenderText_Blended(reload_font_intro, "You need reload", green);

		text_re_rect_intro.x = 60;
		text_re_rect_intro.y = 60;
		text_re_rect_intro.w = tmp_surface->w;
		text_re_rect_intro.h = tmp_surface->h;


		text_re_intro = SDL_CreateTextureFromSurface(g_renderer, tmp_surface);

		SDL_FreeSurface(tmp_surface);
	}
}

void Update_Intro()
{

}

void Render_Intro()
{
	SDL_RenderClear(g_renderer);

	SDL_RenderCopy(g_renderer, bg_game_s_texture_, &bg_source_game_, &bg_destination_game_);

	SDL_SetRenderDrawColor(g_renderer, 255, 255, 0, 0);

	//SDL_RenderCopy(g_renderer, text_re_intro, 0, &text_re_rect_intro);



	SDL_RenderPresent(g_renderer);
}

void HandleEvents_Intro()
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
		 				g_current_game_phase = PHASE_STAGE1;
		 			}
		 			break;

	 		default:
		 			break;
		 		}
	 	}
 }

void ClearGame_Intro()
{
	SDL_DestroyTexture(text_re_intro);
	//SDL_DestroyTexture(bg_game_s_texture_);
}
