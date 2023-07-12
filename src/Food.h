#ifndef FOOD_CLASS_H
#define FOOD_CLASS_H
#include <glm/glm.hpp>
#include<glad/glad.h>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include<GLFW/glfw3.h>
#include "Shader.h"
class Food
{
public:
	bool isEaten;
	double center_y;
	double center_x;
	double center_z;
	GLuint ID;
    GLfloat* vertices;
    GLuint* indices;
	Food(int vsize_, int isize_,double radius_,int steps_){
        vsize = vsize_;
        isize = isize_;
        vertices = new GLfloat[vsize_];
        indices = new GLuint[isize_];
        radius = radius_;
        steps = steps_;
		center_x = 0;
		center_y = 0;
		center_z = 0;
		isEaten = false;
    }
    int getSizeV(){
        return vsize;
    }
    int getSizeI(){
        return isize;
    }
     ~Food() {
        delete[] vertices;
        delete[] indices;
    }
    void createFood(int  &vert_pos, int  &index_pos) {
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


	for (int i = 0; i <= steps; i++)
	{
		indices[index_pos + i * 3] = (vert_pos / 3) + 0;
		indices[index_pos + i * 3 + 1] = (vert_pos / 3) + i + 1;  
		indices[index_pos + i * 3 + 2] = (vert_pos / 3) + i + 2;

		
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

			
		}
	}
	for (int i = 0; i <= steps; i++)
	{
		indices[index_pos + (steps + 1) * 3 + (((steps / 2) - 1 - 1) * (steps + 1) * 6) + i * 3] = (vert_pos / 3) + 1 + (steps + 1) * ((steps / 2) - 2) + i;
		indices[index_pos + (steps + 1) * 3 + (((steps / 2) - 1 - 1) * (steps + 1) * 6) + i * 3 + 1] = (vert_pos / 3) + 1 + (steps + 1) * ((steps / 2) - 2) + i + 1;
		indices[index_pos + (steps + 1) * 3 + (((steps / 2) - 1 - 1) * (steps + 1) * 6) + i * 3 + 2] = (vert_pos / 3) + 1 + (steps + 1) * ((steps / 2) - 1);

		
	}

	//vert_pos += 3 * (steps + 1) * (steps / 2 - 1) + 9;
	//index_pos += ((steps + 1) * (steps / 2 - 1) * 6) + ((steps + 1) * (steps / 2 - 1) * 3) + (steps + 1) * 3 + 3;
    }
     void draw(Shader shaderProgram) {
       double  timeValue = glfwGetTime();
	int vertexColorLocation = glGetUniformLocation(shaderProgram.ID, "ourColor");
	glUniform4f(vertexColorLocation, 1.0f, 1.f, 0.3f, 1.0f);
	glDrawElements(GL_TRIANGLES, (steps + 1) * 3 + (((steps / 2) - 1 - 1) * (steps + 1) * 6) + steps * 3 + 3 , GL_UNSIGNED_INT, 0);


	
       
    }
	
private:
    
    int steps;
    double radius;
    int vsize;
    int isize;
};


#endif