/*
I?i?aoaoa io oaee ec?ac nun ioaa?yue e caoaa?yue neiae ().
-Aa na i?iaa?e aaee neiaeoa na iinoaaaie i?aaeeii, o.a. aaee ia anyea ioaa?yua neiaa eia ioaaeia nuioaaonoaaua caoaa?yua neiaa
-Iaea ec?acuo nuau??a e a?oae aeaiaa neiae <> [] {}.
-Aei a aaaai ei?aeoai ec?ac, aa na caieoao aua oaee ane?ee aaieee iiceoee ia nuioaaoie aaieee neiae.
I?eia?: (a+(b-c)*((d+e)/f)). Aa na ecaaaa: 0-18, 3-7,9-17,10-14
*/



#include <iostream>
#include"Stack_char.hpp"
#include"Stack_num.hpp"

int main()
{
	const char* text = "(a+(b-c)*((d+e)/f))";

	Stack_char scopes;
	Stack_num num;

	int i = 0;
	while(text[i])
	{
		if (text[i] == '(')
		{
			scopes.push(text[i]);
			num.push((char)i);
		}

		if (text[i] == ')')
		{
			if (scopes.top() == '(')
			{
				std::cout << num.top() << "-" << i << std::endl;
				scopes.pop();
				num.pop();
			}
		}
		i++;
	}

	return 0;
}