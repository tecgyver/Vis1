#include "Camera.h"
#include "Keyboard.h"
#include "Maths.h"

using namespace entities;
using namespace input;
using namespace toolbox;

const float MOVESPEED = 0.5f;

Camera::Camera() : pitch(0), yaw(0), roll(0)
{
}


Camera::~Camera()
{
}

void Camera::move(long double timePassed)
{
	if (Keyboard::getKeyPressed(Qt::Key_W))
	{
		position.z -= MOVESPEED;
	}
	if (Keyboard::getKeyPressed(Qt::Key_S))
	{
		position.z += MOVESPEED;
	}
	if (Keyboard::getKeyPressed(Qt::Key_A))
	{
		position.x -= MOVESPEED;
	}
	if (Keyboard::getKeyPressed(Qt::Key_D))
	{
		position.x += MOVESPEED;
	}
	if (Keyboard::getKeyPressed(Qt::Key_Space))
	{
		position.y += MOVESPEED;
	}
	if (Keyboard::getKeyPressed(Qt::Key_Control))
	{
		position.y -= MOVESPEED;
	}
}