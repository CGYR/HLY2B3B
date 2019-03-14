#pragma once
#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<vector>
#include<string>
using namespace std;

class WordNode
{
public:
	string word;
	int tail;
	int len;
	bool uFlag = false;
	WordNode* next = NULL;

	WordNode(string inw);
	~WordNode();

private:

};

WordNode::WordNode(string inw)
{
	word = inw;
	len = word.length;
	tail = word[word.length-1] - 97;
}

WordNode::~WordNode()
{
}

