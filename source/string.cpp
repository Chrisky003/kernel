#include "string.h"
#include "memory.h"

namespace string
{
	int strlen(const char *str)
	{
		int len = 0;
		while (str[len] != 0)
		{
			len++;
		}
		return ++len;
	}
	
	int strcpy(char *dest, const char *src)
	{
		int len = strlen(dest);
		memory::memcpy(dest, src, len);
		return ++len;
	}
	
	int strcmp(const char *str1, const char *str2)
	{
		for(;*str1==*str2;++str1,++str2)
			if(*str1=='\0')
				return(0);
		return((*(unsigned char*)str1<*(unsigned char*)str2)?-1:+1);
	}
}
