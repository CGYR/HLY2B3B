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
WordNode* nowList = NULL;
WordNode* nowNode = NULL;
int nowLen=0;
int maxLen=0;
int nowNum=0;
int maxNum=0;
bool wcFlag = false;//判定最长词链方式：-w对应true（总数最多），-c对于false（字母数最多）
int nNum;//-n对应的找到的单词的数目
int nSet;//-n对应的n值
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