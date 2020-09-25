#include "Player.h"

Player::Player()
{
}


Player::~Player()
{
	TheTexture::Instance()->UnloadFromMemory(TextureManager::TEXTURE_DATA, TextureManager::CUSTOM_DATA, "DWARF");
}

void Player::init(int x, int y, int p_num)
{

	m_position.x = x;
	m_position.y = y;
	if (p_num == 1)
	{
		TheTexture::Instance()->LoadTextureFromFile("Assets/Characters/Dwarf_Attack1.png", "DWARF");
	}
	else 
	{
		TheTexture::Instance()->LoadTextureFromFile("Assets/Characters/Dwarf_Attack2.png", "DWARF");
	}

	
	std::string tag = "dwarf";
	SetTag(tag);
	m_image.SetTexture("DWARF");
	m_image.SetTextureCel(0, 0);
	m_image.SetSpriteDimension(50, 50);
	m_image.SetTextureDimension(8, 16, 38, 32);
	//===================== ANIMATIONS =============================
	m_anim.SetTexture("DWARF");
	m_anim.SetAnimationVelocity(50.0f);
	m_anim.SetSpriteDimension(50, 50);
	m_anim.SetTextureDimension(7, 1, 32, 32);
	m_anim.IsAnimationLooping() = true;

	m_collider.SetDimension(45, 45);

}

void Player::Update()
{
	KeyState key;
	key = TheInput::Instance()->GetKeyStates();
	clock_t dt = clock();
	dt = dt / 1000;

	m_collider.SetPosition(m_position.x, m_position.y);

	if (key[SDL_SCANCODE_A] )
	{
		m_flipped = true;
		m_position.x -= 5;
		move_flag = true;
	}
	else if (key[SDL_SCANCODE_D] && !m_colliding)
	{
		m_flipped = false;
		m_position.x += 5;
		move_flag = true;
	}
	else if (key[SDL_SCANCODE_W])
	{
		m_position.y -= 5;
		move_flag = true;
	}
	else if (key[SDL_SCANCODE_S])
	{
		m_position.y += 5;
		move_flag = true;
	}

	if (key[SDL_SCANCODE_K]) 
	{
		m_attack = true;
	}
	else 
	{
		m_attack = false;
	}
	
}

bool Player::Draw()
{
	if (!m_flipped && !m_attack)
	{
		m_image.Draw(m_position.x, m_position.y);
	}
	else if (m_flipped && !m_attack)
	{
		m_image.Draw(m_position.x, m_position.y, 0, Sprite::HORIZONTAL);
	}
	//============ Drawing Attack ============
	else if (m_attack && !m_flipped)
	{
		m_anim.Draw((int)m_position.x, (int)m_position.y);
	}
	else if (m_attack && m_flipped)
	{
		m_anim.Draw((int)m_position.x, (int)m_position.y, 0, Sprite::HORIZONTAL);
	}
	return true;
}
