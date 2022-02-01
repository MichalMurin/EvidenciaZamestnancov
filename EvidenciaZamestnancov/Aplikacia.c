
#include <stdlib.h>
#include "CMemLeak.h"
#include "Aplikacia.h"

// funkcia ktora vytvori firmu so zadanym nazvom, prideli jej vytvorenu databazu a spusti cyklus s moznostami pokracovania
void SpustiAplikaciu()
{
    FIRMA firma;
    DATABAZA databaza;
    firma.jeFirmaUlozena = false;
    incializujDatabazu(&databaza);
    firma.databazaZamestnancov = &databaza;
    printf(" Zadaj nazov firmy: ");
    scanf("%[^\n]s", &firma.nazovFirmy);
    if (firma.nazovFirmy[0] == '\0')
    {
        printf("Zadali ste prazdny nazov firmy");
        SpustiAplikaciu();
        exit(0);
    }
    printf("\n ");

    int koniec = 1;
    while (koniec)
    {
        int volba = VypisMoznosti();

        switch (volba)
        {
        case 1: volba1(&firma);
            break;
        case 2: volba2(&firma);
            break;
        case 3: volba3(&firma);
            break;
        case 4: volba4(&firma);
            break;
        case 5: volba5(&firma);
            break;
        case 6: volba6(&firma);
            break;
        case 7: volba7(&firma);
            break;
        case 8: volba8(&firma);
            break;
        case 9: volba9(&firma);
            break;
        case 10: volba10(&firma);
            break;
        case 11:
            if (!firma.jeFirmaUlozena)
            {
                printf(" Zmeny v databaze firmy %s niesu ulozene, po ukonceni aplikacie budu neulozene data firmy %s zmazane \n", firma.nazovFirmy, firma.nazovFirmy);
                printf(" Ste si isty, ze chcete ukoncit aplikaciu?\n a = ano         n = nie \n ");
                getchar();
                char volba = '0';
                volba = getchar();

                switch (volba)
                {
                case 'a':
                    koniec = 0;
                    uvolniPamat(firma.databazaZamestnancov);
                    getchar();
                    break;
                case 'n':
                    printf(" Volba ukoncit aplikaciu bola zrusena\n");
                    break;
                default:
                    printf("Zadali ste nespravnu moznost");
                    break;
                }
            }
            else
            {
                printf(" Ste si isty, ze chcete ukoncit aplikaciu?\n a = ano         n = nie \n ");
                getchar();
                char volba = '0';

                volba = getchar();

                switch (volba)
                {
                case 'a':
                    koniec = 0;
                    uvolniPamat(firma.databazaZamestnancov);
                    getchar();
                    break;
                case 'n':
                    printf(" Volba ukoncit aplikaciu bola zrusena\n");
                    break;
                default:
                    printf("Zadali ste nespravnu moznost");
                    break;
                }
            }
            break;
        default:
            printf("Zadali ste nespravnu volbu");


        }

    }


}

// funkcia ktora usporiada databazu firmy zadanej parametrom

void volba1(FIRMA* firma) {
    if (firma->databazaZamestnancov->pocetZamestnancov < 2)
    {
        printf(" Databaza obsahuje malo zaznamov\n");
    }
    else
    {
        printf(" pre usporiadanie podla mena stlac 1\n pre usporiadanie podla priezviska stlac 2\n pre usporiadanie podla veku stlac 3\n");
        int volba = 0;
        scanf("%d", &volba);
        switch (volba)
        {
        case 1: usporiadajDatabazu(firma->databazaZamestnancov, MENO);
            break;
        case 2: usporiadajDatabazu(firma->databazaZamestnancov, PRIEZVISKO);
            break;
        case 3: usporiadajDatabazu(firma->databazaZamestnancov, VEK);
            break;
        default:
            printf("Zadali ste nespravnu volbu\n1");
            getchar();
            volba1(firma);
            break;
        }
        vypisDatabazuFirmy(firma);
    }

}
// funkcia ktora vypise databazu firmy zadanej parametrom
void volba2(FIRMA* firma) {
    vypisDatabazuFirmy(firma);
}
// funkcia ktora umozni pouzivatelovi vytvorit zamestnanca a pridat ho do databazy firmy zadanej parametrom
void volba3(FIRMA* firma) {
    ZAMESTNANEC zamestnanec;
    printf("Zadajte meno zamestnanca: ");
    if (scanf("%s", &zamestnanec.meno) != 1 || zamestnanec.meno[0] == '\0')
    {
        printf("Zadali ste nespravny udaj, zamestnanca sa nepodarilo pridat\n");
        return;
    }

    printf("\n");

    printf("Zadajte priezvisko zamestnanca: ");
    if (scanf("%s", &zamestnanec.priezvisko) != 1 || zamestnanec.meno[0] == '\0')
    {
        printf("Zadali ste nespravny udaj, zamestnanca sa nepodarilo pridat\n");
        return;
    }

    printf("\n");
    printf("Zadajte datum narodenia zamestnanca (v tvare den.mesiac.rok): ");
    if (scanf("%2d%*c%2d%*c%4d%", &zamestnanec.datumNar.den, &zamestnanec.datumNar.mesiac, &zamestnanec.datumNar.rok) > 3 || !jeDatumKorektny(&zamestnanec.datumNar))
    {
        getchar();
        printf("Zadali ste nespravny udaj, zamestnanca sa nepodarilo pridat\n");
        return;
    }
    printf("\n");
    getchar();
    printf("Zadajte bydlisko zamestnanca: ");
    if (gets(&zamestnanec.adresa.mesto) == NULL || zamestnanec.adresa.mesto[0] == '\0')
    {
        printf("Zadali ste nespravny udaj, zamestnanca sa nepodarilo pridat\n");
        return;
    }

    printf("\n");

    printf("Zadajte ulicu: ");
    if (gets(&zamestnanec.adresa.ulica) == NULL || zamestnanec.adresa.ulica[0] == '\0')
    {
        printf("Zadali ste nespravny udaj, zamestnanca sa nepodarilo pridat\n");
        return;
    }
    printf(" a Cislo domu: ");
    if (scanf("%d", &zamestnanec.adresa.CisloDomu) > 4 || zamestnanec.adresa.CisloDomu < 0)
    {
        printf("Zadali ste nespravny udaj, zamestnanca sa nepodarilo pridat\n");
        return;
    }
    printf("\n");
    getchar();
    printf("Zadajte psc bydliska: ");
    if (scanf("%[^\n]s", &zamestnanec.adresa.psc) > 6 || zamestnanec.adresa.psc[0] == '\0')
    {
        printf("Zadali ste nespravny udaj, zamestnanca sa nepodarilo pridat\n");
        return;
    }

    printf("\n");

    if (!jeAdresaKorektna(&zamestnanec.adresa))
    {
        printf("Zadali ste nespravny udaj, zamestnanca sa nepodarilo pridat\n");
        return;
    }

    printf("Stlacte cislo pre pracovne zaradenie zamestnanca\n (riaditel = 1 , manazer = 2 , veduci = 3 , skladnik =4 , sofer = 5 , pracovnik = 6 , uctovnik = 7 ):  ");
    int pozicia = 0;

    if (scanf("%d", &pozicia) != 1 || pozicia > POCET_POZICII + 1 || pozicia < 1) {
        printf("Zadali ste nespravny udaj, zamestnanca sa nepodarilo pridat\n");
        getchar();
        return;
    }

    zamestnanec.pozicia = pozicia;

    if (pridajZamestnanca(firma->databazaZamestnancov, &zamestnanec))
    {
        printf("Zamestnanca %s %s sa podarilo zapisat do databazy\n", zamestnanec.meno, zamestnanec.priezvisko);
        firma->jeFirmaUlozena = false;
    }



}
// funkcia ktora umozni na zaklade ID vymazat zamestnanca z databazy firmy zadanej parametrom
void volba4(FIRMA* firma) {
    if (firma->databazaZamestnancov->pocetZamestnancov == 0)
    {
        printf("Databaza firmy %s neobsahuje ziadne zaznamy", firma->nazovFirmy);
        return;
    }
    unsigned int id = 0;
    printf("Zadaj ID zamestnanca, ktory bude odstraneny z databazy: ");
    if (scanf("%d", &id) == 0)
    {
        printf("Zadali ste nespravny vstup\n");
        getchar();
        return;
    }

    printf("\n");
    if (nachadzaSaZamestnanecSIDvDatabaze(firma->databazaZamestnancov, id) == NULL)
    {
        printf("zamestnanec s ID %06d sa nenachadza v databaze\n", id);
    }

    else {

        if (odoberZamestnanca(id, firma->databazaZamestnancov))
        {
            printf("Podarilo sa ostranit zamestnanca s ID %06d\n", id);
            firma->jeFirmaUlozena = false;
        }
        else {
            printf("Nepodarilo sa odstranit zamestnanca s ID: %06d0\n", id);
        }
    }



}
// funkcia ktora umozni ulozit databazu firmy zadanej parametrom do textoveho suboru
void volba5(FIRMA* firma) {

    if (firma->databazaZamestnancov->pocetZamestnancov == 0)
    {
        printf(" Databaza je prazdna ");
        return;
    }

    char nazovSuboru[DLZKA_STRINGU];
    int volba = 0;
    printf("Zadajte nazov suboru kde sa ulozi databaza (napr: %s.txt): ", firma->nazovFirmy);
    scanf("%s", &nazovSuboru);
    int dlzkaStingu = strlen(nazovSuboru);
    if (dlzkaStingu < 5)
    {
        printf("Nazov suboru je prilis kratky, nazov suboru musi koncit priponou.txt");
        return;
    }
    if (nazovSuboru[dlzkaStingu] != 't' && nazovSuboru[dlzkaStingu - 1] != 't' && nazovSuboru[dlzkaStingu - 2] != 't' && nazovSuboru[dlzkaStingu - 3] != '.')
    {
        printf("Nazov suboru musi koncit priponou .txt");
        return;
    }

    if (strchr(nazovSuboru, '#') != NULL || strchr(nazovSuboru, '%') != NULL || strchr(nazovSuboru, '{') != NULL || strchr(nazovSuboru, '}') != NULL || strchr(nazovSuboru, '&') != NULL || strchr(nazovSuboru, '<') != NULL || strchr(nazovSuboru, '>') != NULL || strchr(nazovSuboru, '*') != NULL || strchr(nazovSuboru, '?') != NULL || strchr(nazovSuboru, '$') != NULL || strchr(nazovSuboru, '!') != NULL || strchr(nazovSuboru, ' " ') != NULL || strchr(nazovSuboru, '+') != NULL || strchr(nazovSuboru, '=') != NULL || strchr(nazovSuboru, '|') != NULL || strchr(nazovSuboru, '/') != NULL)
    {
        printf("Nazov suboru nemoze obsahovat znaky # % { } & < > ! + = | \ / ");
        return;
    }

    int pocetBodiek = 0;
    for (int i = 0; nazovSuboru[i] != '\0'; i++)
    {
        if ('.' == nazovSuboru[i])
        {
            pocetBodiek++;
        }
    }
    if (pocetBodiek > 1)
    {
        printf("Nazov suboru musi obsahovat iba jeden znak '.' ");
        return;
    }

    printf("Ak si prajete databazu usporiadat podla mena stlacte 1, podla priezviska stlacte 2, alebo podla veku sltacte 3 ");
    /*if (scanf("%d", &volba) != 1 || volba > 3 || volba < 0)
    {
        printf("Zadali ste nespravny udaj, nepodarilo sa ulozit databazu\n");
        return;
    }*/

    scanf("%d", &volba);

    switch (volba)
    {
    case 1: zapisUsporiadanuDatabazuFirmyDoSuboru(nazovSuboru, MENO, firma);
        firma->jeFirmaUlozena = true;
        break;
    case 2: zapisUsporiadanuDatabazuFirmyDoSuboru(nazovSuboru, PRIEZVISKO, firma);
        firma->jeFirmaUlozena = true;
        break;
    case 3: zapisUsporiadanuDatabazuFirmyDoSuboru(nazovSuboru, VEK, firma);
        firma->jeFirmaUlozena = true;
        break;
    default:
        printf("Zadali ste nespravnu volbu\n");
        getchar();
        volba5(firma);
        break;
    }

}
// funkcia ktora umozni nacitat databazu pre firmu zadanu parametrom z textoveho suboru
void volba6(FIRMA* firma) {
    char nazovSuboru[DLZKA_STRINGU];
    printf("Zadajte nazov suboru odkial sa nacitaju zamestnanci (napr: data.txt): ");
    scanf("%s", nazovSuboru);
    int dlzkaStingu = strlen(nazovSuboru);
    if (dlzkaStingu < 5)
    {
        printf("Nazov suboru je prilis kratky, nazov suboru musi koncit priponou.txt");
        return;
    }
    if (nazovSuboru[dlzkaStingu - 1] != 't' && nazovSuboru[dlzkaStingu - 2] != 'x' && nazovSuboru[dlzkaStingu - 3] != 't' && nazovSuboru[dlzkaStingu - 4] != '.')
    {
        printf("Nazov suboru musi koncit priponou .txt");
        return;
    }
    char nazovFirmy[VELKOST_STRING];
    precitajNazovFirmyZoSuboru(nazovSuboru, &nazovFirmy);
    //const char* nazovFirmy = precitajNazovFirmyZoSuboru(nazovSuboru);
    if (nazovFirmy[0] != '\0')
    {

        if (strcmp(&firma->nazovFirmy, &nazovFirmy) == 0)
        {
            nacitajDatabazuFirmyZoSuboru(nazovSuboru, firma);
            firma->jeFirmaUlozena = true;
        }
        else {
            printf(" Nazov firmy v subore sa nezhoduje s nazvom firmy zadanym v aplikacii, subor sa nepodarilo nacitat \n");
            return;
        }
    }
    else
    {
        printf("Zadany subor je chybny\n");
        return;
    }



}

// funkcia ktora umozni vymazat celu databazu firmy zadanej parametrom
void volba7(FIRMA* firma) {

    getchar();

    if (firma->databazaZamestnancov->pocetZamestnancov == 0) {
        printf("Databaza je uz prazdna");
        return;
    }

    printf(" Ste si isty, ze chcete vymazat databazu?\n a = ano         n = nie \n ");
    char volba = '0';

    volba = getchar();

    switch (volba)
    {
    case 'a':
        realloc(firma->databazaZamestnancov->zamestnanci, 0);
        firma->databazaZamestnancov->pocetZamestnancov = 0;
        printf("Databaza firmy %s bola vymazana", firma->nazovFirmy);
        firma->jeFirmaUlozena = false;
        return;
    case 'n':
        printf(" Volba zmazat bola zrusena\n");
        return;
    default:
        printf("Zadali ste nespravnu moznost");
        return;
    }


}
// funkcia ktora umozni zmenit nazov firmy zadanej parametrom
void volba8(FIRMA* firma) {
    printf("Aktualny nazov firmy je %s \n", firma->nazovFirmy);
    printf(" Zadajte novy nazov firmy: ");
    getchar();
    const char pom[VELKOST_STRING];
    scanf("%[^\n]s", &pom);
    if (pom[0] == '\0')
    {
        printf("Zadali ste prazdny nazov firm0y\n");
        return;
    }
    else
    {
        strcpy(firma->nazovFirmy, pom);
    }


}
// funkcia ktora umozni spustit aplikaciu nanovo a vytvorit dalsiu databazu pre novu firmu, funkcia kontroluje ci je databaza firmy zadanej parametrom ulozena
void volba9(FIRMA* firma)
{
    if (!firma->jeFirmaUlozena)
    {
        printf(" Zmeny v databaze firmy %s niesu ulozene, po vytvoreni novej firmy budu neulozene data firmy %s zmazane \n", firma->nazovFirmy, firma->nazovFirmy);
        printf(" Ste si isty, ze chcete vytvorit novu firmu?\n a = ano         n = nie \n ");
        getchar();
        char volba = '0';

        volba = getchar();

        switch (volba)
        {
        case 'a':
            uvolniPamat(firma->databazaZamestnancov);
            getchar();
            SpustiAplikaciu();
            exit(0);
            return;
        case 'n':
            printf(" Volba vytvorit novu firmu bola zrusena\n");
            return;
        default:
            printf("Zadali ste nespravnu moznost");
            return;
        }
    }
    else
    {
        printf(" Ste si isty, ze chcete vytvorit novu firmu?\n a = ano         n = nie \n ");
        getchar();
        char volba = '0';

        volba = getchar();

        switch (volba)
        {
        case 'a':
            uvolniPamat(firma->databazaZamestnancov);
            getchar();
            SpustiAplikaciu();
            exit(0);
            return;
        case 'n':
            printf(" Volba vytvorit novu firmu bola zrusena\n");
            return;
        default:
            printf("Zadali ste nespravnu moznost");
            return;
        }
    }
}
// funkcia umozni vyhladat konkretneho zamestnanca na zaklade ID v databaye firmy zadanej parametrom
void volba10(FIRMA* firma)
{
    if (firma->databazaZamestnancov->pocetZamestnancov == 0)
    {
        printf("Databaza firmy %s neobsahuje ziadne zaznamy", firma->nazovFirmy);
        return;
    }
    unsigned int id = 0;
    printf("Zadaj ID zamestnanca, ktoreho chcete vyhladat: ");
    if (scanf("%d", &id) == 0)
    {
        printf("Zadali ste nespravny vstup\n");
        getchar();
        return;
    }

    printf("\n");
    if (nachadzaSaZamestnanecSIDvDatabaze(firma->databazaZamestnancov, id) == NULL)
    {
        printf("zamestnanec s ID %06d sa nenachadza v databaze\n", id);
    }

    else {

        vypisZamestnanca(nachadzaSaZamestnanecSIDvDatabaze(firma->databazaZamestnancov, id));
        return;
    }

}

// funkcie vypise moznosti ovladania aplikacie
int VypisMoznosti()
{
    int volba = 0;
    printf("\n\n pre usporiadanie zamestnancov stlac 1\n pre vypisanie databazy stlac 2\n pre pridanie zamestnanca stlac 3\n pre vymazanie zamestnanca z databazy stlac 4\n pre ulozenie databazy do suboru stlac 5\n pre nacitanie zamestnancov zo suboru stlac 6 \n pre vymazanie celej databazy stlac 7 \n pre zmenu nazvu firmy stlac 8 \n pre vytvorenie novej databazy stlac 9 \n pre vyhladanie konkretneho zamestnanca stlac 10 \n pre ukoncenie aplikacie stlac 11\n ");
    if (scanf("%d", &volba) == 0)
    {
        getchar();
        return 0;
    }
    return volba;
}

