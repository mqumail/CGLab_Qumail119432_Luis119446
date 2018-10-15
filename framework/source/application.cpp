#include "application.hpp"
#include "utils.hpp"
#include "launcher.hpp"

#include <glbinding/gl/gl.h>
// use gl definitions from glbinding 
using namespace gl;

//dont load gl bindings from glfw
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>

#include <iostream>

Application::Application(std::string const& resource_path)
 :m_resource_path{resource_path}
 ,m_window_width{640u}
 ,m_window_height{480u}
 ,m_view_transform{glm::translate(glm::fmat4{}, glm::fvec3{0.0f, 0.0f, 4.0f})}
 ,m_view_projection{calculate_projection_matrix(m_window_width, m_window_height)}
 ,m_shaders{}
{}

Application::~Application() {
  // free all shader program objects
  for (auto const& pair : m_shaders) {
    glDeleteProgram(pair.second.handle);
  }
}

void Application::reloadShaders(GLFWwindow* window, bool throwing) {
  update_shader_programs(m_shaders, throwing);
  // after shader programs are recompiled, uniform locations may change
  uploadUniforms();
}

void Application::resize_callback(GLFWwindow* m_window, int width, int height) {
  m_window_width = width;
  m_window_height = height;
  // resize framebuffer
  glViewport(0, 0, width, height);

  m_view_projection = calculate_projection_matrix(width, height);
  updateProjection();
}

// handle key input
void Application::key_callback(GLFWwindow* m_window, int key, int scancode, int action, int mods) {
  if ((key == GLFW_KEY_ESCAPE || key == GLFW_KEY_Q) && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(m_window, 1);
  }
  else if (key == GLFW_KEY_R && action == GLFW_PRESS) {
    reloadShaders(m_window, false);
  }
  keyCallback(key, scancode, action, mods);
}

//handle mouse movement input
void Application::mouse_callback(GLFWwindow* window, double pos_x, double pos_y) {
  mouseCallback(pos_x, pos_y);
  // reset cursor pos to receive position delta next frame
  glfwSetCursorPos(window, 0.0, 0.0);
}

// update shader uniform locations
void Application::updateUniformLocations() {
  for (auto& pair : m_shaders) {
    for (auto& uniform : pair.second.u_locs) {
      // store uniform location in map
      uniform.second = utils::glGetUniformLocation(pair.second.handle, uniform.first.c_str());
    }
  }
}

std::map<std::string, shader_program>& Application::getShaderPrograms() {
  return m_shaders;
}