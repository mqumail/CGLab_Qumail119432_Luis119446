#include "application_solar.hpp"
#include "window_handler.hpp"


#include "utils.hpp"
#include "shader_loader.hpp"
#include "model_loader.hpp"
#include "PointLightNode.hpp" // assignment 3
#include "texture_loader.hpp" // assignment 4

#define _USE_MATH_DEFINES
#include <math.h>

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

glm::vec4 origin;

// function to generate a random float between min and max parameters
// ref: https://stackoverflow.com/questions/5289613/generate-random-float-between-two-floats
float random(float min, float max)
{
	return (max - min) * (float(rand() % 100) / 100) + min;
}

ApplicationSolar::ApplicationSolar(std::string const& resource_path) : Application{resource_path}
 ,planet_object{}
 ,star_object{} // add this star_object{} since now we have model_object for stars
 ,texture_object{}
 ,m_view_transform{glm::translate(glm::fmat4{}, glm::fvec3{0.0f, 0.0f, 4.0f})}
 ,m_view_projection{utils::calculate_projection_matrix(initial_aspect_ratio)}
{ 
	// Method to initialize SceneGraph and setup the planets
	initializeSceneGraph();

	// Assignment 4 - Helper function to get all solar objects
	getAllSolarObjects(solarSystem);

	// Assignment 4
	initializeTextures();

	// Method to initialize planets
	initializeGeometry();

	// Method to initialize star points
	initializeStarPoints();

	initializeShaderPrograms();
}

void ApplicationSolar::initializeSceneGraph()
{
	// solarSystem is the root for the sceneGraph
	solarSystem->setName("Solar System");

	theSceneGraph.setRoot(solarSystem);

	// theSun is the child of solarSystem
	GeometryNode* theSun = new GeometryNode();
	theSun->setName("sun");
	theSun->setSize(3.0f);
	theSun->setRotationSpeed(1.0f);
	theSun->setDistanceToOrigin(0.0f);
	theSun->setHasMoonAtIndex(-1);
	theSun->setIsMoon(false);
	theSun->setColorR(0.9f);
	theSun->setColorG(0.7f);
	theSun->setColorB(0.2f);
	theSun->angularSpeed = 4.0;
	solarSystem->addChildren(theSun);

	// the code below is creating 8 planets and setting them as children to the sun
	// It is also positioning them so they are not all starting at the same position
	GeometryNode* mercury = new GeometryNode();
	mercury->setName("mercury");
	mercury->setSize(0.3f);
	mercury->setRotationSpeed(0.2f);
	mercury->setDistanceToOrigin(5.0f);
	mercury->setHasMoonAtIndex(-1);
	mercury->setIsMoon(false);
	mercury->setColorR(1.0f);
	mercury->setColorG(1.0f);
	mercury->setColorB(0.0f);
	mercury->angularSpeed = 14.0;
	theSun->addChildren(mercury);

	GeometryNode* venus = new GeometryNode();
	venus->setName("venus");
	venus->setSize(0.89f);
	venus->setRotationSpeed(0.2f);
	venus->setDistanceToOrigin(10.0f);
	venus->setHasMoonAtIndex(-1);
	venus->setIsMoon(false);
	venus->setColorR(1.0f);
	venus->setColorG(0.0f);
	venus->setColorB(1.0f);
	venus->angularSpeed = 24.0;
	theSun->addChildren(venus);

	GeometryNode* earth = new GeometryNode();
	earth->setName("earth");
	earth->setSize(0.9f);
	earth->setRotationSpeed(0.2f);
	earth->setDistanceToOrigin(15.0f);
	earth->setHasMoonAtIndex(4);
	earth->setIsMoon(false);
	earth->setColorR(0.0f);
	earth->setColorG(1.0f);
	earth->setColorB(1.0f);
	earth->angularSpeed = 2.0;
	theSun->addChildren(earth);

	GeometryNode* moon = new GeometryNode();
	moon->setName("moon");
	moon->setSize(0.5f);
	moon->setRotationSpeed(2.1f);
	moon->setDistanceToOrigin(3.7f);
	moon->setHasMoonAtIndex(-1);
	moon->setIsMoon(true);
	moon->setColorR(0.0f);
	moon->setColorG(1.0f);
	moon->setColorB(0.0f);
	earth->addChildren(moon);

	GeometryNode* mars = new GeometryNode();
	mars->setName("mars");
	mars->setSize(0.7f);
	mars->setRotationSpeed(1.1f);
	mars->setDistanceToOrigin(20.7f);
	mars->setHasMoonAtIndex(-1);
	mars->setIsMoon(false);
	mars->setColorR(1.0f);
	mars->setColorG(1.0f);
	mars->setColorB(1.0f);
	mars->angularSpeed = 7.0;
	theSun->addChildren(mars);

	GeometryNode* jupiter = new GeometryNode();
	jupiter->setName("jupiter");
	jupiter->setSize(1.5f);
	jupiter->setRotationSpeed(1.2f);
	jupiter->setDistanceToOrigin(25.7f);
	jupiter->setHasMoonAtIndex(7);
	jupiter->setIsMoon(false);
	jupiter->setColorR(0.3f);
	jupiter->setColorG(0.4f);
	jupiter->setColorB(1.0f);
	jupiter->angularSpeed = 39.0;
	theSun->addChildren(jupiter);

	GeometryNode* saturn = new GeometryNode();
	saturn->setName("saturn");
	saturn->setSize(1.2f);
	saturn->setRotationSpeed(1.0f);
	saturn->setDistanceToOrigin(30.7f);
	saturn->setHasMoonAtIndex(-1);
	saturn->setIsMoon(false);
	saturn->setColorR(1.0f);
	saturn->setColorG(0.4f);
	saturn->setColorB(0.9f);
	saturn->angularSpeed = 55.0;
	theSun->addChildren(saturn);

	GeometryNode* uranus = new GeometryNode();
	uranus->setName("uranus");
	uranus->setSize(1.1f);
	uranus->setRotationSpeed(0.9f);
	uranus->setDistanceToOrigin(35.7f);
	uranus->setHasMoonAtIndex(-1);
	uranus->setIsMoon(false);
	uranus->setColorR(0.1f);
	uranus->setColorG(0.3f);
	uranus->setColorB(0.4f);
	uranus->angularSpeed = 89.0;
	theSun->addChildren(uranus);

	GeometryNode* neptune = new GeometryNode();
	neptune->setName("neptune");
	neptune->setSize(1.0f);
	neptune->setRotationSpeed(0.1f);
	neptune->setDistanceToOrigin(40.7f);
	neptune->setHasMoonAtIndex(-1);
	neptune->setIsMoon(false);
	neptune->setColorR(0.4f);
	neptune->setColorG(0.2f);
	neptune->setColorB(0.9f);
	theSun->addChildren(neptune);

	GeometryNode* pluto = new GeometryNode();
	pluto->setName("pluto");
	pluto->setSize(0.2f);
	pluto->setRotationSpeed(1.2f);
	pluto->setDistanceToOrigin(45.7f);
	pluto->setHasMoonAtIndex(-1);
	pluto->setIsMoon(false);
	pluto->setColorR(0.0f);
	pluto->setColorG(1.0f);
	pluto->setColorB(0.4f);
	theSun->addChildren(pluto);

	GeometryNode* skybox = new GeometryNode();
	skybox->setName("skybox");
	skybox->setSize(50.0f);
	skybox->setRotationSpeed(0.0f);
	skybox->setDistanceToOrigin(0.0f);
	skybox->setHasMoonAtIndex(-1);
	skybox->setIsMoon(false);
	skybox->setColorR(0.0f);
	skybox->setColorG(0.0f);
	skybox->setColorB(1.0f);
	solarSystem->addChildren(skybox);
}

void ApplicationSolar::getAllSolarObjects(Node * theNode)
{
	vector<Node*> childList = theNode->getChildrenList();

	// The line that will stop this function to run forever
	if (childList.empty()) return;

	for (std::vector<Node*>::iterator it = childList.begin(); it != childList.end(); ++it)
	{
		Node* currentChild = *it;
		getAllSolarObjects(currentChild);
		allSolarObjects.push_back(currentChild);
	}
}

void ApplicationSolar::initializeTextures()
{
	pixel_data newTexture;

	for (int i = 0; i < NUM_PLANETS; i++)
	{
		texture_object[i] = i;
		newTexture = texture_loader::file(m_resource_path + "textures/" + allSolarObjects[i]->getName() + ".png");

		glActiveTexture(GL_TEXTURE0 + i);
		glGenTextures(1, &texture_object[i]);
		glBindTexture(GL_TEXTURE_2D, texture_object[i]);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D,
			0,
			GL_RGB,
			newTexture.width, newTexture.height,
			0,
			newTexture.channels, newTexture.channel_type, newTexture.ptr());
	}
}

void ApplicationSolar::initializeGeometry() 
{
	model planet_model = model_loader::obj(m_resource_path + "models/sphere.obj", model::NORMAL | model::TEXCOORD);
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
	
	// texture - Assignment 4
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, model::TEXCOORD.components, model::TEXCOORD.type, GL_FALSE, planet_model.vertex_bytes, planet_model.offsets[model::TEXCOORD]);
	
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

void ApplicationSolar::initializeStarPoints()
{
	// generate 6000 points(3 for position, 3 for color) and add them to star_buffer 
	for (int i = 0; i < 6000; i++)
	{
		// Position
		star_buffer.push_back(random(-50, 50));
		star_buffer.push_back(random(-50, 50));
		star_buffer.push_back(random(-50, -10));

		// Color
		star_buffer.push_back(random(0, 1));
		star_buffer.push_back(random(0, 1));
		star_buffer.push_back(random(0, 1));
	}

	model star_model = { star_buffer, model::POSITION | model::NORMAL};

	// generate vertex array object
	glGenVertexArrays(1, &star_object.vertex_AO);
	// bind the array for attaching buffers
	glBindVertexArray(star_object.vertex_AO);

	// generate generic buffer
	glGenBuffers(1, &star_object.vertex_BO);
	// bind this as an vertex array buffer containing all attributes
	glBindBuffer(GL_ARRAY_BUFFER, star_object.vertex_BO);
	// configure currently bound array buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * star_model.data.size(), star_model.data.data(), GL_STATIC_DRAW);

	// activate first attribute on gpu
	glEnableVertexAttribArray(0);
	// first attribute is 3 floats with no offset & stride
	glVertexAttribPointer(0, model::POSITION.components, model::POSITION.type, GL_FALSE, star_model.vertex_bytes, star_model.offsets[model::POSITION]);
	// activate second attribute on gpu
	glEnableVertexAttribArray(1);
	// second attribute is 3 floats with no offset & stride
	glVertexAttribPointer(1, model::NORMAL.components, model::NORMAL.type, GL_FALSE, star_model.vertex_bytes, star_model.offsets[model::NORMAL]);
	// generate generic buffer
	glGenBuffers(1, &planet_object.element_BO);
	// bind this as an vertex array buffer containing all attributes0.0
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, planet_object.element_BO);
	// configure currently bound array buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, model::INDEX.size * star_model.indices.size(), star_model.indices.data(), GL_STATIC_DRAW);
	// store type of primitive to draw
	star_object.draw_mode = GL_POINTS;
}

void ApplicationSolar::initializeShaderPrograms() 
{
	// store shader program objects in container
	m_shaders.emplace("planet", shader_program{ {{GL_VERTEX_SHADER,m_resource_path + "shaders/simple.vert"},
				{GL_FRAGMENT_SHADER, m_resource_path + "shaders/simple.frag"}} });

	// request uniform locations for shader program
	m_shaders.at("planet").u_locs["NormalMatrix"] = -1;
	m_shaders.at("planet").u_locs["ModelMatrix"] = -1;
	m_shaders.at("planet").u_locs["ViewMatrix"] = -1;
	m_shaders.at("planet").u_locs["ProjectionMatrix"] = -1;
	
	// Assignment 3
	m_shaders.at("planet").u_locs["DiffuseColor"] = -1;
	m_shaders.at("planet").u_locs["SunPosition"] = -1;
	m_shaders.at("planet").u_locs["ShaderMode"] = -1;

	// Assignment 4
	m_shaders.at("planet").u_locs["ColorTex"] = -1;
	m_shaders.at("planet").u_locs["NormalMapIndex"] = -1;
	m_shaders.at("planet").u_locs["UseBumpMap"] = -1;


	// store shader program objects in container
	m_shaders.emplace("star", shader_program{{
		{GL_VERTEX_SHADER,m_resource_path + "shaders/vao.vert"}, 
		{GL_FRAGMENT_SHADER, m_resource_path + "shaders/vao.frag"}
		}});

	// request uniform locations for shader program
	m_shaders.at("star").u_locs["ViewMatrix"] = -1;
	m_shaders.at("star").u_locs["ProjectionMatrix"] = -1;
}

void ApplicationSolar::render() 
{
	uploadStars();
	traverseSceneGraph();
}

// Method to actually draw the stars (render them), called by render method.
void ApplicationSolar::uploadStars()
{
	glUseProgram(m_shaders.at("star").handle);
	glBindVertexArray(star_object.vertex_AO);
	glDrawArrays(star_object.draw_mode, 0, 6000);
}

void ApplicationSolar::traverseSceneGraph()
{
	for (int i = 0; i < NUM_PLANETS; i++) 
	{
		uploadPlanet(i);
	}
}

// Assignment 1
void ApplicationSolar::uploadPlanet(int i) const
{
	Node* newPlanet = allSolarObjects[i];

	if (!newPlanet->getIsMoon())
	{
		glUseProgram(m_shaders.at("planet").handle);
		glm::fmat4 model_matrix = glm::rotate(glm::fmat4{}, float(glfwGetTime() * newPlanet->getRotationSpeed()), glm::fvec3{ 0.0f, 1.0f, 0.0f });
		model_matrix = glm::translate(model_matrix, glm::fvec3{ 0.0f, 0.0f, newPlanet->getDistanceToOrigin() });

		model_matrix = glm::scale(model_matrix, glm::fvec3{ newPlanet->getSize(), newPlanet->getSize(), newPlanet->getSize() });

		glUniformMatrix4fv(m_shaders.at("planet").u_locs.at("ModelMatrix"),
			1, GL_FALSE, glm::value_ptr(model_matrix));

		// extra matrix for normal transformation to keep them orthogonal to surface
		glm::fmat4 normal_matrix = glm::inverseTranspose(glm::inverse(m_view_transform) * model_matrix);
		glUniformMatrix4fv(m_shaders.at("planet").u_locs.at("NormalMatrix"),
			1, GL_FALSE, glm::value_ptr(normal_matrix));

		//assignment 3
		glm::vec3 planetColor(newPlanet->getColorR(), newPlanet->getColorG(), newPlanet->getColorB());
		glUniform3fv(m_shaders.at("planet").u_locs.at("DiffuseColor"), 1, glm::value_ptr(planetColor));

		glm::fmat4 view_matrix = glm::inverse(m_view_transform);
		std::string str = newPlanet->getName();

		if (!str.compare("sun")) 
		{
			origin = glm::vec4{ 0.0, 0.0, 0.0, 0.0 };
		}
		else 
		{
			origin = glm::vec4{ 0.0, 0.0, 0.0, 1.0 };
		}

		glm::vec4 sunPos4 = view_matrix * origin;
		glm::vec3 sunPos3(sunPos4);
		glUniform3fv(m_shaders.at("planet").u_locs.at("SunPosition"), 1, glm::value_ptr(sunPos3));

		glActiveTexture(GL_TEXTURE0 + i);
		int normalMapID = NUM_PLANETS;

		glUseProgram(m_shaders.at("planet").handle);
		glUniform1i(m_shaders.at("planet").u_locs.at("ColorTex"), i);
		glUniform1i(m_shaders.at("planet").u_locs.at("NormalMapIndex"), normalMapID);

		//add planet rotation on it's axis - const for all except skybox
		if (str.compare("skybox")) 
		{
			model_matrix = glm::rotate(model_matrix, float(glfwGetTime() * M_PI / 10), glm::fvec3{ 0.0f, 1.0f, 0.0f });
		}

		if (!str.compare("earth")) 
		{
			glUniform1f(m_shaders.at("planet").u_locs.at("UseBumpMap"), true);
		}
		else 
		{
			glUniform1f(m_shaders.at("planet").u_locs.at("UseBumpMap"), false);
		}

		// bind the VAO to draw
		glBindVertexArray(planet_object.vertex_AO);

		// draw bound vertex array using bound shader
		glDrawElements(planet_object.draw_mode, planet_object.num_elements, model::INDEX.type, NULL);
	}
}

// update uniform locations
void ApplicationSolar::uploadUniforms()
{
	//upload uniform values to new locations
	updateUniformLocations();
	uploadView();
	uploadProjection();
}

void ApplicationSolar::uploadView() 
{
	glUseProgram(m_shaders.at("planet").handle);

  // vertices are transformed in camera space, so camera transform must be inverted
  glm::fmat4 view_matrix = glm::inverse(m_view_transform);
  
  // Assignment 3
  glm::vec4 sunPos4 = view_matrix * origin;
  glm::vec3 sunPos3(sunPos4);
  glUniform3fv(m_shaders.at("planet").u_locs.at("SunPosition"), 1, glm::value_ptr(sunPos3));
  
  // upload matrix to gpu
  glUseProgram(m_shaders.at("planet").handle);
  glUniformMatrix4fv(m_shaders.at("planet").u_locs.at("ViewMatrix"),
                     1, GL_FALSE, glm::value_ptr(view_matrix));

  // upload matrix to gpu
  glUseProgram(m_shaders.at("star").handle);
  glUniformMatrix4fv(m_shaders.at("star").u_locs.at("ViewMatrix"),
					1, GL_FALSE, glm::value_ptr(view_matrix));
}

void ApplicationSolar::uploadProjection() 
{
  // upload matrix to gpu
	glUseProgram(m_shaders.at("planet").handle);
  glUniformMatrix4fv(m_shaders.at("planet").u_locs.at("ProjectionMatrix"),
                     1, GL_FALSE, glm::value_ptr(m_view_projection));

  // upload matrix to gpu
  glUseProgram(m_shaders.at("star").handle);
  glUniformMatrix4fv(m_shaders.at("star").u_locs.at("ProjectionMatrix"),
	  1, GL_FALSE, glm::value_ptr(m_view_projection));
}

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
	// Assignment 3 - shading modes
	else if (key == GLFW_KEY_1 && action != GLFW_PRESS) 
	{
		glUseProgram(m_shaders.at("planet").handle);
		glUniform1f(m_shaders.at("planet").u_locs.at("ShaderMode"), 1);
	}
	else if (key == GLFW_KEY_2 && action != GLFW_PRESS) 
	{
		glUseProgram(m_shaders.at("planet").handle);
		glUniform1f(m_shaders.at("planet").u_locs.at("ShaderMode"), 2);
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

ApplicationSolar::~ApplicationSolar() 
{
	glDeleteBuffers(1, &planet_object.vertex_BO);
	glDeleteBuffers(1, &planet_object.element_BO);
	glDeleteVertexArrays(1, &planet_object.vertex_AO);

	// clean up memory when the program ends
	glDeleteBuffers(1, &star_object.vertex_BO);
	glDeleteBuffers(1, &star_object.element_BO);
	glDeleteVertexArrays(1, &star_object.vertex_AO);
}