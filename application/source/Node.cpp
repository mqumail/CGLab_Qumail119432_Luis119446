#include "Node.h"


Node::Node(void)
{
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
Node Node::getChildren(string passedChildren)
{
  for (std::list<Node>::iterator i = children.begin(); i != children.end(); ++i)
  {
    if (i->getName().compare(passedChildren))
    {
      return i;
    }
  }
}

std::list<Node> Node::getChildrenList()
{

}
string Node::getName()
{

}
string Node::getPath()
{

}
int Node::getDepth()
{

}
glm::mat4 Node::getLocalTransform()
{
}
void Node::setLocalTransform(glm::mat4 passedMat4)
{
}
glm::mat4 Node::getWorldTransform()
{
}
void Node::setWorldTransform(glm::mat4 passedMat4)
{
}
void Node::addChildren(Node passedNode)
{
}
Node Node::removeChildren(string passedString)
{

}