#include <vector>
#include <cstdlib>
#include <ctime>

namespace Figure_Coords {
  float vertices[] = {
    // positions          // colors           // texture coords
     0.05f,  0.27f, 0.0f,   1.0f, 1.0f, 1.0f,   //1.0f, 1.0f,   // top right
     0.05f, -0.27f, 0.0f,   1.0f, 1.0f, 1.0f,   //1.0f, 0.0f,   // bottom right
    -0.05f, -0.27f, 0.0f,   1.0f, 1.0f, 1.0f,   //0.0f, 0.0f,   // bottom left
    -0.05f,  0.27f, 0.0f,   1.0f, 1.0f, 1.0f    //0.0f, 1.0f    // top left 
  };

  unsigned int indices[] = {
    0, 1, 3, 
    1, 2, 3
  };
};

namespace Figure_Sphere {
  float ysp = 1.0f;
  float xsp = 2.5f;
  bool firstSP = true;

void randomSpeed() {
    std::srand(std::time(0));
    int rNum = 1 + std::rand() % 2;
    if (rNum == 1) {
      xsp *= -1;
    }
  }

  std::vector<float> circleVertices(float cx, float cy, float radius, int segments) {
    const float PI = 3.14159265359f;
    std::vector<float> vertices;
    vertices.reserve((segments + 2) * 2);

    vertices.push_back(cx);
    vertices.push_back(cy);

    for (int i = 0; i <= segments; i++) {
      float angle = 2.0f * PI * i / segments;
      vertices.push_back(cx + radius * cos(angle));
      vertices.push_back(cy + radius * cos(angle));
    }

    return vertices;
  }
  void circleSpeed(float glfwTime, glm::vec3 &vec) {
    if (firstSP) {
      randomSpeed();
      firstSP = false;
    }
    //xsp MUST BE > ysp, BTW NO, i've added wall-ricochet(like wall-jump but ricochet)
    vec.x += vec.z * glfwTime * xsp;
    vec.y += vec.z * glfwTime * ysp;
  }
  void resetWhenNeed(glm::vec3 &r, glm::vec3 &l, glm::vec3 &sphere) {
   if (sphere.x > (r.x + 0.1f) || sphere.x < l.x - 0.1f) {
     sphere = glm::vec3(0.0f, 0.0f, 0.2f);
     randomSpeed();
     ysp = 1.0f;
   }
   if (sphere.y > 1.0f || sphere.y < -1.0f) {
     ysp *= -1;
   }
  }

  void processRicochet(glm::vec3 &r, glm::vec3 &l, glm::vec3 &sphere) {
    auto ycof = Figure_Coords::vertices[1];
    const float MAX_ANGLE_FACTOR = 1.0f;

    if ((((r.x - 0.09f) < sphere.x) && r.x < sphere.x) && ((r.y + ycof) > sphere.y && (r.y - ycof) < sphere.y)) {
    float rIY = (sphere.y - r.y) / ycof;
    ysp = rIY * MAX_ANGLE_FACTOR;
    sphere.z *= -1;
    return;
    }
    if ((((l.x + 0.09f) > sphere.x) && l.x > sphere.x) && ((l.y + ycof) > sphere.y && (l.y - ycof) < sphere.y)) {
      float lIY = (sphere.y - l.y) / ycof;
      ysp = lIY * MAX_ANGLE_FACTOR;
      sphere.z *= -1;
      return;
    }
  }

  
};

class Figure {
  public:
//    static unsigned int VBO, VAO, EBO;
    static void init();
    static void init_ball();
    void clear();
};
