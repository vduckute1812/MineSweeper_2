#include "Ball.h"
#include <stdlib.h>

const double PI = 3.141592653589793238463;
Ball *Ball::m_instance = nullptr;

Ball * Ball::GetInstance()
{
	if ( m_instance == nullptr )
	{
		m_instance = new Ball();
	}
	return m_instance;
}

void Ball::Destroy()
{
	if (m_instance)
	{
		delete m_instance;
	}
}

Ball::Ball()
{
	m_direction = 0;
}


Ball::~Ball()
{
	m_direction = 0;
}


void Ball::init(int x, int y)
{
	cycle->init(x, y, R_BALL);
	m_speed = 0;
}

void Ball::update()
{
	if ( m_speed != 0 )
	{
		Position pos;
		double ac = cos( m_direction );
		pos.x = get_position().x + m_speed * cos( m_direction ) * m_directionX;
		pos.y = get_position().y + m_speed * sin( m_direction ) * m_directionY;
		//printf( "\nm_direction:%f", m_direction );
		//printf("\npos.x:%d", pos.x );
		//printf( "\npos.y:%d", pos.y );
		//printf( "\nm_speed:%d", m_speed );
		m_ballSpeedX =  pos.x - get_position().x;
		m_ballSpeedY =  pos.y - get_position().y;
		set_position(&pos);
		m_speed -= m_acc;
		
		if( m_speed < 0 )
		{
			m_speed = 0;
		}
	}
	else
	{
		m_ballSpeedX = 0;
		m_ballSpeedY = 0;
	}

	//CheckCollsionWall(rect);
}

void Ball::CaculateDirection(Position pos, Position target)
{
	int deltaX = pos.x - target.x;
	int deltaY = pos.y - target.y;
	m_direction = acos(sqrt(pow( deltaX, 2)) / (sqrt(pow( deltaX , 2) + pow(deltaY,2))));
	m_directionX = deltaX < 0 ? 1 : -1;
	m_directionY = deltaY < 0 ? 1 : -1;
}

void Ball::SetDirection(float direction, int force)
{
	if (force > MAX_FORCE)
		force = MAX_FORCE;
	m_direction = direction;
	m_directionX = 1;
	m_directionY = 1;
	m_speed = force*BALL_SCALE_SPEED;
}

void Ball::Move(double direction)
{
	m_direction = direction;
}

void Ball::SetTarget( Position target )
{
	m_target = target;
}

Position Ball::CheckCollsionWall( Map *map )
{
	m_isHitWall = false;
	Position point = get_position();
	const Position constPoint = get_position();
	int goalYMin = map->GetHeigh()/2 - GOALWIDTH /2;
	int goalYMax = goalYMin + GOALWIDTH;
	m_percentBallHit = 0;
	if( ( constPoint.x < 0 || constPoint.x > map->GetWidth() )) //&& constPoint.y < goalYMax && constPoint.y > goalYMin )
	{
		//Goal
		int deltaX = constPoint.x < 0 ? ( -constPoint.x ) : ( constPoint.x - map->GetWidth() );
		int deltaY = 0; 
		if ( m_ballSpeedX !=0 )
		{
			double rateX = double(deltaX) / double( abs( m_ballSpeedX ) );
			deltaY = constPoint.y - m_ballSpeedY * rateX;
		}
	
		if ( deltaY < goalYMax && deltaY > goalYMin )
		{
			m_isInGoal = true;
			if ( constPoint.x > map->GetWidth() )
			{
				m_isTeamAScore = true;
			}
			else
			{
				m_isTeamAScore = false;
			}
		
			if( constPoint.x < -OFF_GOAL || constPoint.x > map->GetWidth() + OFF_GOAL )
			{
				point.x = constPoint.x;
				deltaX = constPoint.x < 0 ? ( -constPoint.x ) : ( constPoint.x - map->GetWidth() );
				double rateX = double( deltaX ) / double( abs( m_ballSpeedX ) );
				point.y = constPoint.y - m_ballSpeedY * rateX;
				if( point.y <  goalYMin )
				{
					point.y = goalYMin;
				}
				else if( point.y > goalYMax )
				{
					point.y = goalYMax;
				}
				SetPosition( point );
				//point.x = -OFF_GOAL;
				//point.y = constPoint.y - ();
			}
			/*else
			{
				point.x = map->GetWidth() + OFF_GOAL;
				point.y = constPoint.y 
			}*/
			return point;
		}
		
	}
	if( constPoint.x < 0 )
	{
		m_isHitWall = true;
		point.x = -constPoint.x;
		set_position( &point );
		m_directionX = -m_directionX;
		double rateX = double( point.x ) / double( abs( m_ballSpeedX ) );
		m_percentBallHit = 1 - rateX;
	}
	if( constPoint.x > map->GetWidth() )
	{
		m_isHitWall = true;
		point.x = 2 * map->GetWidth() - constPoint.x;
		set_position( &point );
		m_directionX = -m_directionX;
		double rateX = double( map->GetWidth() - point.x ) / double( abs( m_ballSpeedX ) );
		m_percentBallHit = 1 - rateX;
	}
	if( constPoint.y < 0 )
	{
		m_isHitWall = true;
		point.y = -constPoint.y;
		set_position( &point );
		m_directionY = -m_directionY;
		double rateY = double( point.y ) / double( abs( m_ballSpeedY ) );
		m_percentBallHit = 1 - rateY;
	}
	if( constPoint.y > map->GetHeigh() )
	{
		m_isHitWall = true;
		point.y = 2 * map->GetHeigh() - constPoint.y;
		set_position( &point );
		m_directionY = -m_directionY;
		double rateY = double( ( map->GetHeigh() - point.y ) ) / double( abs( m_ballSpeedY ) );
		m_percentBallHit = 1 - rateY;
	}
	
	// recaculate direction, update pos
	return point;
}

void Ball::ResetBall()
{
	m_speed = 0;
	m_directionX = 1;
	m_directionY = 1;
	m_isInGoal = false;
	m_isTeamAScore = false;
}

void Ball::SetSpeed(int speed)
{
	m_speed = speed;
}

void Ball::SetAcc(int acc)
{
	m_acc = acc;
}

int Ball::GetSpeed()
{
	return m_speed;
}

double Ball::GetDirection()
{
	return m_direction;
}

double Ball::GetPercentHit()
{
	return m_percentBallHit;
}

bool Ball::IsInGoal()
{
	return m_isInGoal;
}

bool Ball::IsTeamAScore()
{
	return m_isTeamAScore;
}

int Ball::GetSpeedX()
{
	return m_ballSpeedX;
}
int Ball::GetSpeedY()
{
	return m_ballSpeedY;
}

bool Ball::IsHitWall()
{
	return m_isHitWall;
}