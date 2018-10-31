#include "Node.hpp"


Node::Node(void)
{
	name = "theNode";
}

Node::~Node(void)
{

}

Node* Node::getParent()
{
  return parent;
}

void Node::setParent(Node* passedNode)
{
  parent = passedNode;
}

Node* Node::getChildren(string passedChildren)
{
  /*for (std::list<Node>::iterator i = children.begin(); i != children.end(); ++i)
  {
    if (i->getName().compare(passedChildren))
    {
      return i;
    }
  }
  */
	return new Node();
}

std::list<Node*> Node::getChildrenList()
{
  return children;
}

string Node::getName()
{
  return name;
}

string Node::getPath()
{
  return path;
}

int Node::getDepth()
{
  //return depth;
	return 0;
}

glm::mat4 Node::getLocalTransform()
{
  return localTransform;
}

void Node::setLocalTransform(glm::mat4 passedMat4)
{
  localTransform = passedMat4;
}

glm::mat4 Node::getWorldTransform()
{
  return worldTransform;
}

void Node::setWorldTransform(glm::mat4 passedMat4)
{
  worldTransform = passedMat4;
}

void Node::addChildren(Node passedNode)
{
  //children.add(passedNode);
}

Node* Node::removeChildren(string passedString)
{
//  for (std::list<Node>::iterator i = children.begin(); i != children.end(); ++i)
  {
    //if (i->getName().compare(passedChildren))
    //{
    //  children.remove(i);
    //}
  }

  return new Node();
}