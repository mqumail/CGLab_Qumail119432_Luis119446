#include "application_solar.hpp"
#include "window_handler.hpp"


#include "utils.hpp"
#include "shader_loader.hpp"
#include "model_loader.hpp"
#include "GeometryNode.hpp"

#include <glbinding/gl/gl.h>
// use gl definitions from glbinding 
using namespace gl;

//dont load gl bindings from glfw
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
using namespace std;


ApplicationSolar::ApplicationSolar(std::string const& resource_path)
:Application{resource_path}
 ,planet_object{}
 ,m_view_transform{glm::translate(glm::fmat4{}, glm::fvec3{0.0f, 0.0f, 4.0f})}
 ,m_view_projection{utils::calculate_projection_matrix(initial_aspect_ratio)}
{ 
  initializeGeometry();
  initializeShaderPrograms();

  // Method to initialize SceneGraph and setup the planets
  initializeSceneGraph();
}

ApplicationSolar::~ApplicationSolar() {
  glDeleteBuffers(1, &planet_object.vertex_BO);
  glDeleteBuffers(1, &planet_object.element_BO);
  glDeleteVertexArrays(1, &planet_object.vertex_AO);
}

void ApplicationSolar::render() 
{
	traverseSceneGraph(theSceneGraph.getRoot());
}


void ApplicationSolar::outputPlanet(float x, float y, float z) {
  // bind shader to upload uniforms
  glUseProgram(m_shaders.at("planet").handle);

  glm::fmat4 model_matrix = glm::rotate(glm::fmat4{}, float(glfwGetTime()), glm::fvec3{0.0f, 1.0f, 0.0f});
  model_matrix = glm::translate(model_matrix, glm::fvec3{x, y, z});
  glUniformMatrix4fv(m_shaders.at("planet").u_locs.at("ModelMatrix"),
                     1, GL_FALSE, glm::value_ptr(model_matrix));

  // extra matrix for normal transformation to keep them orthogonal to surface
  glm::fmat4 normal_matrix = glm::inverseTranspose(glm::inverse(m_view_transform) * model_matrix);
  glUniformMatrix4fv(m_shaders.at("planet").u_locs.at("NormalMatrix"),
                     1, GL_FALSE, glm::value_ptr(normal_matrix));

  // bind the VAO to draw
  glBindVertexArray(planet_object.vertex_AO);

  // draw bound vertex array using bound shader
  glDrawElements(planet_object.draw_mode, planet_object.num_elements, model::INDEX.type, NULL);
}

void ApplicationSolar::uploadView() {
  // vertices are transformed in camera space, so camera transform must be inverted
  glm::fmat4 view_matrix = glm::inverse(m_view_transform);
  // upload matrix to gpu
  glUniformMatrix4fv(m_shaders.at("planet").u_locs.at("ViewMatrix"),
                     1, GL_FALSE, glm::value_ptr(view_matrix));
}

void ApplicationSolar::uploadProjection() {
  // upload matrix to gpu
  glUniformMatrix4fv(m_shaders.at("planet").u_locs.at("ProjectionMatrix"),
                     1, GL_FALSE, glm::value_ptr(m_view_projection));
}

// update uniform locations
void ApplicationSolar::uploadUniforms() { 
  // bind shader to which to upload unforms
  glUseProgram(m_shaders.at("planet").handle);
  // upload uniform values to new locations
  uploadView();
  uploadProjection();
}

///////////////////////////// intialisation functions /////////////////////////
// load shader sources
void ApplicationSolar::initializeShaderPrograms() {
  // store shader program objects in container
  m_shaders.emplace("planet", shader_program{{{GL_VERTEX_SHADER,m_resource_path + "shaders/simple.vert"},
                                           {GL_FRAGMENT_SHADER, m_resource_path + "shaders/simple.frag"}}});
  // request uniform locations for shader program
  m_shaders.at("planet").u_locs["NormalMatrix"] = -1;
  m_shaders.at("planet").u_locs["ModelMatrix"] = -1;
  m_shaders.at("planet").u_locs["ViewMatrix"] = -1;
  m_shaders.at("planet").u_locs["ProjectionMatrix"] = -1;
}

// load models
void ApplicationSolar::initializeGeometry() {
  model planet_model = model_loader::obj(m_resource_path + "models/sphere.obj", model::NORMAL);

  cout << m_resource_path + "models/sphere.obj";

  // generate vertex array object
  glGenVertexArrays(1, &planet_object.vertex_AO);
  // bind the array for attaching buffers
  glBindVertexArray(planet_object.vertex_AO);

  // generate generic buffer
  glGenBuffers(1, &planet_object.vertex_BO);
  // bind this as an vertex array buffer containing all attributes
  glBindBuffer(GL_ARRAY_BUFFER, planet_object.vertex_BO);
  // configure currently bound array buffer
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * planet_model.data.size(), planet_model.data.data(), GL_STATIC_DRAW);

  // activate first attribute on gpu
  glEnableVertexAttribArray(0);
  // first attribute is 3 floats with no offset & stride
  glVertexAttribPointer(0, model::POSITION.components, model::POSITION.type, GL_FALSE, planet_model.vertex_bytes, planet_model.offsets[model::POSITION]);
  // activate second attribute on gpu
  glEnableVertexAttribArray(1);
  // second attribute is 3 floats with no offset & stride
  glVertexAttribPointer(1, model::NORMAL.components, model::NORMAL.type, GL_FALSE, planet_model.vertex_bytes, planet_model.offsets[model::NORMAL]);

   // generate generic buffer
  glGenBuffers(1, &planet_object.element_BO);
  // bind this as an vertex array buffer containing all attributes0.0
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, planet_object.element_BO);
  // configure currently bound array buffer
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, model::INDEX.size * planet_model.indices.size(), planet_model.indices.data(), GL_STATIC_DRAW);

  // store type of primitive to draw
  planet_object.draw_mode = GL_TRIANGLES;
  // transfer number of indices to model object 
  planet_object.num_elements = GLsizei(planet_model.indices.size());
}

//****************************************************
// Function: initializeSceneGraph
//
// Purpose: Initialize the member variable 
//			theSceneGraph with the planets and sun
//
//****************************************************
void ApplicationSolar::initializeSceneGraph() 
{
	// solarSystem is the root for the sceneGraph
	GeometryNode* solarSystem = new GeometryNode();
	solarSystem->setName("Solar System");

	theSceneGraph.setRoot(solarSystem);

	// theSun is the child of solarSystem
	GeometryNode* theSun = new GeometryNode();
	theSun->setName("Sun");
	theSun->setLocalTransform(glm::translate(glm::fmat4{}, glm::fvec3{ 0.0, 0.0, 0.0 }));
	solarSystem->addChildren(theSun);

	// the code below is creating 8 planets and setting them as children to the sun
	// It is also positioning them so they are not all starting at the same position
	GeometryNode* mercury = new GeometryNode();
	mercury->setName("Mercury");
	mercury->setLocalTransform(glm::translate(glm::fmat4{}, glm::fvec3{ 5.0, 0.0, 1.0 }));
	theSun->addChildren(mercury);

	GeometryNode* venus = new GeometryNode();
	venus->setName("Venus");
	venus->setLocalTransform(glm::translate(glm::fmat4{}, glm::fvec3{ 10.0, 0.0, 10.0 }));
	theSun->addChildren(venus);

	GeometryNode* earth = new GeometryNode();
	earth->setName("Earth");
	earth->setLocalTransform(glm::translate(glm::fmat4{}, glm::fvec3{ 15.0, 0.0, 3.0 }));
	theSun->addChildren(earth);

	GeometryNode* mars = new GeometryNode();
	mars->setName("Mars");
	mars->setLocalTransform(glm::translate(glm::fmat4{}, glm::fvec3{ 20.0, 0.0, -1.0 }));
	theSun->addChildren(mars);

	GeometryNode* jupiter = new GeometryNode();
	jupiter->setName("Jupiter");
	jupiter->setLocalTransform(glm::translate(glm::fmat4{}, glm::fvec3{ 25.0, 0.0, 15.0 }));
	theSun->addChildren(jupiter);

	GeometryNode* saturn = new GeometryNode();
	saturn->setName("Saturn");
	saturn->setLocalTransform(glm::translate(glm::fmat4{}, glm::fvec3{ 30.0, 0.0, 19.0 }));
	theSun->addChildren(saturn);

	GeometryNode* uranus = new GeometryNode();
	uranus->setName("Uranus");
	uranus->setLocalTransform(glm::translate(glm::fmat4{}, glm::fvec3{ 35.0, 0.0, 1.0 }));
	theSun->addChildren(uranus);

	GeometryNode* neptune = new GeometryNode();
	neptune->setName("Neptune");
	neptune->setLocalTransform(glm::translate(glm::fmat4{}, glm::fvec3{ 40.0, 0.0, 5.0 }));
	theSun->addChildren(neptune);
}

//****************************************************
// Function: traverseSceneGraph
//
// Purpose: Recursively traverses the SceneGraph
//
//****************************************************
void ApplicationSolar::traverseSceneGraph(Node* theNode) 
{
	// First it gets the child of the solar system which is the sun
	// then it gets the children of the sun recursively and calls outputPlanet method to
	// draw them on the graph
	std::list<Node*> childList = theNode->getChildrenList();

	// The line that will stop this function to run forever
	if (childList.empty()) return;
	
	for (std::list<Node*>::iterator i = childList.begin(); i != childList.end(); ++i)
	{
		Node* currentChild = *i;
		traverseSceneGraph(currentChild);
		glm::vec3 tmpVec = glm::vec3(currentChild->getLocalTransform()[3]);
		outputPlanet(tmpVec[0], tmpVec[1], tmpVec[2]);
	}
}


///////////////////////////// callback functions for window events ////////////
// handle key input
void ApplicationSolar::keyCallback(int key, int action, int mods) {
	if (key == GLFW_KEY_W && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		m_view_transform = glm::translate(m_view_transform, glm::fvec3{ 0.0f, 0.0f, -0.1f });
		uploadView();
	}
	else if (key == GLFW_KEY_S && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		m_view_transform = glm::translate(m_view_transform, glm::fvec3{ 0.0f, 0.0f, 0.1f });
		uploadView();
	}
	if (key == GLFW_KEY_A && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		m_view_transform = glm::translate(m_view_transform, glm::fvec3{ -0.1f, 0.0f, 0.0f });
		uploadView();
	}
	else if (key == GLFW_KEY_D && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		m_view_transform = glm::translate(m_view_transform, glm::fvec3{ 0.1f, 0.0f, 0.0f });
		uploadView();
	}
}

//handle delta mouse movement input
void ApplicationSolar::mouseCallback(double pos_x, double pos_y) {
  // mouse handling
}

//handle resizing
void ApplicationSolar::resizeCallback(unsigned width, unsigned height) {
  // recalculate projection matrix for new aspect ration
  m_view_projection = utils::calculate_projection_matrix(float(width) / float(height));
  // upload new projection matrix
  uploadProjection();
}


// exe entry point
int main(int argc, char* argv[]) {
  Application::run<ApplicationSolar>(argc, argv, 3, 2);
}