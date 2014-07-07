#ifndef		PARSER_H_INCLUDED
#define		PARSER_H_INCLUDED

#include <iostream>
#include <fstream>

// this class doesn't know whether it's operating on files, stdio, etc.
// just uses stream objects - caller decides what they point to
class Parser {
public:
	Parser();
	Parser(std::istream* in, std::ostream* out, bool interactive = false);
	~Parser();
	void SetInput(std::istream* instream);
	void SetOutput(std::ostream* outstream);
	void SetInteractive(bool interactive);
	// returns true if there are lines left in the stream, or always if interactive
	bool HasLines() const;
	// returns true only if the line generated any code
	bool ParseLine();
	// first pass - build symbol table
	void BuildSymbolTable();
	void DumpSymbols();
private:
	std::istream* input;
	std::ostream* output;
	std::ofstream my_ostream;
	bool hasLines;
	bool interactive;
	unsigned int lineCount;
	unsigned int srcLines;
	int currentVar;
};

#endif	//	PARSER_H_INCLUDED
