#include "DisplayManager.h"
#include <iostream>

using namespace renderEngine;

RaycastRenderingWidget* DisplayManager::WINDOW = nullptr;
int DisplayManager::width;
int DisplayManager::height;

DisplayManager::DisplayManager()
{
}


DisplayManager::~DisplayManager()
{
}

void DisplayManager::createDisplay(RaycastRenderingWidget* window)
{
	////Catch cursor
	//glfwSetInputMode(WINDOW, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	DisplayManager::WINDOW = window;
	DisplayManager::width = DisplayManager::WINDOW->width();
	DisplayManager::height = DisplayManager::WINDOW->height();

	if (glewInit() != GLEW_OK)
	{
		critError(std::string("GLEW init failed!"), -3);
	}
	glewExperimental = true;



	//glViewport(0, 0, DisplayManager::width, DisplayManager::height);
}

void DisplayManager::updateDisplay()
{
	WINDOW->update();
	/*
	GLenum error;
	while ((error = glGetError()) != GL_NO_ERROR)
	{
		std::string errorText;
		switch (error) {
		case GL_INVALID_OPERATION:      errorText = "INVALID_OPERATION";      break;
		case GL_INVALID_ENUM:           errorText = "INVALID_ENUM";           break;
		case GL_INVALID_VALUE:          errorText = "INVALID_VALUE";          break;
		case GL_OUT_OF_MEMORY:          errorText = "OUT_OF_MEMORY";          break;
		case GL_INVALID_FRAMEBUFFER_OPERATION:  errorText = "INVALID_FRAMEBUFFER_OPERATION";  break;
		}

		std::cout << "GL Error detected!" << std::endl;
		std::cout << "Error: " << error << " -> " << errorText << std::endl;
	}*/
}

void DisplayManager::closeDisplay()
{
}

void DisplayManager::critError(std::string& errorMsg, int exitcode)
{
	closeDisplay();
	std::cout << errorMsg.c_str() << std::endl;
	system("PAUSE");
	exit(exitcode);
}

bool DisplayManager::windowShouldUpdate()
{
	return true;
}

void DisplayManager::setTitle(std::string& title)
{

}