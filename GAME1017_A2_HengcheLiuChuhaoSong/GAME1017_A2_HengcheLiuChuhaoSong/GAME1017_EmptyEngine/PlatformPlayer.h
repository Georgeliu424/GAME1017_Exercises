#pragma once
#ifndef _PLATFORPLAYER_H_
#define _PLATFORPLAYER_H_

#include "GameObject.h"
#define GRAVITY 10.0
#define JUMPFORCE 40.0 //Upward Y force.

enum PlayerState {STATE_IDLING,STATE_RUNNING, STATE_JUMPING };

class PlatformPlayer : public AnimatedSpriteObject
{
public:
	PlatformPlayer(SDL_Rect s, SDL_FRect d);
	void Update();
	void Render();
	// Getters and setters.
	void Stop();
	void StopX();
	void StopY();
	void SetAccelX(double a);
	void SetAccelY(double a);
	void SetX(float x);
	void SetY(float y);
	void SetGrounded(bool g);
	bool isGrounded();
	double GetVelX();
	double GetVelY();
	SDL_RendererFlip flip = SDL_FLIP_NONE;

private:
	bool m_isGrounded, m_isFacingLeft;
	double m_accelX, m_accelY,
		m_velX, m_velY,
		m_maxVelX, m_maxVelY,
		m_drag, m_grav; 
	PlayerState m_state;
};

#endif // !_PLATFORPLAYER_H_