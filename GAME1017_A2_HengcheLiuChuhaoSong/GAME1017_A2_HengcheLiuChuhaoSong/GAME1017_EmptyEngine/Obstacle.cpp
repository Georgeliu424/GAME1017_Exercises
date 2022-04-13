#include "GameObject.h"
#include"Engine.h"
#define SCROLLSPEED 2


void Sprite::Render()
{
	SDL_RenderCopy(Engine::Instance().GetRenderer(), m_pTexture, this->GetSrc(), this->GetDst());
}



Obstacle::Obstacle(const SDL_Point p, bool makeSprite, int numSprites, const SDL_Rect r,
	const SDL_Color c) :m_pos(p), m_pSprite(nullptr),m_numSprites(numSprites)
{
	if (makeSprite)
	{
		m_pSprite = new Sprite[m_numSprites];
		m_pSprite = new Sprite(r, c);
	}
}

Obstacle::~Obstacle()
{
	if (m_numSprites > 0)
		delete[] m_pSprite;
}

void Obstacle::Update()
{

	m_pos.x -= SCROLLSPEED;
	if (m_pSprite != nullptr)
	{
		m_pSprite->m_dst.x -= SCROLLSPEED;
	}
}



Obstacle* Obstacle::Clone()
{
	Obstacle* clone = new Obstacle(m_pos, (m_numSprites > 0), m_numSprites);
	for (int i = 0; i < m_numSprites; i++)
	 clone->m_pSprite[i] = this->m_pSprite[i];
	return clone;
}

void Obstacle::Render()
{
	for (int i = 0; i < m_numSprites; i++)
		m_pSprite[i].Render();
}
