#include <stdlib.h>
#include "CMemLeak.h"
#include "Databaza.h"
// funkcia nastavi pocet zamestnancov v databaze zadanej parametrom na 0
void incializujDatabazu(DATABAZA* databaza)
{
	databaza->pocetZamestnancov = 0;
}
// funkcia skoontroluje ci je alokovana pamat pre databazu zadanu parametrom, ak ano, dealokuje ju
void uvolniPamat(DATABAZA* databaza)
{
	if (databaza->pocetZamestnancov > 0) {
		realloc(databaza->zamestnanci, 0);
	}
}
// funkcia usporiada databazu zadanu parametrom podla typu usporiadania zadaneho parametrom, fukncia používa funkciu qsort kde sa zadáva smerník na porovnávacie funkcie v súbore Zamestnanec.c
void usporiadajDatabazu(DATABAZA* databaza, TYP typ)
{
	if (databaza->pocetZamestnancov > 0)
	{
		if (typ == MENO)
		{
			qsort(databaza->zamestnanci, databaza->pocetZamestnancov, sizeof(ZAMESTNANEC), porovnajMeno);
			printf( "Databaza bola usporiadana podla Mena\n");
		}
		if (typ == PRIEZVISKO)
		{
			qsort(databaza->zamestnanci, databaza->pocetZamestnancov, sizeof(ZAMESTNANEC), porovnajPriezvisko);
			printf(" Databaza bola usporiadana podla Priezviska\n");
		}
		if (typ == VEK)
		{
			qsort(databaza->zamestnanci, databaza->pocetZamestnancov, sizeof(ZAMESTNANEC), porovnajVek);
			printf(" Databaza bola usporiadana podla Veku\n");
		}
	}
	
	
}
// funkcia prehlada databazu zadanu parametrom a ak najde zamestnanca yadaneho parametrom vrati smernik na tohto zamestnanca, ak nie vrati NULL
ZAMESTNANEC* vratZamestnancaZDatabazy(DATABAZA* databaza, ZAMESTNANEC* zamestnanec)
{
	if (databaza && zamestnanec)
	{
		if (databaza->pocetZamestnancov>0)
		{
			for (unsigned int i = 0; i < databaza->pocetZamestnancov; i++)
			{
				if (jeZamestnanecRovnaky(&databaza->zamestnanci[i],zamestnanec) )
				{
					return zamestnanec;
				}
			}
		}
		return NULL;
	}
	return NULL;
}
// funkcia prehlada databazu zadanu parametrom a vrati zamestnanca so zadanym ID, ak tam taky nieje, vrati NULL
ZAMESTNANEC* nachadzaSaZamestnanecSIDvDatabaze(DATABAZA* databaza, unsigned int ID)
{
	if (databaza)
	{
		for (unsigned int i = 0; i < databaza->pocetZamestnancov; i++)
		{
			if (databaza->zamestnanci[i].ID == ID)
			{
				return &databaza->zamestnanci[i];
			}
			
		}
		return NULL;
	}
	return NULL;
}


// funkcia sa pokusi pridat zamestnanca zadaneho parametrom do databazy zadanej parametrom, pri uspechu vracia true
// pri vytvarani prideli zamestnancovi jedinecne ID
bool pridajZamestnanca(DATABAZA* databaza, ZAMESTNANEC* zamestnanec)
{
	if (databaza && zamestnanec) {
		if (databaza->pocetZamestnancov == 0)
		{
			vytvorID(zamestnanec);
			databaza->zamestnanci = calloc(1, sizeof(ZAMESTNANEC));
			databaza->zamestnanci[0] = *zamestnanec;
			databaza->pocetZamestnancov++;
			return true;
		}
		if (databaza->pocetZamestnancov > 0)
		{
			
			

			if (vratZamestnancaZDatabazy(databaza,zamestnanec) == NULL)
			{
				
				do
				{
					vytvorID(zamestnanec);
				} while (nachadzaSaZamestnanecSIDvDatabaze(databaza,zamestnanec->ID) != NULL);

				int pocet = databaza->pocetZamestnancov;

				databaza->zamestnanci = realloc(databaza->zamestnanci, (pocet + 1) * sizeof(ZAMESTNANEC));
				databaza->zamestnanci[pocet] = *zamestnanec;
				databaza->pocetZamestnancov++;
				return true;
			}
			

		}
	}
	return false;
}

// funkcia sa pokusi vymazat z databazy zadanej parametrom zamestnanca s ID zadanym parametrom, pri uspechu vracia true
bool odoberZamestnanca(unsigned int ID, DATABAZA* databaza)
{
	ZAMESTNANEC* pom = nachadzaSaZamestnanecSIDvDatabaze(databaza, ID);
	if (pom != NULL)
	{
		int index = 0;
		for (unsigned int i = 0; i < databaza->pocetZamestnancov; i++)
		{
			if (jeZamestnanecRovnaky(nachadzaSaZamestnanecSIDvDatabaze(databaza,ID), &databaza->zamestnanci[i]))
			{
				index = i;
			}
		}
		for (unsigned int i = index; i < databaza->pocetZamestnancov - 1; i++)
		{
			databaza->zamestnanci[i] = databaza->zamestnanci[i + 1];
		}
		databaza->zamestnanci = realloc(databaza->zamestnanci, (databaza->pocetZamestnancov - 1) * sizeof(ZAMESTNANEC));
		databaza->pocetZamestnancov--;
		
		return true;
	}
	return false;
}
