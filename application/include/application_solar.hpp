#ifndef APPLICATION_SOLAR_HPP
#define APPLICATION_SOLAR_HPP

#include "application.hpp"
#include "model.hpp"
#include "structs.hpp"
#include "SceneGraph.hpp"

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
  void outputPlanet(float x, float y, float z, float angularSpeed);
  // upload stars
  void uploadStars();

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

  void traverseSceneGraph(Node* theNode);

  // cpu representation of model
  model_object planet_object;

  // cpu representation of star
  model_object star_object;
  
  // camera transform matrix
  glm::fmat4 m_view_transform;
  // camera projection matrix
  glm::fmat4 m_view_projection;

  SceneGraph theSceneGraph;

  // buffers
  vector <float> star_buffer;
};

#endif