// server.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <stdio.h>
// #include <tchar.h>
#include <string>
using namespace std;
int main()
{
	string botInput;
	string rivalInput;
	string botLog;
	int TURN_MAX = 0;
	int turn = TURN_MAX;
	string cmd1;
	cout << "Init game info";
    getline(std::cin, cmd1);//bots ready ?
    cerr<<"status:"<<cmd1;
	while (++turn < 10)
	{
		//send info to bots
		cout << "map info of turn "<<turn;
		//receive input of bots
		getline(std::cin, botInput);
		cerr << "" << botInput;
//		cerr << "Turn " << turn<<endl;
	}
    cout<<"END";
    return 0;
}
