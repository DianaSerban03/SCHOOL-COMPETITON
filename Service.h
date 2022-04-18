#pragma once
#include "Repo.h"
typedef struct {
	List* concurs;
	List* undo_concurs;
}service;

/// <summary>
/// Contest creator
/// </summary>
/// <returns>the contest</returns>
service InitConcurs();

/// <summary>
/// Add to the contest
/// </summary>
/// <param name="s"> the contest </param>
/// <param name="name">string, name of elev</param>
/// <param name="prenume">string, second name of elev</param>
/// <returns>true if added, no if not</returns>
int ConcursAdd(service* s, char* nume, char* prenume);

/// <summary>
/// Find by name and second name
/// </summary>
/// <param name="s">the contest</param>
/// <param name="nume">string, the name</param>
/// <param name="prenume">string, the second name</param>
/// <returns>the position of elev in contest (order) </returns>
int ConcursFind(service* s, char* nume, char* prenume);
/// <summary>
/// Delete elev from concurs
/// </summary>
/// <param name="s">the contest</param>
/// <param name="ind">int, the position</param>
void ConcursDel(service* s, int ind);

/// <summary>
/// Search
/// </summary>
/// <param name="s">the contest</param>
/// <param name="tip">int, switch for mod name or scor</param>
/// <param name="mod">mod of sort cresc/desc</param>
void ConcursSortare(service* s, int tip, int mod);
void EleviSortare(service* s);

/// <summary>
/// Update name 
/// </summary>
/// <param name="s">the contest</param>
/// <param name="ord">int, position of the elev</param>
/// <param name="nume">string, new name</param>
/// <returns>true if updated, no in other cases</returns>
int UpdateElevNume(service* s, int ord, char* nume);

/// <summary>
/// Update second name
/// </summary>
/// <param name="s"></param>
/// <param name="ord">the position</param>
/// <param name="prenume">the new second name</param>
/// <returns>true if updated, no in other cases</returns>
int UpdateElevPrenume(service* s, int ord, char* prenume);

/// <summary>
/// Update nota
/// </summary>
/// <param name="s">the contest</param>
/// <param name="ord">the order</param>
/// <param name="ind">the position</param>
/// <param name="nota">the new grade</param>
/// <returns>true if updated, no in other cases</returns>
int UpdateElevNota(service* s, int ord, int ind, int nota);

/// <summary>
/// Return the nr. of participants
/// </summary>
/// <param name="s"></param>
/// <returns> nr. of participants</returns>
int participants(service* s);


/// <summary>
/// Destructor
/// </summary>
/// <param name="s"> the contest</param>
void EndConcurs(service* s);

///Restore previous pet list
///return 0 on ok, 1 if there is no more available undo
int undo(service* s);

//Test

void test_servCreate();
void test_servAdd();
void test_servAddmore();
void test_servFind();
void test_servUpdate();
void test_servDell();
void test_servSort();
void testUndo();
