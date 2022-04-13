#include "PlatformPlayer.h"
#include "EventManager.h"
#include"TextureManager.h"
#include<cmath>
#include"States.h"

PlatformPlayer::PlatformPlayer(SDL_Rect s, SDL_FRect d) : AnimatedSpriteObject(s,d),
	m_state(STATE_JUMPING), m_isGrounded(false), m_isFacingLeft(false),
	m_maxVelX(8.0), m_maxVelY(m_grav * 2), m_grav(GRAVITY), m_drag(0.9)
{
	m_accelX = m_accelY = m_velX = m_velY = 0.0;
	// SetAnimation(?,?,?);  // Initialize jump animation.
	SetAnimation(1, 8, 9, 0);
}

void PlatformPlayer::Update()
{
	if (EVMA::KeyPressed(SDL_SCANCODE_A))
	{
		flip = SDL_FLIP_HORIZONTAL;
	}
	if (EVMA::KeyPressed(SDL_SCANCODE_D))
	{
		flip = SDL_FLIP_NONE;
	}

	switch (m_state)  // Inside each case is the behaviour in and transitions from that state.
	{
	case STATE_IDLING:
		// Transition to run.
		if (EVMA::KeyPressed(SDL_SCANCODE_A) || EVMA::KeyPressed(SDL_SCANCODE_D))
		{
			m_state = STATE_RUNNING;
			// SetAnimation(?,?,?,?);
			SetAnimation(12,0,9,0);
		}
		// Transition to jump.
		else if (EVMA::KeyPressed(SDL_SCANCODE_SPACE) && m_isGrounded)
		{
			m_accelY = -JUMPFORCE;
			m_isGrounded = false;
			m_state = STATE_JUMPING;
			// SetAnimation(?,?,?,?);
			SetAnimation(12, 8, 9, 0);
		}
		break;
	case STATE_RUNNING:
		// Move on ground.
		if (EVMA::KeyHeld(SDL_SCANCODE_A))   // && m_dst.x > 0
		{
			m_accelX = -1.5;
			if (!m_isFacingLeft)
			{
				m_isFacingLeft = true;
			}
		}
		else if (EVMA::KeyHeld(SDL_SCANCODE_D))  //&& m_dst.x < WIDTH - m_dst.w 
		{
			m_accelX = 1.5;
			if (m_isFacingLeft)
			{
				m_isFacingLeft = false;
			}
		}
		// Transition to idle.
		if (!EVMA::KeyHeld(SDL_SCANCODE_A) && !EVMA::KeyHeld(SDL_SCANCODE_D))
		{
			m_state = STATE_IDLING;
			// SetAnimation(?,?,?,?);
			SetAnimation(12, 1, 1, 0);
		}
		// Transition to jump.
		else if (EVMA::KeyPressed(SDL_SCANCODE_SPACE) && m_isGrounded)
		{
			m_accelY = -JUMPFORCE;
			m_isGrounded = false;
			m_state = STATE_JUMPING;
			// SetAnimation(?,?,?,?);
			SetAnimation(12, 8, 9, 0);
		}
		break;
	case STATE_JUMPING:
		// Move in mid-air
		if (EVMA::KeyHeld(SDL_SCANCODE_A))   // && m_dst.x > 0
		{
			m_accelX = -1.5;
			if (!m_isFacingLeft)
			{
				m_isFacingLeft = true;
			}
		}
		else if (EVMA::KeyHeld(SDL_SCANCODE_D))  //&& m_dst.x < WIDTH - m_dst.w 
		{
			m_accelX = 1.5;
			if (m_isFacingLeft)
			{
				m_isFacingLeft = false;
			}
		}
		// Transition to run.
		if (m_isGrounded)
		{
			m_state = STATE_RUNNING;  // Doesn't matter if this is running or idling
			// SetAnimation(?,?,?,?);
			SetAnimation(1, 1, 1, 0);
		}
		break;

		
			

	}
	// Player movement. Universal for all states. X-axis first.
	m_velX += m_accelX; // Add acceleration to velocity
	m_velX *= (m_isGrounded ? m_drag : 0.9);
	m_velX = std::min(std::max(m_velX, -m_maxVelX), m_maxVelX);
	m_dst.x += (float)m_velX;

	// Wrap the player on-screen. For you to do.
	

	// Y-axis now.
	m_velY += m_accelY + m_grav;
	m_velY = std::min(std::max(m_velY, -(m_maxVelY * 10)), (m_maxVelY));
	m_dst.y += (float)m_velY;

	m_accelX = m_accelY = 0.0;

 Animate();
}

void PlatformPlayer::Render()
{
	/*	To animate the sprite, use SDL_RenderCopyExF() and
		you will have to access the TextureManagerand pass in a key such as "players".*/ 
	//	But for this part, we are just going to use a colored square.

	//SDL_RenderCopyF(Engine::Instance().GetRenderer(), TEMA::GetTexture("player"), &m_src, &m_dst);
	
	//SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 255, 0, 0, 255);
	//SDL_RenderFillRectF(Engine::Instance().GetRenderer(), &m_dst);

	SDL_RenderCopyExF(Engine::Instance().GetRenderer(), TEMA::GetTexture("player"), &m_src, &m_dst, NULL, NULL, flip);
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

bool PlatformPlayer::isGrounded() { return m_isGrounded;}

double PlatformPlayer::GetVelX() { return m_velX;}

double PlatformPlayer::GetVelY() { return m_velY;}
