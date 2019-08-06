// gs_bot.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <stdio.h>
// #include <tchar.h>
#include <string>
#include <thread>
#include <chrono>

#include "Define.h"

using namespace std;

struct Position
{
	Position() : x(0), y(0) {}
	Position(int _x, int _y) : x(_x), y(_y) {}
	const Position& operator =(const Position& pos) { x = pos.x; y = pos.y; return *this; }
	bool operator == (const Position &s) { return x == s.x && y == s.y; }

	// Properties
	int x;
	int y;
};

struct Object
{
public:
	Position m_pos;
	Position m_targetPos; //direction of moving/target pos
	Position m_moveSpeed;

	int m_action;
};

Position Rand(int mW, int mH)
{
	return Position(rand() % mW, rand() % mH);
}

void SendToServer(const Object& player)
{
	//best performance with one-line printf out.
	printf("%d %d %d", player.m_action, player.m_targetPos.x, player.m_targetPos.y);
}

enum Action
{
	WAIT = 0,
	RUN,
	SHOOT
};


int main()
{
	int gameTurn = 0;
	int mapWidth = 0;
	int mapHeight = 0;
	int maxTurn = 0;
	Object player;

	//init timer rand
	srand(time(NULL));

	std::cin >> mapWidth >> mapHeight >> maxTurn;

	while (gameTurn++ < maxTurn)
	{
		std::cin >> player.m_pos.x >> player.m_pos.y;

		player.m_action = Action::RUN;
		player.m_targetPos = Rand(mapWidth, mapHeight);

		SendToServer(player);
	}

    return 0;
}
