//****************************************************
// File: SceneGraph.hpp
//
// Purpose: holds the class definition of 
//			SceneGraph class.
//
// Written By: Muhammad Qumail & Michael Wilde
//
// Compiler: Visual C++ 2017 & openGL 
//              
//****************************************************

#include <iostream>
#include "Node.hpp"

using namespace std;

#pragma once
class SceneGraph
{

	public:
		SceneGraph();
		~SceneGraph();
		string getName();
		void setName(string passedName);
		Node* getRoot();
		void setRoot(Node* passedNode);

	private:
		string name;
		Node* root;
};