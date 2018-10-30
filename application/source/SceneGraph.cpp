#include "SceneGraph.hpp"
#include "Node.hpp"


SceneGraph::SceneGraph(void)
{
	root = new Node();
	name = "theSceneGraph";
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

Node* SceneGraph::getRoot()
{
	return root;
}

void SceneGraph::setRoot(Node* passedNode)
{
	root = passedNode;
}