#ifndef SYMBOL_H_INCLUDED
#define SYMBOL_H_INCLUDED

#include <map>
#include <string>

namespace Symbol {

void init();

void addEntry(std::string symbol, int address);

bool contains(std::string symbol);

int  getAddress(std::string symbol);

void dumpTable();

}

#endif // SYMBOL_H_INCLUDED
