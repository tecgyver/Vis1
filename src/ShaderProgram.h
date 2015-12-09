#pragma once
#include <string>
#include <vector>

#include "GLM/glm.hpp"

namespace shaders
{
	class ShaderProgram
	{
	public:
		ShaderProgram(const std::string& vertexFile, const std::string& fragmentFile);
		~ShaderProgram();
		void init();
		void start();
		void stop();
		void cleanup();

	protected:
		virtual void bindAttributes() = 0;
		virtual void getAllUniformLocations() = 0;

		void bindAttribute(int attribute, std::string& variableName);
		int getUniformLocation(std::string& uniformName);
		void loadFloat(int location, float value);
		void loadVector(int location, glm::vec3& value);
		void loadVector(int location, glm::vec2& value);
		void loadBoolean(int location, bool value); 
		void loadMatrix(int location, glm::mat4& value);

	private:
		int programID;
		int vertexShaderID;
		int fragmentShaderID;

		int loadShader(const std::string& file, int type);
	};
}