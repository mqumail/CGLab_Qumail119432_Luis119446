#include "GeometryNode.hpp"

GeometryNode::GeometryNode(void)
{

}

GeometryNode::~GeometryNode(void)
{

}

model* GeometryNode::getGeometry()
{
    return myModel;
}

void GeometryNode::setGeometry(model* theModel)
{
	myModel = theModel;
}







