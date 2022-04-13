#pragma once
#ifndef _Box_H_
#define _Box_H_
#include<SDL.h>

class Sprite // could be renamed Obstacle for A2
{
private:
	SDL_Rect m_src; //for A2 or use GameObject.h
	SDL_Rect m_dst;

public:
	Sprite(); // If you have a dynamic array of sprite
	Sprite(const SDL_Rect r, const SDL_Rect s);
	//void Update();// may need for A2, e.g.spinning blade
	void Render();
	friend class Box; //Alternately you can make a setter for m_dst
};



class Box // proxy for the obstacle/sprite
{

private:
	SDL_Point m_pos; //position on screen .Y is optional
	Sprite* m_pSprite; // pointer to a dynamic sprite object(s)
	int m_numSprites; // for bonus of A2
public:
	Box(const SDL_Point p, bool makeSprite = false, const SDL_Rect r = { 0,0,0,0 },
		const SDL_Rect s = { 0,0,0,0 });
	~Box();
	Box* Clone(); //we're making box also a prototype
	void Update();
	void Render(); 
	const SDL_Point GetPos() { return m_pos; }
};
#endif
