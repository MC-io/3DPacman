#ifndef _LEVEL_H_
#define _LEVEL_H_

#include "Pacman.h"
#include "Maze.h"
#include "Food.h"
#include "Camera.h"
#include "Ghost.h"
#include "Cherry.h"
#include "text_renderer.h"

class Level
{
public:
    Maze * map;
    Pacman * pacman;
    std::vector<Food*> food_vector;
    std::vector<Ghost*> ghosts;
    std::vector<Cherry*> cherries;
    TextRenderer* text_renderer;

    bool game_over;

    Level(glm::vec3 start_pos, std::vector<std::string> matrix);
    void render_level(GLFWwindow * window, Shader & color_shader, Shader & texture_shader, Shader & text_shader, Camera & camera);
};

#endif