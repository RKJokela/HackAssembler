#include "symbol.h"
#include <string>
#include <iostream>

using namespace std;

namespace Symbol {

namespace {
	map<string,int> symbolTable;
	const string reservedStr[] = {
		"SP",   "LCL",  "ARG",  "THIS", "THAT",
		
		"R0",   "R1",   "R2",   "R3",
		"R4",   "R5",   "R6",   "R7",
		"R8",   "R9",   "R10",  "R11",
		"R12",  "R13",  "R14",  "R15",
		
		"SCREEN", "KBD"
	};
	const int reservedAddr[] = {
		0x0000, 0x0001, 0x0002, 0x0003, 0x0004,
		
		0x0000, 0x0001, 0x0002, 0x0003,
		0x0004, 0x0005, 0x0006, 0x0007,
		0x0008, 0x0009, 0x000a, 0x000b,
		0x000c, 0x000d, 0x000e, 0x000f,
		
		0x4000, 0x6000
	};
}

void init() {
	for (int i = 0; i < (sizeof(reservedAddr)/sizeof(int)); ++i) {
		symbolTable[reservedStr[i]] = reservedAddr[i];
	}
}

void addEntry(string symbol, int address) {
	symbolTable[symbol] = address;
}

bool contains(string symbol) {
	return ( symbolTable.find(symbol) != symbolTable.end() );
}

int  getAddress(string symbol) {
	int addr = 0;
	try {
		addr = symbolTable.at(symbol);
	}
	catch (...) {
		return 0;
	}
	return addr;
}

bool _reserved(const string& s) {
	for (int i = 0; i < (sizeof(reservedAddr)/sizeof(int)); ++i) {
		if (s == reservedStr[i])
			return true;
	}
	return false;
}

void dumpTable() {
	cout << endl << "SYM\tVAL\n---\t---" << endl;
	for (auto it = symbolTable.begin(); it != symbolTable.end(); ++it) {
		if (_reserved(it->first))
			continue;
		cout << it->first << '\t' << it->second << endl;
	}
	cout << endl;
}

}
