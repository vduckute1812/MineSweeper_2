#pragma once

#include "Object.h"
#include <vector>

using namespace std;

class Weapon;
class Helmet;
class Armory;
class Player: public Object
{
public:
	Player();
	~Player();

	void	Init(int id, char* name,Position pos, int characterSpeed, int blood);
	void	Update();

	void	Render();
	void	ShowVisibleRange(bool);
	void	ShowListanableRange(bool);

	bool	IsShowVisibleRange() const;
	bool	IsShowListenableRange() const;

	void	SetName(char* name);
	char*	GetName() const;
	int		GetNameLength() const;
	
	void	Killed();

	bool	IsDead() const;
	bool	IsVisible() const;


private:
	int		m_id;
	char*	m_name;
	int		m_blood;
	int		m_characterSpeed;

	bool	m_isDead;
	bool	m_isVisible;	// Hide on bush

	bool	m_isShowVisibleRange;
	bool	m_isShowListanableRange;

	// Armory of character
	Armory*		m_armory;
};

