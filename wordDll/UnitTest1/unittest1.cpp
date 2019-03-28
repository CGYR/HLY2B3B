#include "stdafx.h"
#include "CppUnitTest.h"
#include "../wordDll/wordDll.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{		
	TEST_CLASS(UnitTest1)
	{
	public:


		TEST_METHOD(single_char)
		{
			string res = "";
			string words = "";
			Core* tmp = new Core();
			tmp->gen_chain_char("a,b,c,d,e,f,g", res, 0, 0);
			Assert::IsTrue(res == "");
			// TODO: 在此输入测试代码
		}
		TEST_METHOD(easy_word)
		{
			string res = "";
			string words = "";
			Core* tmp = new Core();
			tmp->gen_chain_word("abcd,efge,dddeee", res, 0, 0);
			Assert::IsTrue(res == "abcd\ndddeee\nefge\n");
			res = "";
			Core* tmpp = new Core();
			tmpp->gen_chain_word("a", res, 'e', 'e');
			Assert::IsTrue(res == "");
			//tmpp->writeResult(1);
			// TODO: 在此输入测试代码
		}

		TEST_METHOD(easyn)
		{
			string res = "";
			string words = "";
			Core* tmp = new Core();
			tmp->setPath("F:/HLY2B3B/Lab1/test1.txt", "");
			tmp->gen_chain_n("", 'c', 'w', 2, 60);
			Assert::IsTrue(tmp->nListNum == 1);
			// TODO: 在此输入测试代码
		}

		TEST_METHOD(easyn0)
		{
			string res = "";
			string words = "";
			Core* tmp = new Core();
			tmp->gen_chain_n("faksdfjlaksjfe.dslfkefnleknfadkfee/dfjejfjodf'efjeojor...ekjfkndk", 0, 0, 2, 60);
			Assert::IsTrue(tmp->nListNum == 5);
			tmp->writeResult(2);
			// TODO: 在此输入测试代码
		}

		TEST_METHOD(easyn1)
		{
			string res = "";
			string words = "";
			Core* tmp = new Core();
			tmp->gen_chain_n("faksdfjlaksjfe.dslfkefnleknfadkfee/dfjejfjodf'efjeojor...ekjfkndk", 0, 'k', 2, 60);
			Assert::IsTrue(tmp->nListNum == 2);
			// TODO: 在此输入测试代码
		}

		TEST_METHOD(easyn2)
		{
			string res = "";
			string words = "";
			Core* tmp = new Core();
			tmp->gen_chain_n("faksdfjlaksjfe.dslfkefnleknfadkfee/dfjejfjodf'efjeojor...ekjfkndk", 'f', 'k', 2, 60);
			Assert::IsTrue(tmp->nListNum == 1);
			// TODO: 在此输入测试代码
		}
		TEST_METHOD(easyn3)
		{
			string res = "";
			string words = "";
			Core* tmp = new Core();
			tmp->gen_chain_n("faksdfjlaksjfe.dslfkefnleknfadkfee/dfjejfjodf'efjeojoe...ekjfkndk", 'f', 'k', 3, 60);
			Assert::IsTrue(tmp->nListNum == 1);
			// TODO: 在此输入测试代码
		}

		TEST_METHOD(hardn0)
		{
			string res = "";
			string words = "";
			Core* tmp = new Core();
			tmp->setPath("F:/HLY2B3B/test/test_10.txt", "");
			tmp->gen_chain_n("", 'c', 'e', 2, 60);
			Assert::IsTrue(tmp->nListNum == 365);
			// TODO: 在此输入测试代码
		}
		TEST_METHOD(hardn3)
		{
			string res = "";
			string words = "";
			Core* tmp = new Core();
			tmp->setPath("F:/HLY2B3B/test/test_10.txt", "");
			tmp->gen_chain_n("", 0, 'e', 2, 20);
			Assert::IsTrue(tmp->nListNum > 3800);
			// TODO: 在此输入测试代码
		}

		TEST_METHOD(easy_word_ht)
		{
			string res = "";
			string words = "";
			Core* tmp = new Core();
			tmp->gen_chain_word("abcd,efge,dddeee", res, 'a', 'e');
			Assert::IsTrue(res == "abcd\ndddeee\nefge\n");
			Core* tmpp = new Core();
			tmpp->gen_chain_word("abcd,dfge,deef", res, 'a', 'e');
			Assert::IsTrue(res == "abcd\ndfge\n");
			// TODO: 在此输入测试代码
		}

		TEST_METHOD(easy_char)
		{
			string res = "";
			string words = "";
			Core* tmp = new Core();
			tmp->gen_chain_char("abcd,dfge,dddeekkkkkkkkkkkk,efff", res, 0, 0);
			Assert::IsTrue(res == "abcd\ndddeekkkkkkkkkkkk\n");
			// TODO: 在此输入测试代码
		}

		TEST_METHOD(easy_char_ht)
		{
			string res = "";
			string words = "";
			Core* tmp = new Core();
			tmp->gen_chain_char("abcd,kfge,dddeekkkkkkkkkkkk", res, 'd', 0);
			Assert::IsTrue(res == "dddeekkkkkkkkkkkk\nkfge\n");
			Core* tmpp = new Core();
			tmpp->gen_chain_char("abcd,dfgeeeeeee,dddeekkkkkkkkkkkk,dadd", res, 0, 'e');
			Assert::IsTrue(res == "abcd\ndadd\ndfgeeeeeee\n");
			tmpp->writeResult_fordll(res);
			//tmpp->writeResult(1);
			Assert::IsTrue(true);
			// TODO: 在此输入测试代码
		}
		TEST_METHOD(core)
		{
			Core *tmp = new Core();
			tmp->~Core();
			Assert::AreEqual(1, 1);
			// TODO: 在此输入测试代码
		}

		TEST_METHOD(hardn1)
		{
			string res = "";
			string words = "";
			Core* tmp = new Core();
			tmp->setPath("F:/HLY2B3B/test/test_10.txt", "");
			tmp->gen_chain_n("", 0, 0, 5, 20);
			Assert::IsTrue(tmp->nListNum > 200000);
			// TODO: 在此输入测试代码
		}

		TEST_METHOD(hardn2)
		{
			string res = "";
			string words = "";
			Core* tmp = new Core();
			tmp->setPath("F:/HLY2B3B/test/test_10.txt", "");
			tmp->gen_chain_n("", 0, 0, 4, 20);
			Assert::IsTrue(tmp->nListNum > 200000);
			tmp->writeResult(2);
			Assert::IsTrue(true);
			// TODO: 在此输入测试代码
		}
		TEST_METHOD(writeERR)
		{
			string res = "";
			string words = "";
			Core* tmp = new Core();
			tmp->writeError(1);
			Assert::AreEqual(tmp->APIback, -1);
			tmp->writeError(2);
			Assert::AreEqual(tmp->APIback, -2);
			tmp->writeError(3);
			Assert::AreEqual(tmp->APIback, -3);
			tmp->writeError(4);
			Assert::AreEqual(tmp->APIback, -4);
			tmp->writeError(5);
			Assert::AreEqual(tmp->APIback, -5);
			tmp->writeError(6);
			Assert::AreEqual(tmp->APIback, -6);
			tmp->writeError(7);
			Assert::AreEqual(tmp->APIback, -7);
			tmp->writeError(8);
			Assert::AreEqual(tmp->APIback, -8);
			tmp->writeError(9);
			Assert::AreEqual(tmp->APIback, -9);
			tmp->writeError(10);
			Assert::AreEqual(tmp->APIback, -10);
			tmp->writeError(11);
			Assert::AreEqual(tmp->APIback, -11);
			tmp->writeError(12);
			Assert::AreEqual(tmp->APIback, -12);
			tmp->writeError(13);
			Assert::AreEqual(tmp->APIback, -13);
			tmp->writeError(14);
			Assert::AreEqual(tmp->APIback, -14);
			tmp->writeError(15);
			Assert::AreEqual(tmp->APIback, -15);
			tmp->writeError(16);
			Assert::AreEqual(tmp->APIback, -16);
			tmp->writeError(17);
			Assert::AreEqual(tmp->APIback, -17);
			tmp->writeError(18);
			Assert::AreEqual(tmp->APIback, -18);
			tmp->writeError(19);
			Assert::AreEqual(tmp->APIback, -19);
			tmp->writeError(20);
			Assert::AreEqual(tmp->APIback, -20);
			tmp->writeError(21);
			Assert::AreEqual(tmp->APIback, -21);
			tmp->writeError(22);
			Assert::AreEqual(tmp->APIback, -22);
			tmp->writeError(23);
			Assert::AreEqual(tmp->APIback, -23);
			tmp->writeError(24);
			Assert::AreEqual(tmp->APIback, -24);
			tmp->writeError(25);
			Assert::AreEqual(tmp->APIback, -25);
			tmp->writeError(26);
			Assert::AreEqual(tmp->APIback, -26);
			tmp->writeError(27);
			Assert::AreEqual(tmp->APIback, -27);
			tmp->writeError(28);
			Assert::AreEqual(tmp->APIback, -28);
			tmp->writeError(29);
			Assert::AreEqual(tmp->APIback, -29);
			tmp->writeError(30);
			Assert::AreEqual(tmp->APIback, -30);
			tmp->writeError(31);
			Assert::AreEqual(tmp->APIback, -31);
			tmp->writeError(32);
			Assert::AreEqual(tmp->APIback, -32);
			tmp->writeError(33);
			Assert::AreEqual(tmp->APIback, -33);
			tmp->writeError(34);
			Assert::AreEqual(tmp->APIback, -34);
			tmp->writeError(35);
			Assert::AreEqual(tmp->APIback, -35);
			tmp->writeError(36);
			Assert::AreEqual(tmp->APIback, -36);
			tmp->writeError(37);
			Assert::AreEqual(tmp->APIback, -37);
			tmp->writeError(38);
			Assert::AreEqual(tmp->APIback, -38);
			tmp->writeError(39);
			Assert::AreEqual(tmp->APIback, -39);
			tmp->writeError(40);
			Assert::AreEqual(tmp->APIback, -40);
			tmp->writeError(41);
			Assert::AreEqual(tmp->APIback, -41);
			tmp->writeError(42);
			Assert::AreEqual(tmp->APIback, -42);
			tmp->writeError(43);
			Assert::AreEqual(tmp->APIback, -43);
			tmp->writeError(44);
			Assert::AreEqual(tmp->APIback, -44);
			tmp->writeError(45);
			Assert::AreEqual(tmp->APIback, -45);
			tmp->writeError(46);
			Assert::AreEqual(tmp->APIback, -46);
			tmp->writeError(47);
			Assert::AreEqual(tmp->APIback, -47);
			tmp->writeError(48);
			Assert::AreEqual(tmp->APIback, -48);
			tmp->writeError(49);
			Assert::AreEqual(tmp->APIback, -49);
			tmp->writeError(50);
			Assert::AreEqual(tmp->APIback, -50);
			tmp->writeError(51);
			Assert::AreEqual(tmp->APIback, -51);
			tmp->writeError(52);
			Assert::AreEqual(tmp->APIback, -52);
			tmp->writeError(53);
			Assert::AreEqual(tmp->APIback, -53);
			tmp->writeError(54);
			Assert::AreEqual(tmp->APIback, -54);
			tmp->writeError(55);
			Assert::AreEqual(tmp->APIback, -55);
			tmp->writeError(56);
			Assert::AreEqual(tmp->APIback, -56);
			tmp->writeError(57);
			Assert::AreEqual(tmp->APIback, -57);
			tmp->writeError(58);
			Assert::AreEqual(tmp->APIback, -58);
			tmp->writeError(59);
			Assert::AreEqual(tmp->APIback, -59);
			tmp->writeError(60);
			Assert::AreEqual(tmp->APIback, -60);
			tmp->writeError(61);
			Assert::AreEqual(tmp->APIback, -61);
			tmp->writeError(62);
			Assert::AreEqual(tmp->APIback, -62);
			tmp->writeError(63);
			Assert::AreEqual(tmp->APIback, -63);
			tmp->writeError(64);
			Assert::AreEqual(tmp->APIback, -64);
			tmp->writeError(65);
			Assert::AreEqual(tmp->APIback, -65);
			tmp->writeError(66);
			Assert::AreEqual(tmp->APIback, -66);
			tmp->writeError(67);
			Assert::AreEqual(tmp->APIback, -67);
			tmp->writeError(68);
			Assert::AreEqual(tmp->APIback, -68);
			tmp->writeError(69);
			Assert::AreEqual(tmp->APIback, -69);
			tmp->writeError(70);
			Assert::AreEqual(tmp->APIback, -70);
			tmp->writeError(71);
			Assert::AreEqual(tmp->APIback, -71);
			tmp->writeError(72);
			Assert::AreEqual(tmp->APIback, -72);
			tmp->writeError(73);
			Assert::AreEqual(tmp->APIback, -73);
			tmp->writeError(74);
			Assert::AreEqual(tmp->APIback, -74);
			tmp->writeError(75);
			Assert::AreEqual(tmp->APIback, -75);
			tmp->writeError(76);
			Assert::AreEqual(tmp->APIback, -76);
			tmp->writeError(77);
			Assert::AreEqual(tmp->APIback, -77);
			tmp->writeError(78);
			Assert::AreEqual(tmp->APIback, -78);
			tmp->writeError(79);
			Assert::AreEqual(tmp->APIback, -79);
			tmp->writeError(80);
			Assert::AreEqual(tmp->APIback, -80);
			tmp->writeError(81);
			Assert::AreEqual(tmp->APIback, -81);
			tmp->writeError(82);
			Assert::AreEqual(tmp->APIback, -82);
			tmp->writeError(83);
			Assert::AreEqual(tmp->APIback, -83);
			tmp->writeError(84);
			Assert::AreEqual(tmp->APIback, -84);
			tmp->writeError(85);
			Assert::AreEqual(tmp->APIback, -85);
			tmp->writeError(86);
			Assert::AreEqual(tmp->APIback, -86);
			tmp->writeError(87);
			Assert::AreEqual(tmp->APIback, -87);
			tmp->writeError(88);
			Assert::AreEqual(tmp->APIback, -88);
			tmp->writeError(89);
			Assert::AreEqual(tmp->APIback, -89);
			tmp->writeError(90);
			Assert::AreEqual(tmp->APIback, -90);
			tmp->writeError(91);
			Assert::AreEqual(tmp->APIback, -91);
			tmp->writeError(92);
			Assert::AreEqual(tmp->APIback, -92);
			tmp->writeError(93);
			Assert::AreEqual(tmp->APIback, -93);
			tmp->writeError(94);
			Assert::AreEqual(tmp->APIback, -94);
			tmp->writeError(95);
			Assert::AreEqual(tmp->APIback, -95);
			tmp->writeError(96);
			Assert::AreEqual(tmp->APIback, -96);
			tmp->writeError(97);
			Assert::AreEqual(tmp->APIback, -97);
			tmp->writeError(98);
			Assert::AreEqual(tmp->APIback, -98);
			tmp->writeError(99);
			Assert::AreEqual(tmp->APIback, -99);
			tmp->writeError(100);
			Assert::AreEqual(tmp->APIback, -100);
			tmp->writeError(101);
			Assert::AreEqual(tmp->APIback, -101);
			tmp->writeError(102);
			Assert::AreEqual(tmp->APIback, -102);
			tmp->writeError(103);
			Assert::AreEqual(tmp->APIback, -103);
			tmp->writeError(104);
			Assert::AreEqual(tmp->APIback, -104);
			tmp->writeError(105);
			Assert::AreEqual(tmp->APIback, -105);
			tmp->writeError(106);
			Assert::AreEqual(tmp->APIback, -106);
			tmp->writeError(107);
			Assert::AreEqual(tmp->APIback, -107);
			tmp->writeError(108);
			Assert::AreEqual(tmp->APIback, -108);
			tmp->writeError(109);
			Assert::AreEqual(tmp->APIback, -109);
			tmp->writeError(110);
			Assert::AreEqual(tmp->APIback, -110);
			tmp->writeError(111);
			Assert::AreEqual(tmp->APIback, -111);
			tmp->writeError(112);
			Assert::AreEqual(tmp->APIback, -112);
			tmp->writeError(113);
			Assert::AreEqual(tmp->APIback, -113);
			tmp->writeError(114);
			Assert::AreEqual(tmp->APIback, -114);
			tmp->writeError(115);
			Assert::AreEqual(tmp->APIback, -115);
			tmp->writeError(116);
			Assert::AreEqual(tmp->APIback, -116);
			tmp->writeError(117);
			Assert::AreEqual(tmp->APIback, -117);
			tmp->writeError(118);
			Assert::AreEqual(tmp->APIback, -118);
			tmp->writeError(119);
			Assert::AreEqual(tmp->APIback, -119);
			tmp->writeError(120);
			Assert::AreEqual(tmp->APIback, -120);
			tmp->writeError(121);
			Assert::AreEqual(tmp->APIback, -121);
			tmp->writeError(122);
			Assert::AreEqual(tmp->APIback, -122);
			tmp->writeError(123);
			Assert::AreEqual(tmp->APIback, -123);
			tmp->writeError(124);
			Assert::AreEqual(tmp->APIback, -124);
			tmp->writeError(125);
			Assert::AreEqual(tmp->APIback, -125);
			tmp->writeError(126);
			Assert::AreEqual(tmp->APIback, -126);
			tmp->writeError(127);
			Assert::AreEqual(tmp->APIback, -127);
			tmp->writeError(128);
			Assert::AreEqual(tmp->APIback, -128);
			tmp->writeError(129);
			Assert::AreEqual(tmp->APIback, -129);
			tmp->writeError(130);
			Assert::AreEqual(tmp->APIback, -130);
			tmp->writeError(131);
			Assert::AreEqual(tmp->APIback, -131);
			tmp->writeError(132);
			Assert::AreEqual(tmp->APIback, -132);
			tmp->writeError(133);
			Assert::AreEqual(tmp->APIback, -133);
			tmp->writeError(134);
			Assert::AreEqual(tmp->APIback, -134);
			tmp->writeError(135);
			Assert::AreEqual(tmp->APIback, -135);
			tmp->writeError(136);
			Assert::AreEqual(tmp->APIback, -136);
			tmp->writeError(137);
			Assert::AreEqual(tmp->APIback, -137);
			tmp->writeError(138);
			Assert::AreEqual(tmp->APIback, -138);
			tmp->writeError(139);
			Assert::AreEqual(tmp->APIback, -139);
			tmp->writeError(140);
			Assert::AreEqual(tmp->APIback, -140);
			tmp->writeError(141);
			Assert::AreEqual(tmp->APIback, -141);
			tmp->writeError(142);
			Assert::AreEqual(tmp->APIback, -142);
			tmp->writeError(143);
			Assert::AreEqual(tmp->APIback, -143);
			tmp->writeError(144);
			Assert::AreEqual(tmp->APIback, -144);
			tmp->writeError(145);
			Assert::AreEqual(tmp->APIback, -145);
			tmp->writeError(146);
			Assert::AreEqual(tmp->APIback, -146);
			tmp->writeError(147);
			Assert::AreEqual(tmp->APIback, -147);
			tmp->writeError(148);
			Assert::AreEqual(tmp->APIback, -148);
			tmp->writeError(149);
			Assert::AreEqual(tmp->APIback, -149);
			tmp->writeError(150);
			Assert::AreEqual(tmp->APIback, -150);
			tmp->writeError(151);
			Assert::AreEqual(tmp->APIback, -151);
			tmp->writeError(152);
			Assert::AreEqual(tmp->APIback, -152);
			tmp->writeError(153);
			Assert::AreEqual(tmp->APIback, -153);
			tmp->writeError(154);
			Assert::AreEqual(tmp->APIback, -154);
			tmp->writeError(155);
			Assert::AreEqual(tmp->APIback, -155);
			tmp->writeError(156);
			Assert::AreEqual(tmp->APIback, -156);
			tmp->writeError(157);
			Assert::AreEqual(tmp->APIback, -157);
			tmp->writeError(158);
			Assert::AreEqual(tmp->APIback, -158);
			tmp->writeError(159);
			Assert::AreEqual(tmp->APIback, -159);
			tmp->writeError(160);
			Assert::AreEqual(tmp->APIback, -160);
			tmp->writeError(161);
			Assert::AreEqual(tmp->APIback, -161);
			tmp->writeError(162);
			Assert::AreEqual(tmp->APIback, -162);
			tmp->writeError(163);
			Assert::AreEqual(tmp->APIback, -163);
			tmp->writeError(164);
			Assert::AreEqual(tmp->APIback, -164);
			tmp->writeError(165);
			Assert::AreEqual(tmp->APIback, -165);
			tmp->writeError(166);
			Assert::AreEqual(tmp->APIback, -166);
			tmp->writeError(167);
			Assert::AreEqual(tmp->APIback, -167);
			tmp->writeError(168);
			Assert::AreEqual(tmp->APIback, -168);
			tmp->writeError(169);
			Assert::AreEqual(tmp->APIback, -169);
			tmp->writeError(170);
			Assert::AreEqual(tmp->APIback, -170);
			tmp->writeError(171);
			Assert::AreEqual(tmp->APIback, -171);
			tmp->writeError(172);
			Assert::AreEqual(tmp->APIback, -172);
			tmp->writeError(173);
			Assert::AreEqual(tmp->APIback, -173);
			tmp->writeError(174);
			Assert::AreEqual(tmp->APIback, -174);
			tmp->writeError(175);
			Assert::AreEqual(tmp->APIback, -175);
			tmp->writeError(176);
			Assert::AreEqual(tmp->APIback, -176);
			tmp->writeError(177);
			Assert::AreEqual(tmp->APIback, -177);
			tmp->writeError(178);
			Assert::AreEqual(tmp->APIback, -178);
			tmp->writeError(179);
			Assert::AreEqual(tmp->APIback, -179);
			tmp->writeError(180);
			Assert::AreEqual(tmp->APIback, -180);
			tmp->writeError(181);
			Assert::AreEqual(tmp->APIback, -181);
			tmp->writeError(182);
			Assert::AreEqual(tmp->APIback, -182);
			tmp->writeError(183);
			Assert::AreEqual(tmp->APIback, -183);
			tmp->writeError(184);
			Assert::AreEqual(tmp->APIback, -184);
			tmp->writeError(185);
			Assert::AreEqual(tmp->APIback, -185);
			tmp->writeError(186);
			Assert::AreEqual(tmp->APIback, -186);
			tmp->writeError(187);
			Assert::AreEqual(tmp->APIback, -187);
			tmp->writeError(188);
			Assert::AreEqual(tmp->APIback, -188);
			tmp->writeError(189);
			Assert::AreEqual(tmp->APIback, -189);
			tmp->writeError(190);
			Assert::AreEqual(tmp->APIback, -190);
			tmp->writeError(191);
			Assert::AreEqual(tmp->APIback, -191);
			tmp->writeError(192);
			Assert::AreEqual(tmp->APIback, -192);
			tmp->writeError(193);
			Assert::AreEqual(tmp->APIback, -193);
			tmp->writeError(194);
			Assert::AreEqual(tmp->APIback, -194);
			tmp->writeError(195);
			Assert::AreEqual(tmp->APIback, -195);
			tmp->writeError(196);
			Assert::AreEqual(tmp->APIback, -196);
			tmp->writeError(197);
			Assert::AreEqual(tmp->APIback, -197);
			tmp->writeError(198);
			Assert::AreEqual(tmp->APIback, -198);
			tmp->writeError(199);
			Assert::AreEqual(tmp->APIback, -199);
			tmp->writeError(200);
			Assert::AreEqual(tmp->APIback, -200);
			tmp->writeError(201);
			Assert::AreEqual(tmp->APIback, -201);
			tmp->writeError(202);
			Assert::AreEqual(tmp->APIback, -202);
			tmp->writeError(203);
			Assert::AreEqual(tmp->APIback, -203);
			tmp->writeError(204);
			Assert::AreEqual(tmp->APIback, -204);
			tmp->writeError(205);
			Assert::AreEqual(tmp->APIback, -205);
			tmp->writeError(206);
			Assert::AreEqual(tmp->APIback, -206);
			tmp->writeError(207);
			Assert::AreEqual(tmp->APIback, -207);
			tmp->writeError(208);
			Assert::AreEqual(tmp->APIback, -208);
			tmp->writeError(209);
			Assert::AreEqual(tmp->APIback, -209);
			tmp->writeError(210);
			Assert::AreEqual(tmp->APIback, -210);
			tmp->writeError(211);
			Assert::AreEqual(tmp->APIback, -211);
			tmp->writeError(212);
			Assert::AreEqual(tmp->APIback, -212);
			tmp->writeError(213);
			Assert::AreEqual(tmp->APIback, -213);
			tmp->writeError(214);
			Assert::AreEqual(tmp->APIback, -214);
			tmp->writeError(215);
			Assert::AreEqual(tmp->APIback, -215);
			tmp->writeError(216);
			Assert::AreEqual(tmp->APIback, -216);
			tmp->writeError(217);
			Assert::AreEqual(tmp->APIback, -217);
			tmp->writeError(218);
			Assert::AreEqual(tmp->APIback, -218);
			tmp->writeError(219);
			Assert::AreEqual(tmp->APIback, -219);
			tmp->writeError(220);
			Assert::AreEqual(tmp->APIback, -220);
			tmp->writeError(221);
			Assert::AreEqual(tmp->APIback, -221);
			tmp->writeError(222);
			Assert::AreEqual(tmp->APIback, -222);
			tmp->writeError(223);
			Assert::AreEqual(tmp->APIback, -223);
			tmp->writeError(224);
			Assert::AreEqual(tmp->APIback, -224);
			tmp->writeError(225);
			Assert::AreEqual(tmp->APIback, -225);
			tmp->writeError(226);
			Assert::AreEqual(tmp->APIback, -226);
			tmp->writeError(227);
			Assert::AreEqual(tmp->APIback, -227);
			tmp->writeError(228);
			Assert::AreEqual(tmp->APIback, -228);
			tmp->writeError(229);
			Assert::AreEqual(tmp->APIback, -229);
			tmp->writeError(230);
			Assert::AreEqual(tmp->APIback, -230);
			tmp->writeError(231);
			Assert::AreEqual(tmp->APIback, -231);
			tmp->writeError(232);
			Assert::AreEqual(tmp->APIback, -232);
			tmp->writeError(233);
			Assert::AreEqual(tmp->APIback, -233);
			tmp->writeError(234);
			Assert::AreEqual(tmp->APIback, -234);
			tmp->writeError(235);
			Assert::AreEqual(tmp->APIback, -235);
			tmp->writeError(236);
			Assert::AreEqual(tmp->APIback, -236);
			tmp->writeError(237);
			Assert::AreEqual(tmp->APIback, -237);
			tmp->writeError(238);
			Assert::AreEqual(tmp->APIback, -238);
			tmp->writeError(239);
			Assert::AreEqual(tmp->APIback, -239);
			tmp->writeError(240);
			Assert::AreEqual(tmp->APIback, -240);
			tmp->writeError(241);
			Assert::AreEqual(tmp->APIback, -241);
			tmp->writeError(242);
			Assert::AreEqual(tmp->APIback, -242);
			tmp->writeError(243);
			Assert::AreEqual(tmp->APIback, -243);
			tmp->writeError(244);
			Assert::AreEqual(tmp->APIback, -244);
			tmp->writeError(245);
			Assert::AreEqual(tmp->APIback, -245);
			tmp->writeError(246);
			Assert::AreEqual(tmp->APIback, -246);
			tmp->writeError(247);
			Assert::AreEqual(tmp->APIback, -247);
			tmp->writeError(248);
			Assert::AreEqual(tmp->APIback, -248);
			tmp->writeError(249);
			Assert::AreEqual(tmp->APIback, -249);
			tmp->writeError(250);
			Assert::AreEqual(tmp->APIback, -250);
			tmp->writeError(251);
			Assert::AreEqual(tmp->APIback, -251);
			tmp->writeError(252);
			Assert::AreEqual(tmp->APIback, -252);
			tmp->writeError(253);
			Assert::AreEqual(tmp->APIback, -253);
			tmp->writeError(254);
			Assert::AreEqual(tmp->APIback, -254);
			tmp->writeError(255);
			Assert::AreEqual(tmp->APIback, -255);
			tmp->writeError(256);
			Assert::AreEqual(tmp->APIback, -256);
			tmp->writeError(257);
			Assert::AreEqual(tmp->APIback, -257);
			tmp->writeError(258);
			Assert::AreEqual(tmp->APIback, -258);
			tmp->writeError(259);
			Assert::AreEqual(tmp->APIback, -259);
			tmp->writeError(260);
			Assert::AreEqual(tmp->APIback, -260);
			tmp->writeError(261);
			Assert::AreEqual(tmp->APIback, -261);
			tmp->writeError(262);
			Assert::AreEqual(tmp->APIback, -262);
			tmp->writeError(263);
			Assert::AreEqual(tmp->APIback, -263);
			tmp->writeError(264);
			Assert::AreEqual(tmp->APIback, -264);
			tmp->writeError(265);
			Assert::AreEqual(tmp->APIback, -265);
			tmp->writeError(266);
			Assert::AreEqual(tmp->APIback, -266);
			tmp->writeError(267);
			Assert::AreEqual(tmp->APIback, -267);
			tmp->writeError(268);
			Assert::AreEqual(tmp->APIback, -268);
			tmp->writeError(269);
			Assert::AreEqual(tmp->APIback, -269);
			tmp->writeError(270);
			Assert::AreEqual(tmp->APIback, -270);
			tmp->writeError(271);
			Assert::AreEqual(tmp->APIback, -271);
			tmp->writeError(272);
			Assert::AreEqual(tmp->APIback, -272);
			tmp->writeError(273);
			Assert::AreEqual(tmp->APIback, -273);
			tmp->writeError(274);
			Assert::AreEqual(tmp->APIback, -274);
			tmp->writeError(275);
			Assert::AreEqual(tmp->APIback, -275);
			tmp->writeError(276);
			Assert::AreEqual(tmp->APIback, -276);
			tmp->writeError(277);
			Assert::AreEqual(tmp->APIback, -277);
			tmp->writeError(278);
			Assert::AreEqual(tmp->APIback, -278);
			tmp->writeError(279);
			Assert::AreEqual(tmp->APIback, -279);
			tmp->writeError(280);
			Assert::AreEqual(tmp->APIback, -280);
			tmp->writeError(281);
			Assert::AreEqual(tmp->APIback, -281);
			tmp->writeError(282);
			Assert::AreEqual(tmp->APIback, -282);
			tmp->writeError(283);
			Assert::AreEqual(tmp->APIback, -283);
			tmp->writeError(284);
			Assert::AreEqual(tmp->APIback, -284);
			tmp->writeError(285);
			Assert::AreEqual(tmp->APIback, -285);
			tmp->writeError(286);
			Assert::AreEqual(tmp->APIback, -286);
			tmp->writeError(287);
			Assert::AreEqual(tmp->APIback, -287);
			tmp->writeError(288);
			Assert::AreEqual(tmp->APIback, -288);
			tmp->writeError(289);
			Assert::AreEqual(tmp->APIback, -289);
			tmp->writeError(290);
			Assert::AreEqual(tmp->APIback, -290);
			tmp->writeError(291);
			Assert::AreEqual(tmp->APIback, -291);
			tmp->writeError(292);
			Assert::AreEqual(tmp->APIback, -292);
			tmp->writeError(293);
			Assert::AreEqual(tmp->APIback, -293);
			tmp->writeError(294);
			Assert::AreEqual(tmp->APIback, -294);
			tmp->writeError(295);
			Assert::AreEqual(tmp->APIback, -295);
			tmp->writeError(296);
			Assert::AreEqual(tmp->APIback, -296);
			tmp->writeError(297);
			Assert::AreEqual(tmp->APIback, -297);
			tmp->writeError(298);
			Assert::AreEqual(tmp->APIback, -298);
			tmp->writeError(299);
			Assert::AreEqual(tmp->APIback, -299);
			tmp->writeError(300);
			Assert::AreEqual(tmp->APIback, -300);
			tmp->writeError(301);
			Assert::AreEqual(tmp->APIback, -301);
			tmp->writeError(302);
			Assert::AreEqual(tmp->APIback, -302);
			tmp->writeError(303);
			Assert::AreEqual(tmp->APIback, -303);
			tmp->writeError(304);
			Assert::AreEqual(tmp->APIback, -304);
			tmp->writeError(305);
			Assert::AreEqual(tmp->APIback, -305);
			tmp->writeError(306);
			Assert::AreEqual(tmp->APIback, -306);
			tmp->writeError(307);
			Assert::AreEqual(tmp->APIback, -307);
			tmp->writeError(308);
			Assert::AreEqual(tmp->APIback, -308);
			tmp->writeError(309);
			Assert::AreEqual(tmp->APIback, -309);
			tmp->writeError(310);
			Assert::AreEqual(tmp->APIback, -310);
			tmp->writeError(311);
			Assert::AreEqual(tmp->APIback, -311);
			tmp->writeError(312);
			Assert::AreEqual(tmp->APIback, -312);
			tmp->writeError(313);
			Assert::AreEqual(tmp->APIback, -313);
			tmp->writeError(314);
			Assert::AreEqual(tmp->APIback, -314);
			tmp->writeError(315);
			Assert::AreEqual(tmp->APIback, -315);
			tmp->writeError(316);
			Assert::AreEqual(tmp->APIback, -316);
			tmp->writeError(317);
			Assert::AreEqual(tmp->APIback, -317);
			tmp->writeError(318);
			Assert::AreEqual(tmp->APIback, -318);
			tmp->writeError(319);
			Assert::AreEqual(tmp->APIback, -319);
			tmp->writeError(320);
			Assert::AreEqual(tmp->APIback, -320);
			tmp->writeError(321);
			Assert::AreEqual(tmp->APIback, -321);
			tmp->writeError(322);
			Assert::AreEqual(tmp->APIback, -322);
			tmp->writeError(323);
			Assert::AreEqual(tmp->APIback, -323);
			tmp->writeError(324);
			Assert::AreEqual(tmp->APIback, -324);
			tmp->writeError(325);
			Assert::AreEqual(tmp->APIback, -325);
			tmp->writeError(326);
			Assert::AreEqual(tmp->APIback, -326);
			tmp->writeError(327);
			Assert::AreEqual(tmp->APIback, -327);
			tmp->writeError(328);
			Assert::AreEqual(tmp->APIback, -328);
			tmp->writeError(329);
			Assert::AreEqual(tmp->APIback, -329);

			// TODO: 在此输入测试代码
		}
		TEST_METHOD(gen)
		{
			string res = "";
			string words = "";
			Core* tmp = new Core();
			tmp->nSet = 3;
			tmp->nFlag = true;
			tmp->hSet = "abcde";
			tmp->tSet = "fffkl";
			tmp->gen("");
			Assert::IsTrue(tmp->APIback == -1);
			tmp->gen("F:/HLY2B3B/test/test_10.txt");
			Assert::IsTrue(tmp->wordList[25]->word == "zhu");
			tmp->gen("F:/HLY2B3B/test/test_1.txt");
			Assert::IsTrue(tmp->APIback == -1);
			tmp->nSet = 2;
			tmp->nFlag = true;
			tmp->gen("F:/HLY2B3B/test/test_2.txt");
			Assert::IsTrue(tmp->APIback == -1);
			tmp->nSet = 2;
			tmp->nFlag = true;
			tmp->gen("F:/HLY2B3B/test/test_3.txt");
			Assert::IsTrue(tmp->APIback == -1);
			tmp->nSet = 2;
			tmp->nFlag = true;
			tmp->gen("F:/HLY2B3B/test/test_4.txt");
			Assert::IsTrue(tmp->APIback == -1);
			tmp->nSet = 2;
			tmp->nFlag = true;
			tmp->gen("F:/HLY2B3B/test/test_5.txt");
			Assert::IsTrue(tmp->APIback == -1);
			tmp->nSet = 0;
			tmp->gen("F:/HLY2B3B/test/test_1.txt");
			Assert::IsTrue(tmp->APIback == -1);
			tmp->gen("F:/HLY2B3B/test/test_2.txt");
			Assert::IsTrue(tmp->APIback == -1);
			tmp->gen("F:/HLY2B3B/test/test_3.txt");
			Assert::IsTrue(tmp->APIback == -1);
			// TODO: 在此输入测试代码
		}
		TEST_METHOD(fullrept)
		{
			string res = "";
			string words = "";
			Core* tmp = new Core();
			tmp->testCore();
			tmp->buffNum = 2000;
			bool ff = tmp->isFull();
			Assert::IsTrue(ff);
			tmp->nSet = 4;
			tmp->gen("F:/HLY2B3B/test/test_10.txt");

			tmp->wordList[0]->next2[0]->Word1st->uFlag = true;
			tmp->wordList[0]->next2[0]->Word2st->uFlag = true;
			Assert::IsTrue(tmp->isRepeat(tmp->wordList[0]->next2[0]));
			tmp->wordList[0]->next2[0]->Word1st->uFlag = false;
			tmp->wordList[0]->next2[0]->Word2st->uFlag = false;
			Assert::IsFalse(tmp->isRepeat(tmp->wordList[0]->next2[0]));
			//t1->uFlag = false;
			//t2->uFlag = false;
			//rpf = tmp->isRepeat(tmp->nowList->next2[0]);
			//Assert::IsTrue(rpf);
			// TODO: 在此输入测试代码
		}
		TEST_METHOD(writeres) {
			string res = "";
			Core* tmp = new Core();
			string words = "abcd.dfg,gij";
			tmp->maxLen = 0;
			tmp->maxNum = 0;
			tmp->writeResult_fordll(res);
			Assert::IsTrue(res == "");
			tmp->gen_chain_word(words, res, 0, 0);
			tmp->writeResult_fordll(res);
			Assert::IsTrue(res == "abcd\ndfg\ngij\n");
			tmp->~Core();
			Core* tmpp = new Core();
			tmpp->gen_chain_n(words, 0, 0, 3, 20);
			Assert::IsTrue(true);
			Core* tmppp = new Core();
			tmppp->gen_chain_n(words, 0, 0, 1, 20);
			Assert::IsTrue(true);
		}
	};
}