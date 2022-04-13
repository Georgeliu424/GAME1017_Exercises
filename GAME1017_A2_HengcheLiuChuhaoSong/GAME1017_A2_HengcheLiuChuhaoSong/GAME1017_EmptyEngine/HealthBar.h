#pragma once
#ifndef _HEALTHBAR_H_
#define _HEALTHBAR_H_

#include"GameObject.h"

class HealthBar : public GameObject
{
private:
	SDL_FRect m_bar;
	// Using m_dst from GameObject as background bar.
	int m_health;
public:
	HealthBar(/* agent pointer */  int maxHealth);
	void Update();
	void Render();
	void TakeDamage(int amount);
};

#endif 


