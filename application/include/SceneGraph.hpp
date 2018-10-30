
#include <iostream>
#include "Node.hpp"

using namespace std;

#pragma once
class SceneGraph
{

	public:
		SceneGraph(void);
		~SceneGraph(void);
		string getName();
		void setName(string passedName);
		Node* getRoot();
		void setRoot(Node* passedNode);

	private:
		string name;
		Node* root;
};