#ifndef STATEMACHINE_H
#define STATEMACHINE_H
#include "Singleton.h"

class State;
class Graphic;
class StateMachine: public Singleton<StateMachine>
{
public:
	virtual void Init() override;
	virtual void Destroy() override;

	void Update();
	void Render();
	void SwitchState(State *state);
	State* GetState();

private:
	static StateMachine* instance;
	State* m_currentState;
	State* m_nextState;

	bool m_isEnterNextState;
	bool m_isExitCurrentState;
};

#endif // STATEMACHINE_H