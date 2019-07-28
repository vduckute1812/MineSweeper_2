#pragma once

#include "Define.h"

class Map
{
	public:
		Map();
		Map(int width, int height);
		~Map();

		void	Init();
		void	SetWidthMap(int width);
		int		GetWidth();
		void	SetHeightMap(int height);
		int		GetHeigh();

	private:
		int		m_width;
		int		m_heigh;
};

