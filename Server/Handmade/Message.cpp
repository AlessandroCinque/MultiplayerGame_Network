#include "Message.h"



Message::Message(const String& message)
{
	
}


Message::~Message()
{
}

void Message::Setext(String message)
{
	std::string text = Converter(message);
	Text myText;
	TheTexture::Instance()->LoadFontFromFile("Assets/Fonts/Helmswald.ttf", 50, "FONT");
	myText.SetFont("FONT");
	myText.SetColor(255, 10, 10);
	myText.SetSize(message.Length() * 20, 60);
	myText.SetText(text);
	m_messageText.push_back(myText);
}

std::string Message::Converter(String ptext)
{
	const size_t SIZE = ptext.Length() + 1;
	char* char_array;
	char_array = new char[SIZE];
	
	for (size_t i = 0; i < SIZE; i++)
	{
		char_array[i] = ptext[i];
		//text[i] = text +char_array[i];
	}
	std::string text(char_array);
	return std::string(text);
}

void Message::Update()
{
	//Setext();
}

bool Message::Draw()
{
	for (size_t i = 0; i < m_messageText.size(); i++)
	{
		m_messageText[i].Draw(50, 50);
	}
	return true;
}
