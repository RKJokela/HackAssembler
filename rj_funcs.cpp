#include <algorithm>
#include <cctype>
#include <string>
#include "rj_funcs.h"

using namespace std;

namespace rkj
{
	int NumDigits(long long num, char base)
	{
		static long long n;
		switch (base)
		{
		case 'b':
		case 'B':
			n = num/2;
			break;
		case 'h':
		case 'H':
		case 'x':
		case 'X':
			n = num/0x10;
			break;
		case 'o':
		case 'O':
			n = num/8;
			break;
		case 'd':
		case 'D':
		default:
			n = num/10;
		}
		if (n != 0)
			return NumDigits(n, base) + 1;
		return 1;
	}

	inline char my_tolower(char c)
	{
		return static_cast<char>( tolower( static_cast<unsigned char>( c ) ) );
	}

	inline char my_toupper(char c)
	{
		return static_cast<char>( toupper( static_cast<unsigned char>( c ) ) );
	}

	void Capitalize(string& s)
	{
		transform(s.begin(), s.end(), s.begin(), rkj::my_toupper);
	}

	void UnCapitalize(string& s)
	{
		transform(s.begin(), s.end(), s.begin(), rkj::my_tolower);
	}
} // namespace rkj
