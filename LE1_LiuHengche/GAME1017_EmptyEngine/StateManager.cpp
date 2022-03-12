#include "StateManager.h"

void StateManager::Update()
{
	if (!s_states.empty())
		s_states.back()->Update();
}

void StateManager::Render()
{
	if (!s_states.empty())
		s_states.back()->Render();
}

// Used when there are 2 state in vector, i.e. Game and Pause   

void StateManager::PushState(State* pState) // Going from Game to Pause.
{
	s_states.push_back(pState);
	s_states.back()->Enter();
}

void StateManager::PopState() //Going from PauseState to GameState.
{
	if (s_states.size() <= 1) return;
	if (!s_states.empty())//IF vector has states inside
	{
		s_states.back()->Exit();
		delete s_states.back();
		s_states.back() = nullptr; //Wrangle your dangle.
		s_states.pop_back();
	}
	s_states.back()->Resume();//Note, We're resuming not entering 
}

void StateManager::ChangeState(State* pState)
{
	if (!s_states.empty())//IF vector has states inside
	{
		s_states.back()->Exit();
		delete s_states.back();
		s_states.back() = nullptr; //Wrangle your dangle.
		s_states.pop_back();
	}
	s_states.push_back(pState);//Add pState to the vector.
	s_states.back()->Enter();
}

void StateManager::Quit()
{
	while (!s_states.empty())
	{
		s_states.back()->Exit();
		delete s_states.back();
		s_states.back() = nullptr; 
		s_states.pop_back();
	}
}

std::vector<State*>& StateManager::GetState() { return s_states; }
std::vector<State*> StateManager::s_states; // Vector now is allocated memory. it now "exists"

