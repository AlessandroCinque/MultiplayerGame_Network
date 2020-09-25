#include "Orc.h"


Orc::Orc()
{
}


Orc::~Orc()
{
	TheTexture::Instance()->UnloadFromMemory(TextureManager::TEXTURE_DATA, TextureManager::CUSTOM_DATA, "ORK");
}

void Orc::init(int x, int y)
{	// screen size: 1280, 720  1468, 1208
	m_position.x = x;
	m_position.y = y;

	TheTexture::Instance()->LoadTextureFromFile("Assets/Characters/Ork.png", "ORK");

	std::string tag = "ork";
	SetTag(tag);
	m_image.SetTexture("ORK");
	m_image.SetSpriteDimension(120, 100);
	m_image.SetTextureDimension(1, 1, 1468, 1208);
	//==============Collisions===============
	m_collider.SetDimension(120, 100);

	
	
}

void Orc::Update()
{
	m_collider.SetPosition(m_position.x, m_position.y);
	if (!m_colliding) 
	{
		float distance = 0 - m_position.x;
		total_distance = sqrt(distance * distance);
		m_position.x += (0.5 * distance * m_speed / total_distance);
	}
	if (m_position.x <= 0 || !m_isAlive)  
	{
		m_position.x = 1380;
		m_position.y = rand() % 620 + 1;
		m_speed += 0.5f;
	}
	
}

bool Orc::Draw()
{
	m_image.Draw(m_position.x, m_position.y, 0, Sprite::HORIZONTAL);
	return true;
}
