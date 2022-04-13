#include "HealthBar.h"
#include"Engine.h"

HealthBar::HealthBar(int maxHealth) : m_health(maxHealth)
{
	// Adjust the rects to be an offset of an agent position
	m_dst = { 50,100,100,25 };
	m_bar = { 52, 102,96,21 };
}

void HealthBar::Update()
{
	// it is static for now
}

void HealthBar::Render()
{
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 255, 255, 255, 255);
	SDL_RenderFillRectF(Engine::Instance().GetRenderer(), GetDst());

	// z - min/max-min  -> % in a range
	double perc = (m_health / 100.0);
	m_bar.w = 96 * perc;
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 128 * (1 - perc), 128 * perc, 0, 255);
	SDL_RenderFillRectF(Engine::Instance().GetRenderer(), &m_bar);

	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 255, 255, 255, 255);
}

void HealthBar::TakeDamage(int amount)
{
	m_health -= amount;
	if (m_health < 0)
	{
		m_health = 0;
	}
	if (m_health > 100)
	{
		m_health = 100;
	}
}
