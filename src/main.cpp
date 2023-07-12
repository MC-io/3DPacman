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
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Pacman.h"
#include "Food.h"

const char * vertex_shader_file = "C:\\7mo Semestre\\Computacion Grafica\\TrabajoFinal\\src\\shader.vert";
const char * fragment_shader_file = "C:\\7mo Semestre\\Computacion Grafica\\TrabajoFinal\\src\\shader.frag";

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void updateInput(GLFWwindow * window, glm::vec3& position, glm::vec3& rotation, glm::vec3& scale);

double calculateDistance(double x1, double y1, double z1, double x2, double y2, double z2) {
    double deltaX = x2 - x1;
    double deltaY = y2 - y1;
    double deltaZ = z2 - z1;
    double distance = std::sqrt((deltaX * deltaX) + (deltaY * deltaY )+ (deltaZ * deltaZ));
    return distance;
}

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
	double radiusP = 0.4; // ancho del pacman en terminos de la contextura de la ventana, siempre es positivo
	

	double radiusB = 0.15;

	Pacman pacman(radiusP,40);


/*
	int sizeArr = 4;
	std::vector<Food> balls;
	balls.reserve(sizeArr);
	for (int i = 0; i < sizeArr ;i++) {
		Food ball1(30000,50000,radiusB,20);
		int vert_pos1 = 0; 
		int index_pos1 = 0;
		ball1.createFood(vert_pos1, index_pos1);
    	balls.push_back(ball1);
		std::cout<<balls.size();
	}

	// Create and initialize the balls vector here
	std::vector<VAO> ballVAOs;
	std::vector<VBO> ballVBOs;
	std::vector<EBO> ballEBOs;
	for (int i = 0; i < sizeArr ;i++) 
	{

		VAO ballVAO;

		// Generate sphere vertices and indices for the ball
		
		ballVAO.Bind();
		VBO ballVBO(balls[i].vertices, balls[i].getSizeV() * sizeof(GL_FLOAT));

		EBO ballEBO(balls[i].indices,  balls[i].getSizeI() * sizeof(GL_UNSIGNED_INT));
		ballVAO.LinkAttrib(ballVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);


		// Set the vertex attribute pointers for the VAO

		// Unbind the VAO, VBO, and EBO
		ballVAO.Unbind();
		ballVBO.Unbind();
		ballEBO.Unbind();

		// Add the VAO, VBO, and EBO to their respective vectors
		ballVAOs.push_back(ballVAO);
		ballVBOs.push_back(ballVBO);
		ballEBOs.push_back(ballEBO);
	}
	//create_pacman(vertices, 10000, indices, 21942, vert_pos, index_pos, steps, radius);
	// Al terminar esta funcion, actualiza los nuevos valores de vertpos e indexpos para colocar otros vertices e indices


	// Create reference containers for the Vartex Array Object, the Vertex Buffer Object, and the Element Buffer Object
	std::srand(time(NULL));
	 std::random_device rd;
    std::mt19937 gen(rd());
    
    // Create a uniform real distribution
    std::uniform_real_distribution<float> dis(0.0, 1.0);
	std::vector<glm::mat4> translations;
	for(int i = 0;i<sizeArr;i++){
		float randomNum = dis(gen);
		std::cout<<randomNum<<std::endl;
		translations.push_back(glm::translate(glm::mat4(1.0f), glm::vec3(randomNum, randomNum, 0)));
		balls[i].center_x = randomNum;
		balls[i].center_y =  randomNum;
		balls[i].center_z = 0;
	}
*/
	pacman.rotation.x = 90.f;
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, pacman.position);
	model = glm::rotate(model, glm::radians(pacman.rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(pacman.rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(pacman.rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, pacman.scale);
	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		// Tell OpenGL which Shader Program we want to use
		ourShader.use();
		// Bind the VAO so OpenGL knows to use it

  

		pacman.updateInput(window);
		// Dibujando el pacman
		pacman.draw(ourShader);

/*
		for (int i = 0; i < sizeArr; i++) {
			ballVAOs[i].Bind();
				glm::mat4 transform3 = glm::translate(translations[i], glm::vec3(0.0f, 0.f, 0.0f));
		 	 	unsigned int transformLoc2 = glGetUniformLocation(ourShader.ID, "model");
        		glUniformMatrix4fv(transformLoc2, 1, GL_FALSE, glm::value_ptr(transform3));
			
		
			// Render the ball
			if(!balls[i].isEaten){
				double dist = calculateDistance(balls[i].center_x,balls[i].center_y,balls[i].center_z,pacman.center_x,pacman.center_y,pacman.center_z);
				if(dist>=radiusB+radiusP){
					
					balls[i].draw(ourShader);
				}else{
						std::cout<<"COLISION"<<std::endl;
				}
			}
				ballVAOs[i].Unbind();

			
			
	}
		*/
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}

/*
	for(auto& vaos:ballVAOs){
		vaos.Delete();
	}
	for(auto& vaos:ballVBOs){
		vaos.Delete();
	}
	for(auto& vaos:ballEBOs){
		vaos.Delete();
	}
*/
	ourShader.Delete();
	
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

        