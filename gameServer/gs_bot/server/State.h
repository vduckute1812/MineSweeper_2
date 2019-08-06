#ifndef STATE_H
#define STATE_H
#include <vector>

class State
{
public:
	explicit State() {};
	virtual ~State() {};
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Exit() = 0;
};

#endif // STATE_H

