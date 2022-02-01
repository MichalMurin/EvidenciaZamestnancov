#include <stdlib.h>
#include "CMemLeak.h"
#include "Adresa.h"


// funkcia ktora vypise adresu zadanu parametrom
void vypisAdresu(const ADRESA* adresa)
{
    printf(" %s %d \n %s \n %s\n", adresa->ulica, adresa->CisloDomu, adresa->mesto, adresa->psc);
}
// funkcia ktora porovna parametre dvoch adries zadanych parametrami a vrati vysedok porovnania typu bool
bool jeAdresaRovnaka(const ADRESA* adresa1, const ADRESA* adresa2)
{
    if (adresa1->CisloDomu != adresa2->CisloDomu)
    {
        return false;
    }

    if (strcmp(adresa1->psc, adresa2->psc) != 0)
    {
        return false;
    }

    if (strcmp(adresa1->ulica,adresa2->ulica)!=0)
    {
        return false;
    }

    if (strcmp(adresa1->mesto, adresa2->mesto)!= 0)
    {
        return false;
    }

    return true;
}
// funkcia ktora skontroluje atributy adresy zadanej parametrom a zhodnoti spravnost udajov, vysledok vrati typom bool.
bool jeAdresaKorektna(ADRESA* adresa) {
    if (adresa)
    {
        return adresa->CisloDomu > 0 && adresa->psc[0] != '\0' && adresa->mesto[0] != '\0' && adresa->ulica[0] != '\0' ? true : false;
    }
    
}






