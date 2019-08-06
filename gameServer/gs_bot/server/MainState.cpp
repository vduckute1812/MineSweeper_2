#include "stdafx.h"
#include "MainState.h"
#include <fstream>
#include <sstream>

MainState::MainState()
{
}


MainState::~MainState()
{
}

void MainState::Init()
{
}

void MainState::Update()
{
}

void MainState::Render()
{
}

void MainState::Exit()
{
}

void MainState::SendDataToClient()
{

}

bool MainState::GetInputData(std::string data)
{
	m_dataInputA.clear();
	m_dataInputB.clear();
	std::vector<std::string> tokens;
	std::string token;
	std::istringstream tokenStream(data);
	while (getline(tokenStream, token, '#'))
	{
		tokens.push_back(token.c_str());
	}
	std::string userA = tokens.at(0);
	std::string userB = tokens.at(1);
	if (userA != "E101")
	{
		std::vector<std::string> tokens;
		std::string token;
		std::istringstream tokenStream(userA);
		while (getline(tokenStream, token, ' '))
		{
			m_dataInputA.push_back(atoi(token.c_str()));
		}
	}
	if (userB != "E201")
	{
		std::vector<std::string> tokens;
		std::string token;
		std::istringstream tokenStream(userB);
		while (getline(tokenStream, token, ' '))
		{
			m_dataInputB.push_back(atoi(token.c_str()));
		}
	}

	return true;
}
