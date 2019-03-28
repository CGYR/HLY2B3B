// wordDll.cpp : 定义 DLL 应用程序的导出函数。
#include "stdafx.h"
#include "wordDll.h"

WordNode::WordNode(string inw)
{
	word = inw;
	len = word.length();
	head = word[0] - 97;
	tail = word[word.length() - 1] - 97;
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

WordTwo::WordTwo(WordNode*n1, WordNode*n2)
{
	Word1st = n1;
	Word2st = n2;
}

WordTwo::~WordTwo()
{
}

Core::Core()
{

}

Core::~Core()
{

}

void Core::testCore() {
	Core* tmp =new Core();
	tmp->~Core();
}

void Core::setPath(string inp,string op) {
	outputFilePath = "";
	inputFilePath = "";
	outputFilePath = op;
	inputFilePath = inp;
	return;
}

int Core::gen_chain_word(string words, string &result, char head, char tail) {
	wcFlag = true;
	gen_fordll(words,head,tail);
	hSearch(result);
	writeResult_fordll(result);
	return APIback;
}

int Core::gen_chain_char(string words, string &result, char head, char tail) {
	wcFlag = false;
	gen_fordll(words,head,tail);
	hSearch(result);
	writeResult_fordll(result);
	return APIback;
}

int Core::gen_chain_n(string words, char head, char tail, int n, time_t timeset) {
	if (n < 2) return -666;
	timelim = timeset;
	nSet = n;
	nFlag = true;
	outfile.open(outputFilePath + "solution.txt");
	outfile.close();
	outfile.open(outputFilePath + "solution.txt");
	outfile << "                   " << "\n";

	if (words != "") {
		gen_fordll(words, head, tail);
		hSearch_n();
	}
	else {
		if (head != 0) hSet += head;
		if (tail != 0) tSet += tail;
		gen(inputFilePath);
		hSearch_n();
	}
	outfile.seekp(0, ios::beg);
	outfile << to_string(nListNum) << "";
	outfile.close();
	return APIback;
}

bool Core::gen_fordll(string wordIn, char head, char tail) {
	isDLL = true;
	for (int i = 0; i < 26; i++) {
		wordList[i] = new WordNode();
	}
	if (wordIn.length()<2) {
		writeError(1);
		return false;
	}
	if (head != 0) hSet += head;
	if (tail != 0) tSet += tail;
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

	if (nSet == 0) return true;
	
	WordNode *Tmp, *Tmpp;
	for (int i = 0; i < 26 && nSet>2; i++) {
		Tmp = wordList[i];
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

	for (int i = 0; i < nSet * 2000; i++) {//2000 lists output 
		buffList.push_back(new WordNode());
	}
	return true;
}

void Core::writeResult_fordll(string &result) {
	result = "";
	if (maxLen < 2 && maxNum < 2) writeError(7);
	else {
		for (WordNode* nextNode = maxList; nextNode != NULL; nextNode = nextNode->next) {
			result = result + nextNode->word + "\n";
		}
	}
}

bool Core::gen(string path) {
	if (nSet == 0) return false;
	nFlag = true;
	for (int i = 0; i < 26; i++)  wordList[i] = new WordNode();
	
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

	for (int i = 0; i < nSet * 2000; i++) {//2000 lists output 
		buffList.push_back(new WordNode());
	}
	return true;
}

// 将错误代码写入solution.txt
// 在命令行运行模式中，则直接print一个错误后推出
// 输入：错误编号
void Core::writeError(int errorCode) {
		switch (errorCode) {
		case 1: {
			APIback = -1;
			return;
		}
		case 2: {
			APIback = -2;
			return;
		}
		case 3: {
			APIback = -3;
			return;
		}
		case 4: {
			APIback = -4;
			return;
		}
		case 5: {
			APIback = -5;
			return;
		}
		case 6: {
			APIback = -6;
			return;
		}
		case 7: {
			APIback = -7;
			return;
		}
		case 8: {
			APIback = -8;
			return;
		}
		case 9: { APIback = -9; return; }
		case 10: { APIback = -10; return; }
		case 11: { APIback = -11; return; }
		case 12: { APIback = -12; return; }
		case 13: { APIback = -13; return; }
		case 14: { APIback = -14; return; }
		case 15: { APIback = -15; return; }
		case 16: { APIback = -16; return; }
		case 17: { APIback = -17; return; }
		case 18: { APIback = -18; return; }
		case 19: { APIback = -19; return; }
		case 20: { APIback = -20; return; }
		case 21: { APIback = -21; return; }
		case 22: { APIback = -22; return; }
		case 23: { APIback = -23; return; }
		case 24: { APIback = -24; return; }
		case 25: { APIback = -25; return; }
		case 26: { APIback = -26; return; }
		case 27: { APIback = -27; return; }
		case 28: { APIback = -28; return; }
		case 29: { APIback = -29; return; }
		case 30: { APIback = -30; return; }
		case 31: { APIback = -31; return; }
		case 32: { APIback = -32; return; }
		case 33: { APIback = -33; return; }
		case 34: { APIback = -34; return; }
		case 35: { APIback = -35; return; }
		case 36: { APIback = -36; return; }
		case 37: { APIback = -37; return; }
		case 38: { APIback = -38; return; }
		case 39: { APIback = -39; return; }
		case 40: { APIback = -40; return; }
		case 41: { APIback = -41; return; }
		case 42: { APIback = -42; return; }
		case 43: { APIback = -43; return; }
		case 44: { APIback = -44; return; }
		case 45: { APIback = -45; return; }
		case 46: { APIback = -46; return; }
		case 47: { APIback = -47; return; }
		case 48: { APIback = -48; return; }
		case 49: { APIback = -49; return; }
		case 50: { APIback = -50; return; }
		case 51: { APIback = -51; return; }
		case 52: { APIback = -52; return; }
		case 53: { APIback = -53; return; }
		case 54: { APIback = -54; return; }
		case 55: { APIback = -55; return; }
		case 56: { APIback = -56; return; }
		case 57: { APIback = -57; return; }
		case 58: { APIback = -58; return; }
		case 59: { APIback = -59; return; }
		case 60: { APIback = -60; return; }
		case 61: { APIback = -61; return; }
		case 62: { APIback = -62; return; }
		case 63: { APIback = -63; return; }
		case 64: { APIback = -64; return; }
		case 65: { APIback = -65; return; }
		case 66: { APIback = -66; return; }
		case 67: { APIback = -67; return; }
		case 68: { APIback = -68; return; }
		case 69: { APIback = -69; return; }
		case 70: { APIback = -70; return; }
		case 71: { APIback = -71; return; }
		case 72: { APIback = -72; return; }
		case 73: { APIback = -73; return; }
		case 74: { APIback = -74; return; }
		case 75: { APIback = -75; return; }
		case 76: { APIback = -76; return; }
		case 77: { APIback = -77; return; }
		case 78: { APIback = -78; return; }
		case 79: { APIback = -79; return; }
		case 80: { APIback = -80; return; }
		case 81: { APIback = -81; return; }
		case 82: { APIback = -82; return; }
		case 83: { APIback = -83; return; }
		case 84: { APIback = -84; return; }
		case 85: { APIback = -85; return; }
		case 86: { APIback = -86; return; }
		case 87: { APIback = -87; return; }
		case 88: { APIback = -88; return; }
		case 89: { APIback = -89; return; }
		case 90: { APIback = -90; return; }
		case 91: { APIback = -91; return; }
		case 92: { APIback = -92; return; }
		case 93: { APIback = -93; return; }
		case 94: { APIback = -94; return; }
		case 95: { APIback = -95; return; }
		case 96: { APIback = -96; return; }
		case 97: { APIback = -97; return; }
		case 98: { APIback = -98; return; }
		case 99: { APIback = -99; return; }
		case 100: { APIback = -100; return; }
		case 101: { APIback = -101; return; }
		case 102: { APIback = -102; return; }
		case 103: { APIback = -103; return; }
		case 104: { APIback = -104; return; }
		case 105: { APIback = -105; return; }
		case 106: { APIback = -106; return; }
		case 107: { APIback = -107; return; }
		case 108: { APIback = -108; return; }
		case 109: { APIback = -109; return; }
		case 110: { APIback = -110; return; }
		case 111: { APIback = -111; return; }
		case 112: { APIback = -112; return; }
		case 113: { APIback = -113; return; }
		case 114: { APIback = -114; return; }
		case 115: { APIback = -115; return; }
		case 116: { APIback = -116; return; }
		case 117: { APIback = -117; return; }
		case 118: { APIback = -118; return; }
		case 119: { APIback = -119; return; }
		case 120: { APIback = -120; return; }
		case 121: { APIback = -121; return; }
		case 122: { APIback = -122; return; }
		case 123: { APIback = -123; return; }
		case 124: { APIback = -124; return; }
		case 125: { APIback = -125; return; }
		case 126: { APIback = -126; return; }
		case 127: { APIback = -127; return; }
		case 128: { APIback = -128; return; }
		case 129: { APIback = -129; return; }
		case 130: { APIback = -130; return; }
		case 131: { APIback = -131; return; }
		case 132: { APIback = -132; return; }
		case 133: { APIback = -133; return; }
		case 134: { APIback = -134; return; }
		case 135: { APIback = -135; return; }
		case 136: { APIback = -136; return; }
		case 137: { APIback = -137; return; }
		case 138: { APIback = -138; return; }
		case 139: { APIback = -139; return; }
		case 140: { APIback = -140; return; }
		case 141: { APIback = -141; return; }
		case 142: { APIback = -142; return; }
		case 143: { APIback = -143; return; }
		case 144: { APIback = -144; return; }
		case 145: { APIback = -145; return; }
		case 146: { APIback = -146; return; }
		case 147: { APIback = -147; return; }
		case 148: { APIback = -148; return; }
		case 149: { APIback = -149; return; }
		case 150: { APIback = -150; return; }
		case 151: { APIback = -151; return; }
		case 152: { APIback = -152; return; }
		case 153: { APIback = -153; return; }
		case 154: { APIback = -154; return; }
		case 155: { APIback = -155; return; }
		case 156: { APIback = -156; return; }
		case 157: { APIback = -157; return; }
		case 158: { APIback = -158; return; }
		case 159: { APIback = -159; return; }
		case 160: { APIback = -160; return; }
		case 161: { APIback = -161; return; }
		case 162: { APIback = -162; return; }
		case 163: { APIback = -163; return; }
		case 164: { APIback = -164; return; }
		case 165: { APIback = -165; return; }
		case 166: { APIback = -166; return; }
		case 167: { APIback = -167; return; }
		case 168: { APIback = -168; return; }
		case 169: { APIback = -169; return; }
		case 170: { APIback = -170; return; }
		case 171: { APIback = -171; return; }
		case 172: { APIback = -172; return; }
		case 173: { APIback = -173; return; }
		case 174: { APIback = -174; return; }
		case 175: { APIback = -175; return; }
		case 176: { APIback = -176; return; }
		case 177: { APIback = -177; return; }
		case 178: { APIback = -178; return; }
		case 179: { APIback = -179; return; }
		case 180: { APIback = -180; return; }
		case 181: { APIback = -181; return; }
		case 182: { APIback = -182; return; }
		case 183: { APIback = -183; return; }
		case 184: { APIback = -184; return; }
		case 185: { APIback = -185; return; }
		case 186: { APIback = -186; return; }
		case 187: { APIback = -187; return; }
		case 188: { APIback = -188; return; }
		case 189: { APIback = -189; return; }
		case 190: { APIback = -190; return; }
		case 191: { APIback = -191; return; }
		case 192: { APIback = -192; return; }
		case 193: { APIback = -193; return; }
		case 194: { APIback = -194; return; }
		case 195: { APIback = -195; return; }
		case 196: { APIback = -196; return; }
		case 197: { APIback = -197; return; }
		case 198: { APIback = -198; return; }
		case 199: { APIback = -199; return; }
		case 200: { APIback = -200; return; }
		case 201: { APIback = -201; return; }
		case 202: { APIback = -202; return; }
		case 203: { APIback = -203; return; }
		case 204: { APIback = -204; return; }
		case 205: { APIback = -205; return; }
		case 206: { APIback = -206; return; }
		case 207: { APIback = -207; return; }
		case 208: { APIback = -208; return; }
		case 209: { APIback = -209; return; }
		case 210: { APIback = -210; return; }
		case 211: { APIback = -211; return; }
		case 212: { APIback = -212; return; }
		case 213: { APIback = -213; return; }
		case 214: { APIback = -214; return; }
		case 215: { APIback = -215; return; }
		case 216: { APIback = -216; return; }
		case 217: { APIback = -217; return; }
		case 218: { APIback = -218; return; }
		case 219: { APIback = -219; return; }
		case 220: { APIback = -220; return; }
		case 221: { APIback = -221; return; }
		case 222: { APIback = -222; return; }
		case 223: { APIback = -223; return; }
		case 224: { APIback = -224; return; }
		case 225: { APIback = -225; return; }
		case 226: { APIback = -226; return; }
		case 227: { APIback = -227; return; }
		case 228: { APIback = -228; return; }
		case 229: { APIback = -229; return; }
		case 230: { APIback = -230; return; }
		case 231: { APIback = -231; return; }
		case 232: { APIback = -232; return; }
		case 233: { APIback = -233; return; }
		case 234: { APIback = -234; return; }
		case 235: { APIback = -235; return; }
		case 236: { APIback = -236; return; }
		case 237: { APIback = -237; return; }
		case 238: { APIback = -238; return; }
		case 239: { APIback = -239; return; }
		case 240: { APIback = -240; return; }
		case 241: { APIback = -241; return; }
		case 242: { APIback = -242; return; }
		case 243: { APIback = -243; return; }
		case 244: { APIback = -244; return; }
		case 245: { APIback = -245; return; }
		case 246: { APIback = -246; return; }
		case 247: { APIback = -247; return; }
		case 248: { APIback = -248; return; }
		case 249: { APIback = -249; return; }
		case 250: { APIback = -250; return; }
		case 251: { APIback = -251; return; }
		case 252: { APIback = -252; return; }
		case 253: { APIback = -253; return; }
		case 254: { APIback = -254; return; }
		case 255: { APIback = -255; return; }
		case 256: { APIback = -256; return; }
		case 257: { APIback = -257; return; }
		case 258: { APIback = -258; return; }
		case 259: { APIback = -259; return; }
		case 260: { APIback = -260; return; }
		case 261: { APIback = -261; return; }
		case 262: { APIback = -262; return; }
		case 263: { APIback = -263; return; }
		case 264: { APIback = -264; return; }
		case 265: { APIback = -265; return; }
		case 266: { APIback = -266; return; }
		case 267: { APIback = -267; return; }
		case 268: { APIback = -268; return; }
		case 269: { APIback = -269; return; }
		case 270: { APIback = -270; return; }
		case 271: { APIback = -271; return; }
		case 272: { APIback = -272; return; }
		case 273: { APIback = -273; return; }
		case 274: { APIback = -274; return; }
		case 275: { APIback = -275; return; }
		case 276: { APIback = -276; return; }
		case 277: { APIback = -277; return; }
		case 278: { APIback = -278; return; }
		case 279: { APIback = -279; return; }
		case 280: { APIback = -280; return; }
		case 281: { APIback = -281; return; }
		case 282: { APIback = -282; return; }
		case 283: { APIback = -283; return; }
		case 284: { APIback = -284; return; }
		case 285: { APIback = -285; return; }
		case 286: { APIback = -286; return; }
		case 287: { APIback = -287; return; }
		case 288: { APIback = -288; return; }
		case 289: { APIback = -289; return; }
		case 290: { APIback = -290; return; }
		case 291: { APIback = -291; return; }
		case 292: { APIback = -292; return; }
		case 293: { APIback = -293; return; }
		case 294: { APIback = -294; return; }
		case 295: { APIback = -295; return; }
		case 296: { APIback = -296; return; }
		case 297: { APIback = -297; return; }
		case 298: { APIback = -298; return; }
		case 299: { APIback = -299; return; }
		case 300: { APIback = -300; return; }
		case 301: { APIback = -301; return; }
		case 302: { APIback = -302; return; }
		case 303: { APIback = -303; return; }
		case 304: { APIback = -304; return; }
		case 305: { APIback = -305; return; }
		case 306: { APIback = -306; return; }
		case 307: { APIback = -307; return; }
		case 308: { APIback = -308; return; }
		case 309: { APIback = -309; return; }
		case 310: { APIback = -310; return; }
		case 311: { APIback = -311; return; }
		case 312: { APIback = -312; return; }
		case 313: { APIback = -313; return; }
		case 314: { APIback = -314; return; }
		case 315: { APIback = -315; return; }
		case 316: { APIback = -316; return; }
		case 317: { APIback = -317; return; }
		case 318: { APIback = -318; return; }
		case 319: { APIback = -319; return; }
		case 320: { APIback = -320; return; }
		case 321: { APIback = -321; return; }
		case 322: { APIback = -322; return; }
		case 323: { APIback = -323; return; }
		case 324: { APIback = -324; return; }
		case 325: { APIback = -325; return; }
		case 326: { APIback = -326; return; }
		case 327: { APIback = -327; return; }
		case 328: { APIback = -328; return; }
		case 329: { APIback = -329; return; }

		default:return;
		}
}

// 模式1: 针对-w -c 只需要输出一个单词串的情况
// 模式2: 针对-n 需要输出多个单词串的情况
void Core::writeResult(int mode) {
	string result = "";
		int count = 1;
		for (int i = 0; i < 2000 && buffList[i]->word != ""; i++,count++) {
			if (count != 1 && count%nSet == 0) {
				result = result + buffList[i]->word + "\n\n";
			}
			else {
				result = result + buffList[i]->word + "\n";
			}
		outfile << result << "";
	}
}

void Core::hSearch(string& res) {
	WordNode* Tmp;
		if (hSet.empty()) {
			for (int i = 0; i < 26; i++) {
				Tmp = wordList[i];
				if (timenow - startTime > timelim) { writeResult_fordll(res); return; }
				while (Tmp->word != "") {
					if (timenow - startTime > timelim) { writeResult_fordll(res); return; }
					nowLen++;
					nowNum += Tmp->len;//nowNum: sum of char
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
			//sort(hSet.begin(), hSet.end());
			//hSet.erase(unique(hSet.begin(), hSet.end()), hSet.end());//hSet去重字符
			for (unsigned int i = 0; i < hSet.length(); i++) {
				if (timenow - startTime > timelim) { writeResult_fordll(res); return; }
				int num = hSet[i] - 97;
				Tmp = wordList[num];//choose word's begin with chars in hSet
				while (Tmp->word != "") {
					if (timenow - startTime > timelim) { writeResult_fordll(res); return; }
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
		writeResult_fordll(res);
}

void Core::hSearch_n() {
	WordNode* Tmp;
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
				if (timenow - startTime > timelim) { return; }
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
			//sort(hSet.begin(), hSet.end());
			//hSet.erase(unique(hSet.begin(), hSet.end()), hSet.end());//hSet去重字符
			for (unsigned int i = 0; i < hSet.length(); i++) {
				if (timenow - startTime > timelim) { if (!isFull()) writeResult(2); return; }
				int num = hSet[i] - 97;
				Tmp = wordList[num];
				while (Tmp->word != "") {
					if (timenow - startTime > timelim) { if (!isFull()) writeResult(2); return; }
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
							if (timenow - startTime > timelim) { if (!isFull()) writeResult(2); return; }
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

		if (!isFull()) writeResult(2);
}

void Core::fSearch(int rank) {
	timenow = time(NULL);
	if (timenow - startTime > timelim) return;//time limit, avoid ...
	WordNode* Tmp = wordList[rank];
	while (Tmp->word != "") {
		if (timenow - startTime > timelim) return;
		if (Tmp->uFlag == true) {//has searched, find next
			Tmp = Tmp->next;
			continue;
		}
		//insert into now list:
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
	if (Tmp->word == "") {//end of one search
		if (!tSet.empty()) {//-ttttt
			bool tailFlag = false;
			for (unsigned int i = 0; i < tSet.length(); i++) {
				if (nowNode->tail == tSet[i] - 97) {
					tailFlag = true;
					break;
				}
			}
			if (!tailFlag) {//if tail not fit, then back search
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
		if ((nowLen > maxLen) && wcFlag) {//update maxList
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
			//back search:
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
		else if ((nowNum > maxNum) && !wcFlag) {//update maxList
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
				nowNum -= Tmp->next->len;//back search for nowNum
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

void Core::nSearch(WordNode *now, int step) {
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
		if (nowLen == nSet) {//fit len
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
			buffNum++;
			if (isFull()) {
				buffNum = 0;
				writeResult(2);
				for (auto& i : buffList) i->word = "";//init
				WordNode* TnNode = nowList;
				for (int i = 0; i < nSet; i++) {
					buffList[i]->word = TnNode->word;
					TnNode = TnNode->next;
				}
			}
			else {//insert nowList into buff
				WordNode* TnNode = nowList;
				for (int i = buffNum*nSet - nSet; i < buffNum*nSet; i++) {
					buffList[i]->word = TnNode->word;
					TnNode = TnNode->next;
				}
			}

		}
		else {//then 2 step
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
				nSearch(i->Word2st, 2);//searching by 2
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
			buffNum++;
			if (isFull()) {//full
				buffNum = 0;
				writeResult(2);//output buff
				for (auto& i : buffList) i->word = "";//init buff
				WordNode* TnNode = nowList;
				for (int i = 0; i < nSet; i++) {
					buffList[i]->word = TnNode->word;
					TnNode = TnNode->next;
				}
			}
			else {//not full
				WordNode* TnNode = nowList;
				for (int i = buffNum*nSet - nSet; i < buffNum*nSet; i++) {//insert into right pos
					buffList[i]->word = TnNode->word;
					TnNode = TnNode->next;
				}
			}
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
}

bool Core::isRepeat(WordTwo* n) {
	if (n->Word1st->uFlag == false && n->Word2st->uFlag == false) return false;
	return true;
}

bool Core::isFull() {
	if (2000 - buffNum < 1)
		 return true;
	return false;
}