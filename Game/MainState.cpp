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
const double PI = 3.141592653589793238463;

class WordDelimitedByCommas : public std::string
{
};


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
}


MainState::~MainState()
{
	delete map;
}

void MainState::Init()
{
	map = new Map(WIDTH, HEIGH);

}

void MainState::Update()
{
}

void MainState::Render()
{
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
			}
		}
		if( isTeamAFirst )
		{

		} 
		else
		{

			for( int i = 0; i < MAX_FB; i++ )
			{
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
		}
		else
		{
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


#endif // DEBUG_SERVER
}