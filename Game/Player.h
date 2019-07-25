#pragma once

#include "Football_player.h"
#include "Define.h"
#include "Ball.h"

using namespace std;

class Player
{
public:
	Player();
	~Player();

	void init(int id, int pos[MAX_FB][2]); 
	void update();

	void Read_data();

private:
	int m_id;
	Football_player *m_fb[MAX_FB];
};

