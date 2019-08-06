#ifndef MAINSTATE_H
#define MAINSTATE_H

#include "State.h"
#include <string>

class Player;
class MainState: public State
{
public:
	MainState();
	~MainState();
	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Exit();

	void SendDataToClient();
	bool GetInputData(std::string data);

private:
	std::vector<Player*> players;

	std::vector<int> m_dataInputA;
	std::vector<int> m_dataInputB;
};

#endif // MAINSTATE_H