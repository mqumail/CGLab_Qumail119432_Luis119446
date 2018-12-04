//****************************************************
// File: Node.hpp
//
// Purpose: holds the class definition of 
//			Node class.
//
// Written By: Muhammad Qumail & Michael Wilde
//
// Compiler: Visual C++ 2017 & openGL 
//              
//****************************************************

#include <iostream>
#include <glm\glm.hpp>
#include <list>
#include <vector>

using namespace std;

#pragma once
class Node
{
public:
	Node(void);
	~Node(void);
	Node* getParent();
	void setParent(Node* passedNode);
	Node* getChildren(string passedChildren);
	vector<Node*> getChildrenList();
	string getName();
	void setName(string passedName);
	string getPath();
	int getDepth();
	glm::mat4 getLocalTransform();
	void setLocalTransform(glm::mat4 passedMat4);
	glm::mat4 getWorldTransform();
	void setWorldTransform(glm::mat4 passedMat4);
	void addChildren(Node* passedNode);
	Node* removeChildren(string passedString);
	float angularSpeed;

	double getSize();
	void setSize(double passedSize);
	double getRotationSpeed();
	void setRotationSpeed(double passedRotationSpeed);
	double getDistanceToOrigin();
	void setDistanceToOrigin(double passedDistanceToOrigin);
	int getHasMoonAtIndex();
	void setHasMoonAtIndex(int passedHasMoonAtIndex);
	bool getIsMoon();
	void setIsMoon(bool passedIsMoon);
	float getColorR();
	void setColorR(float passedColorR);
	float getColorG();
	void setColorG(float passedColorG);
	float getColorB();
	void setColorB(float passedColorB);

private:
	Node* parent = NULL;
	vector<Node*> children;
	string name;
	string path;
	int dept;
	glm::mat4 localTransform;
	glm::mat4 worldTransform;

	double size;
	double rotationSpeed;
	double distanceToOrigin;
	int hasMoonAtIndex;
	bool isMoon;
	float colorR;
	float colorG;
	float colorB;
};