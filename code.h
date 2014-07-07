#ifndef CODE_H_INCLUDED
#define CODE_H_INCLUDED

#include <string>

namespace Code
{
	std::string Dest(std::string d); // returns "bbb" translated dest opcode
	std::string Comp(std::string c); // returns "bbbbbbb" translated comp opcode
	std::string Jump(std::string j); // returns "bbb" translated jump opcode
}

#endif // CODE_H_INCLUDED
