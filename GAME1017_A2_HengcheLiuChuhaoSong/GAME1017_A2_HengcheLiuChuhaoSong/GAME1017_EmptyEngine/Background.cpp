#include "Background.h"
#include "Engine.h"
#include "TextureManager.h"

Background::Background(const SDL_Rect s, const SDL_FRect d, float ss)
	: SpriteObject(s, d), m_scrollSpeed(ss)
{
	m_startX = GetDst()->x;
	m_endX = m_startX - GetDst()->w;
}

void Background::Update()
{
	// check if at end of journey.
	if (GetDst()->x <= m_endX)
	{
		GetDst()->x = m_startX;
	}
	// Scroll the background
	GetDst()->x -= m_scrollSpeed;
}

void Background::Render()
{
	SDL_RenderCopyF(Engine::Instance().GetRenderer(), TEMA::GetTexture
	("bg"), GetSrc(), GetDst());
}
