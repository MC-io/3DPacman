#include "Level.h"

Level::Level(glm::vec3 start_pos, std::vector<std::string> matrix)
{
	std::vector<Texture> textures = { Texture("C:\\7mo Semestre\\Computacion Grafica\\TrabajoFinal\\Textures\\pared.jpg", 0 ,GL_RGB, GL_UNSIGNED_BYTE)};
    
	text_renderer = new TextRenderer(800,800);
    this->text_renderer->Load("C:\\7mo Semestre\\Computacion Grafica\\TrabajoFinal\\fonts\\OCRAEXT.TTF", 24);

    this->map = new Maze(matrix, 0.3, textures);
    this->pacman = new Pacman(0.1, 40);
    this->pacman->position = start_pos;
	this->pacman->rotation.x = 90.f;

    for (int i = 0; i < matrix.size(); i++)
    {
        for (int j = 0; j < matrix[i].size(); j++)
        {
            if (matrix[i][j] == '.')
            {
                food_vector.push_back(new Food(0.05, 20, i * map->map_size * 2, j * map->map_size * 2));
            }
			else if (matrix[i][j] == '@')
            {
                ghosts.push_back(new Ghost(0.15, 18, i * map->map_size * 2, j * map->map_size * 2));
            }
			else if (matrix[i][j] == '*')
			{
				cherries.push_back(new Cherry(0.15, 18, i * map->map_size * 2, j * map->map_size * 2));
			}
        }
    }
}

void Level::render_level(GLFWwindow * window, Shader & color_shader, Shader & texture_shader, Shader&text_shader, Camera & camera)
{
    camera.process_input(window);
	camera.updateMatrix(45.f, 0.1f, 100.f);

	camera.Matrix(color_shader, "camMatrix");
	camera.Matrix(texture_shader, "camMatrix");
	camera.Matrix(text_shader,"camMatrix");


	this->pacman->updateInput(window);

    this->pacman->draw(color_shader);
    this->map->draw(texture_shader);

	std::string label = "POINTS : " + std::to_string(pacman->pointCounter);
	glDepthMask(GL_FALSE); // Don't write into the depth buffer
	text_renderer->RenderText(label, 15.f, 15.0f, 2.5f,text_shader, glm::vec3(1.0f, .0f, 0.0f));
	glDepthMask(GL_TRUE); // Re-enable writing to the depth buffer

	text_renderer->RenderText( "GAME OVER", 0.0f, 0.0f, 0.025f,text_shader, glm::vec3(1.0f, .0f, 0.0f));

    for (int i = 0; i < food_vector.size(); i++) 
	{
		// Render the ball
		if (!food_vector[i]->is_eaten)
		{
			double dist = glm::distance(food_vector[i]->position, pacman->position);
			if (dist >= 0.05 + 0.2 * pacman->scale.x)
			{
				food_vector[i]->draw(color_shader);
			}
			else
			{
				std::cout << "COLISION" << std::endl;
				pacman->pointCounter++;
				food_vector[i]->is_eaten = true;
			}
		}
	}

	for (int i = 0; i < cherries.size(); i++)
	{
		if (!cherries[i]->is_eaten)
		{
			double dist = glm::distance(cherries[i]->position, pacman->position);
			if (dist >= 0.35)
			{
				cherries[i]->draw(color_shader);
			}
			else
			{
				std::cout << "COLISION" << std::endl;
				pacman->activate_powerup();
				cherries[i]->is_eaten = true;

			}
		}
	}

	for (int i = 0; i < ghosts.size(); i++)
	{
		ghosts[i]->move(this->map->matrix, this->map->map_size);
		ghosts[i]->draw(color_shader);
	}
}