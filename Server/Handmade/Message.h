#pragma once
#include<vector>
#include "GameObject.h"
#include"TextureManager.h"
#include"String.h"
#include"Text.h"
class Message :
	public GameObject
{
public:
	Message(const String& message = "");
	virtual ~Message();
public:
	void Setext(String message);
	void SetMessage(const String message) { m_message = message; }
	
	std::string GetConvertedStuff() { return Converter(m_message); }
	std::string Converter(String ptext);
public:
	virtual void Update();
	virtual bool Draw();
private:
	std::vector<Text> m_messageText;
	String m_message;
};

