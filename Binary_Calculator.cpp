#include <bitset>
#include <cstdio>
#include <sstream>
#include <windows.h>
#include <tchar.h>
#include <Shlwapi.h>
#include <stack>
#include <map>

using namespace std;
static TCHAR* Transfer_Bin(int n, bool b)
{
	TCHAR* ress = new TCHAR[256];
	TCHAR* buf = new TCHAR[256];
	int i = 0, j = 0;
	if (b == TRUE)
		n--;
	while (n >= 1)
	{
		buf[i] = n % 2 + '0';
		i++;
		n /= 2;
	}
	buf[i] = '0';
	buf[++i] = '\0';
	if (b == TRUE)
	{
		i = 0;
		while (buf[i] != '\0')
		{
			if (buf[i] == '0')
				buf[i] = '1';
			else
				buf[i] = '0';
			i++;
		}
	}
	i--;
	while (i >= 0)
	{
		ress[j] = buf[i];
		j++;
		i--;
	}
	ress[j] = '\0';
	delete[] buf;
	return(ress);
}


static TCHAR* charRape(TCHAR* buf_bin, TCHAR a)
{
	size_t len = strlen(buf_bin);

	TCHAR* ret = new TCHAR[len + 2];

	StrCpy(ret, buf_bin);
	ret[len] = a;
	ret[len + 1] = '\0';

	return ret;
}

static TCHAR* Resout_Bin(TCHAR* buf_bin)
{
	TCHAR* res = new TCHAR[256];
	TCHAR* buff = new TCHAR[256];
	bool b = FALSE, c = FALSE, d = FALSE, e = FALSE;
	int num1, num2, i = 0, j = 0;
	TCHAR n1[50] = {}, n2[20] = {};

	if (buf_bin[0] == '-')
	{
		d = TRUE;
		i++;
	}
	while ((buf_bin[i] >= '0' && buf_bin[i] <= '9') || buf_bin[i] == '.')
	{
		n1[j] = buf_bin[i];
		if (buf_bin[i] == '.')
			b = TRUE;
		i++;
		j++;
	}
	j = 0;
	if (b == FALSE)
	{
		num1 = atoi(n1);
		strcpy(res, Transfer_Bin(num1, d));
		delete[] Transfer_Bin(num1, d);
	}
	else
		res = _strdup("Stop it! Get some help!");
	while (buf_bin[i] != '\0' && buf_bin[i] != ' ' && (buf_bin[i] < '0' || buf_bin[i] > '9') && buf_bin[i] != '.')
	{
		res = charRape(res, buf_bin[i]);
		i++;
	}
	if (buf_bin[i] == '\0' || buf_bin[i] == ' ')
		return(res);
	while ((buf_bin[i] >= '0' && buf_bin[i] <= '9') || buf_bin[i] == '.')
	{
		n2[j] = buf_bin[i];
		if (buf_bin[i] == '.')
			c = TRUE;
		i++;
		j++;
	}
	j = 0;
	if (c == FALSE)
	{
		num2 = atoi(n2);
		strcpy(buff, Transfer_Bin(num2, e));
		delete[] Transfer_Bin(num2, e);
		while (buff[j] != '\0')
		{
			res = charRape(res, buff[j]);
			j++;
		}
		delete[] buff;
	}
	else
		res = _strdup("Stop it! Get some help!");
	return(res);
}





