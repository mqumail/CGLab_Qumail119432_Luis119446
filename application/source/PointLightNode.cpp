#include "PointLightNode.hpp"



PointLightNode::PointLightNode()
{

}


PointLightNode::~PointLightNode()
{
}

void PointLightNode::setLightIntensity(int intensity)
{
	lightIntensity = intensity;
}

int PointLightNode::getLightIntensity()
{
	return lightIntensity;
}

void PointLightNode::setLightColor(glm::vec3 color)
{
	lightColor = color;
}

glm::vec3 PointLightNode::getLightColor()
{
	return lightColor;
}
