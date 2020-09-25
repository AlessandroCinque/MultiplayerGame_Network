#pragma once
#include "GameObject.h"
#include"TextureManager.h"
#include "InputManager.h"
#include "Sprite.h"
#include "TCPClient.h"
#include<ctime>
class Player :
	public GameObject
{
public:
	Player();
	virtual ~Player();
public:
	void init(int x, int y, int p_num);
	virtual void Update();
	virtual bool Draw();
public:
	bool GetDirty() { return move_flag; }
	void SetDirty(bool flagreset) { move_flag = flagreset; }
	
	bool GetFlip() { return m_flipped; }
	void SetFlip(bool flip) { m_flipped = flip; }
private:
	TCPClient m_client;
	Sprite m_image;
	bool move_flag = false;

};

