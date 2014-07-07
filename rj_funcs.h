#ifndef RJ_FUNCS_H_INCLUDED
#define RJ_FUNCS_H_INCLUDED

namespace rkj
{
	/*	NumDigits
	 *		Calculates the number of digits in any
	 *		integer. RECURSIVE, WOOOOOUOOO!!!1!
	 *		-  num: number to count digits
	 *		- base: optional representation
	 *				- 'd': Decimal (DEFAULT)
	 *				- 'x': Hexadecimal
	 *				- 'b': Binary
	 *				- 'o': Octal
	 */
	int NumDigits(long long num, char base = 'd');

	inline char my_tolower(char);
	inline char my_toupper(char);

	void Capitalize(std::string&);
	void UnCapitalize(std::string&);
}

#endif // RJ_FUNCS_H_INCLUDED
