#include<iostream>
#include"Stack.hpp"


bool is_operation(char p)
{
	if (p == '+' || p == '-' || p == '*' || p == '/')
		return true;
	else
		return false;
}

double calculate_rpn(const char* t)
{
	Stack<double> st;
	int i = 0;
	//12+34/5-*
	while (t[i])
	{
		if (t[i] >= '0' && t[i] <= '9')
		{
			st.push(t[i] - '0');
		}
		else if (is_operation(t[i]))
		{
			double a = st.top();
			st.pop();
			double b = st.top();
			st.pop();
			if (t[i] == '+')
			{
				b += a;
			}
			else if (t[i] == '-')
			{
				b -= a;
			}
			else if (t[i] == '*')
			{
				b *= a;
			}
			else
			{
				b /= a;
			}
			st.push(b);
		}
		i++;
	}
	double num = st.top();
	st.pop();
	return num;
}

int main()
{
	std::cout << calculate_rpn("12+34/5-*") << std::endl;
	return 0;
}