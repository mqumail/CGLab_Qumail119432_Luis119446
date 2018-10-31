//****************************************************
// File: GeometryNode.hpp
//
// Purpose: holds the class definition of 
//			GeometryNode class.
//
// Written By: Muhammad Qumail & Michael Wilde
//
// Compiler: Visual C++ 2017 & openGL 
//              
//****************************************************

#include "Node.hpp"
#include "model.hpp"


class GeometryNode : public Node
{
public:
    GeometryNode();
    ~GeometryNode();
    model* getGeometry();
    void setGeometry(model* theModel);

protected:
    model* myModel;

};





