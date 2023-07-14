#ifndef _MAZE_H_
#define _MAZE_H_

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

class Maze
{
private:

public:
    std::vector<std::vector<int>> matrix;
    int map_size;

    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;

    VAO vao;

    void draw(Shader &shader);


    Maze(std::vector<std::vector<int>> matrix_);

};

#endif