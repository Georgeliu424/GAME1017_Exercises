#include"PlatformPlayer.h"
#include"EventManager.h"
#include"TextureManager.h"
#include<cmath>


PlatformPlayer::PlatformPlayer(SDL_Rect s, SDL_FRect d):AnimatedSpriteObject(s,d),
	m_state(STATE_JUMPING),m_isGrounded(false),m_isFacingLeft(false),
	m_maxVelX(10.0), m_maxVelY(JUMPFORCE),m_grav(GRAVITY),m_drag(0.8)
{
	m_accelX = m_accelY = m_velX = m_velY = 0.0;
	SetAnimation(1, 8, 9);
}

void PlatformPlayer::Update()
{
	switch (m_state)
	{
	case STATE_IDLING:
		if (EVMA::KeyPressed(SDL_SCANCODE_A)||EVMA::KeyPressed(SDL_SCANCODE_D))
		{
			m_state = STATE_RUNNING;
			SetAnimation(2, 0, 9, 10);
		}
		else if (EVMA::KeyPressed(SDL_SCANCODE_SPACE) && m_isGrounded)
		{
			m_accelY = -JUMPFORCE;
			m_isGrounded = false;
			m_state = STATE_JUMPING;
			SetAnimation(2, 8, 9, 10);
		}
		

		break;
	case STATE_RUNNING:

		if (EVMA::KeyHeld(SDL_SCANCODE_A) && m_dst.x > 0)
		{
			m_accelX = -1.5;
			if (!m_isFacingLeft)
				m_isFacingLeft = true;
		}

		else if (EVMA::KeyHeld(SDL_SCANCODE_D) && m_dst.x < WIDTH - m_dst.w)
		{
			m_accelX = 1.5;
			if (!m_isFacingLeft)
				m_isFacingLeft = false;
		}


		if (EVMA::KeyPressed(SDL_SCANCODE_SPACE) && m_isGrounded)
		{
			m_accelY = -JUMPFORCE;
			m_isGrounded = false;
			m_state = STATE_JUMPING;
			SetAnimation(1, 8, 9, 10);
		}
		if (!EVMA::KeyHeld(SDL_SCANCODE_A) && !EVMA::KeyHeld(SDL_SCANCODE_D))
		{
			m_state = STATE_IDLING;
			SetAnimation(1, 0, 1, 10);

		}

		break;
	case STATE_JUMPING:
		if (EVMA::KeyHeld(SDL_SCANCODE_A) && m_dst.x > 0)
		{
			m_accelX = -1.5;
			if (!m_isFacingLeft)
			m_isFacingLeft = true;
		}
		else if (EVMA::KeyHeld(SDL_SCANCODE_D) && m_dst.x < WIDTH - m_dst.w)
		{
			m_accelY = 1.5;
			if(!m_isFacingLeft)
			m_isFacingLeft = false;
		}

		if (m_isGrounded)
		{
			m_state = STATE_RUNNING;
			SetAnimation(3, 0, 8, 10);
		}

		break;
	
	}
	m_velX += m_accelX;
	m_velX *= (m_isGrounded ? m_drag : 1.0);
	m_velX = std::min(std::max(m_velX, -m_maxVelX),m_maxVelX );
	m_dst.x += m_velX;


	m_velY += m_accelY + m_grav;
	m_velY = std::min(std::max(m_velY, -m_maxVelY), m_maxVelY);
	m_dst.y += m_velY;

	m_accelX = m_accelY = 0.0;

	Animate();

}

void PlatformPlayer::Render()
{
	SDL_RenderCopyExF(Engine::Instance().GetRenderer(), TEMA::GetTexture("player"), &m_src, &m_dst, 0.0, NULL, SDL_FLIP_NONE);
}
void PlatformPlayer::Stop()
{
		StopX();
		StopY();
}

void PlatformPlayer::StopX() { m_velX = 0.0; }

void PlatformPlayer::StopY() { m_velY = 0.0; }

void PlatformPlayer::SetAccelX(double a) { m_accelX = a; }

void PlatformPlayer::SetAccelY(double a) { m_accelY = a; }

void PlatformPlayer::SetX(float x) { m_dst.x = x; }

void PlatformPlayer::SetY(float y) { m_dst.y = y; }

void PlatformPlayer::SetGrounded(bool g) { m_isGrounded = g; }

bool PlatformPlayer::IsGrounded(){return m_isGrounded;}

double PlatformPlayer::GetVelX() { return m_velX; }

double PlatformPlayer::GetVelY() { return m_velY; }
