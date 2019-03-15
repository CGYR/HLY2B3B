#pragma once
#include<stdio.h>
#include <algorithm>
#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<vector>
#include<string>
using namespace std;

class WordNode
{
public:
	string word;
	int head;
	int tail;
	int len;
	bool uFlag = false;
	WordNode* next = NULL;
	WordNode::WordNode();
	WordNode(string inw);
	~WordNode();

private:

};

WordNode::WordNode(string inw)
{
	word = inw;
	len = word.length();
	head = word[0] - 97;
	tail = word[word.length()-1] - 97;
}

WordNode::WordNode()
{
	
}


WordNode::~WordNode()
{
	
}

WordNode* wordList[26];
WordNode* maxList = NULL;
int maxLen;
WordNode* nowList = NULL;
WordNode* nowNode = NULL;
int nowLen;
int nNum;//-n��Ӧ���ҵ��ĵ��ʵ���Ŀ
int nSet;//-n��Ӧ��nֵ
bool wSet;
bool cSet;
string hSet;
string tSet;
string inputFileName;

void writeResult(int mode);
void writeError(int errorCode);
bool gen(string path);
void fSearch(int rank);
void hSearch();
void parseCommandLineEnter(int argc, char* argv[]);