#include "stdafx.h"
#include "StateMachine.h"
#include "State.h"
#include "MainState.h"

void StateMachine::Init()
{
	m_isExitCurrentState = false;
	m_isEnterNextState = false;
	m_currentState = new MainState();
	m_nextState = NULL;
}

void StateMachine::Destroy()
{
	delete m_currentState;
}

void StateMachine::Update()
{
	// call update logics of current state
	m_currentState->Update();

	//check and release current state
	if (m_isExitCurrentState)
	{
		m_isExitCurrentState = false;
		m_currentState->Exit();
		m_isEnterNextState = true;
	}

	//check and intialize state
	if (m_isEnterNextState)
	{
		m_isEnterNextState = false;
		m_currentState = m_nextState;
		m_currentState->Init();
	}
}

void StateMachine::Render()
{
	m_currentState->Render();
}


void StateMachine::SwitchState(State * state)
{
	m_nextState = state;
	m_isExitCurrentState = true;
}


State * StateMachine::GetState()
{
	return m_currentState;
}
