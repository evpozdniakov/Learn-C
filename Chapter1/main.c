#include <stdio.h>

#define STR_MAXLEN 2000
#define TAB_SIZE 8
#define IN_WHITE 0
#define IN_WORD 1
#define IN_CODE 0
#define IN_COMMENT 1

void detab(char s[]);
void entab(char s[]);
int strLen(char s[]);
void copyStr(char target[], char source[]);
void reverseStr(char s[]);
void foldLine(char line[], int maxLen);
void removeComments(char text[]);

int test()
{
    char s[100] = "123456789";

    printf("%s\n", s);
    reverseStr(s);
    printf("%s\n", s);
    
    return 0;
}

int main()
{
    // char s[STR_MAXLEN] = "Psittacus /* avis */ Indiae avis est; instar illi minimo minus quam columbarum, sed color non columbarum; non enim lacteus ille vel lividus vel utrumque, subluteus aut sparsus est, sed color psittaco viridis et intimis plumulis et extimis palmulis, nisi quod sola cervice distinguitur. Enimvero cervicula eius circulo mineo velut aurea torqui pari fulgoris circumactu cingitur et coronatur. Rostri prima duritia: cum in petram quampiam concitus altissimo volatu praecipitat, rostro se velut ancora excipit. Sed et capitis eadem duritia quae rostri. Cum sermonem nostrum cogitur aemulari, ferrea clavicula caput tunditur, imperium magistri ut persentiscat; haec discenti ferula est. Discit autem statim pullus usque ad duos aetatis suae annos, dum facile os, uti conformetur, dum tenera lingua, uti convibretur: senex autem captus et indocilis est et obliviosus. Verum ad disciplinam humani sermonis facilior est psittacus glande qui vescitur et cuius in pedibus ut hominis quini digituli numerantur. Non enim omnibus psittacis id insigne, sed illud omnibus proprium, quod eis lingua latior quam ceteris avibus; eo facilius verba hominis articulant patentiore plectro et palato. Id vero, quod didicit, ita similiter nobis canit vel potius eloquitur, ut, vocem si audias, hominem putes: nam corvum quidem si audias, +idem conate non loqui[. Verum enimvero et corvus et psittacus nihil aliud quam quod didicerunt pronuntiant. Si convicia docueris, conviciabitur diebus ac noctibus perstrepens maledictis: hoc illi carmen est, hanc putat cantionem. Vbi omnia quae didicit maledicta percensuit, denuo repetit eandem cantilenam. Si carere convicio velis, lingua excidenda est aut quam primum in silvas suas remittendus est.";
    char s[STR_MAXLEN] = "#include <stdio.h>\n\n/* copy input to output; 2nd version */\n\nmain()\n{\n\tint c;\n\twhile ((c = getchar()) != EOF)\n\t\tputchar(c);\n}";

    removeComments(s);

    printf("\n\n%s\n\n", s);

    return 0;
}

void detab(char s[])
{
    int i = 0;
    int j = 0;
    int k;
    char c;
    char s2[STR_MAXLEN];

    for (i = 0; (c = s[i]) != '\0'; i++)
    {
        if (c != '\t')
        {
            s2[j] = c;
            j++;
        }
        else
        {
            for (k = j; j < (TAB_SIZE - k % TAB_SIZE + k); j++)
                s2[j] = '-';
        }
    }

    s2[j] = '\0';

    copyStr(s, s2);
}

int strLen(char s[])
{
    int i = 0;

    while (s[i] != '\0')
        i++;

    return i;
}

void entab(char s[])
{
    int i, j;
    char s2[STR_MAXLEN];
    char c;

    detab(s);

    int slen = strLen(s);
    int k = 0;

    for (i = slen / TAB_SIZE; i > 0; i--)
        for (j = 0; j < TAB_SIZE; j++)
        {
            c = s[TAB_SIZE * i - j - 1];

            if (c != ' ')
                s2[k++] = c;
            else if (j == 0)
                s2[k++] = '\t';
            else if (s2[k - 1] != '-')
                s2[k++] = c;
        }

    reverseStr(s2);

    while (j < slen)
    {
        s2[k++] = s[j++];
    }
}

void copyStr(char target[], char source[])
{
    int i = 0;

    while ((source[i] = target[i]) != '\0')
        i++;
}

void reverseStr(char s[])
{
    char c;
    int i;
    int slen = strLen(s);

    for (i = 0; i < (slen / 2); i++)
    {
        c = s[i];
        s[i] = s[slen - i - 1];
        s[slen - i - 1] = c;
    }

    s[slen] = '\0';
}

void foldLine(char line[], int maxLen)
{
    detab(line);

    int len = strLen(line);

    int i = 0;
    int lastSpaceIndex;
    int mode = IN_WORD;
    int currentLineLen = 0;
    char c;

    while ((c = line[i]) != '\0')
    {
        if (c == '\t' || c == ' ')
        {
            if (mode == IN_WORD) {
                mode = IN_WHITE;
                lastSpaceIndex = i;
            }
        }
        else
            mode = IN_WORD;

        if (currentLineLen == maxLen)
        {
            line[lastSpaceIndex] = '\n';
            currentLineLen = i - lastSpaceIndex;
            lastSpaceIndex = 0;
        }

        i++;
        currentLineLen++;
    }
}

void removeComments(char text[])
{
    int writePos = 0;
    int readPos = 0;
    int mode = IN_CODE;
    char c;

    do
    {
        c = text[readPos];

        if (mode == IN_CODE && c == '*' && readPos > 0 && text[readPos - 1] == '/')
        {
            mode = IN_COMMENT;
            writePos--;
            readPos++;
            continue;
        }
        
        if (mode == IN_COMMENT && c == '/' && readPos > 0 && text[readPos - 1] == '*')
        {
            mode = IN_CODE;
            readPos++;
            continue;
        }

        if (mode == IN_CODE)
        {
            if (writePos != readPos)
                text[writePos] = c;

            writePos++;
        }

        readPos++;
    } while (c != '\0');
}
