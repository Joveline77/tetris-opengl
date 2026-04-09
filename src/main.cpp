#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "figure.hpp"
#include "input.hpp"


unsigned int VBO, EBO, VAO, sp_VBO, sp_VAO;

                        //added       //added          //added
//TODO window resizing, block class, sphera class, input_handler class

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

const unsigned int SRC_WIDTH = 800;
const unsigned int SRC_HEIGHT = 600;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
}

void Figure::init_ball() {
  const int segments = 64;
  const float radius = 0.08f;

  std::vector<float> c_vertices;

  auto width  = 1.0f;
  auto height = (SRC_WIDTH / SRC_HEIGHT) * width;

  c_vertices.insert(c_vertices.end(), {0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f});

  for (int i = 0; i <= segments; ++i) {
    float angle = 2.0f * 3.14159265359f * i / segments;
    float x = radius * cosf(angle);
    float y = radius * sinf(angle);

    c_vertices.insert(c_vertices.end(), {x, y, 0.0f, 1.0f, 1.0f, 0.0f});
  }

  glGenVertexArrays(1, &sp_VAO);
  glGenBuffers(1, &sp_VBO);

  glBindVertexArray(sp_VAO);
  glBindBuffer(GL_ARRAY_BUFFER, sp_VBO);
  glBufferData(GL_ARRAY_BUFFER, c_vertices.size() * sizeof(float), c_vertices.data(), GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  glBindVertexArray(0);

}

void Figure::init() {
   
  glGenBuffers(1, &VBO);
  glGenBuffers(1,  &EBO);
  glGenVertexArrays(1, &VAO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Figure_Coords::vertices), Figure_Coords::vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Figure_Coords::indices), Figure_Coords::indices, GL_STATIC_DRAW);
 
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(0));
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  }

int main() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif // __APPLE
  
  GLFWwindow* window = glfwCreateWindow(SRC_WIDTH, SRC_HEIGHT, "Ping-Pong-2D", NULL, NULL); 
  if (window == NULL) {
    std::cerr << "Failed to create GLFW window" << std::endl;
    return -1;
  }
 
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cerr << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  Figure* figure = new Figure();
  figure->init();
  figure->init_ball();

  float l, r = 0.0f;
  
  Shader ourShader("shaders/shader.vert", "shaders/shader.frag");
  ourShader.use();

  float lastTime = 0.0f;
  float deltatime = 0.0f;
  auto temp = glm::vec3(0.0f, 0.0f, 0.2f);
  
  while (!glfwWindowShouldClose(window)) {
    input_keyboard::processInput(window, r, l);


    float currentTime = glfwGetTime();
    deltatime = currentTime - lastTime;
    lastTime = currentTime;


    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    ourShader.use();

    unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");

    glm::mat4 trans;
    
    trans = glm::mat4();
    trans = glm::translate(glm::mat4(1.0f), glm::vec3(0.75f, 0.0f + r, 0.0f));

    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    trans = glm::mat4();
    trans = glm::translate(glm::mat4(1.0f), glm::vec3(-0.75, 0.0f + l, 0.0f));
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    glm::mat4 transBall = glm::mat4(1.0f);
    auto rv = glm::vec3(0.75f, 0.0f + r, 0.0f);
    auto lv = glm::vec3(-0.75f, 0.0f + l, 0.0f);
    Figure_Sphere::processRicochet(rv, lv, temp);
    Figure_Sphere::resetWhenNeed(rv, lv, temp);
    Figure_Sphere::circleSpeed(deltatime, temp);
    transBall = glm::translate(glm::mat4(1.0f), temp);
    
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transBall));
    glBindVertexArray(sp_VAO);

    glDrawArrays(GL_TRIANGLE_FAN, 0, 66);

    glBindVertexArray(0);

    //glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //glBufferData(GL_ARRAY_BUFFER, c_vertices.size() * sizeof(float), c_vertices.data(), GL_DYNAMIC_DRAW);

    //glDrawArrays(GL_TRIANGLE_FAN, 0, c_vertices.size() / 2);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);

  glfwTerminate();

  return 0;
}
