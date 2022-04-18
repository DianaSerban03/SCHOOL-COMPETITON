#pragma once
/*
Created by Zoltan
11.03.22
*/

typedef struct {
	char* nume;
	char* prenume;
	int* scor;
	int total;
} Elev;

/// <summary>
/// Creates a Dynamic elev
/// </summary>
/// <param name="nume">char pointer, 
/// <param prename = "nume">char pointer,
/// </param>
/// <returns></returns>
Elev* InitElev(char* nume, char* prenume);

/// <summary>
/// Validation of the txt 
/// </summary>
/// <param name="nume">A name, string</param>
/// <param name="prenume">A second name, string</param>
/// <returns></returns>
int ValidateName(char* nume, char* prenume);

/// <summary>
/// Validate a input txt
/// </summary>
/// <param name="txt">String, text validator for update</param>
/// <returns></returns>
int ValidTxt(char* txt);

/// <summary>
/// Destructor of elev
/// </summary>
/// <param name="e">Pointer to elev</param>
void DelElev(Elev* e);

/// <summary>
/// Setters
/// </summary>
/// <param name="e"> pointer to elev</param>
/// <param name="nume">string to set as a new name</param>
void SetNume(Elev* e, char* nume);

/// <summary>
/// Setters
/// </summary>
/// <param name="e"> pointer to elev</param>
/// <param prename="prenume">string to set as a new secund name</param>
void SetPrenume(Elev* e, char* prenume);

/// <summary>
/// Setters
/// </summary>
/// <param name="e"> pointer to elev</param>
/// <param name="nota">Integer nota to set as a score on a problem</param>
void SetNota(Elev* e, int ind, int nota);

Elev* copyElev(Elev* e);

/// <summary>
/// Tests
/// </summary>

void test_init_elev();
void test_sets_elev();
//void test_copyElev()
