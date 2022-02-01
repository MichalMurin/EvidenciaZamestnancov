#pragma once
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define VELKOST_STRING 30
#define VELKOST_PSC 7
// struktura adresa
typedef struct adresa {
    char ulica[VELKOST_STRING];
    unsigned int CisloDomu;
    char mesto[VELKOST_STRING];
    char psc[VELKOST_PSC];
}ADRESA;
void vypisAdresu(const ADRESA * adresa);
bool jeAdresaRovnaka(const ADRESA* adresa1, const ADRESA* adresa2);
bool jeAdresaKorektna(ADRESA* adresa);