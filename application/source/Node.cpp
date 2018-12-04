//****************************************************
// File: Node.cpp
//
// Purpose: Defines all the method for  
//			Node class.
//
// Written By: Muhammad Qumail & Michael Wilde
//
// Compiler: Visual C++ 2017 & openGL 
//              
//****************************************************

#include "Node.hpp"

//****************************************************
// Function: Node
//
// Purpose: Default constructor
//
//****************************************************
Node::Node(void)
{

}

//****************************************************
// Function: ~Player
//
// Purpose: Destructor
//
//****************************************************
Node::~Node(void)
{

}

//****************************************************
// Function: getParent
//
// Purpose: returns member variable parent
//
//****************************************************
Node* Node::getParent()
{
  return parent;
}

//****************************************************
// Function: setParent
//
// Purpose: sets member variable parent
//
//****************************************************
void Node::setParent(Node* passedNode)
{
  parent = passedNode;
}

//****************************************************
// Function: getChildren
//
// Purpose: Searches and returns a child node 
//          from the member variable children 
//			using name member variable 
//
//****************************************************
Node* Node::getChildren(string passedChildren)
{
	Node* childNode = new Node();

	for (std::vector<Node*>::iterator it = children.begin(); it != children.end(); ++it)
	{
		if ((*it)->getName().compare(passedChildren))
		{
		childNode = *it;
		}
	}

  return childNode;
}

//****************************************************
// Function: getChildrenList
//
// Purpose: returns children member variable
//
//****************************************************
vector<Node*> Node::getChildrenList()
{
  return children;
}

//****************************************************
// Function: getName
//
// Purpose: returns member variable name
//
//****************************************************
string Node::getName()
{
  return name;
}

//****************************************************
// Function: setName
//
// Purpose: sets member variable name
//
//****************************************************
void Node::setName(string passedName)
{
	name = passedName;
}

//****************************************************
// Function: getPath
//
// Purpose: returns member variable path
//
//****************************************************
string Node::getPath()
{
  return path;
}

//****************************************************
// Function: getDepth
//
// Purpose: returns member variable dept
//
//****************************************************
int Node::getDepth()
{
  return dept;
}

//****************************************************
// Function: getLocalTransform
//
// Purpose: returns member variable localTransform
//
//****************************************************
glm::mat4 Node::getLocalTransform()
{
  return localTransform;
}

//****************************************************
// Function: setLocalTransform
//
// Purpose: sets member variable localTransform
//
//****************************************************
void Node::setLocalTransform(glm::mat4 passedMat4)
{
  localTransform = passedMat4;
}

//****************************************************
// Function: getWorldTransform
//
// Purpose: returns member variable worldTransform
//
//****************************************************
glm::mat4 Node::getWorldTransform()
{
  return worldTransform;
}

//****************************************************
// Function: setWorldTransform
//
// Purpose: sets member variable worldTransform
//
//****************************************************
void Node::setWorldTransform(glm::mat4 passedMat4)
{
  worldTransform = passedMat4;
}

//****************************************************
// Function: addChildren
//
// Purpose: Adds passed in node to the children 
//			member variable 
//
//****************************************************
void Node::addChildren(Node* passedNode)
{
  children.push_back(passedNode);
}

//****************************************************
// Function: removeChildren
//
// Purpose: removes a node from the children member 
//			variable and returns it 
//
//****************************************************
Node* Node::removeChildren(string passedString)
{
	Node* removedNode = new Node();

  for (std::vector<Node*>::iterator it = children.begin(); it != children.end(); ++it)
  {
    if ((*it)->getName().compare(passedString))
    {
		removedNode = *it;
      //children.erase(*it.);
    }
  }

  return removedNode;
}

double Node::getSize()
{
	return size;
}

void Node::setSize(double passedSize)
{
	size = passedSize;
}

double Node::getRotationSpeed()
{
	return rotationSpeed;
}

void Node::setRotationSpeed(double passedRotationSpeed)
{
	rotationSpeed = passedRotationSpeed;
}

void Node::setDistanceToOrigin(double passedDistanceToOrigin)
{
	distanceToOrigin = passedDistanceToOrigin;
}

double Node::getDistanceToOrigin()
{
	return distanceToOrigin;
}

void Node::setHasMoonAtIndex(int passedHasMoonAtIndex)
{
	hasMoonAtIndex = passedHasMoonAtIndex;
}

int Node::getHasMoonAtIndex()
{
	return hasMoonAtIndex;
}

bool Node::getIsMoon()
{
	return isMoon;
}

void Node::setIsMoon(bool passedIsMoon)
{
	isMoon = passedIsMoon;
}

float Node::getColorR()
{
	return colorR;
}

void Node::setColorR(float passedColorR)
{
	colorG = passedColorR;
}

float Node::getColorG()
{
	return colorG;
}

void Node::setColorG(float passedColorG)
{
	colorG = passedColorG;
}

float Node::getColorB()
{
	return colorB;
}

void Node::setColorB(float passedColorB)
{
	colorB = passedColorB;
}