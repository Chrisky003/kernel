#include "types.h"
#include "string.h"

namespace lib::string {
	void memcpy(uint8 *dest, const uint8 *src, uint32 len)
	{
		for (; len != 0; len--) {
			*dest++ = *src++;
		}
	}

	void memset(void *dest, uint8 val, uint32 len)
	{
		uint8 *dst = (uint8 *)dest;

		for ( ; len != 0; len--) {
			*dst++ = val;
		}
	}

	void bzero(void *dest, uint32 len)
	{
		memset(dest, 0, len);
	}
	int strcmp(const char *str1, const char *str2)
	{
		while (*str1 && *str2 && *str1 == *str2) {
			str1++;
			str2++;
		}

		return *str1 - *str2;
	}

	char *strcpy(char *dest, const char *src)
	{
		char *tmp = dest;

		while (*src) {
			*dest++ = *src++;
		}

		*dest = '\0';

		return tmp;
	}

	char *strcat(char *dest, const char *src)
	{
		char *cp = dest;

		while (*cp) {
			cp++;
		}

		while ((*cp++ = *src++))
			;

		return dest;
	}

	int strlen(const char *src)
	{
		const char *eos = src;

			while (*eos++)
			;

		return (eos - src - 1);
	}
}