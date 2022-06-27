#include <iostream>
#include <stack>

struct oper_s
{
	const int start_number_ascii = 48;
	const int end_number_ascii = 57;
	const int Bracket_open = 40;
	const int Bracket_close = 41;
	const int mul_oper = 42;
	const int add_oper = 43;
	const int sub_oper = 45;
	const int div_oper = 47;
};

bool check_braket(const std::string &line, const  struct oper_s &s)
{
	std::stack <char>check_stack;
	int i = 0;
	
	while (line[i])
	{
		if (line[i] == s.Bracket_open)
		{
			check_stack.push(line[i]);
		}
		if (line[i] == s.Bracket_close)
		{
			if (check_stack.empty())
				return false;
			check_stack.pop();
		}
		i++;
	}
	if (check_stack.empty())
		return true;
	return false;
}

int oper_calc(int a, int b, char oper, const  struct oper_s &s)
{
	if (oper == s.add_oper)
		return a + b;
	if (oper == s.mul_oper)
		return a * b;
	if (oper == s.sub_oper)
		return a - b;
	if (oper == s.div_oper)
		return a / b;
	return 0;
}

int main()
{
	int i = 0;
	std::stack <int> values;
	std::stack <char> oper_stack;
	std::string s = "((((1+2)-5)*5)/2)";
	struct oper_s oper;
	int a1 = 0;
	int a2 = 0;
	if (!check_braket(s,oper))
		return 0;
	while (s[i])
	{
		if (s[i] >= oper.start_number_ascii && s[i] <= oper.end_number_ascii)
		{
			values.push(atoi(s.c_str() + i));
		}
		else if (s[i] == oper.Bracket_open)
		{
			i++;
			continue;
		}
		else if(s[i] == oper.mul_oper || s[i] == oper.add_oper \
		|| s[i] == oper.sub_oper || s[i] == oper.div_oper)
		{
			oper_stack.push(s[i]);
		}
		else if(s[i] == oper.start_number_ascii)
		{
			i++;
			continue;
		}
		if (s[i] == oper.Bracket_close)
		{
			a1 = values.top();
			values.pop();
			a2 = values.top();
			values.pop();
			values.push(oper_calc(a2, a1, oper_stack.top(), oper));
			oper_stack.pop();
		}
		i++;
	}
	return 1;
}