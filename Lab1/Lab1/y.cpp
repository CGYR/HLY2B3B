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
			else if( len<=1 ){
				wordTmp = "";
				len = 0;
			}
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
		printf("�����в�������\n");
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
		result += to_string(nListNum) + "\n";
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

void parseCommandLineEnter(int argc, char* argv[]) {
	// ���ж���λ�����Ƿ���ȷ ע�⣬β������Ҫ
	/* ������ע�͵� �������ע��
	if(stricmp("Wordlist.exe",argv[0])){
	// ���ô������
	writeError(2);
	}*/
	// ���������ļ�����
	inputFileName = argv[argc - 1];
	// �ȳ�ʼ������
	nListNum = 0;
	nSet = 0;
	hSet = "";
	tSet = "";
	for (int i = 1; i<argc - 1;) {
		printf("%s\n", argv[i]);
		if (!stricmp("-w", argv[i])) {
			if (wcFlag) {
				// ����
				writeError(2);
			}
			printf("wSet!\n");
			wcFlag = true;
			++i;
		}
		else if (!stricmp("-c", argv[i])) {
			if (!wcFlag) {
				// ����
				writeError(2);
			}
			printf("cSet!\n");
			wcFlag = false;
			++i;
		}
		else if (!stricmp("-h", argv[i])) {
			if (hSet != "" && (argv[i + 1][0]<97 || argv[i + 1][0]>122)) {
				// ����
				writeError(2);
			}
			printf("hSet! and hSet is %s\n", argv[i + 1]);
			hSet = argv[i + 1];
			i += 2;
		}
		else if (!stricmp("-t", argv[i])) {
			if (tSet != "" && (argv[i + 1][0]<97 || argv[i + 1][0]>122)) {
				// ����
				writeError(2);
			}
			printf("tSet! and tSet is %s\n", argv[i + 1]);
			tSet = argv[i + 1];
			i += 2;
		}
		else if (!stricmp("-n", argv[i])) {
			if (nSet>0 && (argv[i + 1][0] < 49 || argv[i + 1][0] > 57)) {
				// ����
				writeError(2);
			}
			printf("nSet! and nSet is %d\n", argv[i + 1][0] - 48);
			nSet = argv[i + 1][0] - 48;
			i += 2;
		}
		else {
			// ���ֲ�������������Ĳ���������
			writeError(2);
			++i;
		}
		// �Ƿ�������ϴ���
		/*if ((wSet && cSet) || (wSet && nSet != 0) || (cSet && nSet != 0)) {
			// ����
			writeError(2);
		}*/
	}
}


void hSearch() {
	WordNode* Tmp;
	if (!tSet.empty()) {
		sort(tSet.begin(), tSet.end());
		tSet.erase(unique(tSet.begin(), tSet.end()), tSet.end());//tSetȥ���ַ�
	}

	if (hSet.empty()) {
		for (int i = 0; i < 26; i++) {
			Tmp = wordList[i];
			while (Tmp->word != "") {
				nowLen++;
				nowNum += Tmp->len;
				nowList = new WordNode(Tmp->word);
				nowNode = nowList;
				Tmp->uFlag = true;
				fSearch(Tmp->tail);
				Tmp->uFlag = false;
				Tmp = Tmp->next;
				nowLen = 0;
				nowNum = 0;
			}
		}
	}
	else {
		sort(hSet.begin(), hSet.end());
		hSet.erase(unique(hSet.begin(), hSet.end()), hSet.end());//hSetȥ���ַ�
		for (unsigned int i = 0; i < hSet.length(); i++) {
			int num = hSet[i] - 97;
			Tmp = wordList[num];
			while (Tmp->word != "") {
				nowLen++;
				nowNum += Tmp->len;
				nowList = new WordNode(Tmp->word);
				nowNode = nowList;
				Tmp->uFlag = true;
				fSearch(Tmp->tail);
				Tmp->uFlag = false;
				Tmp = Tmp->next;
				nowLen = 0;
				nowNum = 0;
			}
		}
	}
}

void fSearch(int rank) {
	WordNode* Tmp = wordList[rank];
	while ( Tmp->word != "") {
		if (Tmp->uFlag == true) {
			Tmp = Tmp->next;
			continue;
		}
		Tmp->uFlag = true;
		WordNode *newNode = new WordNode(Tmp->word);
		nowNode->next = newNode;
		nowNode = newNode;
		nowLen++;
		nowNum += newNode->len;
		fSearch(nowNode->tail);
		Tmp->uFlag = false;
		Tmp = Tmp->next;
	}
	if (Tmp->word == "") {
		if (!tSet.empty()) {
			bool tailFlag = false;
			for (unsigned int i = 0; i < tSet.length(); i++) {
				if (nowNode->tail == tSet[i] - 97) {
					tailFlag = true;
					break;
				}
			}
			if (!tailFlag) {
				nowLen--;
				Tmp = nowList;
				if (Tmp == NULL) return;
				if (Tmp->next == NULL) nowList = NULL;
				else {
					while (Tmp->next->next != NULL)
					{
						Tmp = Tmp->next;
					}
					nowNum -= Tmp->next->len;
					Tmp->next = NULL;
					nowNode = Tmp;
				}
				return;
			}
		}
		if ((nowLen > maxLen) && wcFlag) {
			maxLen = nowLen;
			Tmp = nowList;
			WordNode *maxNode = new WordNode(Tmp->word);
			maxList = maxNode;
			Tmp = Tmp->next;
			while (Tmp != NULL) {
				WordNode *newNode = new WordNode(Tmp->word);
				maxNode->next = newNode;
				maxNode = newNode;
				Tmp = Tmp->next;
			}

			nowLen--;
			Tmp = nowList;
			if (Tmp == NULL) return;
			if (Tmp->next == NULL) nowList = NULL;
			else {
				while (Tmp->next->next != NULL)
				{
					Tmp = Tmp->next;
				}
				nowNum -= Tmp->next->len;
				Tmp->next = NULL;
				nowNode = Tmp;
			}
			return;
		}
		else if ((nowNum > maxNum) && !wcFlag) {
			maxNum = nowNum;
			Tmp = nowList;
			WordNode *maxNode = new WordNode(Tmp->word);
			maxList = maxNode;
			Tmp = Tmp->next;
			while (Tmp != NULL) {
				WordNode *newNode = new WordNode(Tmp->word);
				maxNode->next = newNode;
				maxNode = newNode;
				Tmp = Tmp->next;
			}
			nowLen--;
			Tmp = nowList;
			if (Tmp == NULL) return;
			if (Tmp->next == NULL) nowList = NULL;
			else {
				while (Tmp->next->next != NULL)
				{
					Tmp = Tmp->next;
				}
				nowNum -= Tmp->next->len;
				Tmp->next = NULL;
				nowNode = Tmp;
			}
			return;
		}
		else {
			nowLen--;
			Tmp = nowList;
			if (Tmp == NULL) return;
			if (Tmp->next == NULL) nowList = NULL;
			else {
				while (Tmp->next->next != NULL)
				{
					Tmp = Tmp->next;
				}
				nowNum -= Tmp->next->len;
				Tmp->next = NULL;
				nowNode = Tmp;
			}
			return;
		}
	}
}

void nSearch(int rank) {
	WordNode* Tmp = wordList[rank];
	while (Tmp->word != "") {
		if (Tmp->uFlag == true) {
			Tmp = Tmp->next;
			continue;
		}
		Tmp->uFlag = true;
		WordNode *newNode = new WordNode(Tmp->word);
		nowNode->next = newNode;
		nowNode = newNode;
		nowLen++;
		if (nowLen == nSet) {

		}
		nowNum += newNode->len;
		nSearch(nowNode->tail);
		Tmp->uFlag = false;
		Tmp = Tmp->next;
	}
	if (Tmp->word == "") {
		if (!tSet.empty()) {
			bool tailFlag = false;
			for (unsigned int i = 0; i < tSet.length(); i++) {
				if (nowNode->tail == tSet[i] - 97) {
					tailFlag = true;
					break;
				}
			}
			if (!tailFlag) {
				nowLen--;
				Tmp = nowList;
				if (Tmp == NULL) return;
				if (Tmp->next == NULL) nowList = NULL;
				else {
					while (Tmp->next->next != NULL)
					{
						Tmp = Tmp->next;
					}
					nowNum -= Tmp->next->len;
					Tmp->next = NULL;
					nowNode = Tmp;
				}
				return;
			}
		}
		if ((nowLen > maxLen) && wcFlag) {
			maxLen = nowLen;
			Tmp = nowList;
			WordNode *maxNode = new WordNode(Tmp->word);
			maxList = maxNode;
			Tmp = Tmp->next;
			while (Tmp != NULL) {
				WordNode *newNode = new WordNode(Tmp->word);
				maxNode->next = newNode;
				maxNode = newNode;
				Tmp = Tmp->next;
			}

			nowLen--;
			Tmp = nowList;
			if (Tmp == NULL) return;
			if (Tmp->next == NULL) nowList = NULL;
			else {
				while (Tmp->next->next != NULL)
				{
					Tmp = Tmp->next;
				}
				nowNum -= Tmp->next->len;
				Tmp->next = NULL;
				nowNode = Tmp;
			}
			return;
		}
		else if ((nowNum > maxNum) && !wcFlag) {
			maxNum = nowNum;
			Tmp = nowList;
			WordNode *maxNode = new WordNode(Tmp->word);
			maxList = maxNode;
			Tmp = Tmp->next;
			while (Tmp != NULL) {
				WordNode *newNode = new WordNode(Tmp->word);
				maxNode->next = newNode;
				maxNode = newNode;
				Tmp = Tmp->next;
			}
			nowLen--;
			Tmp = nowList;
			if (Tmp == NULL) return;
			if (Tmp->next == NULL) nowList = NULL;
			else {
				while (Tmp->next->next != NULL)
				{
					Tmp = Tmp->next;
				}
				nowNum -= Tmp->next->len;
				Tmp->next = NULL;
				nowNode = Tmp;
			}
			return;
		}
		else {
			nowLen--;
			Tmp = nowList;
			if (Tmp == NULL) return;
			if (Tmp->next == NULL) nowList = NULL;
			else {
				while (Tmp->next->next != NULL)
				{
					Tmp = Tmp->next;
				}
				nowNum -= Tmp->next->len;
				Tmp->next = NULL;
				nowNode = Tmp;
			}
			return;
		}
	}
}


int main(int argc, char* argv[]) {
	gen("F://google/test.txt");
	hSearch();
	writeResult(1);
}