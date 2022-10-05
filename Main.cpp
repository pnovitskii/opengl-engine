#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define WIDTH 800
#define HEIGHT 800
using namespace std;

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0f, 0.5f, 0.2f, 1.0f);\n"//1.0f
"}\n\0";
class Rgb {
public:
	bool temp1 = false;
	bool temp2 = false;
	bool temp3 = false;
	float r = 0;
	float g = 0;
	float b = 0;
	float start = 0;
	float current = 0;
	void changeColor(double time) {
		current += (float)time;
		if (current - start >= 0.1) {
			if (temp1 == false) r = (r + 0.0003);
			else r = (r - 0.0003);
			if (r > 1) temp1 = !temp1;
			if (r < 0) temp1 = !temp1;
			if (temp2 == false) g = (g + 0.0002);
			else g = (g - 0.0002);
			if (g > 1) temp2 = !temp2;
			if (g < 0) temp2 = !temp2;
			if (temp3 == false) b = (b + 0.0001);
			else b = (b - 0.0001);
			if (b > 1) temp3 = !temp3;
			if (b < 0) temp3 = !temp3;
			start = current;
		}
	}
};
int main()
{
	// Initialize GLFW
	glfwInit();

	// Tell GLFW what version of OpenGL we are using
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLfloat vertices[] =
	{
		0, -0.5, 0,
		0.6, 0.5, 0,
		-0.6, 0.5, 0
	};




	// Create a GLFWwindow object, 800x800 resolution, name: Render engine
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "RGB", NULL, NULL);
	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	//Load GLAD so it configures OpenGL
	gladLoadGL();

	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, WIDTH, HEIGHT);
	
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	GLuint shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	glLinkProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	GLuint VAO, VBO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	Rgb rgb;
	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		rgb.changeColor(glfwGetTime());
		glClearColor(rgb.r, rgb.g, rgb.b, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}