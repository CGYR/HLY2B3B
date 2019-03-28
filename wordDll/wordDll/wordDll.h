// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� WORDDLL_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// WORDDLL_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
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
	bool wcFlag = true;//�ж��������ʽ��-w��Ӧtrue��������ࣩ��-c����false����ĸ����ࣩ
	bool nFlag = false;//������������ȼ�����wcFlag
	int nListNum = 0;
	int nSet = 0;//-n��Ӧ���ҵ��ĵ��ʵ���Ŀ
	string hSet = "";//�޶�ͷ��ĸ�ļ���
	string tSet = "";//�޶�β��ĸ�ļ���
	time_t startTime = time(NULL);
	time_t timenow = 0;
	time_t timelim = 40;
	int APIback = 0;
	int wordSum[26] = { 0 };
	ofstream outfile; // ����ļ�
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

