// testDLL.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<Windows.h>
#include "wordDll.h"

using namespace std;

int main()
{
	Core*tmp = new Core();
	string input = "abcdf.dfkjee.sdfkejf/fkens";
	string result = "abcdefg";
	//tmp->setPath("F:/HLY2B3B/Lab1/test1.txt", "");
	//fff(result);
	//tmp->setPath("F://HLY2B3B/wordDll/" , "F://HLY2B3B/wordDll/");
	int i = tmp->gen_chain_word("",result, 0, 0);
	//cout << i<<endl<<result << endl;
	while (true)
	{

	}
}

