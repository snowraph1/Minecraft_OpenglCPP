#pragma once

#include <glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <glm.hpp>
#include <vec2.hpp>
#include <vec3.hpp>
#include <vec4.hpp>
#include <mat4x4.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

class Shader
{
private:
	GLuint id;

	std::string loadShaderSource(char* fileName) {

	}

	GLuint loadShader(GLenum type, char* fileName) {

	}

public:
};