#pragma once
#include "Elevi.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

//Init Elev
Elev* InitElev(char* nume, char* prenume) {
	Elev* e = (Elev*)malloc(sizeof(Elev));
	if (e == NULL)
		return NULL;
	e->nume = (char*)malloc(sizeof(char) * strlen(nume) + 1);
	if (e->nume != NULL)
		strcpy_s(e->nume, strlen(nume) + 1, nume);

	e->prenume = (char*)malloc(sizeof(char) * strlen(prenume) + 1);
	if (e->prenume != NULL)
		strcpy_s(e->prenume, strlen(prenume) + 1, prenume);

	e->scor = (int*)malloc(10 * sizeof(int));
	if (e->scor != NULL)
		for (int i = 0; i < 10; i++)
			e->scor[i] = 0;
	e->total = 0;
	return e;
}

/*
  Create a copy for the pet
  Deep copy - copy all the sub-parts
*/
Elev* copyElev(Elev* e) {
	return InitElev(e->nume, e->prenume);
}

//setters
void SetNume(Elev* e, char* nume) {
	free(e->nume);
	e->nume = (char*)malloc(sizeof(char) * strlen(nume) + 1);
	if (e->nume != NULL)
		strcpy_s(e->nume, strlen(nume) + 1, nume);

}
void SetPrenume(Elev* e, char* prenume) {
	free(e->prenume);
	e->prenume = (char*)malloc(sizeof(char) * strlen(prenume) + 1);
	if (e->prenume != NULL)
		strcpy_s(e->prenume, strlen(prenume) + 1, prenume);
}
void SetNota(Elev* e, int  ind, int nota) {
	if (e->scor[ind] == 0) {
		e->scor[ind] = nota;
		e->total += e->scor[ind];
	}
	else {
		e->total -= e->scor[ind];
		e->scor[ind] = nota;
		e->total += e->scor[ind];

	}
}
void DelElev(Elev* e)
{
	free(e->nume);
	free(e->prenume);
	free(e->scor);
	free(e);
}

//Tests
void test_init_elev() {
	Elev* e = InitElev("Pop", "Ana");
	assert(strcmp(e->nume, "Pop") == 0);
	assert(strcmp(e->prenume, "Ana") == 0);
	for (int i = 0; i < 10; i++)
		assert(e->scor[i] == 0);
	DelElev(e);
}

void test_sets_elev() {
	Elev* e = InitElev("Pop", "Ana");
	assert(strcmp(e->nume, "Pop") == 0);
	assert(strcmp(e->prenume, "Ana") == 0);
	for (int i = 0; i < 10; i++) {
		assert(e->scor[i] == 0);
	}
	SetNume(e, "Popesco");
	SetPrenume(e, "Ion");
	for (int i = 0; i < 10; i++) {
		SetNota(e, i, i + 1);
		SetNota(e, i, i);
	}
	assert(strcmp(e->nume, "Popesco") == 0);
	assert(strcmp(e->prenume, "Ion") == 0);
	for (int i = 0; i < 10; i++) {
		assert(e->scor[i] == i);
		assert(e->total == 45);
	}
	DelElev(e);
}

