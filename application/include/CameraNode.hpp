//****************************************************
// File: CameraNode.hpp
//
// Purpose: holds the class definition of 
//			CameraNode class.
//
// Written By: Muhammad Qumail & Michael Wilde
//
// Compiler: Visual C++ 2017 & openGL 
//              
//****************************************************

#include "Node.hpp"

class CameraNode : public Node
{
public:
	CameraNode();
	~CameraNode();

	bool getPerspective(void);
	bool getEnabled(void);
	void setEnabled(bool);
	glm::mat4 getProjectionMatrix(void);
	void setProjectionMatrix(glm::mat4);

protected:
	bool isPerspective;
	bool isEnabled;
	glm::mat4 projectionMatrix;

};
