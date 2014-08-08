/*
 * main implementation: use this 'C++' sample to create your own application
 *
 */



#include "derivative.h" /* include peripheral declarations */
#include <iostream>
#include <wchar.h>

char *str1 = "abcdefghi";
char *str2 = "";

class counterclass
{
private:
  	int m_counter;
public:  
	counterclass(void) 
	{
		m_counter = 0;
	};
	void increment(void) 
	{
		m_counter++;
	};  	
};

int main()
{
	counterclass myccounter;
	
	wmemcpy((wchar_t *)str2,(const wchar_t *)str1,5);
	
	for(;;) {	
			myccounter.increment();
		}
	
	return 0;
}
