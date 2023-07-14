#ifndef _LEVEL_H_
#define _LEVEL_H_

#include "Pacman.h"
#include "Maze.h"
#include "Food.h"

class Level
{
public:
    Maze * map;
    Pacman * pacman;
    std::vector<Food*> food_vector;

    bool game_over;


    Level(glm::vec3 start_pos, std::vector<std::vector<int>> matrix, std::vector<glm::vec3> food_pos);
    void render_level();

};

#endif