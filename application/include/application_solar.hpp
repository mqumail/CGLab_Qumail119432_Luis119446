#ifndef APPLICATION_SOLAR_HPP
#define APPLICATION_SOLAR_HPP

#include "application.hpp"
#include "model.hpp"
#include "structs.hpp"
#include "SceneGraph.hpp"
#include "GeometryNode.hpp"

#define NUM_PLANETS 12

// gpu representation of model
class ApplicationSolar : public Application {
 public:

	 //// struct for stars (not being used currently)
	 struct Star {
		 float position[3];
		 float color[3];
		 string name;
	 };

	 vector<Star> star_list;

  // allocate and initialize objects
  ApplicationSolar(std::string const& resource_path);
  // free allocated objects
  ~ApplicationSolar();

  // react to key input
  void keyCallback(int key, int action, int mods);
  //handle delta mouse movement input
  void mouseCallback(double pos_x, double pos_y);
  //handle resizing
  void resizeCallback(unsigned width, unsigned height);
  // draw all objects
  void render();
  // draw all planets
  void uploadPlanet(int i) const;
  // upload stars
  void uploadStars();
  // initialize textures
  void initializeTextures();

 protected:
  void initializeSceneGraph();
  void initializeShaderPrograms();
  void initializeGeometry();
  void initializeStarPoints();
  // update uniform values
  void uploadUniforms();
  // upload projection matrix
  void uploadProjection();
  // upload view matrix
  void uploadView();
  void initializeFrameBuffer();	// _ ass5
  void initializeScreenQuad();	// _ ass5
  void traverseSceneGraph();
  void getAllSolarObjects(Node * theNode);

  // cpu representation of model
  model_object planet_object;

  // cpu representation of star
  model_object star_object;
  
  // camera transform matrix
  glm::fmat4 m_view_transform;
  // camera projection matrix
  glm::fmat4 m_view_projection;

  SceneGraph theSceneGraph;
  GeometryNode* solarSystem = new GeometryNode();

  // buffers
  vector <float> star_buffer;

  // Assignment 4
  vector<Node*> allSolarObjects;

  // cpu representation of textures
  texture_object texture_object[NUM_PLANETS + 1];

  model_object screenquad_object;	// _ ass5

  GLuint fbo_handle = 0;	// frame buffer object _ ass5
  GLuint rb_handle = 0;	// render buffor object _ ass5

};

#endif