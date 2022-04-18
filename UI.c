#pragma once
#include "Service.h"
#include "Ui.h"
#include <stdio.h>
#include <stdlib.h>

int ignored_dumb_var = 0;
void PrintMeniu() {
	printf("\tMENIU\n#1~ Adaugare elev\n#2~ Modificare\n#3~ Stergere\n#4~ Afisare filtru (Care incep cu o litera anume!)\n#5~ Sort nume/scor\n#9~ Print ALL\n#10~ UNDO\n#11~ Sortare dupa NUME, PRENUME si SCOR \n#0~ Inchidere\n");
}

void ReadCommand(int* command) {

	PrintMeniu();
	printf("\nENTER COMMAND: ");
	ignored_dumb_var = scanf_s("%d", command);
}

void Run() {

	int command = 1;
	service concurs = InitConcurs();
	printf("HELLO!!!\n");
	printf("%s", "----------------------------------------------------------------------------------\n");

	while (command) {
		ReadCommand(&command);
		switch (command) {
		case 1: {
			char nume[50];
			char prenume[50];
			printf("~IntreSgistrare~\nNume: ");
			ignored_dumb_var = scanf_s("%s", nume, 50);
			printf("Prenume: ");
			ignored_dumb_var = scanf_s("%s", prenume, 50);

			if (ConcursAdd(&concurs, nume, prenume)) {
				printf("\nElevul %s %s s-a intregistrat la consurs\n", nume, prenume);
			}
			else
				printf("\nElevul NU s-a intregistrat\n");

			printf("%s", "----------------------------------------------------------------------------------\n");
			break;
		}
		case 2: {
			char nume[50];
			char prenume[50];
			int nota, ind;
			printf("~Modificare~\nElevul:\nNume: ");
			ignored_dumb_var = scanf_s("%s", nume, 50);
			printf("Prenume: ");
			ignored_dumb_var = scanf_s("%s", prenume, 50);
			int ord = ConcursFind(&concurs, nume, prenume);
			if (ord != -1) {
				printf("Adaugati modificari asupra ( Tastati '-' pentru a nu modifica):\nNume: ");
				ignored_dumb_var = scanf_s("%s", nume, 50);
				printf("Prenume: ");
				ignored_dumb_var = scanf_s("%s", prenume, 50);
				printf("Adauga/Modificati nota (-1 pentru a omite): ");
				ignored_dumb_var = scanf_s("%d", &ind);

				if (nume[0] != '-') {
					if (UpdateElevNume(&concurs, ord, nume) == 1)
					{
						List* a = concurs.concurs;
						Elev* a1 = a->elems[ord];
						printf("Numele elevului %s s-a schimbat in %s.\n", a1->nume, nume);
					}
					else
					{
						List* a = concurs.concurs;
						Elev* a1 = a->elems[ord];
						printf("Numele elevului %s  NU s-a schimbat.\n", a1->nume);
					}
				}
				else
				{
					List* a = concurs.concurs;
					Elev* a1 = a->elems[ord];
					printf("Numele elevului %s PASTRAT.\n", a1->nume);
				}

				if (prenume[0] != '-') {
					if (UpdateElevPrenume(&concurs, ord, nume) == 1)
					{
						List* a = concurs.concurs;
						Elev* a1 = a->elems[ord];
						printf("Prenumele elevului %s s-a schimbat in %s.\n", a1->nume, nume);
					}
					else
					{
						List* a = concurs.concurs;
						Elev* a1 = a->elems[ord];
						printf("Prenumele elevului %s  NU s-a schimbat.\n", a1->nume);
					}
				}
				else
				{
					List* a = concurs.concurs;
					Elev* a1 = a->elems[ord];
					printf("Prenumele elevului %s PASTRAT.\n", a1->nume);
				}

				if (ind != -1) {
					List* a = concurs.concurs;
					Elev* a1 = a->elems[ord];
					int c = a1->scor[ind];
					printf("Nota nou: ");
					scanf_s("%d", &nota);


					if (UpdateElevNota(&concurs, ord, ind, nota))
						if (c != 0)
						{
							List* b = concurs.concurs;
							Elev* b1 = b->elems[ord];
							printf("Nota %d s-a modificat in %d.\n", c, b1->scor[ind]);
						}
						else
							printf("Nota %d s-a adaugat.\n", nota);
					else
						printf("Nota introdusa este invalida.\n");

				}
				else
					printf("Nu s-a modificat situatia notelor.\n");
			}
			printf("%s", "----------------------------------------------------------------------------------\n");

			break;
		}

		case 3: {
			char nume[50];
			char prenume[50];
			printf("~Stergeree~\nNume: ");
			ignored_dumb_var = scanf_s("%s", nume, 50);
			printf("Prenume: ");
			ignored_dumb_var = scanf_s("%s", prenume, 50);

			int ind = ConcursFind(&concurs, nume, prenume);

			if (ind != -1) {
				ConcursDel(&concurs, ind);
				printf("\nElevul %s %s s-a eliminat la consurs\n", nume, prenume);
			}
			else
				printf("\nNU este o intregistrar cu numele introdus\n");
			printf("%s", "----------------------------------------------------------------------------------\n");
			break;
		}

		case 4: {
			char c;
			int ok = 0;
			printf("~Afisare filtrata\nDati litera de filtru( prima din nume):");
			ignored_dumb_var = scanf_s(" %c", &c, 1);
			printf("\n\tConcurenti:\n");

			for (int i = 0; i < concurs.concurs->lg; i++)
			{
				List* a = concurs.concurs;
				Elev* a1 = a->elems[i];
				if (a1->nume[0] == c) {
					printf("%d %s %s Problema|scor:", i, a1->nume, a1->prenume);
					for (int j = 0; j < 10; j++)
						printf("%d|%d ", j + 1, a1->scor[j]);
					ok = 1;
					printf("\n");
				}
			}
			if (ok == 0)
				printf("Nu avem concurenti a caror nume incepe cu %c\n", c);
			printf("%s", "----------------------------------------------------------------------------------\n");
			break;
		}
		case 5: {
			int tip, mod;
			printf("#1 Nume\n#2 Scor\nAlege:");
			scanf_s("%d", &tip);
			printf("#0 Crescator\n#1 Descrescator\nAlege:");
			scanf_s("%d", &mod);
			ConcursSortare(&concurs, tip, mod);

		}
		case 9: {
			int ok = 0;
			printf("\n\tCONCURENTI\n");
			List* a = concurs.concurs;
			//Elev* a1 = a->lg;
			for (int i = 0; i < a->lg; i++) {
				List* b = concurs.concurs;
				Elev* b1 = b->elems[i];
				printf("%d %s %s Problema|scor:", i, b1->nume, b1->prenume);
				for (int j = 0; j < 10; j++)
					printf("%d|%d ", j + 1, b1->scor[j]);
				ok = 1;
				printf("\n");
			}
			if (ok == 0)
				printf("Nu avem concurenti.\n");
			printf("%s", "----------------------------------------------------------------------------------\n");
			break;
		}
		case 10: {
			if (undo(&concurs) != 0) {
				printf("No more undo!!!\n");
			}
			break;
		}
		case 11: {
			//apelam functia de sortare
			EleviSortare(&concurs);
			break;
		}
		default:
			break;
		}
	}
	EndConcurs(&concurs);
}