#include "ShaderClass.h"


std::string getFileContents(const char* fileName) {
	std::ifstream in(fileName, std::ios::binary);

	if (in) {
		std::string contents;

		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());

		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		
		return(contents);
	} throw (errno);
}

Shader::Shader(const char* vertexFile, const char* fragmentFile) {
	std::string vertex = getFileContents(vertexFile);
	std::string fragment = getFileContents(fragmentFile);

	const char* vertexSource = vertex.c_str();
	const char* fragmentSource = fragment.c_str();

	//vertex shader obj creation
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);

	//fragment shader obj creation
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);

	//create shader program & get ref.
	ID = glCreateProgram();
	//attaching vertex & frag to shader prog
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	//link shaders together into prog
	glLinkProgram(ID);

	//cleanup
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::Activate() {
	glUseProgram(ID);
}

void Shader::Delete() {
	glUseProgram(ID);
}