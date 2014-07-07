#include "code.h"
#include <map>

using namespace std;

namespace {
	map<string,string> mDest;
	map<string,string> mComp;
	map<string,string> mJump;
}

string Code::Dest(string d) {
	static bool isInited = false;
	string s;
	if (!isInited) {
		// map dest codes
		mDest[""]    = "000";
		mDest["M"]   = "001";
		mDest["D"]   = "010";
		mDest["MD"]  = "011";
		mDest["A"]   = "100";
		mDest["AM"]  = "101";
		mDest["AD"]  = "110";
		mDest["AMD"] = "111";
		
		isInited = true;
	}
	try {
		s = mDest.at(d);
	}
	catch (...) {
		s = "INV";
	}
	return s;
}

string Code::Comp(string c) {
	static bool isInited = false;
	string s;
	if (!isInited) {
		// map comp codes
		mComp["0"]   = "0101010";
		mComp["1"]   = "0111111";
		mComp["-1"]  = "0111010";
		mComp["D"]   = "0001100";
		mComp["A"]   = "0110000";
		mComp["M"]   = "1110000";
		mComp["!D"]  = "0001101";
		mComp["!A"]  = "0110001";
		mComp["!M"]  = "1110001";
		mComp["-D"]  = "0001111";
		mComp["-A"]  = "0110011";
		mComp["-M"]  = "1110011";
		mComp["D+1"] = "0011111";
		mComp["A+1"] = "0110111";
		mComp["M+1"] = "1110111";
		mComp["D-1"] = "0001110";
		mComp["A-1"] = "0110010";
		mComp["M-1"] = "1110010";
		mComp["D+A"] = "0000010";
		mComp["D+M"] = "1000010";
		mComp["D-A"] = "0010011";
		mComp["D-M"] = "1010011";
		mComp["A-D"] = "0000111";
		mComp["M-D"] = "1000111";
		mComp["D&A"] = "0000000";
		mComp["D&M"] = "1000000";
		mComp["D|A"] = "0010101";
		mComp["D|M"] = "1010101";
		
		isInited = true;
	}
	try {
		s = mComp.at(c);
	}
	catch (...) {
		s = "INVALID";
	}
	return s;	
}

string Code::Jump(string j) {
	static bool isInited = false;
	string s;
	if (!isInited) {
		// map jump codes
		mJump[""]    = "000";
		mJump["JGT"] = "001";
		mJump["JEQ"] = "010";
		mJump["JGE"] = "011";
		mJump["JLT"] = "100";
		mJump["JNE"] = "101";
		mJump["JLE"] = "110";
		mJump["JMP"] = "111";
		
		isInited = true;
	}
	try {
		s = mJump.at(j);
	}
	catch (...) {
		s = "INV";
	}
	return s;
}
