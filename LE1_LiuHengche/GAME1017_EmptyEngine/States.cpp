#include "States.h"
#include "StateManager.h"
#include "Engine.h"
#include <iostream>
using namespace std;

void State::Render()
{
	SDL_RenderPresent(Engine::Instance().GetRenderer());
}

TitleState::TitleState(){}

void TitleState::Enter()
{
	cout << "Entering TitleState..." << endl;
	m_pMusic = Mix_LoadMUS("Aud/Superboy.mp3");
	Mix_PlayMusic(m_pMusic, -1);
}

void TitleState::Update()
{
	if (Engine::Instance().KeyDown(SDL_SCANCODE_N))
	{
		cout << "Changing to GameState" << endl;
		STMA::ChangeState(new GameState() );
	} 
}

void TitleState::Render()
{
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(),0,0,255,255);
	SDL_RenderClear(Engine::Instance().GetRenderer());
	State::Render();
}

void TitleState::Exit()
{
	cout << "Exiting TitleState..." << endl;
	
}

PauseState::PauseState(){ }

void PauseState::Enter()
{
	cout << "Entering PauseState..." << endl;
}

void PauseState::Update()
{ 
	if (Engine::Instance().KeyDown(SDL_SCANCODE_R))
		STMA::PopState();
}

void PauseState::Render()
{
	//first render the gamestate.
	STMA::GetState().front()->Render();
	// Now render the rest of PauseState.
	SDL_SetRenderDrawBlendMode(Engine::Instance().GetRenderer(),SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 255, 0, 0, 128);
	SDL_Rect rect = { 255,128,512,512 };
	SDL_RenderFillRect(Engine::Instance().GetRenderer(),&rect);
	State::Render();
}

void PauseState::Exit()
{
	cout << "Exiting GameState..." << endl;
}

GameState::GameState(){}

void GameState::Enter()
{
	cout << "Entering GameState..." << endl;
	m_Superboy = Mix_LoadMUS("Aud/Superboy.mp3");
	m_coin = Mix_LoadWAV("Aud/coin.wav");
	m_unlock = Mix_LoadWAV("Aud/unlock.wav");
	Mix_PlayMusic(m_Superboy, -1);
}

void GameState::Update()
{
	if (Engine::Instance().KeyDown(SDL_SCANCODE_P))
	{
		cout << "Changing to PauseState..." << endl;
		Mix_PauseMusic();
		STMA::PushState(new PauseState());
	}
	
	if (Engine::Instance().KeyDown(SDL_SCANCODE_1))
	{
		cout << "playing sound 1" << endl;
		Mix_PlayChannel(-1, m_coin, 0);
	}
	if (Engine::Instance().KeyDown(SDL_SCANCODE_2))
	{
		cout << "playing sound 2" << endl;
		Mix_PlayChannel(-1, m_unlock, 0);
	}

	if (Engine::Instance().KeyDown(SDL_SCANCODE_X))
	{
		cout << "changing to game state" << endl;
		STMA::ChangeState(new EndState);
	}
}

void GameState::Render()
{
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(),0,255,0,255);
	SDL_RenderClear(Engine::Instance().GetRenderer());
	// This Code below prevents SDL_RenderPresent from running twice in one frame.
	if (dynamic_cast<GameState*>(STMA::GetState().back())) //if Current State is GameState.
		State::Render();

}

void GameState::Exit()
{
	cout << "Exiting GameState..." << endl;
}

void GameState::Resume()
{
	cout << "Resuming GameState..." << endl;
	Mix_ResumeMusic();
	
}

EndState::EndState(){}

void EndState::Enter()
{
	cout << "Entering EndState..." << endl;
}

void EndState::Update()
{
	if (Engine::Instance().KeyDown(SDL_SCANCODE_R))
	{
		cout << "changing to Tilestate" << endl;
		STMA::ChangeState(new TitleState);
	}
}

void EndState::Render()
{
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 255, 0, 255, 255);
	SDL_RenderClear(Engine::Instance().GetRenderer());
	State::Render();
}

void EndState::Exit()
{
	cout << "Exiting EndState..." << endl;
}
