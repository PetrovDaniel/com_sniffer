#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <windows.h>
#include <stdio.h>
#include < time.h >


unsigned long GetString(char** buf);
int write_to_file(char buffer[], FILE* ffile, size_t length);