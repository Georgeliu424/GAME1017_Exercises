#include "Box.h"
#include"Engine.h"
#define SCROLLSPEED 2

Sprite::Sprite():m_dst({0,0,0,0}),m_src({255,255,255,255}) {}
Sprite::Sprite(const SDL_Rect r, const SDL_Rect s):m_dst(r),m_src(s) {}

void Sprite::Render()
{
	SDL_RenderCopy(Engine::Instance().GetRenderer(),
		Engine::Instance().GetObstacleText(), &m_src, &m_dst);
}



Box::Box(const SDL_Point p, bool makeSprite , const SDL_Rect r,
	SDL_Rect s ):m_pos(p),m_pSprite(nullptr)//note r and c are for Sprite
{
	if (makeSprite)
	{
		m_pSprite = new Sprite[m_numSprites];//For dynamic array
		m_pSprite = new Sprite(r,s);
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
	Box* clone = new Box(this->m_pos, false); // deep copy for brand new box object 
	clone->m_pSprite = new Sprite(this->m_pSprite->m_dst, this->m_pSprite->m_src);
	return clone;
}


void Box::Update()
{
	m_pos.x -= SCROLLSPEED;
	if (m_pSprite != nullptr)
	{
		m_pSprite->m_dst.x -= SCROLLSPEED;
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
	SDL_RenderDrawRect(Engine::Instance().GetRenderer(), & dst);
}




