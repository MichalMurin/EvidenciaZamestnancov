#include <stdlib.h>
#include "CMemLeak.h"
#include "Datum.h"
// funkcia porovna dva datumy zadane parametrom, ak su rovnake vracia true
bool jeDatumRovnaky(const DATUM* datum1, const DATUM* datum2) {
    if (datum1->rok != datum2->rok) {
        return false;
    }
    if (datum1->mesiac != datum2->mesiac) {
        return false;
    }
    return datum1->den == datum2->den;

}
// funkcia porovna dva datumy zadane parametrom, ak je prvy datum vacsi vrati 1, ak su rovnake vrati 0 a ako je prvy datum mensi vrati -1
int porovnajDatumy(const DATUM* datum1, const DATUM* datum2) {
    if (datum1->rok < datum2->rok
        || (datum1->rok == datum2->rok && datum1->mesiac < datum2->mesiac)
        || (datum1->rok == datum2->rok && datum1->mesiac == datum2->mesiac && datum1->den < datum2->den)) {
        return -1;
    }
    if (jeDatumRovnaky(datum1, datum2)) {
        return 0;
    }
    return 1;
}

// funkcia vypise datum 
void vypisDatum(const DATUM* datum) {
    printf(" %d.%d.%d\n", datum->den, datum->mesiac, datum->rok);
}
// funkcia skontroluje ci je datum korektny, vysledok vrati typom bool
bool jeDatumKorektny(DATUM* datum) {
    if (datum)
    {
        time_t seconds = time(NULL);
        struct tm* current_time = localtime(&seconds);
        int rok = (current_time->tm_year + 1900);
        if (datum->den > 0 && datum->den<32 && datum->mesiac>0 && datum->mesiac <13 && datum->rok <= rok)
        {
            return true;
        }
        return false;
    }
    return false;
}