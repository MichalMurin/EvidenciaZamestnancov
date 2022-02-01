#pragma once
#include <stdlib.h>
#include "Zamestnanec.h"
//enum moznych typov usporiadania databazy
typedef enum TypUsporiadania {
    MENO, PRIEZVISKO, VEK
}TYP;

// struktura evidencia zamestnancov
typedef struct evidencia {
    ZAMESTNANEC* zamestnanci;
    unsigned int pocetZamestnancov;
}DATABAZA;


bool pridajZamestnanca(DATABAZA* databaza, ZAMESTNANEC* zamestnanec);
ZAMESTNANEC* nachadzaSaZamestnanecSIDvDatabaze(DATABAZA* databaza, unsigned int ID);
bool odoberZamestnanca(unsigned int ID, DATABAZA* databaza);
void usporiadajDatabazu(DATABAZA* databaza, TYP typ); 
ZAMESTNANEC* vratZamestnancaZDatabazy(DATABAZA* databaza, ZAMESTNANEC* zamestnanec);
void incializujDatabazu(DATABAZA* databaza);
void uvolniPamat(DATABAZA* databaza);