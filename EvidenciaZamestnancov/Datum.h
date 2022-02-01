#pragma once
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
//struktura datum
typedef struct datum {
    unsigned char den;
    unsigned char mesiac;
    int rok;
}DATUM;

bool jeDatumRovnaky(const DATUM* datum1, const DATUM* datum2);
int porovnajDatumy(const DATUM* datum1, const DATUM* datum2);
void vypisDatum(const DATUM* datum);
bool jeDatumKorektny(DATUM* datum);