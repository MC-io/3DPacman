#ifndef PACMAN_CLASS_H
#define PACMAN_CLASS_H

#include <glm/glm.hpp>
#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>
#include <vector>
#include <random>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "VAO.h"
#include "EBO.h"

class Pacman
{
private:
    int steps;
    double radius;

    float speed;
public:
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;

	VAO vao;

	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	Pacman(double radius_, int steps_);
    int get_vertices_size();
    int get_indices_size();
    ~Pacman();
	void updateInput(GLFWwindow * window);
    void draw(Shader &shaderProgram);
};

#endif