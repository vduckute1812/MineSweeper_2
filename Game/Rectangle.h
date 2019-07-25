#pragma once
class Rectangle
{
public:
	Rectangle();
	~Rectangle();
	void Init(int width, int heigh);
	int GetWidth();
	int GetHeigh();
private:
	int m_x;
	int m_y;
	int m_width;
	int m_heigh;
};

