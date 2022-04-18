#pragma once
#include "Service.h"
#include "Repo.h"
#include "Valid.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

// Initializare concurs
service InitConcurs() {
	service s;
	s.concurs = ListCreate(DelElev);
	s.undo_concurs = ListCreate(Destroy);
	return s;
}
//add 
int ConcursAdd(service* s, char* nume, char* prenume) {

	if (ValidateName(nume, prenume)) {
		Elev* el = InitElev(nume, prenume);
		List* toUndo = copyList(s->concurs, copyElev);
		ListAdd(s->concurs, el);
		//add to undo_list
		ListAdd(s->undo_concurs, toUndo);
		return 1;
	}
	return 0;

}

//sort
void ConcursSortare(service* s, int tip, int mod) {
	if (tip == 1)
		ListSortNume(s->concurs, mod);
	else
		ListSortScor(s->concurs, mod);
}
void EleviSortare(service* s) {
	ListSort3Elem(s->concurs);
}

//search by full name
int ConcursFind(service* s, char* nume, char* prenume) {
	return ListFind(s->concurs, nume, prenume);

}
//delete
void ConcursDel(service* s, int ind) {
	List* toUndo = copyList(s->concurs, copyElev);
	ListDelElev(s->concurs, ind);
	//add to undo_list
	ListAdd(s->undo_concurs, toUndo);
}

//Lenght
int participants(service* s) {
	return(RepoLen(s->concurs));
}

//Update elev
int  UpdateElevNume(service* s, int ord, char* nume) {
	List* toUndo = copyList(s->concurs, copyElev);
	if (ValidTxt(nume)) {
		ListUpdateElevNume(s->concurs, ord, nume);
		//add to undo_list
		ListAdd(s->undo_concurs, toUndo);
		return 1;
	}
	return 0;
}
int UpdateElevPrenume(service* s, int ord, char* prenume) {
	List* toUndo = copyList(s->concurs, copyElev);
	if (ValidTxt(prenume)) {
		ListUpdateElevPrenume(s->concurs, ord, prenume);
		//add to undo_list
		ListAdd(s->undo_concurs, toUndo);
		return 1;
	}
	return 0;
}
int UpdateElevNota(service* s, int ord, int ind, int nota) {
	List* toUndo = copyList(s->concurs, copyElev);
	if (ValidNota(nota) == 1) {
		ListUpdateElevNota(s->concurs, ord, ind, nota);
		//add to undo_list
		ListAdd(s->undo_concurs, toUndo);
		return 1;
	}
	return 0;
}

//Incheiere concurs
void EndConcurs(service* s) {

	Destroy(s->concurs);
	Destroy(s->undo_concurs);
}

/*
  Restore previous list
  return 0 on ok, 1 if there is no more available undo
*/
int undo(service* s) {
	if (RepoLen(s->undo_concurs) == 0) {
		return 1;//no more undo
	}
	List* l = removeLast(s->undo_concurs);
	Destroy(s->concurs);
	s->concurs = l;
	return 0;
}


//Tests

void test_servCreate() {
	service s = InitConcurs();
	assert(participants(&s) == 0);
	EndConcurs(&s);
}
void test_servAdd() {
	service s = InitConcurs();
	ConcursAdd(&s, "Mihai", "Maria");
	ConcursAdd(&s, "Mihai2", "Maria1");
	ConcursAdd(&s, "1", "2");
	assert(participants(&s) == 1);
	EndConcurs(&s);
}
void test_servFind() {
	service s = InitConcurs();
	ConcursAdd(&s, "Onescu", "Maria");
	ConcursAdd(&s, "Two", "Maria");
	ConcursAdd(&s, "Tri", "Maria");
	ConcursAdd(&s, "Patru", "Maria");
	assert(ConcursFind(&s, "Patru", "Maria") == 3);
	assert(ConcursFind(&s, "Onescu", "Maria") == 0);
	assert(ConcursFind(&s, "Niciodatzescu", "Maria") == -1);
	EndConcurs(&s);
}
void test_servDell() {

	service s = InitConcurs();
	ConcursAdd(&s, "A", "A");
	ConcursAdd(&s, "B", "A");
	ConcursAdd(&s, "C", "A");
	assert(participants(&s) == 3);
	ConcursDel(&s, ConcursFind(&s, "A", "A"));
	assert(participants(&s) == 2);
	EndConcurs(&s);

}
void test_servAddmore() {
	service s = InitConcurs();
	ConcursAdd(&s, "1", "1");
	ConcursAdd(&s, "Mihai", "Maria");
	ConcursAdd(&s, "Mihai", "Mariana");
	ConcursAdd(&s, "Mihai", "Marieta");
	ConcursAdd(&s, "Mihai", "Mara6");
	ConcursAdd(&s, "Mihai", "Marina");
	ConcursAdd(&s, "Mihai", "Marianelita");
	ConcursAdd(&s, "Mihai", "Mara");
	assert(participants(&s) == 6);
	EndConcurs(&s);
}
void test_servUpdate() {

	service s = InitConcurs();
	ConcursAdd(&s, "Popa", "Ana");
	List* a = s.concurs;
	Elev* a1 = a->elems[0];
	assert(strcmp(a1->nume, "Popa") == 0);
	List* b = s.concurs;
	Elev* b1 = b->elems[0];
	assert(strcmp(b1->prenume, "Ana") == 0);

	UpdateElevNume(&s, 0, "Popesco");
	UpdateElevPrenume(&s, 0, "Ion");
	UpdateElevNota(&s, 0, 5, 10);
	UpdateElevNume(&s, 0, "Popesc0");
	UpdateElevPrenume(&s, 0, "I0n");
	UpdateElevNota(&s, 0, 5, 11);

	List* c = s.concurs;
	Elev* c1 = c->elems[0];
	assert(strcmp(c1->nume, "Popesco") == 0);
	List* d = s.concurs;
	Elev* d1 = d->elems[0];
	assert(strcmp(d1->prenume, "Ion") == 0);
	List* e = s.concurs;
	Elev* e1 = e->elems[0];
	assert(e1->scor[5] == 10);
	EndConcurs(&s);

}
void test_servSort() {
	service s = InitConcurs();
	ConcursAdd(&s, "a", "a");
	ConcursAdd(&s, "z", "a");
	ConcursAdd(&s, "c", "a");
	ConcursAdd(&s, "b", "a");
	ConcursSortare(&s, 1, 0);

	List* a = s.concurs;
	Elev* a1 = a->elems[0];
	assert(strcmp(a1->nume, "a") == 0);
	List* b = s.concurs;
	Elev* b1 = b->elems[1];
	assert(strcmp(b1->nume, "b") == 0);
	List* c = s.concurs;
	Elev* c1 = c->elems[2];
	assert(strcmp(c1->nume, "c") == 0);
	List* d = s.concurs;
	Elev* d1 = d->elems[3];
	assert(strcmp(d1->nume, "z") == 0);

	ConcursSortare(&s, 2, 0);
	ConcursAdd(&s, "h", "a");
	List* e = s.concurs;
	Elev* e1 = e->elems[0];
	assert(strcmp(e1->nume, "a") == 0);
	List* f = s.concurs;
	Elev* f1 = f->elems[1];
	assert(strcmp(f1->nume, "b") == 0);
	List* g = s.concurs;
	Elev* g1 = g->elems[2];
	assert(strcmp(g1->nume, "c") == 0);
	List* h = s.concurs;
	Elev* h1 = h->elems[3];
	assert(strcmp(h1->nume, "z") == 0);
	List* i = s.concurs;
	Elev* i1 = i->elems[4];
	assert(strcmp(i1->nume, "h") == 0);

	EndConcurs(&s);
}
void testUndo() {
	service s = InitConcurs();
	ConcursAdd(&s, "a", "a");
	ConcursAdd(&s, "z", "a");
	undo(&s);
	List* l = s.concurs;
	assert(l->lg == 1);
	assert(undo(&s) == 0);
	assert(undo(&s) != 0);
	assert(undo(&s) != 0);

	EndConcurs(&s);
}
