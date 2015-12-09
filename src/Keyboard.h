#pragma once
#include "DisplayManager.h"
#include <vector>

namespace input
{
	class Keyboard
	{
	public:
		Keyboard();
		~Keyboard();
		static bool getKeyPressed(Qt::Key key);
		static void keyPressed(Qt::Key key);
		static void keyReleased(Qt::Key key);

	protected:
		static std::vector<bool> keyState;
	};
}