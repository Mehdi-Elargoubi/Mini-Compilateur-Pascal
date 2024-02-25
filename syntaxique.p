#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Définition des tailles de tableaux
#define TABLEINDEX 100
#define TAILLEMEM 100
#define TAILLECODE 100

// Définition des mnémoniques pour les instructions
typedef enum
{
    ADD,
    SUB,
    MUL,
    DIV,
    EQL,
    NEQ,
    GTR,
    LSS,
    GEQ,
    LEQ,
    PRN,
    INN,
    INT,
    LDI,
    LDA,
    LDV,
    STO,
    BRN,
    BZE,
    HLT,
    NUM_TOKEN,
    EOF_TOKEN
} MNEMONIQUES;

// Définition des types d'erreurs possibles
typedef enum
{
    INT_ERR,
    HLT_ERR,
    INST_ERR,
    NUM_TOKEN_ERR
} MNEMONIQUES_ERR;

// Fonction pour obtenir une chaîne de caractères correspondant à un code d'erreur
const char *get_error_string(MNEMONIQUES_ERR error_code)
{
    switch (error_code)
    {
    case INT_ERR:
        return "Error: INT is missing in the beginning of the program";
    case HLT_ERR:
        return "Error: HLT is missing in the program";
    case INST_ERR:
        return "Error: Invalid instruction";
    case NUM_TOKEN_ERR:
        return "Error: Invalid number";
    default:
        return "Error: Unknown error";
    }
}

// Structure représentant un symbole courant
typedef struct
{
    MNEMONIQUES CODE;
    char NOM[20];
    int val;
} TSym_Cour;

// Variables globales
TSym_Cour head;
TSym_Cour SYM_COUR;
FILE *fichier;
char Car_Cour; // Caractère actuel
int IND_DER_SYM_ACC = 0; // Index dans TABLESYM
int OFFSET = -1;
int MEM[TAILLEMEM]; // Mémoire (Pile de la machine)
int SP; // Pointeur vers le sommet du pile

// Structure représentant une instruction P-code
typedef struct
{
    MNEMONIQUES MNE;
    int SUITE;
} INSTRUCTION;

// Variables globales
int LABEL_BRN;
int INDICE_BZE;
int IND_BZE;
int PC = 0; // Compteur d'instructions
int opRELOP = 0;
int opMULOP = 0;
int opADDOP = 0;
int opLoop = 0;

// Déclaration des fonctions
void INTER_INST(INSTRUCTION INST);
void Lire_Car();
void Erreur(MNEMONIQUES_ERR code);
void Test_Symbole(MNEMONIQUES cl, MNEMONIQUES_ERR COD_ERR);
void PCODE();
void INST_PCODE();
void lire_mot();
void lire_nombre();
void Sym_Suiv();

// Fonction pour interpréter une instruction P-code
void INTER_INST(INSTRUCTION INST)
{
    int val1, adr, val2;
    switch (INST.MNE)
    {
    case INT:
        OFFSET = SP = INST.SUITE;
        PC++;
        break;
    case LDI:
        MEM[++SP] = INST.SUITE;
        PC++;
        break;
    case LDA:
        MEM[++SP] = INST.SUITE;
        PC++;
        break;
    case STO:
        val1 = MEM[SP--];
        adr = MEM[SP--];
        MEM[adr] = val1;
        PC++;
        break;
    case LDV:
        adr = MEM[SP--];
        MEM[++SP] = MEM[adr];
        PC++;
        break;
    case EQL:
        val1 = MEM[SP--];
        val2 = MEM[SP--];
        MEM[++SP] = (val1 == val2);
        PC++;
        break;
    case LEQ:
        val2 = MEM[SP--];
        val1 = MEM[SP--];
        MEM[++SP] = (val1 <= val2);
        PC++;
        break;
    case GEQ:
        val2 = MEM[SP--];
        val1 = MEM[SP--];
        MEM[++SP] = (val1 >= val2);
        PC++;
        break;
    case LSS:
        val2 = MEM[SP--];
        val1 = MEM[SP--];
        MEM[++SP] = (val1 < val2);
        PC++;
        break;
    case GTR:
        val2 = MEM[SP--];
        val1 = MEM[SP--];
        MEM[++SP] = (val1 > val2);
        PC++;
        break;
    case NEQ:
        val2 = MEM[SP--];
        val1 = MEM[SP--];
        MEM[++SP] = (val1 != val2);
        PC++;
        break;
    case INN:
        scanf("%d", MEM[SP--]);
        PC++;
        break;
    case BZE:
        if (MEM[SP--] == 0)
            PC = INST.SUITE;
        else
            PC++;
        break;
    case BRN:
        PC = INST.SUITE;
        break;
    case HLT:
        PC++;
        break;
    case ADD:
        val1 = MEM[SP--];
        val2 = MEM[SP--];
        MEM[++SP] = val1 + val2;
        PC++;
        break;
    case SUB:
        val1 = MEM[SP--];
        val2 = MEM[SP--];
        MEM[++SP] = val1 - val2;
        PC++;
        break;
    case MUL:   
        val1 = MEM[SP--];
        val2 = MEM[SP--];
        MEM[++SP] = val1 * val2;
        PC++;
        break;
    case DIV:
        val1 = MEM[SP--];
        val2 = MEM[SP--];
        MEM[++SP] = val1 / val2;
        PC++;
        break;
    case PRN:
        printf("%d\n", MEM[SP--]);
        PC++;
        break;
    } 
}

// Fonction principale pour interpréter le code P-code
void PCODE()
{
    Test_Symbole(INT, INT_ERR);
    Test_Symbole(NUM_TOKEN, NUM_TOKEN_ERR);
    INST_PCODE();
    Test_Symbole(HLT, HLT_ERR);
}

// Fonction pour interpréter les instructions P-code
void INST_PCODE()
{
    INSTRUCTION INST;
    while (SYM_COUR.CODE != HLT && SYM_COUR.CODE != EOF_TOKEN)
    {
        if (SYM_COUR.CODE == NUM_TOKEN && strcmp(SYM_COUR.NOM, "EOF") == 0)
        {
            Erreur(HLT_ERR); // Le fichier ne contient pas l'instruction HLT
            break;
        }
        switch (SYM_COUR.CODE)
        {
        case MUL:
            INST.MNE = MUL;
            INTER_INST(INST);
            Sym_Suiv();
            break;
        case DIV:
            INST.MNE = DIV;
            INTER_INST(INST);
            Sym_Suiv();
            break;
        case SUB:
            INST.MNE = SUB;
            INTER_INST(INST);
            Sym_Suiv();
            break;
        case ADD:
            INST.MNE = ADD;
            INTER_INST(INST);
            Sym_Suiv();
            break;
        case EQL:
            INST.MNE = EQL;
            INTER_INST(INST);
            Sym_Suiv();
            break;
        case NEQ:
            INST.MNE = NEQ;
            INTER_INST(INST);
            Sym_Suiv();
            break;
        case GTR:
            INST.MNE = GTR;
            INTER_INST(INST);
            Sym_Suiv();
            break;
        case LSS:
            INST.MNE = LSS;
            INTER_INST(INST);
            Sym_Suiv();
            break;
        case GEQ:
            INST.MNE = GEQ;
            INTER_INST(INST);
            Sym_Suiv();
            break;
        case LEQ:
            INST.MNE = LEQ;
            INTER_INST(INST);
            Sym_Suiv();
            break;
        case PRN:
            INST.MNE = PRN;
            INTER_INST(INST);
            Sym_Suiv();
            break;
        case INN:
            INST.MNE = INN;
            INTER_INST(INST);
            Sym_Suiv();
            break;
        case INT:
            Sym_Suiv();
            INST.MNE = INT;
            INST.SUITE = SYM_COUR.val;
            INTER_INST(INST);
            Test_Symbole(SYM_COUR.CODE, NUM_TOKEN);
            break;
        case LDI:
            Sym_Suiv();
            INST.MNE = LDI;
            INST.SUITE = SYM_COUR.val;
            INTER_INST(INST);
            Test_Symbole(SYM_COUR.CODE, NUM_TOKEN);
            break;
        case LDA:
            Sym_Suiv();
            INST.MNE = LDA;
            INST.SUITE = SYM_COUR.val;
            INTER_INST(INST);
            Test_Symbole(SYM_COUR.CODE, NUM_TOKEN);
            break;
        case LDV:
            INST.MNE = LDV;
            INTER_INST(INST);
            Sym_Suiv();
            break;
        case STO:
            INST.MNE = STO;
            INTER_INST(INST);
            Sym_Suiv();
            break;
        case BRN:
            Sym_Suiv();
            INST.MNE = BRN;
            INST.SUITE = SYM_COUR.val;
            INTER_INST(INST);
            Test_Symbole(SYM_COUR.CODE, NUM_TOKEN);
            break;
        case BZE:
            Sym_Suiv();
            INST.MNE = BZE;
            INST.SUITE = SYM_COUR.val;
            INTER_INST(INST);
            Test_Symbole(SYM_COUR.CODE, NUM_TOKEN);
            break;
        default:
            Erreur(INST_ERR);
        }
    }
}

// Fonction principale
int main()
{
    fichier = fopen("C:/Users/HP/Desktop/Mini-Compilateur-Pascal/test.p", "r");
    if (fichier == NULL)
    {
        perror("Erreur lors de l'ouverture du fichier!");
        return 1;
    }
    Lire_Car();
    Sym_Suiv();

    PCODE();

    printf("P-code parfait.\n");
    fclose(fichier);
    return 0;
}
// Définition des fonctions

// Fonction pour lire un mot du fichier source
void lire_mot()
{
    char mot[20]; // Tableau pour stocker le mot lu
    int indice = 0; // Indice pour parcourir le mot

    // Lecture du premier caractère (lettre)
    mot[indice++] = Car_Cour;
    Lire_Car(); // Lire le caractère suivant

    // Lecture des caractères suivants (lettres ou chiffres)
    while (isalpha(Car_Cour) || isdigit(Car_Cour))
    {
        mot[indice++] = Car_Cour;
        Lire_Car(); // Lire le caractère suivant
    }

    // Ajout du terminateur de chaîne
    mot[indice] = '\0';

    // Vérification si le mot est un mot-clé et assignation du code correspondant
    // Stockage du mot dans le token
    if (stricmp(mot, "add") == 0)
    {
        SYM_COUR.CODE = ADD;
    }
    else if (stricmp(mot, "sub") == 0)
    {
        SYM_COUR.CODE = SUB;
    }
    // ... (répéter pour chaque mot-clé)

    strcpy(SYM_COUR.NOM, mot);
}

// Fonction pour lire un nombre du fichier source
void lire_nombre()
{
    char nombre[11]; // Tableau pour stocker le nombre lu
    int indice = 0; // Indice pour parcourir le nombre

    // Lecture du premier chiffre
    nombre[indice++] = Car_Cour;
    Lire_Car(); // Lire le caractère suivant

    // Lecture des chiffres suivants
    while (isdigit(Car_Cour))
    {
        nombre[indice++] = Car_Cour;
        Lire_Car(); // Lire le caractère suivant
    }

    // Ajout du terminateur de chaîne
    nombre[indice] = '\0';

    // Stockage du nombre dans le token
    SYM_COUR.CODE = NUM_TOKEN;
    strcpy(SYM_COUR.NOM, nombre);
    SYM_COUR.val = atoi(SYM_COUR.NOM); // Conversion du nombre en entier
}

// Fonction pour passer au prochain symbole du fichier source
void Sym_Suiv()
{
    // Ignorer les espaces, les sauts de ligne et les tabulations
    while (Car_Cour == ' ' || Car_Cour == '\n' || Car_Cour == '\t')
    {
        Lire_Car();
    }

    // Identifier le type de symbole suivant et appeler la fonction correspondante
    if (isdigit(Car_Cour))
    {
        lire_nombre();
    }
    else if (isalpha(Car_Cour))
    {
        lire_mot();
    }
    else
    {
        switch (Car_Cour)
        {
        case EOF:
            SYM_COUR.CODE = EOF_TOKEN;
            break;
        default:
            SYM_COUR.CODE = INST_ERR;
            Lire_Car(); // Passer au caractère suivant
        }
    }
}

// Fonction pour lire le caractère suivant du fichier source
void Lire_Car()
{
    Car_Cour = fgetc(fichier);
}

// Fonction pour afficher les erreurs
void Erreur(MNEMONIQUES_ERR code)
{
    printf("%s\n", get_error_string(code));
    exit(EXIT_FAILURE);
}
// Définition des fonctions

// Fonction pour tester si le symbole courant correspond à celui attendu
void Test_Symbole(MNEMONIQUES cl, MNEMONIQUES_ERR COD_ERR)
{
    if (SYM_COUR.CODE == cl)
    {
        Sym_Suiv(); // Passer au symbole suivant
    }
    else
    {
        Erreur(COD_ERR); // Afficher une erreur si le symbole ne correspond pas à celui attendu
    }
}

// Fonction principale pour générer le P-code
void PCODE()
{
    Test_Symbole(INT, INT_ERR); // Vérifier si le programme commence par INT
    Test_Symbole(NUM_TOKEN, NUM_TOKEN_ERR); // Vérifier si un nombre est présent après INT
    INST_PCODE(); // Générer le P-code des instructions
    Test_Symbole(HLT, HLT_ERR); // Vérifier si le programme se termine par HLT
}

// Fonction pour générer le P-code des instructions
void INST_PCODE()
{
    INSTRUCTION INST; // Déclaration d'une instruction

    // Boucler jusqu'à ce que HLT soit rencontré ou que la fin du fichier soit atteinte
    while (SYM_COUR.CODE != HLT && SYM_COUR.CODE != EOF_TOKEN)
    {
        // Vérifier si le symbole est un nombre spécial indiquant la fin du fichier
        if (SYM_COUR.CODE == NUM_TOKEN && strcmp(SYM_COUR.NOM, "EOF") == 0)
        {
            Erreur(HLT_ERR); // Afficher une erreur si la dernière instruction n'est pas HLT
            break;
        }

        // Traitement de chaque type d'instruction
        switch (SYM_COUR.CODE)
        {
        case MUL:
        case DIV:
        case SUB:
        case ADD:
        case EQL:
        case NEQ:
        case GTR:
        case LSS:
        case GEQ:
        case LEQ:
        case PRN:
        case INN:
            // Instructions arithmétiques et logiques
            INST.MNE = SYM_COUR.CODE;
            INTER_INST(INST); // Appeler la fonction pour interpréter l'instruction
            Sym_Suiv(); // Passer au symbole suivant
            break;

        case INT:
        case LDI:
        case LDA:
        case STO:
        case LDV:
        case BRN:
        case BZE:
            // Instructions de manipulation de la mémoire et de contrôle de flux
            Sym_Suiv(); // Passer au symbole suivant
            INST.MNE = SYM_COUR.CODE;
            INST.SUITE = SYM_COUR.val;
            INTER_INST(INST); // Appeler la fonction pour interpréter l'instruction
            Test_Symbole(SYM_COUR.CODE, NUM_TOKEN); // Vérifier si un nombre suit l'instruction
            break;

        default:
            Erreur(INST_ERR); // Afficher une erreur pour les instructions non reconnues
        }
    }
}

// Fonction principale
int main()
{
    // Ouverture du fichier source
    fichier = fopen("C:/Users/HP/Desktop/Mini-Compilateur-Pascal/test.p", "r");
    if (fichier == NULL)
    {
        perror("Erreur lors de l'ouverture du fichier!");
        return 1;
    }

    // Lecture du premier caractère et initialisation du symbole courant
    Lire_Car();
    Sym_Suiv();

    // Génération du P-code
    PCODE();

    printf("P-code parfait.\n"); // Affichage si le P-code est généré avec succès
    fclose(fichier); // Fermeture du fichier source
    return 0;
}

_---------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TABLEINDEX 100
#define TAILLEMEM 100
#define TAILLECODE 100

typedef enum
{
    ADD,
    SUB,
    MUL,
    DIV,
    EQL,
    NEQ,
    GTR,
    LSS,
    GEQ,
    LEQ,
    PRN,
    INN,
    INT,
    LDI,
    LDA,
    LDV,
    STO,
    BRN,
    BZE,
    HLT,
    NUM_TOKEN,
    EOF_TOKEN
} MNEMONIQUES;

// Error types
typedef enum
{
    INT_ERR,
    HLT_ERR,
    INST_ERR,
    NUM_TOKEN_ERR
} MNEMONIQUES_ERR;

const char *get_error_string(MNEMONIQUES_ERR error_code)
{
    switch (error_code)
    {
    case INT_ERR:
        return "Error: INT is missing in the beginning of the program";
    case HLT_ERR:
        return "Error: HLT is missing in the program";
    case INST_ERR:
        return "Error: Invalid instruction";
    case NUM_TOKEN_ERR:
        return "Error: Invalid number";
    default:
        return "Error: Unknown error";
    }
}

typedef struct
{
    MNEMONIQUES CODE;
    char NOM[20];
    int val;
} TSym_Cour;

TSym_Cour head;
TSym_Cour SYM_COUR;

FILE *fichier;

char Car_Cour; // Current character

int IND_DER_SYM_ACC = 0; // Index dans TABLESYM
int OFFSET = -1;

int MEM[TAILLEMEM]; // M�moire (Pile de la machine)
int SP;             // Pointeur vers le sommet du pile

typedef struct
{
    MNEMONIQUES MNE; // Instru
    int SUITE;       // Son suivant
} INSTRUCTION;



int LABEL_BRN;
int INDICE_BZE;
int IND_BZE;

int PC = 0; // Compteur d'instructions

int opRELOP = 0;
int opMULOP = 0;
int opADDOP = 0;
int opLoop = 0;

// p code functions
void INTER_INST(INSTRUCTION INST);

// Function prototypes
void Lire_Car();
void Erreur(MNEMONIQUES_ERR code);
void Test_Symbole(MNEMONIQUES cl, MNEMONIQUES_ERR COD_ERR);
void PCODE();
void INST_PCODE();
void lire_mot();
void lire_nombre();
void Sym_Suiv();

void INTER_INST(INSTRUCTION INST)
{
    int val1, adr, val2;
    switch (INST.MNE)
    {
    case INT:
        OFFSET = SP = INST.SUITE;
        PC++;
        break;
    case LDI:
        MEM[++SP] = INST.SUITE;
        PC++;
        break;
    case LDA:
        MEM[++SP] = INST.SUITE;
        PC++;
        break;
    case STO:
        val1 = MEM[SP--];
        adr = MEM[SP--];
        MEM[adr] = val1;
        PC++;
        break;
    case LDV:
        adr = MEM[SP--];
        MEM[++SP] = MEM[adr];
        PC++;
        break;
    case EQL:
        val1 = MEM[SP--];
        val2 = MEM[SP--];
        MEM[++SP] = (val1 == val2);
        PC++;
        break;
    case LEQ:
        val2 = MEM[SP--];
        val1 = MEM[SP--];
        MEM[++SP] = (val1 <= val2);
        PC++;
        break;
    case GEQ:
        val2 = MEM[SP--];
        val1 = MEM[SP--];
        MEM[++SP] = (val1 >= val2);
        PC++;
        break;
    case LSS:
        val2 = MEM[SP--];
        val1 = MEM[SP--];
        MEM[++SP] = (val1 < val2);
        PC++;
        break;
    case GTR:
        val2 = MEM[SP--];
        val1 = MEM[SP--];
        MEM[++SP] = (val1 > val2);
        PC++;
        break;
    case NEQ:
        val2 = MEM[SP--];
        val1 = MEM[SP--];
        MEM[++SP] = (val1 != val2);
        PC++;
        break;
    case INN:
        scanf("%d", MEM[SP--]);
        PC++;
        break;
    case BZE:
        if (MEM[SP--] == 0)
            PC = INST.SUITE;
        else
            PC++;
        break;
    case BRN:
        PC = INST.SUITE;
        break;
    case HLT:
        PC++;
        break;
    case ADD:
        val1 = MEM[SP--];
        val2 = MEM[SP--];
        MEM[++SP] = val1 + val2;
        PC++;
        break;
    case SUB:
        val1 = MEM[SP--];
        val2 = MEM[SP--];
        MEM[++SP] = val1 - val2;
        PC++;
        break;
    case MUL:   
        val1 = MEM[SP--];
        val2 = MEM[SP--];
        MEM[++SP] = val1 * val2;
        PC++;
        break;
    case DIV:
        val1 = MEM[SP--];
        val2 = MEM[SP--];
        MEM[++SP] = val1 / val2;
        PC++;
        break;
    case PRN:
        printf("%d\n", MEM[SP--]);
        PC++;
        break;
    } 

    // printf("%d\n", INST.MNE);

    // for (int i = 0; i < SP; i++)
    // {
    //     printf("%d ", MEM[i]);
    // }
    
    // printf("\n\n");
}

// Function definitions
void lire_mot()
{
    char mot[20];
    int indice = 0;

    // Reading the first character (letter)
    mot[indice++] = Car_Cour;
    Lire_Car();

    // Reading the following characters (letters or digits)
    while (isalpha(Car_Cour) || isdigit(Car_Cour))
    {
        mot[indice++] = Car_Cour;
        Lire_Car();
    }

    // Adding the null terminator
    mot[indice] = '\0';

    // Checking if the word is a keyword
    if (stricmp(mot, "add") == 0)
    {
        SYM_COUR.CODE = ADD;
    }
    else if (stricmp(mot, "sub") == 0)
    {
        SYM_COUR.CODE = SUB;
    }
    else if (stricmp(mot, "mul") == 0)
    {
        SYM_COUR.CODE = MUL;
    }
    else if (stricmp(mot, "div") == 0)
    {
        SYM_COUR.CODE = DIV;
    }
    else if (stricmp(mot, "eql") == 0)
    {
        SYM_COUR.CODE = EQL;
    }
    else if (stricmp(mot, "neq") == 0)
    {
        SYM_COUR.CODE = NEQ;
    }
    else if (stricmp(mot, "gtr") == 0)
    {
        SYM_COUR.CODE = GTR;
    }
    else if (stricmp(mot, "lss") == 0)
    {
        SYM_COUR.CODE = LSS;
    }
    else if (stricmp(mot, "geq") == 0)
    {
        SYM_COUR.CODE = GEQ;
    }
    else if (stricmp(mot, "leq") == 0)
    {
        SYM_COUR.CODE = LEQ;
    }
    else if (stricmp(mot, "prn") == 0)
    {
        SYM_COUR.CODE = PRN;
    }
    else if (stricmp(mot, "inn") == 0)
    {
        SYM_COUR.CODE = INN;
    }
    else if (stricmp(mot, "int") == 0)
    {
        SYM_COUR.CODE = INT;
    }
    else if (stricmp(mot, "ldi") == 0)
    {
        SYM_COUR.CODE = LDI;
    }
    else if (stricmp(mot, "lda") == 0)
    {
        SYM_COUR.CODE = LDA;
    }
    else if (stricmp(mot, "ldv") == 0)
    {
        SYM_COUR.CODE = LDV;
    }
    else if (stricmp(mot, "sto") == 0)
    {
        SYM_COUR.CODE = STO;
    }
    else if (stricmp(mot, "brn") == 0)
    {
        SYM_COUR.CODE = BRN;
    }
    else if (stricmp(mot, "bze") == 0)
    {
        SYM_COUR.CODE = BZE;
    }
    else if (stricmp(mot, "hlt") == 0)
    {
        SYM_COUR.CODE = HLT;
    }

    // Storing the word in the token
    strcpy(SYM_COUR.NOM, mot);
}

void lire_nombre()
{
    char nombre[11];
    int indice = 0;

    // Reading the first digit
    nombre[indice++] = Car_Cour;
    Lire_Car();

    // Reading the following digits
    while (isdigit(Car_Cour))
    {
        nombre[indice++] = Car_Cour;
        Lire_Car();
    }

    // Adding the null terminator
    nombre[indice] = '\0';

    // Storing the number in the token
    SYM_COUR.CODE = NUM_TOKEN;
    strcpy(SYM_COUR.NOM, nombre);
    SYM_COUR.val = atoi(SYM_COUR.NOM);
}

void Sym_Suiv()
{
    while (Car_Cour == ' ' || Car_Cour == '\n' || Car_Cour == '\t')
    {
        Lire_Car();
    }
    if (isdigit(Car_Cour))
    {
        lire_nombre();
    }
    else if (isalpha(Car_Cour))
    {
        lire_mot();
    }
    else
    {
        switch (Car_Cour)
        {
        case EOF:
            SYM_COUR.CODE = EOF_TOKEN;
            break;

        default:
            SYM_COUR.CODE = INST_ERR;
            Lire_Car();
        }
    }
}

void Lire_Car()
{
    Car_Cour = fgetc(fichier);
}

void Erreur(MNEMONIQUES_ERR code)
{
    printf("%s\n", get_error_string(code));
    exit(EXIT_FAILURE);
}

void Test_Symbole(MNEMONIQUES cl, MNEMONIQUES_ERR COD_ERR)
{
    if (SYM_COUR.CODE == cl)
    {
        Sym_Suiv();
    }
    else
    {
        Erreur(COD_ERR);
    }
}

void PCODE()
{
    Test_Symbole(INT, INT_ERR);
    Test_Symbole(NUM_TOKEN, NUM_TOKEN_ERR);
    INST_PCODE();
    Test_Symbole(HLT, HLT_ERR);
}

void INST_PCODE()
{
    INSTRUCTION INST;
    while (SYM_COUR.CODE != HLT && SYM_COUR.CODE != EOF_TOKEN)

    {
        if (SYM_COUR.CODE == NUM_TOKEN && strcmp(SYM_COUR.NOM, "EOF") == 0)
        {
            Erreur(HLT_ERR); // File does not contain HLT instruction
            break;
        }
        switch (SYM_COUR.CODE)
        {


        case MUL:
            // Code for multiplication operations
           
            INST.MNE = MUL;
            INTER_INST(INST);
            Sym_Suiv();
            break;
        case DIV:
            // Code for  division operations

            INST.MNE = DIV;
            INTER_INST(INST);
            Sym_Suiv();
            break;
        case SUB:
            // Code for subtraction operation
           
            INST.MNE = SUB;
            INTER_INST(INST);
            Sym_Suiv();
            break;
        case ADD:
            // Code for addition operation
          
            INST.MNE = ADD;
            INTER_INST(INST);
            Sym_Suiv();
            break;
        case EQL:
            // Code for equality comparison
         
            INST.MNE = EQL;
            INTER_INST(INST);
            Sym_Suiv();
            break;
        case NEQ:
            // Code for inequality comparison
       
            INST.MNE = NEQ;
            INTER_INST(INST);
            Sym_Suiv();
            break;
        case GTR:
            // Code for greater than comparison
       
            INST.MNE = GTR;
            INTER_INST(INST);
            Sym_Suiv();
            break;
        case LSS:
            // Code for less than comparison
           
            INST.MNE = LSS;
            INTER_INST(INST);
            Sym_Suiv();
            break;
        case GEQ:
            // Code for greater than or equal to comparison
           
            INST.MNE = GEQ;
            INTER_INST(INST);
            Sym_Suiv();
            break;
        case LEQ:
            // Code for less than or equal to comparison
           
            INST.MNE = LEQ;
            INTER_INST(INST);
            Sym_Suiv();
            break;
        case PRN:
            // Code for print operation
      
            INST.MNE = PRN;
            INTER_INST(INST);
            Sym_Suiv();

            break;
        case INN:
            // Code for input operation
      
            INST.MNE = INN;
            INTER_INST(INST);
            Sym_Suiv();
            break;
        case INT:
            // Code for integer declaration
            Sym_Suiv();
         
            INST.MNE = INT;
            INST.SUITE = SYM_COUR.val;
            INTER_INST(INST);

            Test_Symbole(SYM_COUR.CODE, NUM_TOKEN);
            // defin instrution

            break;
        case LDI:
            // Code for loading value from memory
            Sym_Suiv();
     
            INST.MNE = LDI;
            INST.SUITE = SYM_COUR.val;
            INTER_INST(INST);
            Test_Symbole(SYM_COUR.CODE, NUM_TOKEN);
            break;
        case LDA:
            // Code for loading address
            Sym_Suiv();
            
            INST.MNE = LDA;
            INST.SUITE = SYM_COUR.val;
            INTER_INST(INST);
            Test_Symbole(SYM_COUR.CODE, NUM_TOKEN);
            break;
        case LDV:
            // Code for loading value from address
         
            INST.MNE = LDV;
            INTER_INST(INST);
            Sym_Suiv();
            break;
        case STO:
            // Code for storing value to memory
          
            INST.MNE = STO;
            INTER_INST(INST);
            Sym_Suiv();
            break;
        case BRN:
            // Code for unconditional branch
            Sym_Suiv();
          
            INST.MNE = BRN;
            INST.SUITE = SYM_COUR.val;
            INTER_INST(INST);
            Test_Symbole(SYM_COUR.CODE, NUM_TOKEN);
            break;
        case BZE:
            // Code for branch if zero
            Sym_Suiv();
          
            INST.MNE = BZE;
            INST.SUITE = SYM_COUR.val;
            INTER_INST(INST);
            Test_Symbole(SYM_COUR.CODE, NUM_TOKEN);
            break;

        default:
            Erreur(INST_ERR);
        }
    }
}

int main()
{
    fichier = fopen("C:/Users/HP/Desktop/Mini-Compilateur-Pascal/test.p", "r");
    if (fichier == NULL)
    {
        perror("Erreur lors de l'ouverture du fichier!");
        return 1;
    }
    Lire_Car();
    Sym_Suiv();

    PCODE();

    printf("P-code parfait.\n");
    fclose(fichier);
    return 0;
}
