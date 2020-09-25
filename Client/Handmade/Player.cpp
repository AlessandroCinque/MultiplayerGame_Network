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

}

void Player::Update()
{
	KeyState key;
	key = TheInput::Instance()->GetKeyStates();
	clock_t dt = clock();
	dt = dt / 1000;

	if (key[SDL_SCANCODE_A])
	{
		m_flipped = true;
		m_position.x -= 5;
		move_flag = true;
	}
	else if (key[SDL_SCANCODE_D])
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

}


bool Player::Draw()
{
	if (!m_flipped)
	{
		m_image.Draw(m_position.x, m_position.y);
	}
	else if (m_flipped)
	{
		m_image.Draw(m_position.x, m_position.y, 0, Sprite::HORIZONTAL);
	}
	return true;
}
