#include"yh.h"
#pragma warning(disable:4996)
/*
WordNode* wordList[26];
WordNode* maxList = NULL;
int maxLen;
WordNode* nowList = NULL;
int nowLen;
int nNum;//-n对应的找到的单词的数目
int nSet;//-n对应的n值

void writeResult(int mode);
void writeError(int errorCode);
bool gen(string path);
*/

bool gen(string path) {
	if (nSet > 0) nFlag = true;
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
	int offset = 0;
	bool reaptFlag = false;
	WordNode* nodeTmp = NULL;
	while (charTmp != '\0') {
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
						offset++;
					}
					if (reaptFlag) break;
				}
				nodeTmp = NULL;
				if (reaptFlag) {
					reaptFlag = false;
					wordTmp = "";
					len = 0;
					charTmp = wordIn[++i];
					offset = 0;
					continue;
				}
				WordNode *Node = new WordNode(wordTmp);
				rank = wordTmp[0] - 97;
				Node->offset = offset;
				Node->next = wordList[rank];
				wordList[rank] = Node;
				wordTmp = "";
				len = 0;
			}
			else if (len <= 1) {
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

	WordNode *Tmp, *Tmpp;
	for (int i = 0; i < 26 && nSet>2; i++) {
		Tmp = wordList[i];
		wordSum[i] = Tmp->offset;//offset set by neg-th,so first word's offset is the sum of words in a line.(actually, sum-1)
		while (Tmp->word != "") {//find all word's follow 2 word list
			for (Tmpp = wordList[Tmp->tail]; Tmpp->word != ""; Tmpp = Tmpp->next) {
				for (WordNode* Tmppp = wordList[Tmpp->tail]; Tmppp->word != ""; Tmppp = Tmppp->next) {
					if (Tmp == Tmpp || Tmp == Tmppp || Tmpp == Tmppp) continue;
					Tmp->next2.push_back(new WordTwo(Tmpp, Tmppp));
				}
			}
			Tmp = Tmp->next;
		}
	}

	return true;
}

// 将错误代码写入solution.txt
// 在命令行运行模式中，则直接print一个错误后推出
// 输入：错误编号
void writeError(int errorCode) {
	ofstream outfile;
	outfile.open("solution.txt");
	// 根据错误编号，将错误原因打出/写入/退出
	// 需要更多的错误，可添加
	switch (errorCode) {
	case 1: {
		printf("文件不存在！！！！！\n");
		outfile << "-1" << endl;
		exit(0);
	}
	case 2: {
		printf("非法的命令行参数（-h、-t 后跟的字符串中只允许包含字母）\n");
		outfile << "-2" << endl;
		exit(0);
	}
	case 3: {
		printf("-n参数后面需要一个数字\n");
		outfile << "-3" << endl;
		exit(0);
	}
	case 4: {
		printf("-h参数后面需要至少一个字符\n");
		outfile << "-4" << endl;
		exit(0);
	}
	case 5: {
		printf("-t参数后面需要至少一个字符\n");
		outfile << "-5" << endl;
		exit(0);
	}
	case 6: {
		printf("-w -c -n 参数三者之间只能选择一个\n");
		outfile << "-6" << endl;
		exit(0);
	}
	}
	outfile.close();
}

// 模式1: 针对-w -c 只需要输出一个单词串的情况
// 模式2: 针对-n 需要输出多个单词串的情况
void writeResult(int mode) {
	string result = "";
	if (mode == 1) {
		WordNode* nextNode = maxList;
		while (nextNode != NULL) {
			result = result + nextNode->word + "\n";
			nextNode = nextNode->next;
		}
		ofstream outfile;
		outfile.open("solution.txt");
		outfile << result << endl;
		outfile.close();
	}
	else if (mode == 2) {
		WordNode* nextNode = nowList;
		int count = 1;
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

		//outfile.open("solution.txt",std::ios::app);
		outfile << result << "";
		//outfile.close();
	}
	else {
		// 报错
	}
	/*
	ofstream outfile;
	outfile.open("solution.txt");
	outfile << result << endl;
	outfile.close();
	*/
}

void parseCommandLineEnter(int argc, char* argv[]) {
	// 先判断首位输入是否正确 注意，尾部不需要
	/* 这里先注释掉 最后消除注释
	if(strcmp("Wordlist.exe",argv[0])){
	// 设置错误输出
	writeError(2);
	}*/
	// 设置输入文件名称
	inputFileName = argv[argc - 1];
	// 先初始化参数
	nListNum = 0;
	nSet = 0;
	hSet = "";
	tSet = "";
	for (int i = 0; i<argc; ++i) {
		printf("%s\n", argv[i]);
	}
	bool flag = false;
	bool flag_n = false;
	if (argc <= 2) {
		// 参数数量出现问题
		writeError(2);
	}
	for (int i = 1; i<argc - 1;) {
		printf("%s\n", argv[i]);
		if (!strcmp("-w", argv[i])) {
			if (flag) {
				// 报错
				writeError(6);
			}
			printf("wSet!\n");
			wcFlag = true;
			flag = true;
			++i;
		}
		else if (!strcmp("-c", argv[i])) {
			if (flag) {
				// 报错
				writeError(6);
			}
			printf("cSet!\n");
			wcFlag = false;
			flag = true;
			++i;
		}
		else if (!strcmp("-h", argv[i])) {
			for (int j = 0; j < strlen(argv[i + 1]); j++) {
				if (argv[i + 1][j]<97 || argv[i + 1][j]>122 || i + 1 >= argc - 1) {
					// 报错
					writeError(4);
				}
			}
			
			if (hSet != "") {
				writeError(2);
			}
			printf("hSet! and hSet is %s\n", argv[i + 1]);
			hSet = argv[i + 1];
			i += 2;
		}
		else if (!strcmp("-t", argv[i])) {
			
			for (int j = 0; j < strlen(argv[i + 1]); j++) {
				if (argv[i + 1][j]<97 || argv[i + 1][j]>122 || i + 1 >= argc - 1) {
					// 报错
					writeError(5);
				}
			}
			if (tSet != "") {
				writeError(2);
			}
			printf("tSet! and tSet is %s\n", argv[i + 1]);
			tSet = argv[i + 1];
			i += 2;
		}
		else if (!strcmp("-n", argv[i])) {
			printf("dsfsdfds %d", argv[i + 1][0]);
			int n_num = 0;
			try {
				n_num = std::stoi(argv[i + 1]);
			}
			catch (std::invalid_argument&) {
				writeError(3);
			}

			if (flag) {
				writeError(6);
			}
			else if (flag_n) {
				writeError(2);
			}
			printf("nSet! and nSet is %d\n", n_num);
			nSet = n_num;
			flag_n = true;
			i += 2;
		}
		else {
			// 出现不符合命令参数的参数，报错
			writeError(2);
			++i;
		}
	}
}

void hSearch() {
	WordNode* Tmp;
	if (!tSet.empty()) {
		sort(tSet.begin(), tSet.end());
		tSet.erase(unique(tSet.begin(), tSet.end()), tSet.end());//tSet去重字符
	}

	if (!nFlag) {
		if (hSet.empty()) {
			for (int i = 0; i < 26; i++) {
				Tmp = wordList[i];
				if (timenow-startTime > timelim) { writeResult(1); return; }
				while (Tmp->word != "") {
					if (timenow - startTime > timelim) { writeResult(1); return; }
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
			hSet.erase(unique(hSet.begin(), hSet.end()), hSet.end());//hSet去重字符
			for (unsigned int i = 0; i < hSet.length(); i++) {
				if (timenow - startTime > timelim) { writeResult(1); return; }
				int num = hSet[i] - 97;
				Tmp = wordList[num];
				while (Tmp->word != "") {
					if (timenow - startTime > timelim) { writeResult(1); return; }
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
		writeResult(1);
	}
	else {
		nowNode = new WordNode();
		nowList = nowNode;
		for (int i = 1; i < nSet; i++) {//init nowlist as n length
			Tmp = new WordNode();
			nowNode->next = Tmp;
			nowNode = nowNode->next;
		}

		if (hSet.empty()) {
			for (int i = 0; i < 26; i++) {
				Tmp = wordList[i];
				if (timenow - startTime > timelim) {return; }
				while (Tmp->word != "") {
					if (timenow - startTime > timelim) { return; }
					nowLen++;
					nowList->word = Tmp->word;
					nowList->tail = Tmp->tail;
					nowNode = nowList;
					Tmp->uFlag = true;
					if (nSet % 2 == 0) {//n != odd, then one step first(after that, len == 2), and two step each
						nSearch(wordList[Tmp->tail], 1);
					}
					else {//n == odd, then 2 step each time
						for (auto & i : Tmp->next2) {
							if (isRepeat(i)) continue;
							if (timenow - startTime > timelim) { return; }
							nowNode = nowList->next;
							nowNode->word = i->Word1st->word;
							nowNode->tail = i->Word1st->tail;
							nowNode->next->word = i->Word2st->word;
							nowNode->next->tail = i->Word2st->tail;
							nowNode = nowNode->next;
							nowLen += 2;
							i->Word1st->uFlag = true;
							i->Word2st->uFlag = true;
							nSearch(i->Word2st, 2);
							nowLen -= 2;
							i->Word1st->uFlag = false;
							i->Word2st->uFlag = false;
						}
					}
					Tmp->uFlag = false;
					Tmp = Tmp->next;
					nowLen = 0;
				}
			}
		}
		else {
			sort(hSet.begin(), hSet.end());
			hSet.erase(unique(hSet.begin(), hSet.end()), hSet.end());//hSet去重字符
			for (unsigned int i = 0; i < hSet.length(); i++) {
				if (timenow - startTime > timelim) { return; }
				int num = hSet[i] - 97;
				Tmp = wordList[num];
				while (Tmp->word != "") {
					if (timenow - startTime > timelim) { return; }
					nowLen++;
					nowList->word = Tmp->word;
					nowList->tail = Tmp->tail;
					nowNode = nowList;
					Tmp->uFlag = true;
					if (nSet % 2 == 0) {//n != odd, then one step first(after that, len == 2), and two step each
						nSearch(wordList[Tmp->tail], 1);
					}
					else {//n == odd, then 2 step each time
						for (auto & i : Tmp->next2) {
							if (isRepeat(i)) continue;
							if (timenow - startTime > timelim) { return; }
							nowNode = nowList->next;
							nowNode->word = i->Word1st->word;
							nowNode->tail = i->Word1st->tail;
							nowNode->next->word = i->Word2st->word;
							nowNode->next->tail = i->Word2st->tail;
							nowNode = nowNode->next;
							nowLen += 2;
							i->Word1st->uFlag = true;
							i->Word2st->uFlag = true;
							nSearch(i->Word2st, 2);
							nowLen -= 2;
							i->Word1st->uFlag = false;
							i->Word2st->uFlag = false;
						}
					}
					Tmp->uFlag = false;
					Tmp = Tmp->next;
					nowLen = 0;
				}
			}
		}
	}
}

void fSearch(int rank) {
	timenow = time(NULL);
	if (timenow - startTime > timelim) return;
	WordNode* Tmp = wordList[rank];
	while (Tmp->word != "") {
		if (timenow - startTime > timelim) return;
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
	if (timenow - startTime > timelim) return;
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

void nSearch(WordNode *now, int step) {
	timenow = time(NULL);
	if (timenow - startTime > timelim) { return; }
	WordNode* Tmp = now;
	//one step:
	while (step == 1 && Tmp->word != "") {
		if (timenow - startTime > timelim) { return; }
		if (Tmp->uFlag == true) {
			Tmp = Tmp->next;
			continue;
		}
		Tmp->uFlag = true;
		nowNode = nowList;
		for (int i = 1; i <= nowLen; i++) nowNode = nowNode->next;//right position at list
		nowNode->word = Tmp->word;
		nowNode->tail = Tmp->tail;
		nowLen++;
		if (nowLen == nSet) {
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
					Tmp->uFlag = false;
					Tmp = Tmp->next;
					continue;
				}
			}
			nListNum++;
			writeResult(2);
			//output nowList!! func?
		}

		else {
			for (auto & i : Tmp->next2) {
				if (isRepeat(i)) continue;//if repeat, then skip it 
				nowNode = nowList;
				for (int K = 1; K <= nowLen; K++) nowNode = nowNode->next;//right position at list
				nowNode->word = i->Word1st->word;
				nowNode->tail = i->Word1st->tail;
				nowNode->next->word = i->Word2st->word;
				nowNode->next->tail = i->Word2st->tail;
				nowNode = nowNode->next;
				nowLen += 2;
				i->Word1st->uFlag = true;
				i->Word2st->uFlag = true;
				nSearch(i->Word2st, 2);
				nowLen -= 2;
				i->Word1st->uFlag = false;
				i->Word2st->uFlag = false;
			}
		}
		nowLen--;
		Tmp->uFlag = false;
		Tmp = Tmp->next;
	}
	if (timenow - startTime > timelim) { return; }
	if (step == 2) {
		if (nowLen == nSet) {
			if (!tSet.empty()) {
				bool tailFlag = false;
				for (unsigned int i = 0; i < tSet.length(); i++) {
					if (nowNode->tail == tSet[i] - 97) {
						tailFlag = true;
						break;
					}
				}
				if (!tailFlag) {
					return;
				}
			}
			nListNum++;
			writeResult(2);
		}

		else {
			for (auto & i : now->next2) {
				if (isRepeat(i)) continue;
				nowNode = nowList;
				for (int K = 1; K <= nowLen; K++) nowNode = nowNode->next;//right position at list
				nowNode->word = i->Word1st->word;
				nowNode->tail = i->Word1st->tail;
				nowNode->next->word = i->Word2st->word;
				nowNode->next->tail = i->Word2st->tail;
				nowNode = nowNode->next;
				nowLen += 2;
				i->Word1st->uFlag = true;
				i->Word2st->uFlag = true;
				nSearch(i->Word2st, 2);
				nowLen -= 2;
				i->Word1st->uFlag = false;
				i->Word2st->uFlag = false;
			}
		}
	}
	if (timenow - startTime > timelim) { return; }
	if (Tmp->word == "" && step == 1) {
		nowNode = nowList;
		for (int K = 1; K <= nowLen; K++) nowNode = nowNode->next;//right position at list
		if (nowLen == nSet) {
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
					return;
				}
			}
			nListNum++;
			writeResult(2);
		}
	}
}

bool isRepeat(WordTwo* n) {
	if (n->Word1st->uFlag == false && n->Word2st->uFlag == false) return false;
	return true;
}

int main(int argc, char* argv[]) {
	parseCommandLineEnter(argc, argv);
	/******清空solution.txt文件，并打开等待写入,注意 只针对-n参数s*******/
	if (nSet>0) {
		outfile.open("solution.txt");
		outfile.close();
		outfile.open("solution.txt");
		outfile << "                   " << "\n";
	}
	/****************/
	gen(inputFileName);
	//gen("test2.txt");
	hSearch();
	outfile.close();
	/******对于-n，需要写入数字*******/
	if (nSet > 0) {
		outfile.open("solution.txt", ios::binary | ios::out | ios::in);
		outfile.seekp(0, ios::beg);
		outfile << to_string(nListNum) << "";
		outfile.close();
	}

	/*************/
	return 0;
}