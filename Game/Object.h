#pragma once

#include "Cycle.h"
#include "Define.h"

struct  Position
{
	int x;
	int y;
};

class Object
{
public:
	Object();
	~Object();

	virtual void	init(int x, int y);
	virtual void	update();

	void			set_position(Position *pos);

	Position		get_position();
	void			SetPosition( Position pos );
	Position		GetPosition();

protected:
	Cycle *cycle;
	Position		m_position;
};

