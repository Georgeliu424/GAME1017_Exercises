#pragma once
#ifndef _STATEMANAGER_H_
#define _STATEMANAGER_H_

#include "States.h"
#include <vector>

// We're going to make StateManager a "static class".
class StateManager
{
private://private properties.
	static std::vector<State*>s_states; 
private://private methods.
	StateManager() {};//prevents instantiation. Don't need obeject for static class.

public://Public Method.
	static void Update();
	static void Render();
	static void PushState(State* pState);
	static void PopState();
	static void ChangeState(State* pState);
	static void Quit();
	static std::vector<State*>& GetState();
};

typedef StateManager STMA;

#endif

