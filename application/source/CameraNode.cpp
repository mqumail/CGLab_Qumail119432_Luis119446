#include "CameraNode.h"

CameraNode::CameraNode(void)
{

}

~CameraNode::CameraNode(void)
{

}

bool CameraNode::getPerspective(void)
{
	return isPerspective;
}

bool CameraNode::getEnabled(void)
{
	return isEnabled;
}

void CameraNode::setEnabled(bool theSetting)
{
	isEnabled = theSetting;
}

glm::mat4 CameraNode::getProjectionMatrix(void)
{
	return projectionMatrix;
}

void CameraNode::setProjectionMatrix(glm::mat4 newMatrix)
{
	projectionMatrix = newMatrix;
}





