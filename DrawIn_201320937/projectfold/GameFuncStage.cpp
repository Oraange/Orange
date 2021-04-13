#include "GameFuncStage.h"
#include "GameFuncPhase.h"
#include "SDL_image.h"
#include <iostream>
#include <windows.h>
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include <atlstr.h>
#include <string>

Mix_Chunk *wave1_;
Mix_Chunk *wave2_;
Mix_Music *music1_;

TTF_Font *game_font_;
TTF_Font *reload_font_;

SDL_Texture *play;
SDL_Texture *pause;
SDL_Texture *text_reloaded_;
SDL_Texture *text_number_;
SDL_Texture *text_re_;
SDL_Texture *score;//
SDL_Texture *m_score_;
SDL_Rect play_rect;
SDL_Rect pause_rect;
SDL_Rect text_reloaded_rect_;
SDL_Rect text_number_rect_;
SDL_Rect text_re_rect_;
SDL_Rect score_rect;
SDL_Rect m_score_rect_;

SDL_Rect mush_rect;
SDL_Rect mush_destination_rect;


extern SDL_Window* g_window;
extern SDL_Renderer* g_renderer;
extern bool g_flag_running;
extern int g_current_game_phase;

SDL_Rect bg_source_rectangle_;
SDL_Rect bg_destination_rectangle_;
SDL_Texture* bg_texture_; //  SDL_Texture variable

SDL_Texture* g_ryu_sheet_texture;
SDL_Texture* g_missile_texture;
SDL_Texture* g_missile1_texture;
SDL_Texture* g_missile2_texture;

SDL_Texture* mush_texture;

SDL_Rect g_source_rect;
SDL_Rect g_destination_rect;
SDL_Rect g_m_source_rect;
SDL_Rect g_m_destination_rect;
SDL_Rect g_m1_source_rect;
SDL_Rect g_m1_destination_rect;
SDL_Rect g_m2_source_rect;
SDL_Rect g_m2_destination_rect;

SDL_Texture* bust_texture;
SDL_Rect bust_source_rect;
SDL_Rect bust_destination_rect;

//미사일의 상태

int m1_state;
int m2_state;
int m3_state;

//비행기의 상태

int f_state;


//미사일 개수

int m_number;

//미사일 발사 수

int count_m;

//Score

int m_score = 0;

//적 이동기

int mushroom = 35;

//
class flight
{
public:
	SDL_Rect g_destination_rect;
};
class bg
{
public:
	SDL_Rect bg_destination_rectangle_;
};


void InitGame_Stage()
{
	g_flag_running = true;
	m1_state = 0;
	m2_state = 0;
	m3_state = 0;
	f_state = 0;
	m_number = 3;
	///////////////////////////////////////////배경 로드
	{
		SDL_Surface* bg_surface = IMG_Load("../Resources/bgimage2.jpg");
		bg_destination_rectangle_.x = bg_source_rectangle_.x = 0;
		bg_destination_rectangle_.y = bg_source_rectangle_.y = 0;
		bg_destination_rectangle_.w = bg_source_rectangle_.w = bg_surface->w;
		bg_destination_rectangle_.h = bg_source_rectangle_.h = bg_surface->h;

		bg_texture_ = SDL_CreateTextureFromSurface(g_renderer, bg_surface);
		SDL_FreeSurface(bg_surface);

	}
	///////////////////////////////////////////비행기 로드
	{
		SDL_Surface* ryu_sheet_surface = IMG_Load("../Resources/flight1.png");
		SDL_SetColorKey(ryu_sheet_surface, 1, SDL_MapRGB(ryu_sheet_surface->format, 255, 255, 255)); // Remove Background Color

		g_ryu_sheet_texture = SDL_CreateTextureFromSurface(g_renderer, ryu_sheet_surface);
		SDL_FreeSurface(ryu_sheet_surface);

		g_source_rect.x = 270;
		g_source_rect.y = 290;
		g_source_rect.w = 60;
		g_source_rect.h = 40;
	
		g_destination_rect.x = (bg_destination_rectangle_.w / 2) - g_source_rect.w / 2;
		g_destination_rect.y = bg_destination_rectangle_.h - 50;// +g_source_rect.h * 2 + 90;
		g_destination_rect.w = g_source_rect.w;
		g_destination_rect.h = g_source_rect.h;
	}

	///////////////////////////////////////////적 로드
	{
		SDL_Surface* mush_surface = IMG_Load("../Resources/mush.jpg");
		SDL_SetColorKey(mush_surface, 1, SDL_MapRGB(mush_surface->format, 255, 255, 255)); // Remove Background Color

		mush_texture = SDL_CreateTextureFromSurface(g_renderer, mush_surface);
		SDL_FreeSurface(mush_surface);

		mush_rect.x = 0;
		mush_rect.y = 0;
		mush_rect.w = mush_surface->w;
		mush_rect.h = mush_surface->h;

		mush_destination_rect.x = 20;
		mush_destination_rect.y = 20;// +g_source_rect.h * 2 + 90;
		mush_destination_rect.w = mush_rect.w/8;
		mush_destination_rect.h = mush_rect.h/8;
	}
	//////////폭발
	{
		SDL_Surface* bust_surface = IMG_Load("../Resources/bust.jpg");
		SDL_SetColorKey(bust_surface, 1, SDL_MapRGB(bust_surface->format, 255, 255, 255)); // Remove Background Color

		bust_texture = SDL_CreateTextureFromSurface(g_renderer, bust_surface);
		SDL_FreeSurface(bust_surface);

		bust_source_rect.x = 0;
		bust_source_rect.y = 0;
		bust_source_rect.w = bust_surface->w;
		bust_source_rect.h = bust_surface->h;

		//bust_destination_rect.x = 20;
		//bust_destination_rect.y = 20;// +g_source_rect.h * 2 + 90;
		//bust_destination_rect.w = bust_source_rect.w / 8;
		//bust_destination_rect.h = bust_source_rect.h / 8;
	}
	///////////////////////////////////////////
	{
		SDL_Surface* missile_surface = IMG_Load("../Resources/missile.png");
		SDL_SetColorKey(missile_surface, 1, SDL_MapRGB(missile_surface->format, 255, 255, 255));

		g_missile_texture = SDL_CreateTextureFromSurface(g_renderer, missile_surface);
		SDL_FreeSurface(missile_surface);

		g_m_source_rect.x = 513;
		g_m_source_rect.y = 190;
		g_m_source_rect.w = 50;
		g_m_source_rect.h = 120;
	}

	{
		SDL_Surface* missile1_surface = IMG_Load("../Resources/missile.png");
		SDL_SetColorKey(missile1_surface, 1, SDL_MapRGB(missile1_surface->format, 255, 255, 255));

		g_missile1_texture = SDL_CreateTextureFromSurface(g_renderer, missile1_surface);
		SDL_FreeSurface(missile1_surface);

		g_m1_source_rect.x = 513;
		g_m1_source_rect.y = 190;
		g_m1_source_rect.w = 50;
		g_m1_source_rect.h = 120;
	}

	{
		SDL_Surface* missile2_surface = IMG_Load("../Resources/missile.png");
		SDL_SetColorKey(missile2_surface, 1, SDL_MapRGB(missile2_surface->format, 255, 255, 255));

		g_missile2_texture = SDL_CreateTextureFromSurface(g_renderer, missile2_surface);
		SDL_FreeSurface(missile2_surface);

		g_m2_source_rect.x = 513;
		g_m2_source_rect.y = 190;
		g_m2_source_rect.w = 50;
		g_m2_source_rect.h = 120;
	}
	
	{
		Mix_VolumeMusic(120);

		// Load the wave and mp3 files 
		
		wave1_ = Mix_LoadWAV("../Resources/clap.wav");
		if (wave1_ == NULL)
		{
			printf("Couldn't load the wav: %s\n", Mix_GetError());
		}

		wave2_ = Mix_LoadWAV("../Resources/pokerchipscut.wav");
		if (wave1_ == NULL)
		{
			printf("Couldn't load the wav: %s\n", Mix_GetError());
		}
		
		music1_ = Mix_LoadMUS("../Resources/handclap.mp3");
		if (!music1_)
		{
			printf(" %s\n", Mix_GetError());
			// this might be a critical error...
		}
		Mix_FadeInMusic(music1_, -1,10000);


	}
	
	game_font_ = TTF_OpenFont("../Resources/Chlorinp.ttf", 50);
	reload_font_ = TTF_OpenFont("../Resources/arose.ttf", 50);
	///////////////////////////////////////////'Reloaded'
	{

		SDL_Color green = { 0, 0, 0, 0 };
		SDL_Surface *tmp_surface = TTF_RenderText_Blended(game_font_, "Score : ", green);

		score_rect.x = bg_destination_rectangle_.w + 10;
		score_rect.y = 200;
		score_rect.w = tmp_surface->w;
		score_rect.h = tmp_surface->h;

		score = SDL_CreateTextureFromSurface(g_renderer, tmp_surface);

		SDL_FreeSurface(tmp_surface);
	}

	{

		SDL_Color green = { 0, 0, 0, 0 };
		SDL_Surface *tmp_surface = TTF_RenderText_Blended(game_font_, "Reloaded : ", green);

		text_reloaded_rect_.x = bg_destination_rectangle_.w+10;
		text_reloaded_rect_.y = 0;
		text_reloaded_rect_.w = tmp_surface->w;
		text_reloaded_rect_.h = tmp_surface->h;

		text_reloaded_ = SDL_CreateTextureFromSurface(g_renderer, tmp_surface);

		SDL_FreeSurface(tmp_surface);
	}
	///////////////////////////////////////////'Play'
	{

		SDL_Color black = { 0, 0, 0, 0 };
		SDL_Surface *tmp_surface = TTF_RenderText_Blended(game_font_, "Play-Mouse_Right", black);

		play_rect.x = bg_destination_rectangle_.w + 10;
		play_rect.y = 150;
		play_rect.w = tmp_surface->w;
		play_rect.h = tmp_surface->h;

		play = SDL_CreateTextureFromSurface(g_renderer, tmp_surface);

		SDL_FreeSurface(tmp_surface);
	}
	///////////////////////////////////////////'Pause'
	{

		SDL_Color black = { 0, 0, 0, 0 };
		SDL_Surface *tmp_surface = TTF_RenderText_Blended(game_font_, "Pause-Mouse_Left", black);

		pause_rect.x = bg_destination_rectangle_.w + 10;
		pause_rect.y = 100;
		pause_rect.w = tmp_surface->w;
		pause_rect.h = tmp_surface->h;

		pause = SDL_CreateTextureFromSurface(g_renderer, tmp_surface);

		SDL_FreeSurface(tmp_surface);
	}
	
}


void Update_Stage()
{
	/*
	if (Mix_ResumeMusic)
	{
		SDL_Color red = { 255, 0, 0, 0 }, bgcolor = { 0xff,0xff,0xff };
		SDL_Surface *tmp_surface = TTF_RenderText_Shaded(game_font_, "Play", red, bgcolor);

		play_rect.x = bg_destination_rectangle_.w + 10;
		play_rect.y = 100;
		play_rect.w = tmp_surface->w;
		play_rect.h = tmp_surface->h;

		play = SDL_CreateTextureFromSurface(g_renderer, tmp_surface);

		SDL_FreeSurface(tmp_surface);
	}
	else if(Mix_PauseMusic)
	{
		SDL_Color red = { 255, 0, 0, 0 }, bgcolor = { 0xff,0xff,0xff };
		SDL_Surface *tmp_surface = TTF_RenderText_Shaded(game_font_, "Pause", red, bgcolor);

		play_rect.x = bg_destination_rectangle_.w + 10;
		play_rect.y = 100;
		play_rect.w = tmp_surface->w;
		play_rect.h = tmp_surface->h;

		play = SDL_CreateTextureFromSurface(g_renderer, tmp_surface);

		SDL_FreeSurface(tmp_surface);
	}
	*/
	///////////////////도전해보다가 실패..
	{
		
		if (text_number_ != 0)
		{
			SDL_DestroyTexture(text_number_);		// !!!중요!!!  이미 생성되어있는 texture 가 있으면 반드시 메모리에서 지워야한다. !!!
			text_number_ = 0;					//////시간에만 해당하는 것인지? 아니면 변수를 받아서 업데이트하는 texture에 모두 해당하는 것인지?
		}
		
		SDL_Color green = { 0, 0, 0, 0 };
		SDL_Surface *tmp_surface = TTF_RenderText_Blended(game_font_, std::to_string(m_number).c_str(), green);

		text_number_rect_.x = text_reloaded_rect_.x + text_reloaded_rect_.w;
		text_number_rect_.y = 0;
		text_number_rect_.w = tmp_surface->w;
		text_number_rect_.h = tmp_surface->h;

		text_number_ = SDL_CreateTextureFromSurface(g_renderer, tmp_surface);

		SDL_FreeSurface(tmp_surface);
	}

	SDL_Color green = { 0, 0, 0, 0 };
	SDL_Surface *tmp_surface = TTF_RenderText_Blended(game_font_, std::to_string(m_score).c_str(), green);

	m_score_rect_.x = score_rect.x + score_rect.w;
	m_score_rect_.y = 200;
	m_score_rect_.w = tmp_surface->w;
	m_score_rect_.h = tmp_surface->h;

	m_score_ = SDL_CreateTextureFromSurface(g_renderer, tmp_surface);

	SDL_FreeSurface(tmp_surface);

	/////////////////////////////////////////// 비행기와 미사일의 상태 업데이트
	{
		if (f_state == 1)
		{
			g_destination_rect.x -= 10;
		}

		else if (f_state == 2)
		{
			g_destination_rect.x += 10;
		}

		else if (f_state == 3)
		{
			g_destination_rect.y -= 10;
		}
		else if (f_state == 4)
		{
			g_destination_rect.y += 10;
		}
	}

	if (m1_state == 0)
	{
		g_m_destination_rect.x = g_destination_rect.x + 25;
		g_m_destination_rect.y = g_destination_rect.y;
		g_m_destination_rect.w = 0;
		g_m_destination_rect.h = 0;
	}
	else if (m1_state == 1)
	{
		g_m_destination_rect.y -= 10;
		if (g_m_destination_rect.y == 10)
		{
			m1_state = 0;
			m_number += 1;
		}
	}

	if (m2_state == 0)
	{
		g_m1_destination_rect.x = g_destination_rect.x + 25;
		g_m1_destination_rect.y = g_destination_rect.y;
		g_m1_destination_rect.w = 0;
		g_m1_destination_rect.h = 0;
	}
	else if (m2_state == 1)
	{
		g_m1_destination_rect.y -= 10;
		if (g_m1_destination_rect.y == 10)
		{
			m2_state = 0;
			m_number += 1;
		}
	}

	if (m3_state == 0)
	{
		g_m2_destination_rect.x = g_destination_rect.x + 25;
		g_m2_destination_rect.y = g_destination_rect.y;
		g_m2_destination_rect.w = 0;
		g_m2_destination_rect.h = 0;
	}
	else if (m3_state == 1)
	{
		g_m2_destination_rect.y -= 10;
		if (g_m2_destination_rect.y == 10)
		{
			m3_state = 0;
			m_number += 1;
		}
	}

	if (m_number == -1||m_number==0)
	{
		{

			SDL_Color green = { 0, 0, 0, 0 };
			SDL_Surface *tmp_surface = TTF_RenderText_Blended(reload_font_, "You need reload", green);

			text_re_rect_.x = text_reloaded_rect_.x;
			text_re_rect_.y = 60;
			text_re_rect_.w = tmp_surface->w;
			text_re_rect_.h = tmp_surface->h;
			 

			text_re_ = SDL_CreateTextureFromSurface(g_renderer, tmp_surface);

			SDL_FreeSurface(tmp_surface);
		}
		if (m_number == -1)
		{
			m_number += 1;
		}
	}
	else
	{
		text_re_rect_.w = 0;
		text_re_rect_.h = 0;
	}

	// 캐릭터의 위치가 경계에 닿으면 벽에 부딪힌다.  
	if (g_destination_rect.x >= bg_destination_rectangle_.w-50) g_destination_rect.x -= 10;
	else if (g_destination_rect.x < -10) g_destination_rect.x += 10;
	else if (g_destination_rect.y >= bg_destination_rectangle_.h - 40) g_destination_rect.y -= 10;
	else if (g_destination_rect.y < -10) g_destination_rect.y += 10;

	//count missile

	if (m_score == 10)
	{
		g_current_game_phase = PHASE_ENDING;
		m_score = 0;
	}

	// 적 이동

	if (mush_destination_rect.x < bg_destination_rectangle_.w-10)
	{
		mush_destination_rect.x += 10;
		if (mush_destination_rect.x == bg_destination_rectangle_.w - 20)
		{
			mush_destination_rect.x=20;
		}
	}

	//적 처치

	if (abs(mush_destination_rect.x - g_m_destination_rect.x) <= 15 && g_m_destination_rect.y - mush_destination_rect.y <= 15)
	{
		m_score += 2;
		m1_state = 0;
		{
			bust_destination_rect.x = mush_destination_rect.x;
			bust_destination_rect.y = mush_destination_rect.y;
			bust_destination_rect.w = mush_destination_rect.w * 3;
			bust_destination_rect.h = mush_destination_rect.h * 3;
		}
		
	}
	else if (abs(mush_destination_rect.x - g_m1_destination_rect.x) <= 15 && g_m1_destination_rect.y - mush_destination_rect.y <= 15)
	{
		m_score += 2;
		m2_state = 0;
		{
			bust_destination_rect.x = mush_destination_rect.x;
			bust_destination_rect.y = mush_destination_rect.y;
			bust_destination_rect.w = mush_destination_rect.w*3;
			bust_destination_rect.h = mush_destination_rect.h*3;
		}
		
	}
	else if (abs(mush_destination_rect.x - g_m2_destination_rect.x) <= 15 && g_m2_destination_rect.y - mush_destination_rect.y <= 15)
	{
		m_score += 2;
		m3_state = 0;
		{
			bust_destination_rect.x = mush_destination_rect.x;
			bust_destination_rect.y = mush_destination_rect.y;
			bust_destination_rect.w = mush_destination_rect.w * 3;
			bust_destination_rect.h = mush_destination_rect.h * 3;
		}
		
	}
	if (abs(bust_destination_rect.x - mush_destination_rect.x) > 10)
	{
		bust_destination_rect.x = mush_destination_rect.x;
		bust_destination_rect.y = mush_destination_rect.y;
		bust_destination_rect.w = 0;// mush_destination_rect.w;
		bust_destination_rect.h = 0;//mush_destination_rect.h;
	}
}


void Render_Stage()
///////////////////////////////////////////모든 이미지 파일과 텍스트를 렌더링
{
	SDL_RenderClear(g_renderer); // clear the renderer to the draw color

	SDL_RenderCopy(g_renderer, bg_texture_, &bg_source_rectangle_, &bg_destination_rectangle_);

	SDL_SetRenderDrawColor(g_renderer, 255,255,0,0);
	//SDL_RenderClear(g_renderer); // clear the frame buffer
	SDL_RenderCopy(g_renderer, g_ryu_sheet_texture, &g_source_rect, &g_destination_rect);

	SDL_RenderCopy(g_renderer, g_missile_texture, &g_m_source_rect, &g_m_destination_rect);

	SDL_RenderCopy(g_renderer, g_missile1_texture, &g_m1_source_rect, &g_m1_destination_rect);

	SDL_RenderCopy(g_renderer, g_missile2_texture, &g_m2_source_rect, &g_m2_destination_rect);

	SDL_RenderCopy(g_renderer, text_reloaded_, 0, &text_reloaded_rect_);

	SDL_RenderCopy(g_renderer, text_number_, 0, &text_number_rect_);

	SDL_RenderCopy(g_renderer, text_re_, 0, &text_re_rect_);

	SDL_RenderCopy(g_renderer, play, 0, &play_rect);

	SDL_RenderCopy(g_renderer, pause, 0, &pause_rect);

	SDL_RenderCopy(g_renderer, score, 0, &score_rect);

	SDL_RenderCopy(g_renderer, m_score_, 0, &m_score_rect_);

	SDL_RenderCopy(g_renderer, mush_texture, &mush_rect, &mush_destination_rect);

	SDL_RenderCopy(g_renderer, bust_texture, &bust_source_rect, &bust_destination_rect);



	SDL_RenderPresent(g_renderer);

}



void HandleEvents_Stage()
{
	SDL_Event event;
	const Uint8 *keystate;
	if(SDL_PollEvent(&event))
	{
		/*
		keystate = SDL_GetKeyboardState(NULL);

		if (keystate[SDL_SCANCODE_LEFT])
		{
			g_destination_rect.x -= 5;//f_state = 1;
		}
		if (keystate[SDL_SCANCODE_RIGHT])
		{
			g_destination_rect.x += 5;//f_state = 2;
		}
		if (keystate[SDL_SCANCODE_UP])
		{
			g_destination_rect.y -= 5;//f_state = 3;
		}
		if (keystate[SDL_SCANCODE_DOWN])
		{
			g_destination_rect.y += 5;//f_state = 4;
		}
		*/
		//SDL_Delay(40);
		
		switch (event.type)
		{
		case SDL_QUIT:
			g_flag_running = false;
			break;

		case SDL_KEYDOWN:
			
			if ( event.key.keysym.sym == SDLK_LEFT )
			{
				f_state = 1;

			}
			if ( event.key.keysym.sym == SDLK_RIGHT )
			{
				f_state = 2;
			}
			
			if (event.key.keysym.sym == SDLK_UP)
			{
				f_state = 3;
			}
			if (event.key.keysym.sym == SDLK_DOWN)
			{
				f_state = 4;
			}
			if (event.key.keysym.sym == SDLK_LEFT && event.key.keysym.sym == SDLK_UP)
			{
				//f_state = 1;
				//f_state = 3;
			}
			
			else if (event.key.keysym.sym == SDLK_SPACE)
			{
				if (10<g_m_destination_rect.y && g_m_destination_rect.y < g_destination_rect.y && 
					10 < g_m1_destination_rect.y && g_m1_destination_rect.y < g_destination_rect.y &&
					10 < g_m2_destination_rect.y && g_m2_destination_rect.y < g_destination_rect.y)
				{
					Mix_PlayChannel(-1, wave2_, 0);
					
				}
				else
				{
					Mix_PlayChannel(-1, wave1_, 0);
					//m_score += 1;
				}
			
				if (g_m_destination_rect.y >= g_m1_destination_rect.y)
				{
					m1_state = 1;
					g_m_destination_rect.w = g_m_source_rect.w / 4;
					g_m_destination_rect.h = g_m_source_rect.h / 4;
					m_number -= 1;
					//m_score += 1;
				}
				else if (g_m1_destination_rect.y >= g_m2_destination_rect.y)
				{
					m2_state = 1;
					m_number -= 1;
					g_m1_destination_rect.w = g_m1_source_rect.w / 4;
					g_m1_destination_rect.h = g_m1_source_rect.h / 4;
					//m_score += 1;
				}
				else if (g_m2_destination_rect.y > g_m_destination_rect.y)
				{
					m3_state = 1;
					m_number -= 1;
					g_m2_destination_rect.w = g_m2_source_rect.w / 4;
					g_m2_destination_rect.h = g_m2_source_rect.h / 4;
					//m_score += 1;
				}

			}
			break;

		case SDL_KEYUP:
			if ( event.key.keysym.sym == SDLK_LEFT 
				|| event.key.keysym.sym == SDLK_RIGHT
				||event.key.keysym.sym==SDLK_UP
				||event.key.keysym.sym==SDLK_DOWN)
			{
				f_state = 0;
			}
			break;

		case SDL_MOUSEBUTTONDOWN:
		
			// If the mouse left button is pressed. 
			if ( event.button.button == SDL_BUTTON_LEFT )
			{
				Mix_PauseMusic();

			}
			else if (event.button.button == SDL_BUTTON_RIGHT)
			{
				Mix_ResumeMusic();
			}
			break;


		default:
			break;
		}
	}
}



void ClearGame_Stage()
{
	SDL_DestroyTexture(g_ryu_sheet_texture);
	SDL_DestroyTexture(g_missile_texture);
	SDL_DestroyTexture(bg_texture_);
	SDL_DestroyTexture(mush_texture);
	SDL_DestroyTexture(bust_texture);
	if (music1_) Mix_FreeMusic(music1_);
}








