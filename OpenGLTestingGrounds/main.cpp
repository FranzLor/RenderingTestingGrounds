#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>



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

	//grayish blue: #626b7a
	glClearColor(0.38f, 0.42f, 0.48f, 1.0f);

	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(window);

	//main while loop
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

	}

	//deinit
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}