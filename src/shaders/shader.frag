#version 330 core
  out vec4 FragColor;

  in vec2 TexCoord;
  uniform vec3 objColor;

  void main() {

  FragColor = vec4(objColor, 1.0); //= mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);// * vec4(ourColor, 1.0);

  }
