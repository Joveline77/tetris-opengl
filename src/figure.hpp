#include <vector>

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
};

class Figure {
  public:
//    static unsigned int VBO, VAO, EBO;
    static void init();
    static void init_ball();
    void clear();
};
