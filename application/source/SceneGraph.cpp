//****************************************************
// File: SceneGraph.cpp
//
// Purpose: Defines all the method for  
//			SceneGraph class.
//
// Written By: Muhammad Qumail & Michael Wilde
//
// Compiler: Visual C++ 2017 & openGL 
//              
//****************************************************

#include "SceneGraph.hpp"
#include "Node.hpp"

//****************************************************
// Function: SceneGraph
//
// Purpose: Default constructor that sets the member 
//			variables
//
//****************************************************
SceneGraph::SceneGraph(void)
{
	root = new Node();
	name = "theSceneGraph";
}

//****************************************************
// Function: ~SceneGraph
//
// Purpose: Destructor that cleans up memory
//			
//
//****************************************************
SceneGraph::~SceneGraph(void)
{
	root = NULL;
}

//****************************************************
// Function: getName
//
// Purpose: returns member variable name
//			
//
//****************************************************
string SceneGraph::getName()
{
	return name;
}

//****************************************************
// Function: setName
//
// Purpose: sets member variable name
//			
//
//****************************************************
void SceneGraph::setName(string passedName)
{
	name = passedName;
}

//****************************************************
// Function: getRoot
//
// Purpose: returns member variable root
//			
//
//****************************************************
Node* SceneGraph::getRoot()
{
	return root;
}

//****************************************************
// Function: setRoot
//
// Purpose: sets member variable root
//			
//
//****************************************************
void SceneGraph::setRoot(Node* passedNode)
{
	root = passedNode;
}