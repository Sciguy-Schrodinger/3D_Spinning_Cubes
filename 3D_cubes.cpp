#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <functional>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace std;
using namespace glm;

int width = 1000;
int height = 1000;

int num_of_cubes = 0;

struct Cube {
  int fx, fy;
  float t;
};

vector<Cube> cubes;

int main(){
  glewExperimental = true;

  if(!glfwInit()){
    fprintf(stderr, "Failed to initialize GLFW\n");
    return -1;
  }

  glfwWindowHint(GLFW_SAMPLES, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
  glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow* window;
  window = glfwCreateWindow(width,height,"3D Cubes",NULL,NULL);
  if(window == NULL){
    fprintf(stderr,"Failed to open GLFW window\n");
    glfwTerminate();
    return -1;
  }
  
  glfwMakeContextCurrent(window);
  glewExperimental = true;

  if(glewInit() != GLEW_OK){
    fprintf(stderr,"Failed to initalize GLEW\n");
    return -1;
  }

  glm::mat4 Projection = glm::perspective(glm::radians(45.0f), float(width)/float(height), 0.1f, 100.0f);
  glm::mat4 View = glm::lookAt(glm::vec3(4,3,3), // Camera position
		   glm::vec3(0,0,0), // Look at origin
		   glm::vec3(0,1,0)  // Up vector
			       );
    
  glfwSetInputMode(window,GLFW_STICKY_KEYS,GL_TRUE);
    static const GLfloat g_vertex_buffer_data[] = {
    -1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f, 1.0f,-1.0f, 
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f, 
    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f
};

    static const GLfloat g_color_buffer_data[] = {
    0.583f,  0.771f,  0.014f,
    0.609f,  0.115f,  0.436f,
    0.327f,  0.483f,  0.844f,
    0.822f,  0.569f,  0.201f,
    0.435f,  0.602f,  0.223f,
    0.310f,  0.747f,  0.185f,
    0.597f,  0.770f,  0.761f,
    0.559f,  0.436f,  0.730f,
    0.359f,  0.583f,  0.152f,
    0.483f,  0.596f,  0.789f,
    0.559f,  0.861f,  0.639f,
    0.195f,  0.548f,  0.859f,
    0.014f,  0.184f,  0.576f,
    0.771f,  0.328f,  0.970f,
    0.406f,  0.615f,  0.116f,
    0.676f,  0.977f,  0.133f,
    0.971f,  0.572f,  0.833f,
    0.140f,  0.616f,  0.489f,
    0.997f,  0.513f,  0.064f,
    0.945f,  0.719f,  0.592f,
    0.543f,  0.021f,  0.978f,
    0.279f,  0.317f,  0.505f,
    0.167f,  0.620f,  0.077f,
    0.347f,  0.857f,  0.137f,
    0.055f,  0.953f,  0.042f,
    0.714f,  0.505f,  0.345f,
    0.783f,  0.290f,  0.734f,
    0.722f,  0.645f,  0.174f,
    0.302f,  0.455f,  0.848f,
    0.225f,  0.587f,  0.040f,
    0.517f,  0.713f,  0.338f,
    0.053f,  0.959f,  0.120f,
    0.393f,  0.621f,  0.362f,
    0.673f,  0.211f,  0.457f,
    0.820f,  0.883f,  0.371f,
    0.982f,  0.099f,  0.879f
};

    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);
    
    GLuint vertexbuffer;
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,(void*)0);

    GLuint colorbuffer;
    glGenBuffers(1, &colorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,0,(void*)0);
    
  const char* vertex_shader_src = R"(
#version 330 core
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 vertexColor;
uniform mat4 MVP;
out vec3 fragColor;
void main(){
    gl_Position = MVP*vec4(vertexPosition_modelspace, 1.0);
    
    fragColor = vertexColor;
}
)";

const char* fragment_shader_src = R"(
#version 330 core
in vec3 fragColor;
out vec4 color;
void main(){
    color = vec4(fragColor,1.0);
}
)";

 GLuint vs = glCreateShader(GL_VERTEX_SHADER);
 glShaderSource(vs, 1, &vertex_shader_src, NULL);
 glCompileShader(vs);

 GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
 glShaderSource(fs, 1, &fragment_shader_src, NULL);
 glCompileShader(fs);

 GLuint shaderProgram = glCreateProgram();
 glAttachShader(shaderProgram, vs);
 glAttachShader(shaderProgram, fs);
 glLinkProgram(shaderProgram);
 glUseProgram(shaderProgram);

 glEnable(GL_DEPTH_TEST);
 glUseProgram(shaderProgram);
  
 GLuint MatrixID = glGetUniformLocation(shaderProgram, "MVP");

 static bool spacePressedPreviousFrame = false;
 vector<glm::vec3> positions;
 vector<function<float(float)>> functions;

 functions.push_back([](float t){return sin(t);});
 functions.push_back([](float t){return cos(t);});
 functions.push_back([](float t){return fmod(tan(t),1.0f);});
 functions.push_back([](float t){return exp(-t);});
 functions.push_back([](float t){return pow(t,2)+5*t-10;});

 char title[128];
 
 double previousTime = glfwGetTime();
 int framecount = 0;
 
  do{

    double currentTime = glfwGetTime();
    framecount++;

    if(currentTime - previousTime >= 1.0){
      sprintf(title, "3D Cubes | Number of cubes: %d at FPS: %d ", num_of_cubes, framecount);
      glfwSetWindowTitle(window, title);
      framecount = 0;
      previousTime = currentTime;
    }
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    bool spacePressed = glfwGetKey(window,GLFW_KEY_SPACE) == GLFW_PRESS;
    
    if(spacePressed && !spacePressedPreviousFrame){
      num_of_cubes++;
      Cube newcube;
      newcube.fx = rand()%functions.size();
      newcube.fy = rand()%functions.size();
      newcube.t = 0.0f;
      cubes.push_back(newcube);
    }

    spacePressedPreviousFrame = spacePressed;

    for(auto &cube : cubes){
    cube.t += 0.01f;
    float x = glm::clamp(functions[cube.fx](cube.t), 0.0f*width, 1.0f*width);
    float y = glm::clamp(functions[cube.fy](cube.t), 0.0f*height, 1.0f*height);
    float z = 0;

    float scale = glm::clamp(functions[cube.fy](cube.t),-5.0f,5.0f);
    
    glm::vec3 pos(x,y,z);
    glm::mat4 Model = glm::translate(glm::mat4(1.0f), pos) * glm::rotate(glm::mat4(1.0f), cube.t, glm::vec3(0.5f, 1.0f, 0.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(scale));

    glm::mat4 MVP = Projection * View * Model;
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
    
    glBindVertexArray(VertexArrayID);
    glDrawArrays(GL_TRIANGLES, 0, 12*3);
  }
    glfwSwapBuffers(window);
    glfwPollEvents();
    
    }
    while(glfwGetKey(window,GLFW_KEY_ENTER) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);

  glfwTerminate();
  return 0;
}
