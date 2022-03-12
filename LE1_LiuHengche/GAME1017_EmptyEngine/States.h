#pragma once
#ifndef _STATES_H_
#define _STATES_H_
#include<SDL_mixer.h>

class State //this is an abstract base class for all states(interface)
{
protected://private but inherited.
	State() = default;
public://Public method.
	virtual void Enter() = 0;//=0 means pure virtual - must be define in subclass.
	virtual void Update() = 0;
	virtual void Render();
	virtual void Exit() = 0;
	virtual void Resume(){};
};

class TitleState : public State
{
private:// private properties
	Mix_Music* m_pMusic;
public://public methods.
	TitleState();
	virtual void Enter();
	virtual void Update();
	virtual void Render(); 
	virtual void Exit() ;
};
class PauseState : public State
{
public://public methods.
	PauseState();
	virtual void Enter();
	virtual void Update();
	virtual void Render();
	virtual void Exit();
};
class GameState : public State
{
private:// private properties
	Mix_Chunk* m_coin;
	Mix_Chunk* m_unlock;

	Mix_Music* m_Superboy;

public://public methods.
	GameState();
	virtual void Enter();
	virtual void Update();
	virtual void Render();
	virtual void Exit();
	virtual void Resume();
};
class EndState :public State
{
private:
public:
	EndState();
	virtual void Enter();
	virtual void Update();
	virtual void Render();
	virtual void Exit();
};


#endif