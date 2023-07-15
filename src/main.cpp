#include <iostream>
#include <random>
#include <vector>
#include <cmath>
#include <time.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Pacman.h"
#include "Food.h"
#include "Camera.h"

const char * vertex_shader_file = "C:\\7mo Semestre\\Computacion Grafica\\TrabajoFinal\\src\\shader.vert";
const char * fragment_shader_file = "C:\\7mo Semestre\\Computacion Grafica\\TrabajoFinal\\src\\shader.frag";

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
double calculate_distance(double x1, double y1, double z1, double x2, double y2, double z2);

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

	// Create a GLFWwindow object of 800 by 800 pixels, naming it "YoutubeOpenGL"
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Trabajo Final", NULL, NULL);
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
	// Specify the viewport of OpenGL in the Windo	w
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	glEnable(GL_DEPTH_TEST);

	Shader ourShader(vertex_shader_file, fragment_shader_file);

	int steps = 70;	// La cantidad de lineas para hacer la figura semejante al circulo que ira rotando, por conveniencia que sea un numero par
	double radiusP = 0.2; // ancho del pacman en terminos de la contextura de la ventana, siempre es positivo
	double radiusB = 0.05;

	Pacman pacman(radiusP,40);

	int sizeArr = 8;
	std::vector<glm::vec3> ball_positions = {glm::vec3(-0.3f, 0.4f, 0.0f), 
											glm::vec3(-0.1f, 0.6f, 0.0f),
											glm::vec3(0.3f, -0.6f, 0.0f),
											glm::vec3(0.2f, 0.9f, 0.0f),
											glm::vec3(-0.8f, -0.7f, 0.0f),
											glm::vec3(-0.2f, -0.4f, 0.0f),
											glm::vec3(-0.1f, -0.9f, 0.0f),
											glm::vec3(-0.2f, 0.5, 0.0f)};

	std::vector<Food*> balls;
	for (int i = 0; i < sizeArr ;i++)
	{
		Food * ball = new Food(radiusB,20);
    	balls.push_back(ball);
		balls[i]->position = ball_positions[i];
	}

	pacman.rotation.x = 90.f;

	Camera camera(SCR_WIDTH, SCR_HEIGHT, glm::vec3(0.0f, 0.0f, 3.f));
	
	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// Take care of all GLFW events
		glfwPollEvents();
		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		// Tell OpenGL which Shader Program we want to use
		ourShader.use();

		camera.process_input(window);
		camera.updateMatrix(45.f, 0.1f, 100.f);
		camera.Matrix(ourShader, "camMatrix");

		pacman.updateInput(window);
		// Rendering pacman
		pacman.draw(ourShader);

		for (int i = 0; i < sizeArr; i++) 
		{
			// Render the ball
			if (!balls[i]->is_eaten)
			{
				double dist = calculate_distance(balls[i]->position.x,balls[i]->position.y,balls[i]->position.z,pacman.position.x,pacman.position.y,pacman.position.z);
				if (dist >= radiusB + radiusP)
				{
					balls[i]->draw(ourShader);
				}
				else
				{
					std::cout << "COLISION" << std::endl;
					balls[i]->is_eaten = true;
				}
			}
		}
		
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
	}

	ourShader.Delete();
	
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}


double calculate_distance(double x1, double y1, double z1, double x2, double y2, double z2) {
    double deltaX = x2 - x1;
    double deltaY = y2 - y1;
    double deltaZ = z2 - z1;
    double distance = std::sqrt((deltaX * deltaX) + (deltaY * deltaY )+ (deltaZ * deltaZ));
    return distance;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

        