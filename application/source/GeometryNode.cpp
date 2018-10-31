//****************************************************
// File: GeometryNode.cpp
//
// Purpose: Defines all the method for  
//			GeometryNode class.
//
// Written By: Muhammad Qumail & Michael Wilde
//
// Compiler: Visual C++ 2017 & openGL 
//              
//****************************************************

#include "GeometryNode.hpp"

//****************************************************
// Function: GeometryNode
//
// Purpose: Default constructor
//			
//
//****************************************************
GeometryNode::GeometryNode(void)
{

}

//****************************************************
// Function: ~GeometryNode
//
// Purpose: Destructor
//			
//
//****************************************************
GeometryNode::~GeometryNode(void)
{

}

//****************************************************
// Function: getGeometry
//
// Purpose: returns member variable myModel
//			
//
//****************************************************
model* GeometryNode::getGeometry()
{
    return myModel;
}

//****************************************************
// Function: setGeometry
//
// Purpose: sets member variable theModel
//			
//
//****************************************************
void GeometryNode::setGeometry(model* theModel)
{
	myModel = theModel;
}







