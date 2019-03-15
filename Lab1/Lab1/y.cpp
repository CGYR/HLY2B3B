#include"yh.h"
#pragma warning(disable:4996)
/*
WordNode* wordList[26];
WordNode* maxList = NULL;
int maxLen;
WordNode* nowList = NULL;
int nowLen;
int nNum;//-n��Ӧ���ҵ��ĵ��ʵ���Ŀ
int nSet;//-n��Ӧ��nֵ

void writeResult(int mode);
void writeError(int errorCode);
bool gen(string path);
*/

bool gen(string path) {
	for (int i = 0; i < 26; i++) {
		wordList[i] = new WordNode();
	}
	std::ifstream in(path);
	if (!in) {
		writeError(1);
		return false;
	}
	istreambuf_iterator<char> begin(in);
	istreambuf_iterator<char> end;
	string wordIn(begin, end);

	string wordTmp = "";
	transform(wordIn.begin(), wordIn.end(), wordIn.begin(), ::tolower);
	char charTmp = wordIn[0];
	int i = 0;
	int rank = 0;
	int len = 0;
	bool reaptFlag = false;
	WordNode* nodeTmp = NULL;
	while (charTmp!='\0') {
		if (charTmp < 97 || charTmp > 122) {
			if (wordTmp != "" && len >1) {
				for (int j = 0; j < 26; j++) {
					nodeTmp = wordList[j];
					while (nodeTmp->word != "") {
						if (wordTmp == nodeTmp->word) {
							reaptFlag = true;
							break;
						}
						nodeTmp = nodeTmp->next;
					}
					if (reaptFlag) break;
				}
				nodeTmp = NULL;
				if (reaptFlag) {
					reaptFlag = false;
					wordTmp = "";
					len = 0;
					charTmp = wordIn[++i];
					continue;
				}
				WordNode *Node = new WordNode(wordTmp);
				rank = wordTmp[0] - 97;
				Node->next = wordList[rank];
				wordList[rank] = Node;
				wordTmp = "";
				len = 0;
			}
			else{}
		}
		else {
			wordTmp += charTmp;
			len++;
		}
		charTmp = wordIn[++i];
	}

	if (charTmp == '\0') {
		if (wordTmp != "" && len >1) {
			for (int j = 0; j < 26; j++) {
				nodeTmp = wordList[j];
				while (nodeTmp->word != "") {
					if (wordTmp == nodeTmp->word) {
						reaptFlag = true;
						break;
					}
					nodeTmp = nodeTmp->next;
				}
				if (reaptFlag) break;
			}
			nodeTmp = NULL;
			if (reaptFlag) {
				return true;
			}
			WordNode *Node = new WordNode(wordTmp);
			rank = wordTmp[0] - 97;
			Node->next = wordList[rank];
			wordList[rank] = Node;
		}
	}

	return true;
}

// ���������д��solution.txt
// ������������ģʽ�У���ֱ��printһ��������Ƴ�
// ���룺������
void writeError(int errorCode) {
	ofstream outfile;
	outfile.open("solution.txt");
	// ���ݴ����ţ�������ԭ����/д��/�˳�
	// ��Ҫ����Ĵ��󣬿����
	switch (errorCode) {
	case 1: {
		printf("�ļ������ڣ���������\n");
		outfile << "-1" << endl;
		exit(0);
	}
	case 2: {
		printf("����2\n");
		outfile << "-2" << endl;
		exit(0);
	}
	}
	outfile.close();
}

// ģʽ1: ���-w -c ֻ��Ҫ���һ�����ʴ������
// ģʽ2: ���-n ��Ҫ���������ʴ������
void writeResult(int mode) {
	string result = "";
	if (mode == 1) {
		WordNode* nextNode = maxList;
		while (nextNode != NULL) {
			result = result + nextNode->word + "\n";
			nextNode = nextNode->next;
		}
	}
	else if (mode == 2) {
		WordNode* nextNode = maxList;
		int count = 1;
		result += to_string(nNum) + "\n";
		while (nextNode != NULL) {
			if (count != 1 && count%nSet == 0) {
				result = result + nextNode->word + "\n\n";
			}
			else {
				result = result + nextNode->word + "\n";
			}
			count++;
			nextNode = nextNode->next;
		}
	}
	else {
		// ����
	}
	ofstream outfile;
	outfile.open("solution.txt");
	outfile << result << endl;
	outfile.close();
}

void hSearch() {
	WordNode* Tmp;
	for (int i = 0; i < 26; i++) {
		Tmp = wordList[i];
		while(Tmp->word!=""){
			nowLen++;
			nowList = new WordNode(Tmp->word);
			nowNode = nowList;
			Tmp->uFlag = true;
			fSearch(Tmp->tail);
			Tmp->uFlag = false;
			Tmp = Tmp->next;
		}
	}
}

void fSearch(int rank) {
	WordNode* Tmp = wordList[rank];
	while (Tmp->word != "") {
		if (Tmp->uFlag == true) {
			Tmp = Tmp->next;
			continue;
		}
		break;
	}
	if (Tmp->word == "") {
		if (nowLen > maxLen) {
			maxLen = nowLen;
			maxList = nowList;
		}
		nowLen = 0;
		/*Tmp = nowList->next;
		WordNode* Tnext;
		while (Tmp != NULL) {
			Tnext = Tmp->next;
			delete Tmp;
			Tmp = Tnext;
		}*/
		nowList = NULL;
		return;
	}
	Tmp->uFlag = true;
	WordNode *newNode = new WordNode(Tmp->word);
	nowNode->next = newNode;
	nowNode = newNode;
	nowLen++;
	fSearch(nowNode->tail);
	Tmp->uFlag = false;
}

int main(int argc, char* argv[]) {
	gen("F://google/test.txt");
	hSearch();
	writeResult(1);
}