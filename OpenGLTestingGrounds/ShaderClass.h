#pragma once

#include <iostream>
#include <glad/glad.h>
#include <fstream>
#include <string>
#include <sstream>
#include <cerrno>

std::string getFileContents(const char* fileName);

class Shader {
private:
	void Error(unsigned int shader, const char* type);

public:
	GLuint ID;
	Shader(const char* vertexFile, const char* fragmentFile);

	void Activate();
	void Delete();
};