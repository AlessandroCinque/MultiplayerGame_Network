#pragma once
#include "GameObject.h"
#include"TextureManager.h"
#include "InputManager.h"
#include "Sprite.h"
#include "Animation.h"
#include "TCPServer.h"
#include<ctime>
class Player :
	public GameObject
{
public:
	Player();
	virtual ~Player();
public:
	void init(int x , int y, int p_num);
	virtual void Update();
	void RemoteUpdate() { m_collider.SetPosition(m_position.x, m_position.y); }
	virtual bool Draw();
public:
	bool GetDirty() {return move_flag;}
	void SetDirty(bool flagreset) {move_flag = flagreset;}

	bool GetFlip() { return m_flipped; }
	void SetFlip(bool flip) { m_flipped = flip; }

	AABB GetBoundBox() { return m_collider; }
	void SetCollision(bool collision) { m_colliding = collision; }
	bool GetCollision() { return m_colliding; }

private:
	Sprite m_image;
	Animation m_anim;
	bool move_flag = false;

	AABB m_collider;
	bool m_colliding = false;

	bool m_attack = false;

};

