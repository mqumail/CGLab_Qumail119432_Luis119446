//****************************************************
// File: CameraNode.cpp
//
// Purpose: Defines all the method for  
//			CameraNode class.
//
// Written By: Muhammad Qumail & Michael Wilde
//
// Compiler: Visual C++ 2017 & openGL 
//              
//****************************************************

#include "CameraNode.hpp"

//****************************************************
// Function: CameraNode
//
// Purpose: Default constructor
//			
//
//****************************************************
CameraNode::CameraNode(void)
{

}

//****************************************************
// Function: ~CameraNode
//
// Purpose: destructor
//			
//
//****************************************************
CameraNode::~CameraNode(void)
{

}

//****************************************************
// Function: getPerspective
//
// Purpose: returns member variable isPerspective
//			
//
//****************************************************
bool CameraNode::getPerspective(void)
{
	return isPerspective;
}

//****************************************************
// Function: getEnabled
//
// Purpose: returns member variable isEnabled
//			
//
//****************************************************
bool CameraNode::getEnabled(void)
{
	return isEnabled;
}

//****************************************************
// Function: setEnabled
//
// Purpose: sets member variable isEnabled
//			
//
//****************************************************
void CameraNode::setEnabled(bool theSetting)
{
	isEnabled = theSetting;
}

//****************************************************
// Function: getProjectionMatrix
//
// Purpose: returns member variable projectionMatrix
//			
//
//****************************************************
glm::mat4 CameraNode::getProjectionMatrix(void)
{
	return projectionMatrix;
}

//****************************************************
// Function: setProjectionMatrix
//
// Purpose: sets member variable projectionMatrix
//			
//
//****************************************************
void CameraNode::setProjectionMatrix(glm::mat4 newMatrix)
{
	// For future pass in the 4 values and create a mat4 in the function
	projectionMatrix = newMatrix;
}





