#pragma once
#include "GameObject.h"
#include"TextureManager.h"
#include "InputManager.h"
#include "Sprite.h"
#include <stdlib.h>
#include<ctime>
class Orc :
	public GameObject
{
public:
	Orc();
	~Orc();
public:
	void init();
	virtual void Update();
	virtual bool Draw();

private:
	Sprite m_image;
};

