#include "Box.h"
#include"Engine.h"
#define SCROLLSPEED 2

Sprite::Sprite():m_dst({0,0,0,0}),m_color({255,255,255,255}) {}
Sprite::Sprite(const SDL_Rect r, const SDL_Color c):m_dst(r),m_color(c) {}

void Sprite::Render()
{
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), m_color.r, m_color.g, m_color.b, m_color.a);
	SDL_RenderFillRect(Engine::Instance().GetRenderer(), &m_dst);
}



Box::Box(const SDL_Point p, bool makeSprite = false, const SDL_Rect r ,
	const SDL_Color c ):m_pos(p),m_pSprite(nullptr)//note r and c are for Sprite
{
	if (makeSprite)
	{
		//m_pSprite = new Sprite[m_numSprites];//For dynamic array
		m_pSprite = new Sprite(r,c);
	}
}

Box::~Box()
{
	if (m_pSprite != nullptr)
	{
		delete m_pSprite;
	}
}

Box* Box::Clone()
{
	return nullptr;
}

void Box::Update()
{
	if (m_pSprite != nullptr)
	{
		m_pos.x = SCROLLSPEED;
		m_pSprite->m_dst.x = m_pos.x;
	}
}

void Box::Render()
{
	if (m_pSprite != nullptr)
	{
		m_pSprite->Render();
	}

	//if we want to render a border around each box...
	SDL_Rect dst = { m_pos.x, m_pos.y, 128, 128 };
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 156,230,200,255);
	SDL_RenderFillRect(Engine::Instance().GetRenderer(), & dst);
}


