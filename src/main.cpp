#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

const float angle = 3.1415926 * 2.f / 70;

// Vertex Shader source code
const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec2 aTexCoord;\n"
    "out vec2 TexCoord;\n"
    "uniform mat4 transform;\n"
    "void main()\n"
    "{\n"
    "gl_Position = transform * vec4(aPos, 1.0f);\n"
    "TexCoord = vec2(aTexCoord.x, aTexCoord.y);\n"
    "}\0";


const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "uniform vec4 ourColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = ourColor;\n"
    "}\n\0";


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
	GLFWwindow* window = glfwCreateWindow(800, 800, "YoutubeOpenGL", NULL, NULL);
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
	glViewport(0, 0, 800, 800);



	// Create Vertex Shader Object and get its reference
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// Attach Vertex Shader source to the Vertex Shader Object
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	// Compile the Vertex Shader into machine code
	glCompileShader(vertexShader);

	// Create Fragment Shader Object and get its reference
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// Attach Fragment Shader source to the Fragment Shader Object
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	// Compile the Vertex Shader into machine code
	glCompileShader(fragmentShader);

	// Create Shader Program Object and get its reference
	GLuint shaderProgram = glCreateProgram();
	// Attach the Vertex and Fragment Shaders to the Shader Program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	// Wrap-up/Link all the shaders together into the Shader Program
	glLinkProgram(shaderProgram);

	// Delete the now useless Vertex and Fragment Shader objects
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);



	// Vertices coordinates
	GLfloat vertices[3 + (3 * (71 * 34) + 3)];

	vertices[0] = 0.4 * sin(0); 
	vertices[1] = -0.4 * cos(0); 
	vertices[2] = 0.0f;
	for (int i = 0; i < 34; i++)
	{
		vertices[3 + (3 * 71 * i)] = 0.4 * sin(angle * (i + 1)); 
		vertices[3 + (3 * 71 * i + 1)] = -0.4 * cos(angle * (i + 1)); 
		vertices[3 + (3 * 71 * i + 2)] = 0.0f;

		for (int j = 1; j <= 70; j++)
		{
			glm::mat4 trans = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
			trans = glm::rotate(trans, angle, glm::vec3(0.0, 1.0, 0.0));
			glm::vec4 newm = trans * glm::vec4(vertices[3 + (3 * (71 * i + (j - 1)))], vertices[3 + (3 * (71 * i + (j - 1))) + 1], vertices[3 + (3 * (71 * i + (j - 1))) + 2], 0.0f);
			vertices[3 + (3 * (71 * i + j))] = newm[0];
			vertices[3 + (3 * (71 * i + j) + 1)] = newm[1];
			vertices[3 + (3 * (71 * i + j) + 2)] = newm[2]; 
		}
	}
	vertices[3 + (3 * (71 * 34))] =  0.4 * sin(angle * 35); 
	vertices[3 + (3 * (71 * 34) + 1)] = -0.4 * cos(angle * 35); 
	vertices[3 + (3 * (71 * 34) + 2)] = 0.0f;

	GLuint indices[14484];

	for (int i = 0; i <= 70; i++)
	{
		indices[i * 3] = 0;
		indices[i * 3 + 1] = i + 1;  
		indices[i * 3 + 2] = i + 2;
	}
	for (int i = 1; i < 34; i++)
	{
		for (int j = 0; j <= 70; j++)
		{
			indices[213 + ((i - 1) * 71 * 6) + j * 6] = 1 + 71 * (i - 1) + j;
			indices[213 + ((i - 1) * 71 * 6) + j * 6 + 1] = 1 + 71 * (i - 1) + j + 1;
			indices[213 + ((i - 1) * 71 * 6) + j * 6 + 2] =  1 + 71 * i + j;

			indices[213 + ((i - 1) * 71 * 6) + j * 6 + 3] = 1 + 71 * (i - 1) + j + 1;
			indices[213 + ((i - 1) * 71 * 6) + j * 6 + 4] = 1 + 71 * i + j;
			indices[213 + ((i - 1) * 71 * 6) + j * 6 + 5] = 1 + 71 * i + j + 1;
		}
	}
	for (int i = 0; i <= 70; i++)
	{
		indices[213 + ((34 - 1) * 71 * 6) + i * 3] = 1 + 71 * 33 + i;
		indices[213 + ((34 - 1) * 71 * 6) + i * 3 + 1] = 1 + 71 * 33 + i + 1;
		indices[213 + ((34 - 1) * 71 * 6) + i * 3 + 2] = 1 + 71 * 34;
	}
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
	double factor = 1;

	glm::mat4 prev_transform = glm::mat4(1.0f);

    glEnable(GL_DEPTH_TEST); 
	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		// Tell OpenGL which Shader Program we want to use
		glUseProgram(shaderProgram);
		// Bind the VAO so OpenGL knows to use it


        double  timeValue = glfwGetTime();
        int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
        glUniform4f(vertexColorLocation, 1.0f, 0.0f, 0.0f, 1.0f);


         // create transformations
		glm::mat4 transform = prev_transform; // make sure to initialize matrix to identity matrix first

        if (glfwGetKey(window,GLFW_KEY_UP) == GLFW_PRESS)
        {
            transform = glm::rotate(transform, 0.001f, glm::vec3(1.0, 0.0, 0.0));
        }
        if (glfwGetKey(window,GLFW_KEY_DOWN) == GLFW_PRESS)
        {
            transform = glm::rotate(transform, 0.001f, glm::vec3(-1.0, 0.0, 0.0));
        }
        if (glfwGetKey(window,GLFW_KEY_RIGHT) == GLFW_PRESS)
        {
            transform = glm::rotate(transform, 0.001f, glm::vec3(0.0, -1.0, 0.0));
        }
        if (glfwGetKey(window,GLFW_KEY_LEFT) == GLFW_PRESS)
        {
            transform = glm::rotate(transform, 0.001f, glm::vec3(0.0, 1.0, 0.0));
        }
        if (glfwGetKey(window,GLFW_KEY_F) == GLFW_PRESS)
        {
            transform = glm::rotate(transform, 0.001f, glm::vec3(0.0, 0.0, 1.0));
        }
        if (glfwGetKey(window,GLFW_KEY_G) == GLFW_PRESS)
        {
            transform = glm::rotate(transform, 0.001f, glm::vec3(0.0, 0.0, -1.0));
        }
		prev_transform = transform;
		factor *= 1.00005;
        unsigned int transformLoc = glGetUniformLocation(shaderProgram, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

        // draw our first triangle
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
		// Draw primitives, number of indices, datatype of indices, index of indices

		for (int i = 0; i <= 71; i++)
		{
			if (i % 3 == 0)
			{
				glUniform4f(vertexColorLocation, 1.0f, 0.0f, 0.0f, 1.0f);
			}
			else if (i % 3 == 1)
			{
				glUniform4f(vertexColorLocation, 0.0f, 1.0f, 0.0f, 1.0f);
			}
			else
			{
				glUniform4f(vertexColorLocation, 0.0f, 0.0f, 1.0f, 1.0f);
			}
			glDrawElements(GL_TRIANGLES, 68 * 3, GL_UNSIGNED_INT, (void*)(i * 68 * 3  * sizeof(float)));

		}


		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}



	// Delete all the objects we've created
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram);
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}

        