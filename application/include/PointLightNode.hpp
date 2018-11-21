#include "Node.hpp"

class PointLightNode : public Node
{
public:
	PointLightNode();
	~PointLightNode();
	void setLightIntensity(int intensity);
	int getLightIntensity();
	void setLightColor(glm::vec3 color);
	glm::vec3 getLightColor();

private:
	int lightIntensity;
	glm::vec3 lightColor;
};

