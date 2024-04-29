#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


//vertex shader source code
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
//fragment shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";


int main() {

	//init glf
	glfwInit();

	//GLFW versions, OpenGL 3.3 core profile
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//vert coords
	GLfloat vertices[] = {
		//lower left corner
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
		//lower right corner
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
		//upper right corner
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f,
	};

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

	//vertex shader obj creation
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	//fragment shader obj creation
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	//create shader program & get ref.
	GLuint shaderProgram = glCreateProgram();
	//attaching vertex & frag to shader prog
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	//link shaders together into prog
	glLinkProgram(shaderProgram);

	//cleanup
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	//ref contianers for vertex array obj & buffer
	GLuint VAO, VBO;

	//generate vao before vbo
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	//bind and put vertices into VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//config vertex attr. for openGL to read VBO
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//bind VAO & VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glfwSwapBuffers(window);

	//main while loop
	while (!glfwWindowShouldClose(window)) {

		//grayish blue: #626b7a
		glClearColor(0.38f, 0.42f, 0.48f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);

		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window);

		glfwPollEvents();

	}

	//destroy vertex
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

	//deinit
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}