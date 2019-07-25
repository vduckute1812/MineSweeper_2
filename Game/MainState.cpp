#include "MainState.h"
#include "Object.h"
#include <time.h>
#include "DebugDraw.h"
#include <iterator>
#include <sstream>
#include <string.h>
#include <stdio.h>
#include <fstream>
#ifdef __unix__ 
#include <unistd.h>
#elif defined(_WIN32) || defined(WIN32)
#include <windows.h>
#endif
#include <chrono>


using namespace std::chrono;
MainState *MainState::m_instance = NULL;
const double PI = 3.141592653589793238463;

class WordDelimitedByCommas : public std::string
{
};

MainState* MainState::GetInstance()
{
	if (m_instance == NULL)
	{
		m_instance = new MainState();
	}
	return m_instance;
}

void MainState::Destroy()
{
	if (m_instance)
	{
		delete m_instance;
	}
}

int MainState::GetResult()
{
	if( m_scoreTeamA > m_scoreTeamB )
	{
		return 3;
	}
	else if ( m_scoreTeamA < m_scoreTeamB )
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

string MainState::GetResultString()
{
	char buffer[128];
	sprintf(buffer, "%d - %d", m_scoreTeamA, m_scoreTeamB);
	return buffer;
}


MainState::MainState()
{
	map = new Map( WIDTH, HEIGH );
	//ball->GetInstance();
	ball = new Ball();
	ball->init( 0, 0 );
	for( int i = 0; i < MAX_FB; i++ )
	{
		teamA[i].init( 0, 0 );
		teamA[i].SetMap( *map );
		teamB[i].init( 0, 0 );
		teamB[i].SetMap( *map );
	}
	m_isFinishMatch = false;
}


MainState::~MainState()
{
	delete ball;
	delete map;
}

void MainState::init()
{
	//ifstream file( "test.bin", ios::binary | ios::in );
	//if( file.is_open() )
	//{
	//	//file.read()
	//	int number;
	//	do
	//	{
	//		file.read( reinterpret_cast<char*>( &number ), sizeof( int ) );
	//		printf( "\nturn:%d ", number );
	//		file.read( reinterpret_cast<char*>( &number ), sizeof( int ) );
	//		printf( "scoreA:%d ", number );
	//		file.read( reinterpret_cast<char*>( &number ), sizeof( int ) );
	//		printf( "scoreB:%d ", number );
	//		file.read( reinterpret_cast<char*>( &number ), sizeof( int ) );
	//		printf( "state:%d ", number );
	//		file.read( reinterpret_cast<char*>( &number ), sizeof( int ) );
	//		printf( "ballX:%d ", number );
	//		file.read( reinterpret_cast<char*>( &number ), sizeof( int ) );
	//		printf( "ballY:%d ", number );
	//		file.read( reinterpret_cast<char*>( &number ), sizeof( int ) );
	//		printf( "ballSpeedX:%d ", number );
	//		file.read( reinterpret_cast<char*>( &number ), sizeof( int ) );
	//		printf( "ballSpeedY:%d ", number );
	//		bool m_isHit;
	//		file.read( reinterpret_cast<char*>( &m_isHit ), sizeof( bool ) );
	//		printf( "m_isHit:%d ", m_isHit );
	//		file.read( reinterpret_cast<char*>( &m_isHit ), sizeof( bool ) );
	//		printf( "isHitWall:%d ", m_isHit );
	//		double percentHit;
	//		file.read( reinterpret_cast<char*>( &percentHit ), sizeof( double ) );
	//		printf( "isHitWall:%ld ", percentHit );
	//		printf ("Team A: ");
	//		for( int i = 0; i < MAX_FB; i++ )
	//		{
	//			file.read( reinterpret_cast<char*>( &number ), sizeof( int ) );
	//			printf( "i:%d ", number );
	//			file.read( reinterpret_cast<char*>( &number ), sizeof( int ) );
	//			printf( "posX:%d ", number );
	//			file.read( reinterpret_cast<char*>( &number ), sizeof( int ) );
	//			printf( "posY:%d ", number );
	//			double direction;
	//			file.read( reinterpret_cast<char*>( &direction ), sizeof( double ) );
	//			printf( "direction:%ld ", direction );
	//			file.read( reinterpret_cast<char*>( &number ), sizeof( int ) );
	//			printf( "state:%d ", number );
	//		}
	//		//team B
	//		printf( "Team B: " );
	//		for( int i = 0; i < MAX_FB; i++ )
	//		{
	//			file.read( reinterpret_cast<char*>( &number ), sizeof( int ) );
	//			printf( "i:%d ", number );
	//			file.read( reinterpret_cast<char*>( &number ), sizeof( int ) );
	//			printf( "posX:%d ", number );
	//			file.read( reinterpret_cast<char*>( &number ), sizeof( int ) );
	//			printf( "posY:%d ", number );
	//			double direction;
	//			file.read( reinterpret_cast<char*>( &direction ), sizeof( double ) );
	//			printf( "direction:%ld ", direction );
	//			file.read( reinterpret_cast<char*>( &number ), sizeof( int ) );
	//			printf( "state:%d ", number );
	//		}
	//	} while ( true );
	//	//int iconB;
	//	//file.read( reinterpret_cast<char*>( &iconB ), sizeof( int ) );
	//	//printf( "\nnameB:%d", iconB );
	//	file.close();
	//}
	//string turn = std::to_string( m_turn );
	//m_fileNameBin = m_path;
	milliseconds ms = duration_cast< milliseconds >(system_clock::now().time_since_epoch());
	m_fileNameBin = m_nameTeamA;
	m_fileNameBin += "_";
	m_fileNameBin += m_nameTeamB;
	m_fileNameBin += "_";
	//m_fileNameBin += std::to_string( time( 0 ) );
	m_fileNameBin += std::to_string( ms.count() );
	m_fileNameBin += ".bin";
	int matchTurn = TURN_PER_MATCH * 2;
	int matchExtra = TURN_EXTRA_MATCH;
	std::ofstream m_outfileBin( m_path + m_fileNameBin, ios::app | ios::binary );
	m_outfileBin.write( (char*)&matchTurn, sizeof( int ) );
	m_outfileBin.write( (char*)&matchExtra, sizeof( int ) );
	m_outfileBin.close();
	Input_data();

	//player_1->init(1, data_pl1);
	//player_2->init(2, data_pl2);
	m_turn = 0;
	Position initPos = { map->GetWidth() / 2 , map->GetHeigh() / 2 };
	ball->init( initPos.x, initPos.y );
	
	ball->SetAcc( BALL_ACC_SPEED );

#ifdef CHECK_MODE_FROM_FILE
	if (m_GameModeFromFileConfig == 2)
	{
		m_isPenalty = true;
		m_resetPenalty = true;
		m_turn = TURN_PER_MATCH * 2 + TURN_EXTRA_MATCH;
	}
	else if (m_GameModeFromFileConfig == 1)
	{
		m_turn = TURN_PER_MATCH * 2;
	}
#endif // CHECK_MODE_FROM_FILE
	
	if( !m_isUserInput )
	{
		for( int i = 0; i < MAX_FB; i++ )
		{
			teamA[i].init( map->GetWidth() / 2,0);
			teamB[i].init( map->GetWidth() / 2,0);
		}
	}
	else
	{
		cout << "START !!!!";

		string clientInput;
		getline(std::cin, clientInput);
		cerr << "Init players infos: " << clientInput;

		//@TODO: Init map then send 
		//string playersA = GetDefautlTeam(map->GetWidth(), map->GetHeigh());
		//string playersB = GetDefautlTeam(map->GetWidth(), map->GetHeigh());
		//clientInput = playersA+ "#" + playersB + "#khoi tao doi hinh";
		//cerr << clientInput << endl;
		//133 120 266 120 133 240 133 360 266 360  #667 360 534 360 667 240 667 120 534 120 #khoi tao doi hinh
		m_isUserInputinform = GetInputInform( clientInput );
		InitInformation(true);
	}
	m_time = time( NULL );
	srand(m_time);
//#ifdef MODE_PENALTY
	//m_isPenalty = true;
	//m_resetPenalty = true;
//#endif
	Out_data();

}

void MainState::SetGameModeFromFileConfig(int m_GameConfig)
{	
	m_GameModeFromFileConfig = m_GameConfig;
}

void MainState::SetGameShortMode()
{
	TURN_PER_MATCH = TURN_PER_MATCH_ORIGINAL / 2;
	TURN_EXTRA_MATCH = TURN_EXTRA_MATCH_ORIGINAL / 2;
}

void MainState::SetTeamDefault( int teamID )
{
	if( teamID == 0 )
	{
		m_dataInputInitA.clear();
		//xuan.maithanh updated the Team Information to be : 3 midfielders + 2 defenders
		m_dataInputInitA.push_back(map->GetWidth() / 3);
		m_dataInputInitA.push_back(map->GetHeigh() / 2);
		m_dataInputInitA.push_back(map->GetWidth() / 3);
		m_dataInputInitA.push_back(map->GetHeigh() / 4);
		m_dataInputInitA.push_back(map->GetWidth() / 3);
		m_dataInputInitA.push_back(map->GetHeigh() / 4 * 3);
		m_dataInputInitA.push_back(map->GetWidth() / 6);
		m_dataInputInitA.push_back(map->GetHeigh() / 4);
		m_dataInputInitA.push_back(map->GetWidth() / 6);
		m_dataInputInitA.push_back(map->GetHeigh() / 4 * 3);
	}
	else
	{
		m_dataInputInitB.clear();
		//xuan.maithanh updated the Team Information to be : 3 midfielders + 2 defenders
		m_dataInputInitB.push_back(map->GetWidth() / 3);
		m_dataInputInitB.push_back(map->GetHeigh() / 2);
		m_dataInputInitB.push_back(map->GetWidth() / 3);
		m_dataInputInitB.push_back(map->GetHeigh() / 4);
		m_dataInputInitB.push_back(map->GetWidth() / 3);
		m_dataInputInitB.push_back(map->GetHeigh() / 4 * 3);
		m_dataInputInitB.push_back(map->GetWidth() / 6);
		m_dataInputInitB.push_back(map->GetHeigh() / 4);
		m_dataInputInitB.push_back(map->GetWidth() / 6);
		m_dataInputInitB.push_back(map->GetHeigh() / 4 * 3);
	}
}

void MainState::InitInformation(bool isTeamAFirst )
{
	if( !m_isUserInput )
	{
		for( int i = 0; i < MAX_FB; i++ )
		{
			teamA[i].init( map->GetWidth() / 2, 0 );
			teamB[i].init( map->GetWidth() / 2, 0 );
		}
	}
	else
	{
		bool isValidTeamA = true;
		bool isValidTeamB = true;
		Position posCenterMap;
		posCenterMap.x = map->GetWidth() / 2;
		posCenterMap.y = map->GetHeigh() / 2;
		if( m_turn < TURN_PER_MATCH || m_turn >= TURN_PER_MATCH * 2 )
		{
			for( int i = 0; i < MAX_FB; i++ )
			{
				if (m_dataInputInitA[i * 2] < 0 || m_dataInputInitA[i * 2] > map->GetWidth() / 2 || m_dataInputInitA[i * 2 + 1] < 0 || m_dataInputInitA[i * 2 + 1] >  map->GetHeigh())
				{
					isValidTeamA = false;
				}
				if( m_dataInputInitB[i * 2] <  0 || m_dataInputInitB[i * 2] > map->GetWidth() / 2 || m_dataInputInitB[i * 2 + 1] < 0 || m_dataInputInitB[i * 2 + 1] >  map->GetHeigh())
				{
					isValidTeamB = false;
				}
				if ( isValidTeamA )
					teamA[i].init( m_dataInputInitA[i * 2], m_dataInputInitA[i * 2 + 1] );
				if ( isValidTeamB )
					teamB[i].init( map->GetWidth() - m_dataInputInitB[i * 2], map->GetHeigh() - m_dataInputInitB[i * 2 + 1] );
			}
		}
		else
		{
			for( int i = 0; i < MAX_FB; i++ )
			{
				if( m_dataInputInitA[i * 2] < 0 || m_dataInputInitA[i * 2] > map->GetWidth() / 2 || m_dataInputInitA[i * 2 + 1] < 0 || m_dataInputInitA[i * 2 + 1] >  map->GetHeigh())
				{
					isValidTeamA = false;
				}
				if( m_dataInputInitB[i * 2] < 0 || m_dataInputInitB[i * 2] > map->GetWidth() / 2 || m_dataInputInitB[i * 2 + 1] < 0 || m_dataInputInitB[i * 2 + 1] >  map->GetHeigh())
				{
					isValidTeamB = false;
				}
				teamB[i].init( m_dataInputInitB[i * 2], m_dataInputInitB[i * 2 + 1] );
				teamA[i].init( map->GetWidth() - m_dataInputInitA[i * 2], map->GetHeigh() - m_dataInputInitA[i * 2 + 1] );
			}
		}
		if( isTeamAFirst )
		{
			for( int i = 0; i < MAX_FB; i++ )
			{
				if (GetDistance( posCenterMap, teamB[i].get_position() ) < RADIUS_CENTER)
				{
					isValidTeamB = false;
				}
			}
		} 
		else
		{

			for( int i = 0; i < MAX_FB; i++ )
			{
				if( GetDistance( posCenterMap, teamA[i].get_position() ) < RADIUS_CENTER )
				{
					isValidTeamA = false;
				}
			}
		}
		if( !isValidTeamA )
		{
			SetTeamDefault( 0 );
		}
		if ( !isValidTeamB )
		{

			SetTeamDefault( 1 );
		}
		if ( !isValidTeamB || !isValidTeamA )
		{
			InitInformation( isTeamAFirst );
		}
		int playerNearBall = 0;
		float distancePlayer = 0.0f;
		if ( isTeamAFirst )
		{
			distancePlayer = GetDistance( teamA[0].get_position(), posCenterMap );
			for( int i = 1; i < MAX_FB; i++ )
			{
				float distance = GetDistance( teamA[i].get_position(), posCenterMap );
				if ( distance < distancePlayer )
				{
					playerNearBall = i;
					distancePlayer = distance;
				}
			}
			teamA[playerNearBall].init( map->GetWidth() / 2, map->GetHeigh() / 2 );
		}
		else
		{
			distancePlayer = GetDistance( teamB[0].get_position(), posCenterMap );
			for( int i = 1; i < MAX_FB; i++ )
			{
				float distance = GetDistance( teamB[i].get_position(), posCenterMap );
				if( distance < distancePlayer )
				{
					playerNearBall = i;
					distancePlayer = distance;
				}
			}
			teamB[playerNearBall].init( map->GetWidth() / 2, map->GetHeigh() / 2 );
		}
	}
}

float MainState::GetDistance( Position pos1, Position pos2 )
{
	return sqrt( pow( pos1.x - pos2.x, 2 ) + pow ( pos1.y - pos2.y, 2 ) );
}

bool MainState::GetInputInform( string textInput )
{
	m_dataInputInitA.clear();
	m_dataInputInitB.clear();
	vector<string> tokens;
	string token;
	istringstream tokenStream( textInput );
	while( getline( tokenStream, token, '#' ) )
	{
		tokens.push_back( token.c_str() );
	}
	string userA = tokens.at( 0 );
	string userB = tokens.at( 1 );
	if (userA == "E101")
	{
		userA = GetDefautlTeam(map->GetWidth(), map->GetHeigh());
	}
	//init playerA pos
	{
		vector<string> tokens;
		string token;
		istringstream tokenStream(userA);
		while (getline(tokenStream, token, ' '))
		{
			m_dataInputInitA.push_back(atoi(token.c_str()));
		}
	}

	if (userB == "E201")
	{
		userB = GetDefautlTeam(map->GetWidth(), map->GetHeigh());
	}
	{
		vector<string> tokens;
		string token;
		istringstream tokenStream( userB );
		while( getline( tokenStream, token, ' ' ) )
		{
			m_dataInputInitB.push_back( atoi( token.c_str() ) );
		}
	}
	if( token.length() > 2 )
		m_log = token.at( 2 );
	return true;
}

void MainState::ConfigBot( char* nameTeamA, char* nameTeamB, int id1, int id2, string path ,bool isExtraTime )
{
	m_nameTeamA = nameTeamA;
	m_nameTeamB = nameTeamB;
	m_iconTeamA = id1;
	m_iconTeamB = id2;
	m_path = path;
	m_isPlayExtraTime = isExtraTime;
}

string MainState::GetDefautlTeam( int mapW, int mapH, int teamID)
{
	//teamID == 0: Team A
	char DefaultTeamBuffer[250];
	//if(teamID == 0)
		sprintf(DefaultTeamBuffer, "%d %d %d %d %d %d %d %d %d %d  ", mapW / 6, mapH / 4, mapW / 3, mapH / 4, mapW / 6, mapH / 2, mapW / 6, 3 * mapH / 4, mapW / 3, 3 * mapH / 4);
	//else
		//sprintf(DefaultTeamBuffer, "%d %d %d %d %d %d %d %d %d %d ", mapW / 6, mapH / 4, mapW - mapW / 3, mapH - mapH / 4, mapW - mapW / 6, mapH / 2, mapW - mapW / 6, mapH - 3 * mapH / 4, mapW - mapW / 3, mapH - 3 * mapH / 4);

	return DefaultTeamBuffer;
}

void MainState::update()
{
int m_time_sleep = 1;
#ifdef __unix__ 	
	m_time_sleep = 0;
	sleep(m_time_sleep);
#elif defined(_WIN32) || defined(WIN32)
	#ifdef DEBUG_SERVER
		m_time_sleep = 100;
	#endif
	Sleep(m_time_sleep);
#endif
	if ( !m_isFinishMatch )
	{
		//m_deltaTime = time( NULL ) - m_time;
		m_isHit = false;
		m_turn++;
		if ( m_isScore || m_resetPenalty )
		{
			//just read and ignore AI msg
			string clientInput;
			getline(std::cin, clientInput);
			cerr << "Server ignore read: " << clientInput;
			if ( !m_resetPenalty )
			{
				ball->ResetBall();
				Position initPos = { map->GetWidth() >> 1 , map->GetHeigh() / 2 };
				ball->init( initPos.x, initPos.y );
				if( false )
				{
					for( int i = 0; i < MAX_FB; i++ )
					{
						teamA[i].init( map->GetWidth() / 2, 0 );
						teamB[i].init( map->GetWidth() / 2, 0 );
					}
				}
				else
				{
					if( m_turn < TURN_PER_MATCH )
						InitInformation( !m_isTeamAScore );
					else
						InitInformation( m_isTeamAScore );
				}
				m_isScore = false;
			}
			else
			{
				m_isPlayerShootPen = false;
				m_turnBeginPen = m_turn;
				m_totalPen++;
				for( int i = 1; i < MAX_FB; i++ )
				{
					int offset = 400;
					teamA[i].init( map->GetWidth() >> 1, ( map->GetHeigh() >> 1 ) - offset * i );
					teamB[i].init( map->GetWidth() >> 1, ( map->GetHeigh() >> 1 ) + offset * i );
					ball->ResetBall();
					Position initPos = { PENALTY_POINT , map->GetHeigh() / 2 };
					ball->init( initPos.x, initPos.y );
				}
				if ( m_isTeamAPenalty )
				{
					teamA[0].init( PENALTY_POINT + 150, map->GetHeigh() >> 1 );
					teamB[0].init( 0, map->GetHeigh() >> 1 );
				}
				else
				{
					teamB[0].init( PENALTY_POINT + 150, map->GetHeigh() >> 1 );
					teamA[0].init( 0, map->GetHeigh() >> 1 );
				}
				m_resetPenalty = false;
			}
		}
		else
		{
			
		//Random AI
	#ifdef DEBUG_SERVER
			if ( m_isUserInput )
	#else
			if( true )
	#endif
			{
				string clientInput;
				//std::cin >> clientInput;
				getline(std::cin, clientInput);
				cerr << "Server read: " << clientInput;
				//clientInput = "1 2 4 5 1 58 38 10 1 11 5 20 1 229 188 0 2 259 395 100#1 7 88 30 1 48 38 5 1 131 5 0 1 29 188 4 1 259 33 9#Day la log cua portal";
				if( GetInputData( clientInput ) )
				{
					for( int i = 0; i < MAX_FB; i++ )
					{
						int count = i * FILE_INPUT_STEP;
						if( m_isPenalty && i > 0)
						{
							continue;
						}
						bool isTeamAPenalty = m_isPenalty && m_isTeamAPenalty;
						bool isTeamBPenalty = m_isPenalty && !m_isTeamAPenalty;
						if ( m_dataInputA.size() == 20 )
						{
							int actionA = m_dataInputA.at( count );
							switch( actionA )
							{
							case Action::FREEZE:
								{
									teamA[i].SetState(Action::FREEZE);
									break;
								}
							case Action::RUN:
								{
									if( ( isTeamBPenalty && ball->GetSpeedX() == 0 && ball->GetSpeedY() == 0 ) || isTeamAPenalty )
									{
										break;
									}
									Position target = { m_dataInputA.at( count + 1 ) , m_dataInputA.at( count + 2) };
									teamA[i].SetTarget( target );
									break;
								}
								case Action::SHOOT:
								{
									if( isTeamAPenalty )
									{
										if( !m_isPlayerShootPen )
										{
											m_isPlayerShootPen = m_isPlayerShootPen;
										}
										else
										{
											break;
										}
									}
									Position target = { m_dataInputA.at( count + 1 ) , m_dataInputA.at( count + 2 ) };
									teamA[i].Shoot( ball->get_position(), m_dataInputA.at( count + 3 ) , teamA[i].get_position() , target );
									break;
								}
								default:
									break;
							}
						}
						count = i * FILE_INPUT_STEP;
						if( m_dataInputB.size() == 20 )
						{
							int actionB = m_dataInputB.at( count );
							switch( actionB )
							{
								case Action::FREEZE:
								{
									teamB[i].SetState(Action::FREEZE);
									break;
								}
								case Action::RUN:
								{
									if (( isTeamAPenalty &&  ball->GetSpeedX()==0 && ball->GetSpeedY()==0  ) || isTeamBPenalty)
									{
										break;
									}
									Position target = { m_dataInputB.at( count + 1 ) , m_dataInputB.at( count + 2 ) };
									teamB[i].SetTarget( target );
									break;
								}
								case Action::SHOOT:
								{
									if( isTeamBPenalty )
									{
										if( !m_isPlayerShootPen )
										{
											m_isPlayerShootPen = m_isPlayerShootPen;
										}
										else
										{
											break;
										}
									}
									Position target = { m_dataInputB.at( count + 1 ) , m_dataInputB.at( count + 2 ) };
									teamB[i].Shoot( ball->get_position(), m_dataInputB.at( count + 3 ), teamB[i].get_position(), target );
									break;
								}
								default:
									break;
							}
						}
					}
				}
			}
			else
			{
				//int i =0;
				for( int i = 0; i < MAX_FB; i++ )
				{
					int count = i * FILE_INPUT_STEP;
					if( m_isPenalty && i > 0 )
					{
						continue;
					}
					bool isTeamAPenalty = m_isPenalty && m_isTeamAPenalty;
					bool isTeamBPenalty = m_isPenalty && !m_isTeamAPenalty;
					//printf("\nPlayer : %d",i);
					if( teamA[i].CanBeShoot( ball->get_position() ) )
					{
						if( !isTeamAPenalty || !m_isPlayerShootPen )
						{
							int force = Rand( 0, 100 );
							double radian = Rand (0 , 627) / 100;
							teamA[i].Shoot( ball->get_position(), force, radian );
						}
					}
					else if( teamA[i].GetDirection() == 0 && !isTeamAPenalty )
					{
						int posX = Rand( 0, map->GetWidth() );
						int posY = Rand( 0, map->GetHeigh() );
						/*printf( "\nteamA:%d", i );
						printf("\nposX:%d" , posX );
						printf( "\nposy:%d" , posY );*/
						Position target = { posX,posY };
						teamA[i].SetTarget( target );
					}
			
					if( teamB[i].CanBeShoot( ball->get_position() ) )
					{
						if( !isTeamBPenalty || !m_isPlayerShootPen )
						{
							int force = Rand( 0, 300 );
							double radian = Rand( 0, 627 ) / 100;
							teamB[i].Shoot( ball->get_position(), force, radian );
						}
					}
					else if( teamB[i].GetDirection() == 0 && !isTeamBPenalty )
					{
						int posX = Rand( 0, map->GetWidth() );
						int posY = Rand( 0, map->GetHeigh() );
						Position target = { posX,posY };
						teamB[i].SetTarget( target );
					}
				}
			}
			
			int totalForced = 0;
			int totalPlayerShoot = 0;
			double totalDirection = 0;
			for( int i = 0; i < MAX_FB; i++ )
			{
				teamA[i].update();
				teamB[i].update();
				int totalForcedTemp = totalForced;
				if( teamA[i].GetForceToShoot() != 0 )
				{
					m_isHit = true;
					//double GetDirectionToShoot = teamA[i].GetDirectionToShoot();
					totalForced = sqrt( pow( totalForced, 2 ) + pow( teamA[i].GetForceToShoot(), 2 ) + 2 * totalForced  * teamA[i].GetForceToShoot() * cos( totalDirection - teamA[i].GetDirectionShootPI() ) );
					if( totalDirection == 0 )
					{
						totalDirection = teamA[i].GetDirectionShootPI();
						totalPlayerShoot++;
					}
					else if( fabs(fabs (totalDirection - teamA[i].GetDirectionShootPI()) - PI) < 0.001  )
					{
						totalDirection = totalForced > teamA[i].GetForceToShoot() ? totalDirection : teamA[i].GetDirectionShootPI();
					}
					else
					{
						//double directionMin = totalDirection > teamA[i].GetDirectionShootPI() ? teamA[i].GetDirectionShootPI() : totalDirection;
						//double directionMax = totalDirection > teamA[i].GetDirectionShootPI() ? totalDirection : teamA[i].GetDirectionShootPI();
						double forceA = totalForcedTemp * totalDirection;
						double forceB = teamA[i].GetDirectionShootPI() * teamA[i].GetForceToShoot();
						totalDirection = ( forceA + forceB ) / ( totalForcedTemp + teamA[i].GetForceToShoot() ) ;
						totalPlayerShoot++;
					}
					//teamA[i].ResetState();
				}
				totalForcedTemp = totalForced;
				if( teamB[i].GetForceToShoot() != 0 )
				{
					m_isHit = true;
					totalForced = sqrt( pow( totalForced, 2 ) + pow( teamB[i].GetForceToShoot(), 2 ) + 2 * totalForced  * teamB[i].GetForceToShoot() * cos( totalDirection - teamB[i].GetDirectionShootPI() ) );
					if( totalDirection == 0 )
					{
						totalDirection = teamB[i].GetDirectionShootPI();
						totalPlayerShoot++;
					}
					else if( fabs( fabs( totalDirection - teamB[i].GetDirectionShootPI() ) - PI ) < 0.001 )
					{
						totalDirection = totalForced > teamB[i].GetForceToShoot() ? totalDirection : teamB[i].GetDirectionShootPI();
					}
					else
					{
						/*double directionMin = totalDirection > teamB[i].GetDirectionShootPI() ? teamB[i].GetDirectionShootPI() : totalDirection;
						double directionMax = totalDirection > teamB[i].GetDirectionShootPI() ? totalDirection : teamB[i].GetDirectionShootPI();
						totalDirection = directionMin + ( directionMin / directionMax ) * ( directionMax - directionMin );*/
						double forceA = totalForcedTemp * totalDirection;
						double forceB = teamB[i].GetDirectionShootPI() * teamB[i].GetForceToShoot();
						totalDirection = ( forceA + forceB ) / ( totalForcedTemp + teamB[i].GetForceToShoot() );
						totalPlayerShoot++;
					}
					//teamB[i].ResetState();
				}
			}
			if( totalPlayerShoot > 0 )
			{
				ball->SetDirection( totalDirection, totalForced);
			}
			ball->update();
			ball->CheckCollsionWall( map );
			/*
			if( teamA[0].CanBeShoot( ball->get_position() ) )
			{
				int force = Rand( 0, 100 );
				teamA[0].Shoot( ball->get_position(), force, 0.5 );
			}
			else if( teamA[0].GetDirection() == 0 )
			{
				int posX = Rand( 0, map->GetWidth() );
				int posY = Rand( 0, map->GetHeigh() );
				Position target = {posX,posY};
				teamA[0].SetTarget( target );
			}
			*/
			
			if( ball->IsInGoal() )
			{
				if( m_isPenalty )
				{
					m_resetPenalty = true;
					
					if ( m_isTeamAPenalty )
					{
						m_scoreTeamA++;
					}
					else
					{
						m_scoreTeamB++;
					}
					m_isTeamAPenalty = !m_isTeamAPenalty;
				}
				else
				{
					m_isTeamAScore = ball->IsTeamAScore();
					if( m_turn <= TURN_PER_MATCH )
					{
						if( m_isTeamAScore )
						{
							m_scoreTeamA++;
						}
						else
						{
							m_scoreTeamB++;
						}
					}
					else
					{
						if( m_isTeamAScore )
						{
							m_scoreTeamB++;
						}
						else
						{
							m_scoreTeamA++;
						}
					}

					m_isScore = true;
				}
			} 
			else if( m_isPenalty )
			{
				if( ( ball->GetSpeedX() > 0 || ball->GetSpeedX() == 0 ) && ( m_turn - m_turnBeginPen > TURN_PER_PEN ) )
				{
					m_resetPenalty = true;
					m_isTeamAPenalty = !m_isTeamAPenalty;
				}
			}
			if( m_turn >= 2 * TURN_PER_MATCH )
			{
				if ((m_scoreTeamA != m_scoreTeamB && !m_isPenalty ) || !m_isPlayExtraTime)
				{
					m_isFinishMatch = true;
				}
				else if (m_turn == ( 2 * TURN_PER_MATCH + TURN_EXTRA_MATCH ) )
				{
					m_isPenalty = true;
					m_resetPenalty = true;
				}
			}
			if ( m_turn == TURN_PER_MATCH )
			{
				ball->ResetBall();
				Position initPos = { map->GetWidth() >> 1 , map->GetHeigh() / 2 };
				ball->init( initPos.x, initPos.y );
				if( !m_isUserInput )
				{
					for( int i = 0; i < MAX_FB; i++ )
					{
						teamA[i].init( map->GetWidth() / 2, 0 );
						teamB[i].init( map->GetWidth() / 2, 0 );
					}
				}
				else
				{
					InitInformation(false);
				}
			}
		}
		if( m_isRandomPlayer )
		{
			int rand =  Rand( 0, 9 );
			if( rand % 2 == 0 )
			{
				m_scoreTeamA++;
			}
			else
			{
				m_scoreTeamB++;
			}
			m_isFinishMatch = true;
		}
		if( m_resetPenalty && m_totalPen >= NUMBER_PENALTY && m_totalPen %2 == 0 )
		{
			if ( m_scoreTeamA != m_scoreTeamB )
			{
				m_isFinishMatch = true;
			}
			else if (m_totalPen >= ( NUMBER_PENALTY + EXTRA_PENALTY) )
			{
				if( m_scoreTeamA != m_scoreTeamB )
				{
					m_isFinishMatch = true;
				}
				else
				{
					m_isRandomPlayer = true;
				}
			}
		}
		for( int i = 0; i < MAX_FB; i++ )
		{
			if( teamA[i].GetForceToShoot() != 0 )
			{
				teamA[i].ResetState();
			}
			if( teamB[i].GetForceToShoot() != 0 )
			{
				teamB[i].ResetState();
			}
		}
	
	}


	Out_data();

	//test bin
	/*ifstream file( m_fileNameBin, ios::binary | ios::in );
	if( file.is_open() )
	{
		char nameA[100];
		file.read( nameA, 100);
		printf("\nnameA:%s", nameA );
		char nameB[100];
		file.read( nameB, 100 );
		printf( "\nnameB:%s", nameB );
		int iconA;
		file.read( reinterpret_cast<char*>( &iconA ), sizeof(int) );
		printf( "\nnameA:%d", iconA );
		int iconB;
		file.read( reinterpret_cast<char*>( &iconB ), sizeof( int ) );
		printf( "\nnameB:%d", iconB );
		file.close();
	}*/
	/*ifstream myReadFile;
	myReadFile.open( "client.txt" );
	if( myReadFile.is_open() )
	{
		string out;
		while( !myReadFile.eof() )
		{
			getline( myReadFile , out);
			printf("AAAA:%s",out);
		}
	}*/
	
	
}

bool MainState::GetInputData(string textInput )
{
	m_dataInputA.clear();
	m_dataInputB.clear();
	vector<string> tokens;
	string token;
	istringstream tokenStream( textInput );
	while( getline( tokenStream, token, '#' ) )
	{
		tokens.push_back( token.c_str() );
	}
	string userA = tokens.at( 0 );
	string userB = tokens.at( 1 );
	if( userA != "E101" )
	{
		vector<string> tokens;
		string token;
		istringstream tokenStream( userA );
		while( getline( tokenStream, token, ' ' ) )
		{
			m_dataInputA.push_back( atoi(token.c_str()) );
		}
	}
	if( userB != "E201" )
	{
		vector<string> tokens;
		string token;
		istringstream tokenStream( userB );
		while( getline( tokenStream, token, ' ' ) )
		{
			m_dataInputB.push_back( atoi( token.c_str() ) );
		}
	}
	if(token.length() > 2)
		m_log = token.at(2);
	return true;
}

int MainState::Rand( int min, int max )
{
	//srand( time( NULL ) );
	return min + rand() % (max - min) ;
}

void MainState::end()
{

}

Ball MainState::GetBall()
{
	return *ball;
}

void MainState::Input_data()
{
	//read data_pl1 & data_pl2
}

string MainState::GetFileName()
{
	return m_fileNameBin;
}

bool MainState::IsFinishMatch()
{
	return m_isFinishMatch;
}

void MainState::Out_data()
{
	//Server send to Bot each turn :
	//[Turn] [m_scoreTeamA] [m_scoreTeamB] [stateMath] [ballPosX] [ballPosY] [ballSpeedX] [ballSpeedY] [Player1_Team1] [Player1_Team1_posX] [Player1_Team1_posY] ...[Player1_Team2][Player1_Team2_posX][Player1_Team2_posY]...[Player1_Team2][Player5_Team2_posX][Player5_Team2_posY]
	
	//ofstream outfile;
	//std::ofstream m_outfileBin( m_fileName , ios::app | ios::binary );
	//outfile << " more lorem ipsum";

	//write data player1, player2 & ball to control
	//if ( m_outfile && !m_isWriteBinary )
	{
		string strOutputFile = " ";
		string serverOutPut = "";

		string turnTeamBall = "";
		char buffer[128];
		if (!m_isPenalty || m_totalPen == 0)
			sprintf(buffer, "%d %d %d", m_turn, m_scoreTeamA, m_scoreTeamB);
		else
			sprintf( buffer, "%d %d %d", ((m_totalPen - 1)%2), m_scoreTeamA, m_scoreTeamB );
		turnTeamBall += buffer;
//#ifdef MODE_PENALTY
		//if( m_isPenalty )
		//{
			//turnTeamBall += " 4";
		//}
		//else
//#endif
		if( m_turn < TURN_PER_MATCH )
		{
			turnTeamBall += " 1";
		}
		else if ( m_turn <= TURN_PER_MATCH * 2 )
		{
			turnTeamBall += " 2";
		}
		else if( !m_isPenalty || m_totalPen == 0 )
		{
			turnTeamBall += " 3";
		}
		else
		{
			turnTeamBall += " 4";
		}
		serverOutPut += turnTeamBall;
		strOutputFile += turnTeamBall;

		sprintf(buffer, " %d %d %d %d", ball->get_position().x, ball->get_position().y, ball->GetSpeedX(), ball->GetSpeedY());
		serverOutPut += buffer;
		strOutputFile += buffer;

		sprintf(buffer, " %d %d %f", m_isHit, ball->IsHitWall(), ball->GetPercentHit());
		strOutputFile += buffer;

		for( int i = 0; i < MAX_FB; i++ )
		{
			char buffer[128];
			sprintf(buffer, " %d %d %d", i, teamA[i].get_position().x, teamA[i].get_position().y);
			serverOutPut += buffer;
			strOutputFile += buffer;
			
			sprintf(buffer, " %.2f %d", teamA[i].GetDirectionAlpha(), teamA[i].GetState());
			strOutputFile += buffer;
		}

		for( int i = 0; i < MAX_FB; i++ )
		{
			char buffer[128];
			sprintf(buffer, " %d %d %d", i, teamB[i].get_position().x, teamB[i].get_position().y);
			serverOutPut += buffer;
			strOutputFile += buffer;

			sprintf(buffer, " %.2f %d", teamB[i].GetDirectionAlpha(), teamB[i].GetState());
			strOutputFile += buffer;
		}
		
		cout << serverOutPut;
		if (!m_isUserInput) cout << endl;
		//cerr << serverOutPut; 

#ifndef DEBUG_SERVER
		std::ofstream m_outfile(m_fileName, ios::app | ios::binary);
		m_outfile << strOutputFile;
		m_outfile.close();
#endif

	}
#ifndef DEBUG_SERVER
	//else if ( m_outfile )
	{
		std::ofstream m_outfileBin( m_path + m_fileNameBin, ios::app | ios::binary );
		//match
		m_outfileBin.write( (char*)&m_turn, sizeof( int ) );
		m_outfileBin.write( (char*)&m_scoreTeamA, sizeof( int ) );
		m_outfileBin.write( (char*)&m_scoreTeamB, sizeof( int ) );
		int typeMatch = 0;
		if( m_turn < TURN_PER_MATCH )
		{
			typeMatch = 1;
		}
		else if( m_isFinishMatch )
		{
			typeMatch = 6;
		}
		else if( m_isRandomPlayer )
		{
			typeMatch = 5;
		}
		else if( m_turn <= TURN_PER_MATCH * 2 )
		{
			typeMatch = 2;
		}
		else if (!m_isPenalty || m_totalPen == 0 )
		{
			typeMatch = 3;
		}
		else
		{
			typeMatch = 4;
		}
		m_outfileBin.write( (char*)&typeMatch, sizeof( int ) );
		/*int numberPen = 0;
		if ( typeMatch == 3 )
		{
			numberPen = 0;
		}
		else
		{
			numberPen = m_totalPen + 1;
		}*/
		m_outfileBin.write( (char*)&m_totalPen, sizeof( int ) );
		//ball
		int ballX = ball->get_position().x;
		int ballY = ball->get_position().y;
		int ballSpeedX = ball->GetSpeedX();
		int ballSpeedY = ball->GetSpeedY();
		bool isHitWall = ball->IsHitWall();
		double percentHit = ball->GetPercentHit();
		m_outfileBin.write( (char*)&ballX, sizeof( int ) );
		m_outfileBin.write( (char*)&ballY, sizeof( int ) );
		m_outfileBin.write( (char*)&ballSpeedX, sizeof( int ) );
		m_outfileBin.write( (char*)&ballSpeedY, sizeof( int ) );
		m_outfileBin.write( (char*)&m_isHit, sizeof( bool ) );
		m_outfileBin.write( (char*)&isHitWall, sizeof( bool ) );
		m_outfileBin.write( (char*)&percentHit, sizeof( double ) );
		//team A
		for( int i = 0; i < MAX_FB; i++ )
		{
			int posX = teamA[i].get_position().x;
			int posY = teamA[i].get_position().y;
			int state = teamA[i].GetState();
			double direction = teamA[i].GetDirectionAlpha();
			//player id
			m_outfileBin.write( (char*)&i, sizeof( int ) );
			m_outfileBin.write( (char*)&posX, sizeof( int ) );
			m_outfileBin.write( (char*)&posY, sizeof( int ) );
			m_outfileBin.write( (char*)&direction, sizeof( double ) );
			m_outfileBin.write( (char*)&state, sizeof( int ) );
		}
		//team B
		for( int i = 0; i < MAX_FB; i++ )
		{
			int posX = teamB[i].get_position().x;
			int posY = teamB[i].get_position().y;
			int state = teamB[i].GetState();
			double direction = teamB[i].GetDirectionAlpha();
			//player id
			m_outfileBin.write( (char*)&i, sizeof( int ) );
			m_outfileBin.write( (char*)&posX, sizeof( int ) );
			m_outfileBin.write( (char*)&posY, sizeof( int ) );
			m_outfileBin.write( (char*)&direction, sizeof( double ) );
			m_outfileBin.write( (char*)&state, sizeof( int ) );
		}
		m_outfileBin.close();
	}
#endif
	/*glBegin( GL_LINES );
	glVertex2f( 10, 10 );
	glVertex2f( 20, 20 );
	glEnd();*/
}

Map MainState::GetMap()
{
	return *map;
}

void MainState::Draw()
{
#ifdef DEBUG_SERVER

	b2Vec2 centerMap = { MAP_SIZE / 2.0 , MAP_SIZE / 2.0 };
	float radiusCenterBg = MAP_SIZE / 2.0;
	g_debugDraw.DrawCircle(centerMap, radiusCenterBg, b2Color( 0.9f, 0.9f, 0.9f ) );

	//draw players
	for( int i = 0; i < MAX_FB; i++ )
	{
		b2Color colorTeamA( 0.0f, 1.0f, 0.0f );
		b2Color colorTeamB( 1.0f, 1.8f, 1.9f );

		float radius = CHARACTER_SIZE / 2.f;
		b2Vec2 posA = { float( teamA[i].get_position().x ), float( teamA[i].get_position().y ) };
		g_debugDraw.DrawPlayer(posA, radius, colorTeamA);
		char* nameA = teamA[i].GetName();
		int lengthNameA = teamA[i].GetLength(nameA);
		g_debugDraw.DrawPlayerName({ posA.x - radius - lengthNameA / 2.f * 80 , posA.y - int(CHARACTER_SIZE *1.5) }, nameA, b2Color({0, 255, 255, 255}));
		int playerBloodA = teamA[i].GetBlood();
		g_debugDraw.DrawVisibleRange(posA, VISIBLE_RANGE / 2.f, b2Color({ 255.f, 255.f, 0.f, 0.f }));
		g_debugDraw.DrawBlood({ float(posA.x - CHARACTER_SIZE / 2.f) , float(posA.y + int(CHARACTER_SIZE*1.2)) },
										CHARACTER_BLOOD, playerBloodA, b2Color({ 1.f, 0, 0 }));

		int playerBloodB = teamB[i].GetBlood();
		b2Vec2 posB = { float( teamB[i].get_position().x ), float( teamB[i].get_position().y ) };
		g_debugDraw.DrawPlayer(posB, radius, colorTeamB );
		char* nameB = teamA[i].GetName();
		int lengthNameB = teamA[i].GetLength(nameB);
		g_debugDraw.DrawPlayerName({ posB.x - radius - lengthNameB / 2.f * 80  , posB.y - int(CHARACTER_SIZE *1.5) }, nameB, b2Color({ 0, 255, 255, 255 }));
		g_debugDraw.DrawVisibleRange(posB, VISIBLE_RANGE / 2.f, b2Color({ 255.f, 255.f, 0.f, 0.f }));
		g_debugDraw.DrawBlood({ float(posB.x - CHARACTER_SIZE / 2.f) , float(posB.y + int(CHARACTER_SIZE*1.2)) },
										CHARACTER_BLOOD, playerBloodB, b2Color({ 1.f, 0, 0 }));
	}
#endif // DEBUG_SERVER
}