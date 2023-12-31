#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *CHIFFRE_DICS[] =
    {
        "", "un ", "deux ", "trois ", "quatre ", "cinq ", "six ", "sept ", "huit ", "neuf ", "dix ", "onze ", "douze ", "treize ", "quatorze ", "quinze ", "seize ", "dix-sept ", "dix-huit ", "dix-neuf "};
const char *DOUZAINES_DICS[] =
    {
        "", "", "vingt ", "trente ", "quarante ", "cinquante ", "soixante ", "soixante ", "quatre-vingts ", "quatre-vingts "};
const char *SEC_DICS[] =
    {
        "", "milles ", "million ", "milliard ", "billion ", "billiard ", "trillion ", "trilliard ", "quatrillion ", "quatrilliard ", "quintillion ", "quintilliard ", "sextillion ", "sextilliard ", "Septillion ", "septilliard "};
char *saisirChaine();
char *unites(char uni);
char *centaines(char cen);
int hasOnlyZeros(const char *str);
char *douzaines(char dou, char uni);
void convert(char **letter, char *number);
void convertIntegerSection(char **letter, char *n);
void convertRealSection(char **letter, char *n);
void add(char **destinationLetter, const char *sourceLetter);

int main()
{
    while (1)
    {
        printf("\nDonner un nombre : ");
        char *n = saisirChaine();
        char *letter = NULL;
        convert(&letter, n);
        printf("%s", letter);
    }
    getchar();
    return 0;
}

void convert(char **letter, char *number)
{
    char *nE = NULL;
    char *token = strtok(number, ".");
    nE = strdup(token);
    if (hasOnlyZeros(nE))
        add(letter, "zero ");
    else
        convertIntegerSection(letter, nE);
    token = strtok(NULL, ".");
    if (token != NULL)
    {
        char *nR = strdup(token);
        add(letter, "virgule ");
        if (hasOnlyZeros(nR))
            add(letter, "zero ");
        else
            convertRealSection(letter, nR);
    }
}

void convertRealSection(char **letter, char *n)
{
    while (*n == '0')
    {
        add(letter, "zero ");
        n++;
    }
    convertIntegerSection(letter, n);
}

void convertIntegerSection(char **letter, char *n)
{
    int i = strlen(n) % 3;
    int zerosNeeded = (i == 0) ? 0 : (i == 1) ? 2
                                              : 1;
    char *number = (char *)malloc(zerosNeeded + 1 * sizeof(char));
    for (int j = 0; j < zerosNeeded; j++)
        number[j] = '0';
    number[zerosNeeded] = '\0';
    add(&number, n);
    for (int i = 0, j = (strlen(number) / 3) - 1; i < strlen(number); i += 3, j--)
    {
        char *buff = (char *)malloc(3 * sizeof(char));
        sprintf(buff, "%c%c%c", number[i], number[i + 1], number[i + 2]);
        add(letter, centaines(buff[0]));
        add(letter, douzaines(buff[1], buff[2]));
        if (strcmp(buff, "000"))
            add(letter, SEC_DICS[j]);
    }
}

char *centaines(char cen)
{
    if (cen == '0')
        return "";
    else if (cen == '1')
        return "cent ";
    char *res = unites(cen);
    add(&res, "cent ");
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
    add(&res, DOUZAINES_DICS[dou - '0']);
    add(&res, (douInt == 7 || douInt == 9) ? CHIFFRE_DICS[uniInt + 10] : unites(uni));
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
        *destinationLetter = strdup(sourceLetter);
    else
    {
        *destinationLetter = (char *)realloc(*destinationLetter, (strlen(*destinationLetter) + strlen(sourceLetter) + 1) * sizeof(char));
        strcat(*destinationLetter, sourceLetter);
    }
}

int hasOnlyZeros(const char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
        if (str[i] != '0')
            return 0;
    return 1;
}