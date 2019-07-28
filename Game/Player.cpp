#include "Player.h"
#include "Define.h"
#include "Pistal.h"
#include "Rifle.h"
#include "Grenade.h"
#include "Helmet.h"
#include "DebugDraw.h"
#include "Weapon.h"
#include "Armory.h"
#include "Define.h"

Player::Player()
{
	m_name = new char[100];

	m_isShowVisibleRange = false;
	m_isShowListanableRange = false;
}

Player::~Player()
{
	delete []m_name;
}

void Player::Init(int id, char* name, Position pos, int characterSpeed, int blood)
{
	m_id = id;
	m_name = name;
	m_position = pos;
	m_blood = blood;
	m_isDead = false;
	m_characterSpeed = characterSpeed;
}


void Player::ShowVisibleRange(bool isShowVisible)
{
	m_isShowVisibleRange = isShowVisible;
}

void Player::ShowListanableRange(bool isShowListenable)
{
	m_isShowListanableRange = isShowListenable;
}

bool Player::IsShowVisibleRange() const
{
	return m_isShowVisibleRange;
}

bool Player::IsShowListenableRange() const
{
	return m_isShowListanableRange;
}

void Player::SetName(char* name)
{
	m_name = name;
}

char* Player::GetName() const
{
	return m_name;
}

int Player::GetNameLength() const
{
	int size = 0;
	char* tmp = m_name;

	while (*tmp != '\0')
	{
		size++;
		tmp++;
	}
	return size;
}

void Player::Killed()
{
	m_isDead = true;
}

bool Player::IsDead() const
{
	return m_isDead;
}

bool Player::IsVisible() const
{
	return m_isVisible;
}

void Player::Move(Position target)
{
	//m_position.x = 
}

Weapon* Player::GetWeapon() const
{
	return m_armory->GetCurrentWeapon();
}

WeaponType Player::GetWeaponType() const
{
	return m_armory->GetCurrentWeaponType();
}

void Player::UseWeapon()
{
	m_armory->UseWeapon();
}

void Player::ChangeWeapon(WeaponType type)
{
	m_armory->SetWeapon(type);
}

void Player::Update()
{
}

void Player::Render()
{

}
