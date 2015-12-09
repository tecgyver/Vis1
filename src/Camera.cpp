#include "Camera.h"
#include "Maths.h"

using namespace entities;
using namespace toolbox;

const float MOVESPEED = 0.5f;

Camera::Camera() : pitch(0), yaw(0), roll(0)
{
}


Camera::~Camera()
{
}