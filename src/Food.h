#ifndef FOOD_CLASS_H
#define FOOD_CLASS_H

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

class Food
{
private:
    int steps;
    double radius;
public:
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;

	VAO vao;

	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	bool is_eaten;
	Food(double radius_, int steps_);
    int get_vertices_size();
    int get_indices_size();
    ~Food();
    void draw(Shader &shaderProgram);
};

#endif