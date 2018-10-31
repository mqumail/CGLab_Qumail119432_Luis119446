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

  for (std::list<Node*>::iterator i = children.begin(); i != children.end(); ++i)
  {
    if ((*i)->getName().compare(passedChildren))
    {
      childNode = *i;
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
std::list<Node*> Node::getChildrenList()
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

  for (std::list<Node*>::iterator i = children.begin(); i != children.end(); ++i)
  {
    if ((*i)->getName().compare(passedString))
    {
		removedNode = *i;
      children.remove(*i);
    }
  }

  return removedNode;
}