#pragma once
#include <string>

#include "glew.h"
#include "RaycastRenderingWidget.h"

namespace renderEngine {
	class DisplayManager
	{
	public:
		DisplayManager();
		~DisplayManager();

		static int width;
		static int height;
		static RaycastRenderingWidget* WINDOW;

		static void createDisplay(RaycastRenderingWidget* window);
		static void updateDisplay();
		static void closeDisplay();
		static bool windowShouldUpdate();
		static void setTitle(std::string& title);

	private:
		static const int FPS_CAP = 120;

		static void critError(std::string& errorMsg, int exitcode);
	};
}