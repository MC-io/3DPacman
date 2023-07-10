#include <iostream>
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

const char * vertex_shader_file = "C:\\7mo Semestre\\Computacion Grafica\\TrabajoFinal\\src\\shader.vert";
const char * fragment_shader_file = "C:\\7mo Semestre\\Computacion Grafica\\TrabajoFinal\\src\\shader.frag";

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void updateInput(GLFWwindow * window, glm::vec3& position, glm::vec3& rotation, glm::vec3& scale);

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

	int steps = 30;	// La cantidad de lineas para hacer la figura semejante al circulo que ira rotando, por conveniencia que sea un numero par
	double radius = 0.5; // ancho del pacman en terminos de la contextura de la ventana, siempre es positivo
	int vert_pos = 0; // Posicion del nuevo vertice a colocar para el arreglo, como solo tenemos al pacman es 0
	int index_pos = 0; // Lo mismo pero con los indices

	Pacman pacman(100000,100000,0.3,70);
	pacman.createPacman(vert_pos,index_pos);
	// Al terminar esta funcion, actualiza los nuevos valores de vertpos e indexpos para colocar otros vertices e indices


	// Create reference containers for the Vartex Array Object, the Vertex Buffer Object, and the Element Buffer Object
	//GLuint VAO, VBO, EBO;
	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(pacman.vertices, pacman.getSizeV() * sizeof(GL_FLOAT));
	// Generates Element Buffer Object and links it to indices
	EBO EBO1(pacman.indices,  pacman.getSizeI() * sizeof(GL_FLOAT));
     
	// Links VBO attributes such as coordinates and colors to VAO
	
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
	
	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	glm::vec3 position(0.f);
	glm::vec3 rotation(0.f);
	glm::vec3 scale(1.f);

	rotation.x = 90.f;
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, position);
	model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, scale);

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
		VAO1.Bind();		// Draw primitives, number of indices, datatype of indices, index of indices

        ourShader.setFloat4("ourColor", 1.0f, 0.0f, 0.0f, 1.0f);

        updateInput(window, position, rotation, scale);

         // create transformations
		model = glm::mat4(1.0f);
		model = glm::translate(model, position);
		model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, scale);

        ourShader.setMat4("model", model);

		glm::mat4 view = glm::mat4(1.0f);
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f)); 
        ourShader.setMat4("view", view);

		glm::mat4 projection;
		projection = glm::perspective(glm::radians(45.0f), 800.0f / 800.0f, 0.1f, 100.0f);
		ourShader.setMat4("projection", projection);
	
        // draw our first triangle
        ourShader.use();
		
		// Dibujando el pacman
		pacman.draw(ourShader);
		
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}

	// Delete all the objects we've created
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();

	ourShader.Delete();
	
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}


void updateInput(GLFWwindow * window, glm::vec3& position, glm::vec3& rotation, glm::vec3& scale)
{
	if (glfwGetKey(window,GLFW_KEY_UP) == GLFW_PRESS)
	{
		rotation.y += 0.1f;
	}
	if (glfwGetKey(window,GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		rotation.y -= 0.1f;
	}
	if (glfwGetKey(window,GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		rotation.x += 0.1f;
	}
	if (glfwGetKey(window,GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		rotation.x -= 0.1f;
	}
	if (glfwGetKey(window,GLFW_KEY_F) == GLFW_PRESS)
	{
		rotation.z += 0.1f;
	}
	if (glfwGetKey(window,GLFW_KEY_G) == GLFW_PRESS)
	{
		rotation.z -= 0.1f;
	}
	if (glfwGetKey(window,GLFW_KEY_A) == GLFW_PRESS)
	{
		position.x += 0.001f;
	}
	if (glfwGetKey(window,GLFW_KEY_D) == GLFW_PRESS)
	{
		position.x -= 0.001f;
	}
	if (glfwGetKey(window,GLFW_KEY_W) == GLFW_PRESS)
	{
		position.z -= 0.001f;
	}
	if (glfwGetKey(window,GLFW_KEY_S) == GLFW_PRESS)
	{
		position.z += 0.001f;
	}
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

        