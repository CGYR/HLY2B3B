// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 WORDDLL_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// WORDDLL_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
#ifdef WORDDLL_EXPORTS
#define WORDDLL_API __declspec(dllexport)
#else
#define WORDDLL_API __declspec(dllimport)
#endif

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
	vector<WordTwo*> next2;
	WordNode* next = NULL;
	WordNode();
	WordNode(string inw);
	WordNode(WordNode* inNode);
	~WordNode();
private:

};

class WordTwo {
public:
	friend class WordNode;
	WordTwo(WordNode*n1, WordNode*n2);
	~WordTwo();
	WordNode* Word1st = NULL;
	WordNode* Word2st = NULL;
private:

};

class WORDDLL_API Core
{
public:
	void setPath(string inp, string op);
	int gen_chain_word(string words, string &result, char head, char tail);
	int gen_chain_char(string words, string &result, char head, char tail);
	int gen_chain_n(string words, char head, char tail, int n, time_t timelim);

public:
	WordNode* wordList[26];
	WordNode* maxNode = NULL;
	WordNode* maxList = NULL;
	WordNode* nowList = NULL;
	WordNode* nowNode = NULL;
	vector<WordNode*> buffList = {};
	int buffNum = 0;
	int nowLen = 0;
	int maxLen = 0;
	int nowNum = 0;
	int maxNum = 0;
	bool isDLL = false;
	bool wcFlag = true;//判定最长词链方式：-w对应true（总数最多），-c对于false（字母数最多）
	bool nFlag = false;//输出定长，优先级高于wcFlag
	int nListNum = 0;
	int nSet = 0;//-n对应的找到的单词的数目
	string hSet = "";//限定头字母的集合
	string tSet = "";//限定尾字母的集合
	time_t startTime = time(NULL);
	time_t timenow = 0;
	time_t timelim = 40;
	int APIback = 0;
	int wordSum[26] = { 0 };
	ofstream outfile; // 输出文件
	string inputFilePath = "";
	string outputFilePath = "";

	void writeError(int errorCode);
	void hSearch(string &res);
	void hSearch_n();
	void fSearch(int rank);
	void nSearch(WordNode*n, int step);
	void writeResult(int mode);
	bool gen(string path);
	bool isRepeat(WordTwo* n);
	bool isFull();
	bool gen_fordll(string wordIn, char head, char tail);
	void writeResult_fordll(string &result);
	Core();
	~Core();
	void testCore();

private:
	

};

