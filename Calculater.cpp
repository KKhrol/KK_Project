#include <cstdio>
#include <sstream>
#include <windows.h>
#include <tchar.h>
#include <Shlwapi.h>
#include <stack>
#include <map>
#pragma warning(disable : 4996)
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS
#define N 100

inline TCHAR *Calculate(TCHAR *buf)
{
	std::basic_string<TCHAR> s(buf), scalc, sres;
	std::basic_string<TCHAR>::size_type sym;
	
	while ((sym = s.find(TEXT(' '))) != std::basic_string<TCHAR>::npos)
	{
		s.erase(sym, 1);

	}

	std::map<TCHAR, size_t> map;

	map.insert(std::make_pair(TEXT('|'), 5));
	map.insert(std::make_pair(TEXT('^'), 5));
	map.insert(std::make_pair(TEXT('&'), 4));
	map.insert(std::make_pair(TEXT('*'), 3));
	map.insert(std::make_pair(TEXT('/'), 3));
	map.insert(std::make_pair(TEXT('+'), 2));
	map.insert(std::make_pair(TEXT('-'), 2));
	map.insert(std::make_pair(TEXT('('), 1));


	std::stack<TCHAR> stack;

	for (auto it = s.begin(); it != s.end(); ++it)
	{
		if ((!isdigit(*it) && TEXT('.') != *it) && !(s.begin() == it && '-' == *it))
		{
			scalc += TEXT(' ');

			if (TEXT(')') == *it)
			{
				while (stack.top() != TEXT('('))
				{
					scalc += stack.top();
					stack.pop();
					scalc += TEXT(' ');
				}
				stack.pop();
			}
			else if (TEXT('(') == *it)
			{
				stack.push(*it);
			}

			else if (stack.empty() || (map[stack.top()] < map[*it]))
			{
				stack.push(*it);
			}
			else
			{
				do
				{
					scalc += stack.top();
					stack.pop();
					scalc += TEXT(' ');
				} while (!(stack.empty() || (map[stack.top()] < map[*it])));

				stack.push(*it);
			}
		}
		else
		{
			scalc += *it;
		}
	}


	while (!stack.empty())
	{
		scalc += stack.top();
		scalc += TEXT(' ');
		stack.pop();
	}
	
	std::stack<double> dstack;
	std::basic_stringstream<TCHAR> ss(scalc);
	double x, y;
	TCHAR c;

	while (ss.get(c))
	{
		if (isdigit(c) || TEXT('.') == c || (1 == ss.tellg() && TEXT('-') == c))
		{
			ss.unget();
			ss >> x;
			dstack.push(x);
		}

		else if (!isspace(c))
		{
			y = dstack.top();
			dstack.pop();
			x = dstack.top();
			dstack.pop();

			switch (c)
			{
			case TEXT('+'):
				dstack.push(x + y);
				break;
			case TEXT('-'):
				dstack.push(x - y);
				break;
			case TEXT('*'):
				dstack.push(x * y);
				break;
			case TEXT('/'):
				dstack.push(x / y);
				break;
			case TEXT('|'):
				dstack.push(int(x) | int(y));
				break;
			case TEXT('&'):
				dstack.push(int(x) & int(y));
				break;
			case TEXT('^'):
				dstack.push(int(x) ^ int(y));
				break;
			}
		}
	}
	if (1 == dstack.size())
	{
		_stprintf(buf, TEXT("%lf"), dstack.top());

		dstack.pop();
	}
	else
	{
		_stprintf(buf, TEXT("Error"));
	}
	return buf;
}

