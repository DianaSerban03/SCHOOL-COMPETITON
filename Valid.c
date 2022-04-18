#pragma once
#include "Valid.h"
#include <ctype.h>
#include <string.h>
#include <assert.h>

int ValidateName(char* nume, char* prenume) {

	return ValidTxt(nume) && ValidTxt(prenume);
}



int ValidTxt(char* txt) {
	int i;
	for (i = 0; i < strlen(txt); i++)
		if (!isalpha(txt[i]))
			return 0;

	if (strlen(txt) == 0)
		return 0;
	return 1;
}

int ValidNota(int nota) {

	return nota <= 10 && nota >= 0;
}

void test_valid_name()
{
	assert(ValidateName("Pop", "Ana") == 1);
	assert(ValidateName("Pop", "Anca") == 1);
	assert(ValidTxt("") == 0);
	assert(ValidTxt("\0") == 0);
	assert(ValidTxt("P0p") == 0);
	assert(ValidTxt("A9a") == 0);
	assert(ValidTxt("") == 0);
	assert(ValidTxt("A A") == 0);
}

void test_valid_nota()
{
	assert(ValidNota(12) == 0);
	assert(ValidNota(10) == 1);
	assert(ValidNota(8) == 1);
	assert(ValidNota(0) == 1);
	assert(ValidNota(2) == 1);
	assert(ValidNota(-2) == 0);
}

void test_valid_txt() {
	assert(ValidTxt("                ") == 0);
	assert(ValidTxt("Pop") == 1);
	assert(ValidTxt("") == 0);
	assert(ValidTxt("\0") == 0);
	assert(ValidTxt("P0p") == 0);
	assert(ValidTxt("A9a") == 0);
	assert(ValidTxt("") == 0);
	assert(ValidTxt("A A") == 0);
}
