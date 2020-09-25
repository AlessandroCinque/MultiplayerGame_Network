#include <iostream>
#include <time.h>
#include "EndState.h"
#include "Game.h"
#include "InputManager.h"
#include "MenuState.h"
#include "PlayState.h"

//------------------------------------------------------------------------------------------------------
//constructor that assigns all defaults
//------------------------------------------------------------------------------------------------------
PlayState::PlayState(GameState* state) : GameState(state)
{

	m_image = nullptr;
	
}
//------------------------------------------------------------------------------------------------------
//function that creates a new background screen object
//------------------------------------------------------------------------------------------------------
bool PlayState::OnEnter()
{

	m_image = new Background("Assets/Textures/BackGround.jpg", "Assets/Audio/Play.ogg");
	Setext("CLIENT!");

	player1.init(200, 200,1);
	player2.init(100, 100,2);
	orc.init();

	m_client.Initialise();
	m_client.Open();
	std::thread t_Receive(&PlayState::Receive, this);
	std::thread tSend(&PlayState::Send, this);

	t_Receive.detach();
	tSend.detach();
	

	return true;

}
//------------------------------------------------------------------------------------------------------
//function that reads key presses, mouse clicks and updates all game objects in scene
//------------------------------------------------------------------------------------------------------
bool PlayState::Update()
{

	//play the background music associated with the image
	//when the state transitions to the next state stop it
	m_image->PlayMusic();


	//read keyboard state
	KeyState keys = TheInput::Instance()->GetKeyStates();

	//the M key moves to the main menu
	if (keys[SDL_SCANCODE_M])
	{
		m_image->StopMusic();
		m_isActive = m_isAlive = false;
		TheGame::Instance()->ChangeState(new MenuState(this));
	}

	//the Q key moves to the ending state
	if (keys[SDL_SCANCODE_Q])
	{
		
		m_image->StopMusic();
		m_isActive = m_isAlive = false;
		TheGame::Instance()->ChangeState(new EndState(this));

	}
	
	player1.Update();
	

	return true;

}
//------------------------------------------------------------------------------------------------------
//function that renders the background image and all game objects in scene
//------------------------------------------------------------------------------------------------------
bool PlayState::Draw()
{

	//render the background image
	m_image->Draw();

	//This is the text that I want, the rest is just painted in the background
	for (size_t i = 0; i < m_Text.size(); i++)
	{
		m_Text[i].Draw(50,50);
	}
	
	player1.Draw();
	if (m_client.GetClientOn())
	{
		player2.Draw();
		orc.Draw();
	}

	return true;

}
//------------------------------------------------------------------------------------------------------
//function that removes all game objects from memory
//------------------------------------------------------------------------------------------------------
void PlayState::OnExit()
{
	m_client.ShutDown();
	//destroy all individual game objects
	delete m_image;

}

void PlayState::Setext(const std::string& text)
{
	Text myText;

	myText.SetFont("MENU_FONT");
	myText.SetColor(255, 174, 0);
	myText.SetSize(text.size() * 20, 60);
	myText.SetText(text);
	m_Text.push_back(myText);
}

void PlayState::Send()
{
	String s_message;
	
	while (m_isAlive)
	{
		KeyState key;


		system("color e9");
		if (player1.GetDirty())
		{
			String command;
			if (player1.GetFlip())
			{
				command = "F_";
			}
			else
			{
				command = "M_";
			}

			SDL_Point position = player1.GetPosition();
			char x[5];
			_itoa_s(position.x, x, _countof(x), 10);
			char y[5];
			_itoa_s(position.y, y, _countof(y), 10);
			String final_command = command + x + "_" + y;

			m_client.SendMessage(final_command);
			player1.SetDirty(false);
		}

	}
}

void PlayState::Receive()
{
	std::vector<String> parsed_str;
	char* token = new char;
	*token = '_';
	String r_message;
	while (m_isAlive)
	{
		m_client.ReceiveMessage(r_message);
		

		String message = m_client.GetResponse();
		
		std::cout << message[0] << std::endl;
		message.ParseString(message, parsed_str, token);
		
			
		String first = parsed_str[1];
		char* c = new char[first.Length() + 1];
		for (size_t i = 0; i < first.Length() + 1; i++)
		{
			c[i] = first[i];
		}
		int x = atoi(c);
			
		String second = parsed_str[2];
		char* d = new char[second.Length() + 1];
		for (size_t i = 0; i < second.Length() + 1; i++)
		{
			d[i] = second[i];
		}
		int y = atoi(d);
		//std::cout << "We are in x: " <<x <<" y: "<<y << std::endl;
		 if (parsed_str[0] == "O")
		{
			orc.SetPosition(x, y);
		}
		else if (parsed_str[0] == "F")
		{
			player2.SetFlip(true);
			player2.SetPosition(x, y);
		}
		
		else if(parsed_str[0] == "M")
		{
			player2.SetFlip(false);
			player2.SetPosition(x, y);
		}
			
			
		c = nullptr;
		delete c;
		d = nullptr;
		delete d;
		parsed_str.clear();
	}
	token = nullptr;
	delete token;
}
