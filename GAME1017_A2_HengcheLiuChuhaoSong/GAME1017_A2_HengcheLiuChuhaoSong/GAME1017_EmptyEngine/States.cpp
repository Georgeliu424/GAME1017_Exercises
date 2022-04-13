#include "States.h"
#include "StateManager.h"
#include "TextureManager.h"
#include "Engine.h"
#include "EventManager.h"
#include "CollisionManager.h"
#include "SoundManager.h"
#include "Primitives.h"
#include "Button3.h"
#include"PlatformPlayer.h"
#include"FontManager.h"
#include"TiledLevel.h"
#include <iostream>
#include<ctime>
using namespace std;

void State::Render()
{
	
	SDL_RenderPresent(Engine::Instance().GetRenderer());
}

void State::Resume(){}

GameObject* State::GetGo(const std::string& s)
{ // Using 'std' just to show origin.
	auto it = std::find_if(m_objects.begin(), m_objects.end(), 
		// Lambda expression/function. An in-function function.
		[&](const std::pair<std::string, GameObject*>& element)
		{
			return element.first == s;
		} 
	); // End of find_if.
	if (it != m_objects.end())
		return it->second;
	else return nullptr;
}

auto State::GetIt(const std::string& s)
{ 
	auto it = std::find_if(m_objects.begin(), m_objects.end(),
		[&](const std::pair<std::string, GameObject*>& element)
		{
			return element.first == s;
		});
	return it;
}

// Begin TitleState
TitleState::TitleState(){}

void TitleState::Enter()
{
	TEMA::Load("Img/button.png", "play");
	TEMA::Load("Img/gametitle.png", "title");
	TEMA::Load("Img/background.png", "bg");
	m_objects.push_back(pair<string, GameObject*>("bg",
		new Image({ 0, 0, 1920, 1200 }, { 0, 0, 1024, 768 }, "bg")));
	m_objects.push_back(pair<string, GameObject*>("title",
		new Image({ 0, 0, 615, 219 }, { 300, 150, 400, 100 }, "title")));
	m_objects.push_back(pair<string, GameObject*>("play",
		new PlayButton({ 0, 0, 400, 100 }, { 412, 450, 200, 50 }, "play")));

}

void TitleState::Update()
{
	for (auto const& i : m_objects)
	{
		i.second->Update();
		if (STMA::StateChanging()) return;
	}
}

void TitleState::Render()
{
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0, 0, 0, 255);
	SDL_RenderClear(Engine::Instance().GetRenderer());
	for (auto const& i : m_objects)
		i.second->Render();
	State::Render();
}

void TitleState::Exit()
{
	TEMA::Unload("play");
	TEMA::Unload("title");
	TEMA::Unload("bg");
	for (auto& i : m_objects)
	{
		delete i.second;
		i.second = nullptr;
	}
	m_objects.clear();
	m_objects.shrink_to_fit();
}
// End TitleState

PauseState::PauseState() {}

void PauseState::Enter()
{
	TEMA::Load("Img/continue.png", "continue");
	TEMA::Load("Img/gamepause.png", "title");
	TEMA::Load("Img/background.png", "bg1");
	m_objects.push_back(pair<string, GameObject*>("bg1",
		new Image({ 0, 0, 1920, 1200 }, { 0, 0, 1024, 768 }, "bg1")));
	m_objects.push_back(pair<string, GameObject*>("title",
		new Image({ 0, 0, 615, 316 }, { 300, 150, 400, 100 }, "title")));
	m_objects.push_back(pair<string, GameObject*>("continue",
		new PlayButton({ 0, 0, 600, 164 }, { 412, 450, 200, 50 }, "continue")));
}

void PauseState::Update()
{
	for (auto const& i : m_objects)
	{
		i.second->Update();
		if (STMA::StateChanging()) return;
	}
}

void PauseState::Render()
{
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 64, 0, 16, 255);
	SDL_RenderClear(Engine::Instance().GetRenderer());
	for (auto const& i : m_objects)
		i.second->Render();
	State::Render();
}

void PauseState::Exit()
{
	TEMA::Unload("resume");
	TEMA::Unload("bg1");
	TEMA::Unload("title");
	for (auto& i : m_objects)
	{
		delete i.second;
		i.second = nullptr;
	}
	m_objects.clear();
	m_objects.shrink_to_fit();
}


// Begin GameState
GameState::GameState(){}

void GameState::Enter() // Used for initialization.
{
	FOMA::Load("Img/LTYPE.TTF", "Label", 24);
	TEMA::Load("Img/Tiles.png", "tiles");
	TEMA::Load("Img/Player.png", "player");
	TEMA::Load("Img/BG.png", "bg");
	SOMA::Load("Aud/Music.mp3", "music", SOUND_MUSIC);
	TEMA::Load("Img/Obstacles.png", "obs");

	// Load player image and give it a string key of "player".
	
	

	//srand((unsigned)time(NULL));
	m_label = new Label("Label", 50, 50, "Time: 0 ");
	m_timer.Start();

	m_healthBar = new HealthBar(100);

	// For obstacle


	m_vec.reserve(9);
	for (int i = 0; i < 9; i++)
	
		m_box.push_back(new Box({ 128 * i,384 }));
	

	// Create the map of Boxed with sprites.
	/*m_protos.emplace("Spikes", new Box({ 1024,384 }, true, { 1024, 384, 128, 128 }, { 128, 64, 128, 64 }));*/
	m_protos.emplace("spike_wall", new Box({ 1024,384 }, true, { 1024,0,128,448 }, { 0,0,128,448 }));
	/*m_protos.emplace("Circular", new Box({ 1024,384 }, true, { 1024, 448, 128,128 }, { 128,128,128,128 }));*/

	// Set the gap properties
	m_gapCtr = 0;
	m_gapMax = 3;


	// Backgrounds.
	m_vec.reserve(10);  // To prevent growth of 1.5x in push_back

	m_vec.push_back(new Background({ 0,0,1024,768 }, { 0,0,1024,768 }, 1));
	m_vec.push_back(new Background({ 0,0,1024,768 }, { 1024,0,1024,768 }, 1));
	// Midgrounds.
	m_vec.push_back(new Background({ 1024,0,256,512 }, { 0,0,256,512 }, 3));
	m_vec.push_back(new Background({ 1024,0,256,512 }, { 256,0,256,512 }, 3));
	m_vec.push_back(new Background({ 1024,0,256,512 }, { 512,0,256,512 }, 3));
	m_vec.push_back(new Background({ 1024,0,256,512 }, { 768,0,256,512 }, 3));
	m_vec.push_back(new Background({ 1024,0,256,512 }, { 1024,0,256,512 }, 3));
	// Foregrounds.
	m_vec.push_back(new Background({ 1024,512,512,256 }, { 0,512,512,256 }, 4));
	m_vec.push_back(new Background({ 1024,512,512,256 }, { 512,512,512,256 }, 4));
	m_vec.push_back(new Background({ 1024,512,512,256 }, { 1024,512,512,256 }, 4));

	m_objects.push_back(pair<string, GameObject*>("player", new PlatformPlayer(
		{ 0,0,128,128 }, { 288,480,100,64 })));


	SOMA::AllocateChannels(16);
	SOMA::SetMusicVolume(30);
	SOMA::PlayMusic("music", -1, 2000);

}

void GameState::Update()
{
	m_timer.Update();

	// Update for obstacle
	if (m_box[1]->GetPos().x <= -128)
	{
		// Pop the first element off.
		delete m_box[0]; // Deallocates Box.
		m_box.erase(m_box.begin());  // "pop_front"
		//Add a new Box to the end.
		if (m_gapCtr++ % m_gapMax == 0)  // Create Box with Sprite.
		{
			m_box.push_back(m_protos[m_keys[1]]->Clone());  // Instead of this ,pick a random clone from map of Box*
		}
		else
		{
			m_box.push_back(new Box({ 1024,384 }));
		}
	}
	// Update the boxes. which scroll themselves.
	for (unsigned int i = 0; i < m_box.size(); i++)
	
		m_box[i]->Update();
	



	// Update the background
	for (auto bg : m_vec)
	{
		bg->Update();
	}

	if (EVMA::KeyPressed(SDL_SCANCODE_X))
	{
		STMA::ChangeState(new TitleState());
		return;
	}

	if (EVMA::KeyPressed(SDL_SCANCODE_P))
	{
		STMA::ChangeState(new PauseState());
		return;
	}

	if (EVMA::KeyPressed(SDL_SCANCODE_E))
	{
		STMA::ChangeState(new EndState());
		return;
	}

	for (auto const& i : m_objects)
	{
		i.second->Update();
		if (STMA::StateChanging()) return;
	}

	// Check Collision
	
}



void GameState::Render()
{
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0, 0, 0, 255);

	
	if ( dynamic_cast<GameState*>(STMA::GetStates().back()) ) 
		State::Render();

	if (m_timer.HasChanged())
	{
		string temp = "Time: " + m_timer.GetTime();
		m_label->SetText(temp.c_str());
	}

	// Render the backgrounds.
	/*for (auto bg : m_vec)
	{
		bg->Render();
	}*/

	// Render the obstacle
	for (unsigned int i = 0; i < m_box.size(); i++)
	{
		m_box[1]->Render();
	}

	m_label->Render();
	m_healthBar->Render();

	for (auto const& i : m_objects)
		i.second->Render();

	SDL_RenderPresent(Engine::Instance().GetRenderer());


}

void GameState::Exit()
{
	for (auto& i : m_objects)
	{
		delete i.second; 
		i.second = nullptr;
	}
	m_objects.clear();
	m_objects.shrink_to_fit();
	delete m_healthBar;

	// Clean the backgrounds.
	for (auto bg : m_vec)
	{
		delete bg;
	}
	m_vec.clear();
	m_vec.shrink_to_fit();
	
	// Clean the obstacle
	for (unsigned int i = 0; i < m_box.size(); i++)
	{
		delete m_box[i];
		m_box[i] = nullptr;
	}
	m_box.clear(); //Clear out vector
	m_box.shrink_to_fit(); // Optional
	

}

void GameState::Resume(){}

// End GameState

EndState::EndState(){}

void EndState::Enter()
{
	TEMA::Load("Img/replay.png", "replay");
	TEMA::Load("Img/gameover.png", "title");
	TEMA::Load("Img/background.png", "bg2");
	m_objects.push_back(pair<string, GameObject*>("bg2",
		new Image({ 0, 0, 1920, 1200 }, { 0, 0, 1024, 768 }, "bg2")));
	m_objects.push_back(pair<string, GameObject*>("title",
		new Image({ 0, 0, 615, 219 }, { 300, 150, 400, 100 }, "title")));
	m_objects.push_back(pair<string, GameObject*>("replay",
		new PlayButton({ 0, 0, 670, 310 }, { 365, 450, 300, 100 }, "replay")));
}

void EndState::Update()
{
	for (auto const& i : m_objects)
	{
		i.second->Update();
		if (STMA::StateChanging()) return;
	}
}

void EndState::Render()
{
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 64, 0, 16, 255);
	SDL_RenderClear(Engine::Instance().GetRenderer());
	for (auto const& i : m_objects)
		i.second->Render();
	State::Render();
}

void EndState::Exit()
{
	TEMA::Unload("play");
	TEMA::Unload("bg2");
	TEMA::Unload("replay");
	for (auto& i : m_objects)
	{
		delete i.second;
		i.second = nullptr;
	}
	m_objects.clear();
	m_objects.shrink_to_fit();
}
