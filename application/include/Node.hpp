#include <iostream>
#include <glm\glm.hpp>
#include <list>

using namespace std;

#pragma once
class Node
{
public:
	Node(void);
	~Node(void);
	Node* getParent();
	void setParent(Node* passedNode);
	Node getChildren(string passedChildren);
	std::list<Node> getChildrenList();
	string getName();
	string getPath();
	int getDepth();
	glm::mat4 getLocalTransform();
	void setLocalTransform(glm::mat4 passedMat4);
	glm::mat4 getWorldTransform();
	void setWorldTransform(glm::mat4 passedMat4);
	void addChildren(Node passedNode);
	Node removeChildren(string passedString);

private:
	Node* parent;
	std::list<Node> children;
	string name;
	string path;
	int dept;
	glm::mat4 localTransform;
	glm::mat4 worldTransform;

};