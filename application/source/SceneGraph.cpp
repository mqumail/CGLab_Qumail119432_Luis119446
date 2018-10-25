#include "SceneGraph.h"


SceneGraph::SceneGraph(void)
{
}


SceneGraph::~SceneGraph(void)
{
}

string SceneGraph::getName()
{
	return name;
}

void SceneGraph::setName(string passedName)
{
	name = passedName;
}

Node SceneGraph::getRoot()
{
	return root;
}

void SceneGraph::setRoot(Node passedNode)
{
	root = passedNode;
}