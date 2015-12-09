#include "Keyboard.h"

using namespace input;
using namespace renderEngine;

std::vector<bool> Keyboard::keyState;

Keyboard::Keyboard()
{
}


Keyboard::~Keyboard()
{
}

bool Keyboard::getKeyPressed(Qt::Key key)
{
	if (Keyboard::keyState.size() > (uint)key)
		return Keyboard::keyState[(uint)key];
	return false;
}

void Keyboard::keyPressed(Qt::Key key)
{
	/*if ((uint)key > keyState.size())
	{
	keyState.resize((uint)key, false);
	}*/
	Keyboard::keyState[(uint)key] = true;
}

void Keyboard::keyReleased(Qt::Key key)
{
	/*if ((uint)key > keyState.size())
	{
	keyState.resize((uint)key, false);
	}*/
	Keyboard::keyState[(uint)key] = false;
}