#pragma once
#ifndef _STATES_H_
#define _STATES_H_

#include "GameObject.h"
#include"Timer.h"
#include"Primitives.h"
#include"HealthBar.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <vector>
#include "Background.h"
#include"Box.h"


class State // This is the abstract base class for all states
{
public:
	virtual void Enter() = 0; // = 0 means pure virtual - must be defined in subclass
	virtual void Update() = 0;
	virtual void Render() ;
	virtual void Exit() = 0;
	virtual void Resume();
	virtual ~State() {} // or = default;
	GameObject* GetGo(const std::string& s);
	auto GetIt(const std::string& s);
protected: // Private but inherited
	State() {} // What does this prevent?
	vector<std::pair<std::string, GameObject*>> m_objects;
};

class TitleState : public State
{
public:
	TitleState();
	virtual void Enter();
	virtual void Update();
	virtual void Render();
	virtual void Exit();
};

class GameState : public State
{
private:
	Label* m_label;
	Timer m_timer;
	HealthBar* m_healthBar;
	vector<Background*> m_vec;
	vector<Box*> m_box;
	map<string, Box*> m_protos;
	string m_keys[3] = { "Spikes","spike_wall","Circular" };
	int m_gapCtr, m_gapMax;
	SDL_Texture* m_pObsText;

public:
	GameState();
	virtual void Enter();
	virtual void Update();
	virtual void Render();
	virtual void Exit();
	virtual void Resume();

};

class PauseState : public State
{
public:
	PauseState();
	virtual void Enter();
	virtual void Update();
	virtual void Render();
	virtual void Exit();
};

class EndState : public State
{
public:
	EndState();
	virtual void Enter();
	virtual void Update();
	virtual void Render();
	virtual void Exit();
};

#endif