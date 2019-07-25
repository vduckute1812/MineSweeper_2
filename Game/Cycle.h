#pragma once
class Cycle
{
public:
	Cycle();
	~Cycle();

	void init(int x, int y, int r);
	void update();

public:
	int m_x;
	int m_y;
	int m_r;
};

