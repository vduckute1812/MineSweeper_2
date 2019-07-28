#pragma once

#include "Player.h"
#include "Map.h"
#include <iostream>
#include <fstream>  

class MainState
{
public:
	MainState();
	~MainState();

	void	Init();
	void	Update();
	void	Render();
	bool	IsFinishMatch();

	int		Rand(int min, int max);

	void	end();

	void	Input_data();
	Map		GetMap();
	void	Draw();
	void	InitInformation(bool isTeamAFirst);
	bool	GetInputData( string textInput );
	bool	GetInputInform( string textInput );
	float	GetDistance(Position pos1, Position pos2);
	string	GetFileName();
	int		GetResult();
	string	GetResultString();
	void	ConfigBot( char* m_nameTeamA, char* m_nameTeamB, int id1, int id2, string path, bool isExtraTime );
	string	GetDefautlTeam(int mapW, int mapH, int teamID = 0);
	void	SetTeamDefault(int teamID);
	void	SetGameModeFromFileConfig(int m_GameConfig);
	void	SetGameShortMode();
private:
	Map *map;

	int m_scoreTeamA = 0;
	int m_scoreTeamB = 0;
	long int m_time;
	int m_deltaTime = 0;
	std::ofstream m_outfile;
	char* m_nameTeamA;
	char* m_nameTeamB;
	string m_path;
	int m_iconTeamA;
	int m_iconTeamB;
	string m_fileName = "test.txt";
	string m_fileNameBin = "test.bin";
	bool m_isHit = false;
	bool m_isWriteBinary = true;
	bool m_isWriteText = false;
	int m_turn = 0;
	bool m_isFinishMatch = false;

	bool m_isUserInput = true;
	bool m_isUserInputinform = false;
	vector<int> m_dataInputA;
	vector<int> m_dataInputB;
	vector<int> m_dataInputInitA;
	vector<int> m_dataInputInitB;
	string m_log ;
	bool m_isScore = false;
	bool m_isTeamAScore = false;
	bool m_isPenalty = false;
	bool m_resetPenalty = false;
	bool m_isTeamAPenalty = true;
	int m_totalPen = 0;
	int m_turnBeginPen = 0;
	bool m_isPlayerShootPen = false;
	int m_GameModeFromFileConfig = 0;
	int TURN_PER_MATCH = TURN_PER_MATCH_ORIGINAL;
	int TURN_EXTRA_MATCH = TURN_EXTRA_MATCH_ORIGINAL;
	bool m_isPlayExtraTime = true;
	bool m_isRandomPlayer = false;
};

