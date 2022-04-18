#pragma once
#include "Elevi.h"

typedef int(*FunctieComparare)(Elev* o1, Elev* o2);

typedef void* ElemType;
/*
  function type for copy an element
*/
typedef ElemType(*CopyFct) (ElemType);
/*
function type for realeasing an element
*/
typedef void(*DestroyFunction) (ElemType);


typedef struct {
	ElemType* elems;
	int lg;
	int cap; //capacity
	DestroyFunction dfnc;//used on destroy to release elements
} List;

/// <summary>
/// List creator
/// </summary>
/// <returns> the list</returns>
List* ListCreate(DestroyFunction f);

/// <summary>
/// Add to the list function
/// </summary>
/// <param name="l">The list</param>
/// <param name="el">The element to be added </param>
void ListAdd(List* l, ElemType el);

/// <summary>
/// Update name of the elev
/// </summary>
/// <param name="l">the list of elevi</param>
/// <param name="ord">int, the elev position in list</param>
/// <param name="nume">string, the new name</param>
void ListUpdateElevNume(List* l, int ord, char* nume);
/// <summary>
/// Update second name of the elev
/// </summary>
/// <param name="l">the list</param>
/// <param name="ord">int, the eleve position</param>
/// <param name="prenume">string, new second name</param>
void ListUpdateElevPrenume(List* l, int ord, char* prenume);
/// <summary>
/// Update grade
/// </summary>
/// <param name="l">the list</param>
/// <param name="ord">int, the eleve position</param>
/// <param name="prenume">string, the new grade</param>
void ListUpdateElevNota(List* l, int ord, int ind, int nota);

/// <summary>
/// Sort by name
/// </summary>
/// <param name="l">the list</param>
void ListSortNume(List* l, int reverse);
/// <summary>
/// sort by score
/// </summary>
/// <param name="l">the list</param>
void ListSortScor(List* l, int reverse);
void ListSort3Elem(List* l);

/// <summary>
/// Function that returns the lenght of the list
/// </summary>
/// <param name="l">the list</param>
/// <returns> |list| - lenght of the list </returns>
int RepoLen(List* l);

/// <summary>
/// The search function
/// </summary>
/// <param name="l">the list</param>
/// <param name="nume">string, name</param>
/// <param name="prenume">string, secund name</param>
/// <returns>the elev position in list </returns>
int ListFind(List* l, char* nume, char* prenume);

/// <summary>
/// Destructor of the list
/// </summary> 
/// <param name="l"></param>, function
void Destroy(List* l);

/// <summary>
/// Destructor of the list of elev
/// </summary> 
/// <param name="l"></param>
void DestroyListElev(List* l);

/// <summary>
/// Delete el from list
/// </summary>
/// <param name="l"></param>
/// <param name="i"></param>
void ListDelElev(List* l, int i);

/*
Remove last element from the list
!!!! do not destroy removed element
return the removed element
*/
ElemType removeLast(List* l);
/*
  Make a shallow copy of the list
  return Mylist containing the same elements as l
*/
List* copyList(List* l, CopyFct cf);


/// <summary>
/// TESTE
/// </summary>

void test_create_repo();
void test_find_repo();
void test_delete_from_repo();
void test_repo_add();
void test_add_more_repo();
void test_modify_repo();
void test_sort_nume_repo();
void test_sort_nume2_repo();
void test_sort_scor_repo();
void test_sort_scor2_repo();
//void testCopyList()