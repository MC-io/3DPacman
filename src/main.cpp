#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <Shader.h>

const char * vertex_shader_file = "C:\\7mo Semestre\\Computacion Grafica\\TrabajoFinal\\src\\shader.vert";
const char * fragment_shader_file = "C:\\7mo Semestre\\Computacion Grafica\\TrabajoFinal\\src\\shader.frag";

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void updateInput(GLFWwindow * window, glm::vec3& position, glm::vec3& rotation, glm::vec3& scale);
void create_pacman(GLfloat vertices[], GLuint indices[], int & vert_pos, int & index_pos, int steps, double radius);
void draw_pacman(int steps, int shaderProgram);
void create_food();
void draw_food();
void create_berry();
void draw_berry();
void create_ghost();
void draw_ghost();


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

	// Vertices coordinates
	GLfloat vertices[100000];
	GLuint indices[100000];


	int steps = 100;	// La cantidad de lineas para hacer la figura semejante al circulo que ira rotando, por conveniencia que sea un numero par
	double radius = 0.5; // ancho del pacman en terminos de la contextura de la ventana, siempre es positivo
	int vert_pos = 0; // Posicion del nuevo vertice a colocar para el arreglo, como solo tenemos al pacman es 0
	int index_pos = 0; // Lo mismo pero con los indices

	create_pacman(vertices, indices, vert_pos, index_pos, steps, radius);
	// Al terminar esta funcion, actualiza los nuevos valores de vertpos e indexpos para colocar otros vertices e indices


	// Create reference containers for the Vartex Array Object, the Vertex Buffer Object, and the Element Buffer Object
	GLuint VAO, VBO, EBO;

	// Generate the VAO, VBO, and EBO with only 1 object each
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Make the VAO the current Vertex Array Object by binding it
	glBindVertexArray(VAO);

	// Bind the VBO specifying it's a GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// Introduce the vertices into the VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Bind the EBO specifying it's a GL_ELEMENT_ARRAY_BUFFER
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	// Introduce the indices into the EBO
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Configure the Vertex Attribute so that OpenGL knows how to read the VBO
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	// Enable the Vertex Attribute so that OpenGL knows to use it
	glEnableVertexAttribArray(0);

	// Bind both the VBO and VAO to 0 so that we don't accidentally modify the VAO and VBO we created
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	// Bind the EBO to 0 so that we don't accidentally modify it
	// MAKE SURE TO UNBIND IT AFTER UNBINDING THE VAO, as the EBO is linked in the VAO
	// This does not apply to the VBO because the VBO is already linked to the VAO during glVertexAttribPointer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


	glm::vec3 position(0.f);
	glm::vec3 rotation(0.f);
	glm::vec3 scale(1.f);

	rotation.x = 90.f;

	glm::mat4 transform = glm::mat4(1.0f);
	transform = glm::translate(transform, position);
	transform = glm::rotate(transform, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	transform = glm::rotate(transform, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	transform = glm::rotate(transform, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	transform = glm::scale(transform, scale);

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

        double  timeValue = glfwGetTime();
        ourShader.setFloat4("ourColor", 1.0f, 0.0f, 0.0f, 1.0f);

        updateInput(window, position, rotation, scale);

         // create transformations
		glm::mat4 transform = glm::mat4(1.0f);
		transform = glm::translate(transform, position);
		transform = glm::rotate(transform, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		transform = glm::rotate(transform, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		transform = glm::rotate(transform, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
		transform = glm::scale(transform, scale);

        ourShader.setMat4("model", transform);

		glm::mat4 view = glm::mat4(1.0f);
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f)); 
        ourShader.setMat4("view", view);

		glm::mat4 projection;
		projection = glm::perspective(glm::radians(45.0f), 800.0f / 800.0f, 0.1f, 100.0f);
		ourShader.setMat4("projection", projection);
	
        // draw our first triangle
        ourShader.use();
		
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
		// Draw primitives, number of indices, datatype of indices, index of indices

		// Dibujando el pacman
		draw_pacman(steps, ourShader.ID);
		
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}

	// Delete all the objects we've created
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	ourShader.Delete();
	
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}


void create_pacman(GLfloat vertices[], GLuint indices[], int & vert_pos, int & index_pos, int steps, double radius)
{
	const float angle = 3.1415926 * 2.f / steps;
	vertices[vert_pos + 0] = radius * sin(0); 
	vertices[vert_pos + 1] = -radius * cos(0); 
	vertices[vert_pos + 2] = 0.0f;

	for (int i = 0; i < (steps / 2) - 1; i++)
	{
		vertices[vert_pos + 3 * (1 + (steps + 1) * i)] = radius * sin(angle * (i + 1)); 
		vertices[vert_pos + 3 * (1 + (steps + 1) * i) + 1] = -radius * cos(angle * (i + 1)); 
		vertices[vert_pos + 3 * (1 + (steps + 1) * i) + 2] = 0.0f;

		for (int j = 1; j <= steps; j++)
		{
			glm::mat4 trans = glm::mat4(1.0f);
			trans = glm::rotate(trans, angle, glm::vec3(0.0, 1.0, 0.0));
			glm::vec4 newm = trans * glm::vec4(vertices[vert_pos + 3 * (1 + ((steps + 1) * i + (j - 1)))],
			 									vertices[vert_pos + 3 * (1 + ((steps + 1) * i + (j - 1))) + 1],
			  									vertices[vert_pos + 3 * (1 + ((steps + 1) * i + (j - 1))) + 2], 0.0f);
			vertices[vert_pos + 3 * (1 + ((steps + 1) * i + j))] = newm[0];
			vertices[vert_pos + 3 * (1 + ((steps + 1) * i + j)) + 1] = newm[1];
			vertices[vert_pos + 3 * (1 + ((steps + 1) * i + j)) + 2] = newm[2]; 
		}
	}
	vertices[vert_pos + 3 * (1 + ((steps + 1) * (steps / 2 - 1)))] =  radius * sin(angle * (steps / 2)); 
	vertices[vert_pos + 3 * (1 + ((steps + 1) * (steps / 2 - 1))) + 1] = -radius * cos(angle * (steps / 2)); 
	vertices[vert_pos + 3 * (1 + ((steps + 1) * (steps / 2 - 1))) + 2] = 0.0f;

	vertices[vert_pos + 3 * (1 + ((steps + 1) * (steps / 2 - 1))) + 3] = 0.0f;
	vertices[vert_pos + 3 * (1 + ((steps + 1) * (steps / 2 - 1))) + 4] = 0.0f; 
	vertices[vert_pos + 3 * (1 + ((steps + 1) * (steps / 2 - 1))) + 5] = 0.0f;

	for (int i = 0; i <= steps; i++)
	{
		indices[index_pos + i * 3] = (vert_pos / 3) + 0;
		indices[index_pos + i * 3 + 1] = (vert_pos / 3) + i + 1;  
		indices[index_pos + i * 3 + 2] = (vert_pos / 3) + i + 2;

		indices[index_pos + ((steps + 1) * (steps / 2 - 1) * 6) + i * 3] = (vert_pos / 3) + (steps + 1) * (steps / 2 - 1) + 2;
		indices[index_pos + ((steps + 1) * (steps / 2 - 1) * 6) + i * 3 + 1] =  (vert_pos / 3) + i + 1;
		indices[index_pos + ((steps + 1) * (steps / 2 - 1) * 6) + i * 3 + 2] = (vert_pos / 3) + 0;
	}
	for (int i = 1; i < (steps / 2) - 1; i++)
	{
		for (int j = 0; j <= steps; j++)
		{
			indices[index_pos + (steps + 1) * 3 + ((i - 1) * (steps + 1) * 6) + j * 6] = (vert_pos / 3) + 1 + (steps + 1) * (i - 1) + j;
			indices[index_pos + (steps + 1) * 3 + ((i - 1) * (steps + 1) * 6) + j * 6 + 1] = (vert_pos / 3) + 1 + (steps + 1) * (i - 1) + j + 1;
			indices[index_pos + (steps + 1) * 3 + ((i - 1) * (steps + 1) * 6) + j * 6 + 2] = (vert_pos / 3) + 1 + (steps + 1) * i + j;

			indices[index_pos + (steps + 1) * 3 + ((i - 1) * (steps + 1) * 6) + j * 6 + 3] = (vert_pos / 3) + 1 + (steps + 1) * (i - 1) + j + 1;
			indices[index_pos + (steps + 1) * 3 + ((i - 1) * (steps + 1) * 6) + j * 6 + 4] = (vert_pos / 3) + 1 + (steps + 1) * i + j;
			indices[index_pos + (steps + 1) * 3 + ((i - 1) * (steps + 1) * 6) + j * 6 + 5] = (vert_pos / 3) + 1 + (steps + 1) * i + j + 1;

			indices[index_pos + ((steps + 1) * (steps / 2 - 1) * 6) + ((steps + 1) * i * 3) + j * 3] = (vert_pos / 3) + 1 + (steps + 1) * (i - 1) + j;
			indices[index_pos + ((steps + 1) * (steps / 2 - 1) * 6) + ((steps + 1) * i * 3) + j * 3 + 1] = (vert_pos / 3) + 1 + (steps + 1) * i + j;
			indices[index_pos + ((steps + 1) * (steps / 2 - 1) * 6) + ((steps + 1) * i * 3) + j * 3 + 2] = (vert_pos / 3) + (steps + 1) * (steps / 2 - 1) + 2;

		}
	}
	for (int i = 0; i <= steps; i++)
	{
		indices[index_pos + (steps + 1) * 3 + (((steps / 2) - 1 - 1) * (steps + 1) * 6) + i * 3] = (vert_pos / 3) + 1 + (steps + 1) * ((steps / 2) - 2) + i;
		indices[index_pos + (steps + 1) * 3 + (((steps / 2) - 1 - 1) * (steps + 1) * 6) + i * 3 + 1] = (vert_pos / 3) + 1 + (steps + 1) * ((steps / 2) - 2) + i + 1;
		indices[index_pos + (steps + 1) * 3 + (((steps / 2) - 1 - 1) * (steps + 1) * 6) + i * 3 + 2] = (vert_pos / 3) + 1 + (steps + 1) * ((steps / 2) - 1);

		indices[index_pos + ((steps + 1) * (steps / 2 - 1) * 6) + ((steps + 1) * (steps / 2 - 1) * 3) + i * 3] = (vert_pos / 3) + (steps + 1) * (steps / 2 - 1) + 2;
		indices[index_pos + ((steps + 1) * (steps / 2 - 1) * 6) + ((steps + 1) * (steps / 2 - 1) * 3) + i * 3 + 1] = (vert_pos / 3) + 1 + (steps + 1) * (steps / 2 - 2) + i;
		indices[index_pos + ((steps + 1) * (steps / 2 - 1) * 6) + ((steps + 1) * (steps / 2 - 1) * 3) + i * 3 + 2] = (vert_pos / 3) + (steps + 1) * (steps / 2 - 1) + 1;
	}

	vert_pos += 3 * (steps + 1) * (steps / 2 - 1) + 9;
	index_pos += ((steps + 1) * (steps / 2 - 1) * 6) + ((steps + 1) * (steps / 2 - 1) * 3) + (steps + 1) * 3 + 3;
}

void draw_pacman(int steps, int shaderProgram)
{
	double  timeValue = glfwGetTime();
	int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
	glUniform4f(vertexColorLocation, 1.0f, 0.0f, 0.0f, 1.0f);
	int change =  (steps + 1) * 3 - 3 * (int)(sin(timeValue * 10) * (steps / 12) + (steps / 12) + 1);
	glUniform4f(vertexColorLocation, 1.0f, 0.8f, 0.0f, 1.0f);
	glDrawElements(GL_TRIANGLES, change - ((steps + 1) * 3 - change), GL_UNSIGNED_INT, (void*)(((steps + 1) * 3 - change) * sizeof(float)));

	for (int i = 0; i < (steps / 2 - 2); i++)
		glDrawElements(GL_TRIANGLES, (change - ((steps + 1) * 3 - change)) * 2, GL_UNSIGNED_INT, (void*)((((steps + 1) * 6 - change * 2) + (steps + 1) * 3 + (steps + 1) * 6 * i) * sizeof(float)));

	glDrawElements(GL_TRIANGLES, change - ((steps + 1) * 3 - change), GL_UNSIGNED_INT, (void*)((((steps + 1) * 3 - change) + (steps + 1) * 3 + (steps + 1) * 6 * (steps / 2 - 2)) * sizeof(float)));

	glUniform4f(vertexColorLocation, 0.0f, 0.0f, 0.0f, 1.0f);
	for (int i = 0; i < steps / 2; i++)
	{
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(((steps + 1) * (steps / 2 - 1) * 6 + i * (steps + 1) * 3 + (steps + 1) * 3 - change) * sizeof(float)));
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(((steps + 1) * (steps / 2 - 1) * 6 + i * (steps + 1) * 3 + change) * sizeof(float)));
	}
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

void create_food()
{

}
void draw_food()
{

}
void create_berry()
{

}
void draw_berry()
{

}
void create_ghost()
{

}
void draw_ghost()
{

}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

        