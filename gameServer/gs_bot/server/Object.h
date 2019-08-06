#ifndef OBJECT_H
#define OBJECT_H

struct Position
{
	Position() : x(0), y(0) {}
	Position(int _x, int _y) : x(_x), y(_y) {}
	const Position& operator =(const Position& pos) { x = pos.x; y = pos.y; return *this; }
	bool operator == (const Position &s) { return x == s.x && y == s.y; }

	// Properties
	int x;
	int y;
};

class Object
{
public:
	Object();
	virtual ~Object();

	void			SetPosition(const Position& pos);
	const Position&	GetPosition();

private:
	Position m_position;
};

#endif