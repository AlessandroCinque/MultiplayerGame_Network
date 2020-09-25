#include <iostream>
#include <time.h>
#include "EndState.h"
#include "Game.h"
#include "InputManager.h"
#include "MenuState.h"
#include "PlayState.h"
#include<thread>

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

	Setext("SERVER!");
	
	m_message = new Message ("Marooooonnnnn!");
	m_message->SetMessage("Maroooonnnn22222!");

	player1.init(100,100,1);
	player2.init(200, 200,2);
	srand((unsigned)time(0));
	orc.init(1180, rand() % 670 + 1);

	m_server.Initialize();
	m_server.Open();

	//============= NETWORKING SIDE!!! =================
//====== THIS HAVE ALWAYS TO STAY AT THE BOTTOM COUSE OF THE JOINS!!!! =================
	std::thread t_Listen(&PlayState::Listen, this);
	std::thread t_Receive(&PlayState::Receive, this);
	std::thread t_Send(&PlayState::Send, this);

	t_Listen.detach();
	t_Receive.detach();
	t_Send.detach();

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
	//For write score use a flag for see if the score is changed and then activate the update
	//m_message->Setext("blaaaaaaaaaaaaaaaaaa");
	
	
	
	if (m_server.GetClientOn())
	{
		player1.Update();
		player2.RemoteUpdate();
		orc.Update();
		if (orc.GetBoundBox().IsColliding(player1.GetBoundBox()))
		{
			orc.SetCollision(true);
			player1.SetCollision(true);
		}
		else if (orc.GetBoundBox().IsColliding(player2.GetBoundBox()))
		{
			orc.SetCollision(true);
			player2.SetCollision(true);
		}
		else
		{
			orc.SetCollision(false);
			player1.SetCollision(false);
			player2.SetCollision(false);
		}

	}
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
	
	if (m_server.GetClientOn())
	{
		orc.Draw();
		player2.Draw();
	}
	//std::cout << "..." << std::endl;
	m_message->Draw();
	
	return true;

}
//------------------------------------------------------------------------------------------------------
//function that removes all game objects from memory
//------------------------------------------------------------------------------------------------------
void PlayState::OnExit()
{
	m_server.Close();
	m_server.ShutDown();
	//destroy all individual game objects
	delete m_image;
	delete m_message;

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

void PlayState::Listen()
{
	while (m_isAlive)
	{
		if (m_server.Listen())
		{
			m_message->SetMessage("Bhooooooooooooo!");
		}
	}
}

void PlayState::Send()
{
	String s_message;
	SDL_Point temp_pos = player1.GetPosition();
	while (m_isAlive)
	{
		KeyState key;
		key = TheInput::Instance()->GetKeyStates();


		system("color e9");
			String command;
			SDL_Point position;

			if (player1.GetFlip() && player1.GetDirty())
			{
				command = "F_";
				position = player1.GetPosition();
			}
			else if(!player1.GetFlip() && player1.GetDirty())
			{
				command = "M_";
				position = player1.GetPosition();
			}
			else
			{
				command = "O_";
				position = orc.GetPosition();
			}
			
			
			char x[5];
			_itoa_s(position.x, x, _countof(x), 10);
			char y[5];
			_itoa_s(position.y, y, _countof(y), 10);
			String final_command = command + x + "_" + y;
			
			m_server.SendMessage(final_command);
			player1.SetDirty(false);
	}
}

void PlayState::Receive()
{
	/*String r_message;
	while (m_isAlive)
	{
		m_server.ReceiveMessage(r_message);
	}*/

	std::vector<String> parsed_str;
	char* token = new char;
	*token = '_';
	String r_message;
	while (m_isAlive)
	{
		if (m_server.GetClientOn()) {
			m_server.ReceiveMessage(r_message);


			String message = m_server.GetResponse();

			std::cout << m_server.GetResponse() << std::endl;
			message.ParseString(message, parsed_str, token);

			if (parsed_str[0] == "M" || parsed_str[0] == "F")
			{


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
				
				if (parsed_str[0] == "F")
				{
					player2.SetFlip(true);
				}
				else
				{
					player2.SetFlip(false);
				}

				player2.SetPosition(x, y);
				c = nullptr;
				delete c;
				d = nullptr;
				delete d;
				parsed_str.clear();
			}
		}
	}
	token = nullptr;
	delete token;
}

