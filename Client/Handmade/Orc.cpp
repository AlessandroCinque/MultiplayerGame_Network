#include "Orc.h"



Orc::Orc()
{
}


Orc::~Orc()
{
}

void Orc::init()
{
	TheTexture::Instance()->LoadTextureFromFile("Assets/Characters/Ork.png", "ORK");

	std::string tag = "ork";
	SetTag(tag);
	m_image.SetTexture("ORK");
	m_image.SetSpriteDimension(120, 100);
	m_image.SetTextureDimension(1, 1, 1468, 1208);
}

void Orc::Update()
{
}

bool Orc::Draw()
{
	m_image.Draw(m_position.x, m_position.y, 0, Sprite::HORIZONTAL);
	return true;
}
