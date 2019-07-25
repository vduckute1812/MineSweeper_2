#pragma once

#include "Object.h"
#include <math.h>
#include "Rectangle.h"
#include "Map.h"

using namespace std;

class Ball : public Object
{
public:
	static Ball *GetInstance();
	static void Destroy();

	Ball();
	~Ball();

	void init(int x, int y);
	void update();
	void SetTarget(Position target);
	void Move(double direction);
	Position CheckCollsionWall( Map *map);
	void SetDirection( float direction, int force );
	void SetSpeed(int speed);
	void SetAcc(int acc);
	void ResetBall();
	int GetSpeed();
	int GetSpeedX();
	int GetSpeedY();
	double GetDirection();
	void CaculateDirection( Position pos, Position target );
	bool IsInGoal();
	bool IsTeamAScore();
	bool IsHitWall();
	double GetPercentHit();
private:
	static Ball		*m_instance;
	Position		m_target;
	double			m_direction;
	int				m_speed;
	int				m_acc;
	int				m_directionX = 1;
	int				m_directionY = 1;
	bool			m_isInGoal = false;
	bool			m_isTeamAScore = false;
	int				m_ballSpeedX = 0;
	int				m_ballSpeedY = 0;
	bool			m_isHitWall = false;
	double			m_percentBallHit = 0;
};

