#include "Level.h"

Level::Level(glm::vec3 start_pos, std::vector<std::string> matrix, std::vector<glm::vec3> food_pos)
{
    this->map = new Maze(matrix, 0.1);

    this->pacman = new Pacman(50, 0.4);
    this->pacman->position = start_pos;

    for (int i = 0; i < food_pos.size(); i++)
    {
        food_vector.push_back(new Food(30, 0.15));
        food_vector[i]->position = food_pos[i];
    }


}