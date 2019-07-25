#pragma once

#include <vector>
#include "Object.h"
#include "Ball.h"
#include "Map.h"

using namespace std;

enum Action
{
	FREEZE = 0,
	RUN,
	SHOOT,
	HOLD
};

struct EVENT
{
	Action m_action;
	Position m_target;
	int m_force;
	double m_direction;
};

class Football_player :
	public Object
{
public:
	Football_player();
	~Football_player();

	void	init(int x, int y);
	void	update();

	void	push_action(EVENT *event);

	void	Run();
	void	SetTarget(Position target);
	void	Shoot( Position posBall, int force, double direction );
	void	Shoot( Position posBall, int force, Position pos, Position target );
	void	CaculateDirection( Position pos, Position target );
	void	SetMap( Map map );
	void	ResetState();
	bool	CanBeShoot(Position posBall);
	int		GetForceToShoot();
	double	GetDirectionToShoot();
	int		GetSpeed();
	double	GetDirection();
	double	GetDirectionAlpha();
	void	SetState(Action _state);
	int		GetState();
	double	GetDirectionShootPI();
	int		GetBlood() const;
	
	void	SetName(char* name);
	char*	GetName();
	int		GetLength(char* str);

private:
	vector<EVENT*>	m_event;
	Action			state;
	int				m_speed = PLAYER_SPEED;
	int				m_blood;

	Position		m_target;
	int				m_directionX = 1;
	int				m_directionY = 1;
	double			m_direction;
	int				m_forceToShoot;
	double			m_directionToShoot;
	Map				m_map;
	int				m_directionShootX = 1;
	int				m_directionShootY = 1;
	char*			m_name;
};

