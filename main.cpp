#include "parser.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
	Parser parser;
	if (argc < 2) {
		cerr << "no filename specified; using interactive mode" << endl << endl;
		parser.SetInteractive(true);
		while (parser.HasLines()) {
			if (!parser.ParseLine()) {
				parser.SetInteractive(false);
			}
		}
	}
	else { // use command line filename
		string infile(argv[1]);
		size_t dotPos = infile.find(".asm");
		if (dotPos == string::npos || infile.substr(dotPos).length() != 4) {
			cerr << "Invalid filename. Must use '.asm' extension." << endl;
			return -1;
		}
		ifstream fin(infile);
		if (!fin) {
			cerr << "Cannot open file " << infile << endl;
			return -1;
		}
		infile.erase(dotPos);
		string outfile = infile + ".hack";
		ofstream fout(outfile);
		if (!fout) {
			cerr << "Cannot open file " << outfile << endl;
			return -1;
		}
		
		parser.SetInput(&fin);
		parser.SetOutput(&fout);
		
		cout << "Building symbol table..." << endl;
		parser.BuildSymbolTable();
		cout << "done." << endl;
		
		int srcLines = 0, codeLines = 0;
		while (parser.HasLines()) {
			srcLines++;
			if (parser.ParseLine())
				codeLines++;
		}
		
		parser.DumpSymbols();
		
		cout << "Finished processing " << infile << ".asm (" << srcLines << " lines)" << endl;
		cout << "Created " << outfile << " (" << codeLines << " lines)" << endl;
		
		fin.close();
		fout.close();
	}
	return 0;
}
