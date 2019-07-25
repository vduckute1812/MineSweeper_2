#include <cstdlib>
#include "Football_player.h"

const double PI = 3.141592653589793238463;

Football_player::Football_player()
{
	m_name = new char[100];
}


Football_player::~Football_player()
{
	delete []m_name;
}

void Football_player::init(int x, int y)
{
	cycle->init(x, y, R_FB);
	m_direction = 0;
	m_forceToShoot = 0;
	m_directionToShoot = 0;
	m_target.x = x;
	m_target.y = y;
	m_blood = CHARACTER_BLOOD;
	m_name = "Duc";
}

void Football_player::update()
{
	if (m_event.empty())
	{
		return;
	}

	EVENT *event;
	event = m_event.front();

	switch (event->m_action)
	{
	case Action::FREEZE:
		m_event.clear();
		break;
	case Action::RUN:
		Run();
		//m_event.clear();
		break;
	case Action::SHOOT:
		//Shoot(event->m_direction);
		m_event.clear();
		break;
	case Action::HOLD:
		break;
	default:
		m_event.clear();
		break;
	}
}

void Football_player::push_action(EVENT *event)
{
	m_event.push_back(event);
}

void Football_player::Run()
{
	//state = Action::RUN;
	if( m_target.x < 0 || m_target.y < 0 || m_target.x > m_map.GetWidth() || m_target.y > m_map.GetHeigh() )
	{
		SetState(Action::FREEZE);
		return;
	}
	//printf("\nget_position().x:%d", get_position().x);
	//printf( "\nm_target.x:%d", m_target.x );	

	if( get_position().x != m_target.x || get_position().y != m_target.y )
	{
		SetState(Action::RUN);
		CaculateDirection( get_position() , m_target );
		if( m_speed != 0 )
		{
			Position pos;
			pos.x = get_position().x + m_speed * cos( m_direction ) * m_directionX;
			pos.y = get_position().y + m_speed * sin( m_direction ) * m_directionY;
			int checkTargetX = (get_position().x - pos.x) * (m_target.x - pos.x );
			int checkTargetY = ( get_position().y - pos.y ) * ( m_target.y - pos.y );
			if( checkTargetX >= 0 && checkTargetY >= 0 )
			{
				set_position( &m_target );
			} else
			{
				set_position( &pos );
			}
		}
	}
	else
	{
		SetState(Action::FREEZE);
		m_direction = 0;
	}
	//check_collision_ball();
}

void Football_player::Shoot( Position posBall,int force, double direction)
{
	if( !CanBeShoot( posBall ) || (force > MAX_FORCE ) || (force < 0))
	{
		m_forceToShoot = 0;
		m_directionToShoot = 0;
		return;
	}

#if ENABLE_RANDOM_FORCE
	if (force != 0) {
		int randx = rand() % (2 * ENABLE_RANDOM_FORCE + 1);
		int randForce = ceil(((randx - ENABLE_RANDOM_FORCE)*force)/100.0);
		force += randForce;
		if (force > 100) force = 100;
	}
#endif
#if ENABLE_RANDOM_DIRECTION
	int randx = rand() % (2 * ENABLE_RANDOM_DIRECTION + 1);
	double randDir = ((randx - ENABLE_RANDOM_DIRECTION)*PI) / 100.0;
	direction += randDir;
#endif

	EVENT *e = new EVENT();
	e->m_action = Action::SHOOT;
	m_forceToShoot = force;
	m_directionToShoot = direction;
	push_action( e );
}

void Football_player::Shoot( Position posBall, int force, Position pos, Position target )
{
	if( !CanBeShoot( posBall ) || force > MAX_FORCE || force <= 0 )
	{
		m_forceToShoot = 0;
		m_directionToShoot = 0;
		m_directionShootX = 1;
		m_directionShootY = 1;
		SetState(Action::FREEZE);
		return;
	}
	
	SetState(Action::SHOOT);

#if ENABLE_RANDOM_FORCE
	if (force != 0) {
		int randx = rand() % (2 * ENABLE_RANDOM_FORCE + 1);
		int randForce = ceil(((randx - ENABLE_RANDOM_FORCE)*force) / 100.0);
		force += randForce;
		if (force > 100) force = 100;
	}
#endif

	m_forceToShoot = force;
	int deltaX = posBall.x - target.x;
	int deltaY = posBall.y - target.y;
	if (posBall.x == target.x && posBall.y == target.y) {
		m_directionToShoot = (rand() % 627) / 100.0;
	}
	else {
		m_directionToShoot = acos(sqrt(pow(deltaX, 2)) / (sqrt(pow(deltaX, 2) + pow(deltaY, 2))));
	}
#if ENABLE_RANDOM_DIRECTION
	int randx = rand() % (2 * ENABLE_RANDOM_DIRECTION + 1);
	double randDir = ((randx - ENABLE_RANDOM_DIRECTION)*PI) / 100.0;
	m_directionToShoot += randDir;
#endif

	m_directionShootX = deltaX < 0 ? 1 : -1;
	m_directionShootY = deltaY < 0 ? 1 : -1;
}

void Football_player::SetTarget( Position target )
{
	m_target = target;
	EVENT *e = new EVENT();
	e->m_action = Action::RUN;
	e->m_target = target;
	//printf("\ntargetCX:%d", m_target.x);
	//printf( "  targetCY:%d", m_target.y );
	push_action(e);
}

bool Football_player::CanBeShoot(Position posBall)
{
	/*Position pos = ball->GetInstance()->get_position();
	if (get_position().x == pos.x && get_position().y == pos.y)
	{
		state = Action::HOLD;
	}*/
	//Position posBall = ball->GetPosition();
	float m_distance = sqrt( pow( posBall.x - get_position().x, 2 ) + pow( posBall.y - get_position().y, 2 ) );
	if( m_distance <= RAD_TO_SHOOT )
	{
		return true;
	}
	return false;
}

void Football_player::CaculateDirection( Position pos, Position target )
{
	int deltaX = pos.x - target.x;
	int deltaY = pos.y - target.y;
	m_direction = acos( sqrt( pow( deltaX, 2 ) ) / ( sqrt( pow( deltaX, 2 ) + pow( deltaY, 2 ) ) ) );
	m_directionX = deltaX < 0 ? 1 : -1;
	m_directionY = deltaY < 0 ? 1 : -1;
}

int Football_player::GetForceToShoot()
{
	return m_forceToShoot;
}
double Football_player::GetDirectionToShoot()
{
	return m_directionToShoot;
}

int Football_player::GetSpeed()
{
	return m_speed;
}

double Football_player::GetDirection()
{
	return m_direction;
}


double Football_player::GetDirectionAlpha()
{
	double alpha = m_direction * 180 / PI;
	if( m_directionX == -1 && m_directionY == -1 )
	{
		alpha += 180;
	}
	else if( m_directionX == -1 )
	{
		alpha = 180 - alpha ;
	}
	else if( m_directionY == -1 )
	{
		alpha = 360 - alpha;
	}
	return alpha;
}

double Football_player::GetDirectionShootPI()
{
	double alpha = m_directionToShoot;
	if( m_directionShootX == -1 && m_directionShootY == -1 )
	{
		alpha += PI;
	}
	else if( m_directionShootX == -1 )
	{
		alpha = PI - alpha;
	}
	else if( m_directionShootY == -1 )
	{
		alpha = 2 * PI - alpha;
	}
	return alpha;
}

int Football_player::GetBlood() const
{
	return m_blood;
}

void Football_player::SetName(char * name)
{
	m_name = name;
}

char * Football_player::GetName()
{
	return m_name;
}

int Football_player::GetLength(char * str)
{
	int size = 0;
	char* tmp = str;
	while (*tmp != '\0')
	{
		size++;
		tmp++;
	}
	return size;
}

void Football_player::SetState(Action _state)
{
	state = _state;
}


int Football_player::GetState()
{
	//EVENT *event;
	//event = m_event.front();
	//int action = event->m_action;
	/*
	if( m_forceToShoot != 0 )
	{
		return Action::SHOOT;
	}
	if( m_target.x != get_position().x || m_target.y != get_position().y )
	{
		return Action::RUN;
	}
	return Action::FREEZE;
	*/


	return state;
	
}

void Football_player::SetMap( Map map )
{
	m_map = map;
}

void Football_player::ResetState()
{
	m_target = get_position();
	EVENT *e = new EVENT();
	e->m_action = Action::FREEZE;
	e->m_target = m_target;
	push_action( e );
	m_forceToShoot = 0;
	m_directionToShoot = 0;
}