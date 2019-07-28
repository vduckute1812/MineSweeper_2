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

int MainState::Rand(int min, int max)
{
	return 0;
}
