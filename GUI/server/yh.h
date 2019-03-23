#pragma once
#include<stdio.h>
#include <algorithm>
#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<vector>
#include<list>
#include<string>
#include<ctime>
using namespace std;

class WordTwo;

class WordNode
{
public:
	string word;
	int head;
	int tail;
	int len;
	bool uFlag = false;
	int offset = 0;
	vector<WordTwo*> next2;
	WordNode* next = NULL;
	WordNode();
	WordNode(string inw);
	WordNode(WordNode* inNode);
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

WordNode::WordNode(WordNode* inNode) {
	word = inNode->word;
	len = inNode->len;
	uFlag = inNode->uFlag;
	next = inNode->next;
}

WordNode::WordNode()
{
	
}


WordNode::~WordNode()
{
	
}

class WordTwo{
public:
	friend class WordNode;
	WordTwo(WordNode*n1,WordNode*n2);
	~WordTwo();
	WordNode* Word1st = NULL;
	WordNode* Word2st = NULL;
private:

};

WordTwo::WordTwo(WordNode*n1, WordNode*n2)
{
	Word1st = n1;
	Word2st = n2;
}

WordTwo::~WordTwo()
{
}

WordNode* wordList[26];
WordNode* maxList = NULL;
WordNode* maxNode = NULL;
WordNode* maxL = NULL;
WordNode* maxN = NULL;
WordNode* headNow = NULL;
list<WordNode*> nList;
WordNode* nowList = NULL;
WordNode* nowNode = NULL;
int nowLen=0;
int maxLen=0;
int nowNum=0;
int maxNum=0;
bool wcFlag = true;//判定最长词链方式：-w对应true（总数最多），-c对于false（字母数最多）
bool nFlag = false;//输出定长，优先级高于wcFlag
int nListNum = 0;//-n对应的找到的单词的数目
int nSet = 0;//-n对应的n值
string hSet = "";//限定头字母的集合
string tSet = "";//限定尾字母的集合
string inputFileName;
time_t startTime = time(NULL);
bool timeFlag = false;
int step = 1;
int wordSum[26] = { 0 };
ofstream outfile; // 输出文件

void writeResult(int mode);
void writeError(int errorCode);
bool gen(string path);
void hSearch();
void fSearch(int rank);
void nSearch(WordNode*n,int step);
void parseCommandLineEnter(int argc, char* argv[]);
bool isRepeat(WordTwo* n);