#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *CHIFFRE_DICS[] =
    {
        "", "un ", "deux ", "trois ", "quatre ", "cinq ", "six ", "sept ",
        "huit ", "neuf ", "dix", "onze", "douze", "treize", "quatorze",
        "quinze", "seize", "dix-sept", "dix-huit", "dix-neuf"};
const char *DOUZAINES_DICS[] =
    {
        "", "", "vingt ", "trente ", "quarante ", "cinquante ",
        "soixante ", "soixante ", "quatre-vingts ", "quatre-vingts "};
const char *SEC_DICS[] =
    {
        "", "", "milles ", "million ", "billion ", "trillion ", "quadrillion ", "quintillion ", "sextillion ", "septillion ", "octillion ", "nonillion ", "decillion "};

char *saisirChaine();
char *unites(char uni);
char *centaines(char cen);
char *douzaines(char dou, char uni);
void troisChiffres(char **letter, char *number);
void add(char **destinationLetter, const char *sourceLetter);

int main()
{
    printf("\nDonner un nombre (3 chiffres) : ");
    char *n = saisirChaine();
    char *letter = NULL;
    int i = strlen(n) % 3;
    int zerosNeeded = (i == 0) ? 0 : (i == 1) ? 2
                                              : 1;
    char *number = (char *)malloc(zerosNeeded + 1 * sizeof(char));
    for (int j = 0; j < zerosNeeded; j++)
        number[j] = '0';
    number[zerosNeeded] = '\0';
    number = (char *)realloc(number, (strlen(n) + strlen(number) * sizeof(char)));
    strcat(number, n);
    for (int i = 0, j = strlen(number) / 3; i < strlen(number); i += 3, j--)
    {
        char *buff = (char *)malloc(3 * sizeof(char));
        sprintf(buff, "%c%c%c", number[i], number[i + 1], number[i + 2]);
        troisChiffres(&letter, buff);
        add(&letter, SEC_DICS[j]);
    }
    printf("%s", letter);
    getchar();
    return 0;
}

void troisChiffres(char **letter, char *number)
{
    add(letter, centaines(number[0]));
    add(letter, douzaines(number[1], number[2]));
}

char *centaines(char cen)
{
    if (cen == '0')
        return "";
    else if (cen == '1')
        return "cent ";
    char *res = unites(cen);
    res = (char *)realloc(res, (strlen(res) + 8) * sizeof(char));
    strcat(res, "cent ");
    return res;
}

char *douzaines(char dou, char uni)
{
    int number = (dou - '0') * 10 + (uni - '0');
    char *res = NULL;
    int douInt = dou - '0', uniInt = uni - '0';
    if (dou == '0')
        return unites(uni);
    else if (dou == '1')
        return strdup(CHIFFRE_DICS[number]);
    res = (char *)malloc((strlen(unites(uni)) + strlen(DOUZAINES_DICS[douInt]) + 1) * sizeof(char));
    strcpy(res, DOUZAINES_DICS[dou - '0']);
    strcat(res, (douInt == 7 || douInt == 9) ? CHIFFRE_DICS[uniInt + 10] : unites(uni));
    return res;
}

char *saisirChaine()
{
    unsigned int c, nbc = 0;
    char *str = NULL;
    while ((c = getchar()) != '\n')
    {
        str = (char *)realloc(str, (nbc + 1) * sizeof(char));
        str[nbc++] = c;
    }
    str = (char *)realloc(str, (nbc + 1) * sizeof(char));
    str[nbc] = '\0';
    return str;
}

char *unites(char uni)
{
    int number = uni - '0';
    return strdup(CHIFFRE_DICS[number]);
}

void add(char **destinationLetter, const char *sourceLetter)
{
    if (*destinationLetter == NULL)
    {
        *destinationLetter = strdup(sourceLetter);
    }
    else
    {
        *destinationLetter = (char *)realloc(*destinationLetter, (strlen(*destinationLetter) + strlen(sourceLetter) + 1) * sizeof(char));
        strcat(*destinationLetter, sourceLetter);
    }
}
