#include <GLFW/glfw3.h>

class input_keyboard {
  private:
    float speed = 0.5f;

    GLFWwindow *window;
    float loffset;
    float offset;

public:
static void processInput(GLFWwindow *window, float &loffset, float &offset) {

  float butt_speed = 0.03f;

  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
     offset += butt_speed; 
  }
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
     offset += -butt_speed;
  }
  if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS) {
     loffset += butt_speed; 
  }
  if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
     loffset += -butt_speed;
  }
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
}
};
