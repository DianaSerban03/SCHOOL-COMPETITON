#pragma once
#include "Repo.h"
#include "Elevi.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
List* ListCreate(DestroyFunction f) {
	List* l = (List*)malloc(sizeof(List));
	if (l != NULL) {
		l->lg = 0;
		l->cap = 3;
		l->elems = malloc(sizeof(ElemType) * l->cap);
		l->dfnc = f;
	}
	return l;
}

// expand the list
void CheckCap(List* l) {
	if (l->cap > l->lg)
		return;// there is spac

	//make space
	ElemType* newElem = calloc(2 * l->cap, sizeof(ElemType));
	if (newElem != NULL)
		for (int i = 0; i < l->lg; i++) {
			newElem[i] = l->elems[i];
		}
	free(l->elems);
	l->elems = newElem;
	l->cap = 2 * l->cap;
}

//add to list
void ListAdd(List* l, ElemType el) {
	CheckCap(l);
	l->elems[l->lg] = el;
	l->lg++;

}

//fnc for sorts

int cmpScorDescrescator(Elev* e1, Elev* e2) {
	return e1->total < e2->total;
}
int cmpScorCrescator(Elev* e1, Elev* e2) {
	return e1->total > e2->total;
}
int cmpNumeDescrescator(Elev* e1, Elev* e2) {

	if (strcmp(e1->nume, e2->nume) > 0)
		return 0;
	else if (strcmp(e1->nume, e2->nume) < 0)
		return 1;
	else {
		if (strcmp(e1->prenume, e2->prenume) == 0)
			return 0;
		else if (strcmp(e1->prenume, e2->prenume) > 0)
			return 0;
		else
			return 1;
	}
}
int cmpNumeCrescator(Elev* e1, Elev* e2) {

	if (strcmp(e1->nume, e2->nume) > 0)
		return 1;
	else if (strcmp(e1->nume, e2->nume) < 0)
		return 0;
	else {
		if (strcmp(e1->prenume, e2->prenume) == 0)
			return 0;
		else if (strcmp(e1->prenume, e2->prenume) > 0)
			return 1;
		else
			return 0;

	}


}

//sort
void SortFnc(List* l, FunctieComparare fn) {
	for (int i = 0; i < l->lg - 1; i++)
		for (int j = i + 1; j < l->lg; j++)
			if (fn(l->elems[i], l->elems[j])) {
				ElemType aux = l->elems[j];
				l->elems[j] = l->elems[i];
				l->elems[i] = aux;
			}
}
void ListSortNume(List* l, int reverse) {
	if (reverse == 1)
		SortFnc(l, cmpNumeDescrescator);
	else
		SortFnc(l, cmpNumeCrescator);
}
void ListSortScor(List* l, int reverse) {
	if (reverse == 1)
		SortFnc(l, cmpScorDescrescator);
	else
		SortFnc(l, cmpScorCrescator);
}
void ListSort3Elem(List* l) {
	SortFnc(l, cmpNumeCrescator);
	SortFnc(l, cmpScorCrescator);
}
//find in list
int ListFind(List* l, char* nume, char* prenume) {
	for (int i = 0; i < l->lg; i++)
	{
		Elev* a = l->elems[i];
		if (strcmp(a->nume, nume) == 0 && strcmp(a->prenume, prenume) == 0) {
			return i;
		}
	}
	return -1;
}

//update
void ListUpdateElevNume(List* l, int ord, char* nume) {
	SetNume(l->elems[ord], nume);

}
void ListUpdateElevPrenume(List* l, int ord, char* prenume) {
	SetPrenume(l->elems[ord], prenume);
}
void ListUpdateElevNota(List* l, int ord, int ind, int nota) {
	SetNota(l->elems[ord], ind, nota);

}

//Destroy list
void Destroy(List* l) {
	for (int i = 0; i < l->lg; i++) {
		l->dfnc(l->elems[i]);
	}
	free(l->elems);
	free(l);

}

//Destroy 1 elev
void ListDelElev(List* l, int i) {
	DelElev(l->elems[i]);
	for (int j = i; j < l->lg - 1; j++) {
		l->elems[j] = l->elems[j + 1];

	}
	l->elems[l->lg - 1] = NULL;
	l->lg--;
}


//Lenght of the list
int RepoLen(List* l) {
	return l->lg;
}

/*
Remove last element from the list
!!!! do not destroy removed element
return the removed element
*/
ElemType removeLast(List* l) {
	ElemType rez = l->elems[l->lg - 1];
	l->lg -= 1;
	return rez;
}
/*
Make a shallow copy of the list
return Mylist containing the same elements as l
*/
List* copyList(List* l, CopyFct cf) {
	List* rez = ListCreate(l->dfnc);
	for (int i = 0; i < RepoLen(l); i++) {
		ElemType p = l->elems[i];
		ListAdd(rez, cf(p));
	}
	return rez;
}



void test_create_repo() {
	List* l = ListCreate(DelElev);
	assert(RepoLen(l) == 0);
	Destroy(l);
}
void test_find_repo() {
	List* l = ListCreate(DelElev);
	Elev* a = InitElev("Pop", "Ana");
	Elev* b = InitElev("Papa", "Ionana");
	Elev* c = InitElev("Pbpa", "Ionana");
	Elev* d = InitElev("Pcpa", "Ionana");
	ListAdd(l, a);
	ListAdd(l, c);
	ListAdd(l, d);
	ListAdd(l, b);
	assert(RepoLen(l) == 4);
	assert(ListFind(l, "Pcpa", "Ionana") == 2);
	assert(ListFind(l, "Pop", "Ana") == 0);
	assert(ListFind(l, "Papa", "Ionana") == 3);
	assert(ListFind(l, "never ", "nix") == -1);
	Destroy(l);
}
void test_delete_from_repo() {
	List* l = ListCreate(DelElev);
	Elev* a = InitElev("a", "Anabanana");
	Elev* b = InitElev("b", "Ionana");
	Elev* c = InitElev("c", "Ionana");
	Elev* d = InitElev("d", "Ionana");
	ListAdd(l, a);
	ListAdd(l, b);
	ListAdd(l, c);
	ListAdd(l, d);
	assert(RepoLen(l) == 4);
	ListDelElev(l, 2);
	ListDelElev(l, ListFind(l, "d", "Ionana"));
	assert(RepoLen(l) == 2);
	Destroy(l);
}
void test_repo_add() {
	List* l = ListCreate(DelElev);
	Elev* a = InitElev("Pop", "Ana");
	Elev* c = InitElev("Popa", "Ionana");
	ListAdd(l, a);
	ListAdd(l, c);
	assert(RepoLen(l) == 2);
	Destroy(l);
}
void test_add_more_repo() {
	List* l = ListCreate(DelElev);
	Elev* a = InitElev("Pop", "Ana");
	Elev* b = InitElev("Papa", "Ionana");
	Elev* c = InitElev("Pbpa", "Ionana");
	Elev* d = InitElev("Pcpa", "Ionana");
	ListAdd(l, a);
	ListAdd(l, b);
	ListAdd(l, c);
	ListAdd(l, d);
	assert(RepoLen(l) == 4);
	Destroy(l);

}
void test_modify_repo() {
	List* l = ListCreate(DelElev);
	Elev* e = InitElev("Pop", "Ana");
	ListAdd(l, e);
	assert(strcmp(e->nume, "Pop") == 0);
	assert(strcmp(e->prenume, "Ana") == 0);

	ListUpdateElevNume(l, 0, "Popesco");
	ListUpdateElevPrenume(l, 0, "Ion");
	ListUpdateElevNota(l, 0, 5, 10);
	Elev* a = l->elems[0];
	assert(strcmp(a->nume, "Popesco") == 0);
	assert(strcmp(a->prenume, "Ion") == 0);
	assert(a->scor[5] == 10);

	Destroy(l);

}
void test_sort_nume_repo() {
	List* l = ListCreate(DelElev);

	Elev* a = InitElev("a", "Bna");
	Elev* e = InitElev("e", "Ana");
	Elev* b = InitElev("b", "Ionana");
	Elev* g = InitElev("b", "Ionana");
	Elev* u = InitElev("c", "Zonana");
	Elev* c = InitElev("c", "Ionana");
	Elev* y = InitElev("d", "bca");
	Elev* d = InitElev("d", "cab");
	Elev* x = InitElev("d", "bac");

	ListAdd(l, d);
	ListAdd(l, b);
	ListAdd(l, u);
	ListAdd(l, g);
	ListAdd(l, a);
	ListAdd(l, c);
	ListAdd(l, e);
	ListAdd(l, x);
	ListAdd(l, y);
	ListSortNume(l, 0);

	Elev* a1 = l->elems[0];
	assert(strcmp(a1->nume, "a") == 0);

	Elev* b1 = l->elems[1];
	assert(strcmp(b1->nume, "b") == 0);

	Elev* c1 = l->elems[2];
	assert(strcmp(c1->nume, "b") == 0);

	Elev* d1 = l->elems[3];
	assert(strcmp(d1->nume, "c") == 0);

	Elev* e1 = l->elems[4];
	assert(e1->prenume[0] == 'Z');

	Elev* f1 = l->elems[4];
	assert(strcmp(f1->nume, "c") == 0);

	Elev* g1 = l->elems[4];
	assert(g1->prenume[0] == 'Z');

	Elev* h1 = l->elems[5];
	assert(strcmp(h1->nume, "d") == 0);

	Elev* m1 = l->elems[6];
	assert(strcmp(m1->nume, "d") == 0);

	Elev* j1 = l->elems[7];
	assert(strcmp(j1->nume, "d") == 0);

	Elev* k1 = l->elems[8];
	assert(strcmp(k1->nume, "e") == 0);

	Destroy(l);
}
void test_sort_nume2_repo() {

	List* l = ListCreate(DelElev);

	Elev* a = InitElev("a", "Bna");
	Elev* e = InitElev("e", "Ana");
	Elev* b = InitElev("b", "Ionana");
	Elev* g = InitElev("b", "Ionana");
	Elev* u = InitElev("c", "Zonana");
	Elev* c = InitElev("c", "Ionana");
	Elev* y = InitElev("d", "bca");
	Elev* d = InitElev("d", "cab");
	Elev* x = InitElev("d", "bac");

	ListAdd(l, d);
	ListAdd(l, b);
	ListAdd(l, u);
	ListAdd(l, g);
	ListAdd(l, a);
	ListAdd(l, c);
	ListAdd(l, e);
	ListAdd(l, x);
	ListAdd(l, y);
	ListSortNume(l, 1);
	Elev* a1 = l->elems[0];
	assert(strcmp(a1->nume, "e") == 0);
	Elev* b1 = l->elems[1];
	assert(strcmp(b1->nume, "d") == 0);
	Elev* c1 = l->elems[2];
	assert(strcmp(c1->nume, "d") == 0);
	Elev* d1 = l->elems[3];
	assert(strcmp(d1->nume, "d") == 0);
	Elev* e1 = l->elems[4];
	assert(strcmp(e1->nume, "b"));
	Elev* h1 = l->elems[5];
	assert(strcmp(h1->nume, "c") == 0);
	Elev* i1 = l->elems[6];
	assert(strcmp(i1->nume, "b") == 0);
	Elev* j1 = l->elems[7];
	assert(strcmp(j1->nume, "b") == 0);
	Elev* k1 = l->elems[8];
	assert(strcmp(k1->nume, "a") == 0);
	//Elev* m1 = l->elems[3];
	//assert(strcmp(m1->prenume[0], "I") == 0);
	//Elev* n1 = l->elems[4];
	//assert(strcmp(n1->prenume[0], "Z") == 0);

	Destroy(l);
}
void test_sort_scor_repo() {

	List* l = ListCreate(DelElev);
	Elev* a = InitElev("a", "Bna");
	Elev* e = InitElev("e", "Ana");
	Elev* b = InitElev("b", "Ionana");
	Elev* c = InitElev("c", "Ionana");
	SetNota(a, 0, 10);
	SetNota(e, 0, 1);
	SetNota(b, 0, 7);
	SetNota(c, 0, 6);
	ListAdd(l, b);
	ListAdd(l, a);
	ListAdd(l, c);
	ListAdd(l, e);
	ListSortScor(l, 0);
	Elev* a1 = l->elems[0];
	assert(strcmp(a1->nume, "e") == 0);
	Elev* b1 = l->elems[1];
	assert(strcmp(b1->nume, "c") == 0);
	Elev* c1 = l->elems[2];
	assert(strcmp(c1->nume, "b") == 0);
	Elev* d1 = l->elems[3];
	assert(strcmp(d1->nume, "a") == 0);
	Destroy(l);
}
void test_sort_scor2_repo() {

	List* l = ListCreate(DelElev);
	Elev* a = InitElev("a", "Bna");
	Elev* e = InitElev("e", "Ana");
	Elev* b = InitElev("b", "Ionana");
	Elev* c = InitElev("c", "Ionana");
	SetNota(a, 0, 10);
	SetNota(e, 0, 1);
	SetNota(b, 0, 7);
	SetNota(c, 0, 6);
	ListAdd(l, b);
	ListAdd(l, a);
	ListAdd(l, c);
	ListAdd(l, e);
	ListSortScor(l, 1);
	Elev* d = l->elems[0];
	assert(strcmp(d->nume, "a") == 0);
	Elev* f = l->elems[0];
	assert(strcmp(f->nume, "a") == 0);
	Elev* g = l->elems[1];
	assert(strcmp(g->nume, "b") == 0);
	Elev* h = l->elems[2];
	assert(strcmp(h->nume, "c") == 0);
	Elev* i = l->elems[3];
	assert(strcmp(i->nume, "e") == 0);

	Destroy(l);
}
/*void testCopyList() {
	List* l = ListCreate();
	Elev* a = InitElev("Pop", "Ana");
	Elev* c = InitElev("Popa", "Ionana");
	ListAdd(l, a);
	ListAdd(l, c);
	List* l2 = copyList(l);
	assert(RepoLen(l2) == 2);
	Elev* p = l2->elems[0];
	assert(strcmp(p->nume, "Pop") == 0);
	Destroy(l);
	Destroy(l2);
}*/
