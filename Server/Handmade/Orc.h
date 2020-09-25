#pragma once
#include "GameObject.h"
#include"TextureManager.h"
#include "InputManager.h"
#include "Sprite.h"
#include "TCPServer.h"
#include <stdlib.h>
#include<ctime>
class Orc :
	public GameObject
{
	//alc0778@my.londonmet.ac.uk
public:
	Orc();
	~Orc();
public:
	void init(int x, int y);
	virtual void Update();
	virtual bool Draw();

public:
	AABB GetBoundBox() { return m_collider; }
	void SetCollision(bool collision) {	m_colliding = collision;}

private:
	AABB m_collider;
	bool m_colliding = false;
	Sprite m_image;
	float total_distance;
	float m_speed = 5.0f;
};

