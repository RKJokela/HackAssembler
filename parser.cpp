#include <string>
#include <bitset>
#include "parser.h"
#include "code.h"
#include "symbol.h"
#include "rj_funcs.h"

#define DST_DELIM    '='
#define JMP_DELIM    ';'
#define COMMENT_MARK "//"
#define WHITESPACE   " \t"

using namespace std;

enum InstType {
	A_INSTRUCTION,
	C_INSTRUCTION,
	L_INSTRUCTION
};

Parser::Parser() :
	input(&cin),
	output(NULL),
	hasLines(false),
	interactive(false),
	lineCount(0),
	srcLines(0),
	currentVar(16) { 
	}

Parser::Parser(std::istream* in, std::ostream* out, bool _int) :
	input(in),
	output(out),
	hasLines(false),
	interactive(_int),
	lineCount(0),
	srcLines(0),
	currentVar(16) { 
	}
	
Parser::~Parser() {
	my_ostream.close();
}
	
void Parser::SetInput(std::istream* instream) {
	input = instream;
}

void Parser::SetOutput(std::ostream* outstream) {
	my_ostream.close();
	output = outstream;
}
	
void Parser::SetInteractive(bool interactive) {
	this->interactive = interactive;
}

bool Parser::HasLines() const {
	if (interactive)
		return true;
	return !input->eof();
}

void remove_ws(string& s) {
	size_t pos = 0;
	while ( (pos = s.find_first_of(WHITESPACE)) != string::npos ) {
		s.erase(pos, 1); // erase the space and loop
	}
}
void remove_comments(string& s) {
	size_t pos = s.find(COMMENT_MARK);
	if ( pos != string::npos ) {
		s.erase(pos); // erase to end of line
	}
}

bool Parser::ParseLine() {
	static char cs[80];
	if (!output)
		my_ostream.open("out.hack");
	srcLines++;
	ostream& out = *output;
	istream& in  = *input;
	in.getline(cs, 80);
	string s(cs);
	remove_ws(s);
	remove_comments(s);
	rkj::Capitalize(s);
	if (s.empty() || s.find_first_not_of("01AMD-!(@") == 0)
		return false;
	string code;
	switch (s[0]) {
	case '(': // L_COMMAND
		// do nothing - symbol already defined in first pass
		return false;
	case '@': do {// A_COMMAND
		code = s.substr(1);
		int addr;
		try {
			addr = stoul(code);
		}
		catch (...) {
			if (!Symbol::contains(code))
				Symbol::addEntry(code, currentVar++);
			addr = Symbol::getAddress(code);
		}
		bitset<15> bits(addr);
		code = "0" + bits.to_string();
		} while(0); break;
	default:  // C_COMMAND
		string dst = "", cmp = "", jmp = "";
		size_t dstPos = s.find(DST_DELIM);
		size_t jmpPos = s.find(JMP_DELIM);
		if (jmpPos != string::npos) {
			jmp = s.substr(jmpPos+1, string::npos);
			s.erase(jmpPos);
		}
		if (dstPos != string::npos) {
			dst = s.substr(0, dstPos);
			s.erase(0, dstPos+1);
		}
		cmp = s;
		code = "111" + Code::Comp(cmp) + Code::Dest(dst) + Code::Jump(jmp);
		break;
	}
	if (code.find("INV") != string::npos) {
		cerr << "INVALID INSTRUCTION: LINE " << srcLines << endl;
		return false;
	}
	lineCount++;
	// if (code.length() > 12) {
		// code.insert(12, " ");
		// code.insert(8, " ");
		// code.insert(4, " ");
	// }
	out << code << endl;
	return true;
}

// Works on pre-processed lines - no whitespace before first character
// Does NOT check if the C_INSTRUCTION is a valid instruction
InstType get_inst_type(string& s) {
	if (s[0] == '@')
		return A_INSTRUCTION;
	if (s[0] == '(')
		return L_INSTRUCTION;
	return C_INSTRUCTION;
}

void Parser::BuildSymbolTable() {
	Symbol::init();
	if (!input)
		return;
	istream& in = *input;
	char cs[80];
	int address = 0;
	while (in) {
		in.getline(cs, 80);
		string s(cs);
		remove_ws(s);
		remove_comments(s);
		rkj::Capitalize(s);
		if (s.empty() || s.find_first_not_of("01AMD-!(@") == 0)
			continue;
		InstType inst = get_inst_type(s);
		if (inst == A_INSTRUCTION || inst == C_INSTRUCTION) {
			address++;
		}
		else if (inst == L_INSTRUCTION) {
			s.erase(0, 1);
			try {s.erase(s.find(')'));}
			catch (...) {
				cerr << "ERROR IN LABEL DEFINITION: ADDRESS = " << address << endl;
				return;
			}
			Symbol::addEntry(s, address);
		}
	}
	in.clear();
	in.seekg(0, in.beg);
#ifdef DEBUG
	Symbol::dumpTable();
#endif // DEBUG
}

void Parser::DumpSymbols() {
	Symbol::dumpTable();
}
