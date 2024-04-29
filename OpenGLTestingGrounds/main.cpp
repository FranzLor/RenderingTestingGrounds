#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "ShaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"


//vert coords
GLfloat vertices[] = {
	//lower left corner
	-0.5f, -0.5f * float(sqrt(3)) / 3,
	//color
	0.0f, 0.02f, 0.3f, 0.8f,

	//lower right corner
	0.5f, -0.5f * float(sqrt(3)) / 3,
	0.0f, 0.02f, 0.3f, 0.8f,

	//upper right corner
	0.0f, 0.5f * float(sqrt(3)) * 2 / 3,
	0.0f, 0.32f, 0.6f, 1.02f,

	//inner left
	-0.5f / 2, 0.5f * float(sqrt(3)) / 6,
	0.0f, 0.2f, 0.45f, 0.9f,

	//inner right
	0.5f / 2, 0.5f * float(sqrt(3)) / 6,
	0.0f, 0.2f, 0.45f, 0.9f,

	//inner down
	0.0f, -0.5f * float(sqrt(3)) / 3,
	0.0f, 0.02f, 0.3f, 0.8f

};

//lower left triangle, lower right, upper
GLuint indices[] = {
	0, 3, 5,
	3, 2, 4,
	5, 4, 1
};


int main() {

	//init glf
	glfwInit();

	//GLFW versions, OpenGL 3.3 core profile
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	//main window, 800x800
	GLFWwindow* window = glfwCreateWindow(800, 800, "Rendering Testing Grounds", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to Create GLFW Window!" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	gladLoadGL();

	glViewport(0, 0, 800, 800);

	Shader shaderProgram("default.vert", "default.frag");

	//creates vertex array obj & binds it
	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));


	//links VBO to VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	//stops modifying it
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

	//main while loop
	while (!glfwWindowShouldClose(window)) {

		//grayish blue: #626b7a
		glClearColor(0.38f, 0.42f, 0.48f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shaderProgram.Activate();
		glUniform1f(uniID, 0.5f);

		VAO1.Bind();

		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);

		glfwPollEvents();

	}

	//deinit
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}