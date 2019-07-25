#include "Player.h"


Player::Player()
{
	for (int i = 0; i < MAX_FB; i++)
	{
		m_fb[i] = new Football_player();
	}
}


Player::~Player()
{
	for (int i = 0; i < MAX_FB; i++)
	{
		delete m_fb[i];
	}
}

void Player::init(int id, int pos[MAX_FB][2])
{
	m_id = id;
	for (int i = 0; i < MAX_FB; i++)
	{
		m_fb[i]->init(pos[i][0], pos[i][1]);
	}
}

void Player::update()
{
	Read_data();

	for (int i = 0; i < MAX_FB; i++)
	{
		m_fb[i]->update();
	}
}

void Player::Read_data()
{
	EVENT event[MAX_FB];


	//read data from control
	for (int i = 0; i < MAX_FB; i++)
	{
		//template
		event[i].m_action = Action::RUN;
		//event[i].m_pos.x = 10;
		//event[i].m_pos.y = 20;
		//event[i].m_direction = 0;

	}

	for (int i = 0; i < MAX_FB; i++)
	{
		m_fb[i]->push_action(&event[i]);
	}
}
