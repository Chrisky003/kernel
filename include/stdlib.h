#pragma once
#include "types.h"

void memcpy(uint8 *dest, const uint8 *src, uint32 len);
void memset(void *dest, uint8 val, uint32 len);
void bzero(void *dest, uint32 len);
int strcmp(const char *str1, const char *str2);
char *strcpy(char *dest, const char *src);
char *strcat(char *dest, const char *src);
int strlen(const char *src);

#include "io.h"
