#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Directives de préprocesseur
#define TABLEINDEX 100   // Taille de l'index de table
#define TAILLEMEM 100    // Taille de la mémoire
#define TAILLECODE 100   // Taille du code

// Déclaration de variable globale
int numberOfTokens = 0;  // Nombre de tokens dans le code

// Déclaration de l'énumération pour les tokens lexicaux
typedef enum {
    ID_TOKEN,              // Token pour un identifiant
    PROGRAM_TOKEN,         // Token pour le mot-clé PROGRAM
    CONST_TOKEN,           // Token pour le mot-clé CONST
    VAR_TOKEN,             // Token pour le mot-clé VAR
    BEGIN_TOKEN,           // Token pour le mot-clé BEGIN
    END_TOKEN,             // Token pour le mot-clé END
    IF_TOKEN,              // Token pour le mot-clé IF
    THEN_TOKEN,            // Token pour le mot-clé THEN
    WHILE_TOKEN,           // Token pour le mot-clé WHILE
    DO_TOKEN,              // Token pour le mot-clé DO
    READ_TOKEN,            // Token pour le mot-clé READ
    WRITE_TOKEN,           // Token pour le mot-clé WRITE
    PV_TOKEN,              // Token pour le point-virgule ;
    PT_TOKEN,              // Token pour le point .
    PLUS_TOKEN,            // Token pour l'opérateur d'addition +
    MOINS_TOKEN,           // Token pour l'opérateur de soustraction -
    MULT_TOKEN,            // Token pour l'opérateur de multiplication *
    DIV_TOKEN,             // Token pour l'opérateur de division /
    VIR_TOKEN,             // Token pour la virgule ,
    AFF_TOKEN,             // Token pour l'opérateur d'affectation :=
    INF_TOKEN,             // Token pour l'opérateur de comparaison <
    INFEG_TOKEN,           // Token pour l'opérateur de comparaison <=
    SUP_TOKEN,             // Token pour l'opérateur de comparaison >
    SUPEG_TOKEN,           // Token pour l'opérateur de comparaison >=
    DIFF_TOKEN,            // Token pour l'opérateur de comparaison !=
    PO_TOKEN,              // Token pour la parenthèse ouvrante (
    PF_TOKEN,              // Token pour la parenthèse fermante )
    FIN_TOKEN,             // Token pour la fin du programme
    ERREUR_TOKEN,          // Token pour une erreur
    EOF_TOKEN,             // Token pour la fin du fichier
    EG_TOKEN,              // Token pour l'opérateur de comparaison ==
    REPEAT_TOKEN,          // Token pour le mot-clé REPEAT
    UNTIL_TOKEN,           // Token pour le mot-clé UNTIL
    FOR_TOKEN,             // Token pour le mot-clé FOR
    ELSE_TOKEN,            // Token pour le mot-clé ELSE
    CASE_TOKEN,            // Token pour le mot-clé CASE
    OF_TOKEN,              // Token pour le mot-clé OF
    INTO_TOKEN,            // Token pour le mot-clé INTO
    DOWNTO_TOKEN,          // Token pour le mot-clé DOWNTO
    DDOT_TOKEN,            // Token pour le double point :
    INTEGER_TOKEN,         // Token pour le type de données INTEGER
    FLOAT_TOKEN,           // Token pour le type de données FLOAT
    BOOLEAN_TOKEN,         // Token pour le type de données BOOLEAN
    STRING_TOKEN,          // Token pour le type de données STRING
    ARRAY_TOKEN,           // Token pour le type de données ARRAY
    INTEGER_DATA_TOKEN,    // Token pour les données de type INTEGER
    FLOAT_DATA_TOKEN,      // Token pour les données de type FLOAT
    BOOLEAN_DATA_TOKEN,    // Token pour les données de type BOOLEAN
    STRING_DATA_TOKEN,     // Token pour les données de type STRING
    ARRAY_DATA_TOKEN      // Token pour les données de type ARRAY
} CODES_LEX;

// Déclaration de l'énumération pour les codes d'erreur
typedef enum {
    ID_ERR,                   // Erreur pour un identifiant
    PROGRAM_ERR,              // Erreur pour le mot-clé PROGRAM
    CONST_ERR,                // Erreur pour le mot-clé CONST
    VAR_ERR,                  // Erreur pour le mot-clé VAR
    BEGIN_ERR,                // Erreur pour le mot-clé BEGIN
    END_ERR,                  // Erreur pour le mot-clé END
    IF_ERR,                   // Erreur pour le mot-clé IF
    THEN_ERR,                 // Erreur pour le mot-clé THEN
    WHILE_ERR,                // Erreur pour le mot-clé WHILE
    DO_ERR,                   // Erreur pour le mot-clé DO
    READ_ERR,                 // Erreur pour le mot-clé READ
    WRITE_ERR,                // Erreur pour le mot-clé WRITE
    PV_ERR,                   // Erreur pour le point-virgule ;
    PT_ERR,                   // Erreur pour le point .
    PLUS_ERR,                 // Erreur pour l'opérateur d'addition +
    MOINS_ERR,                // Erreur pour l'opérateur de soustraction -
    MULT_ERR,                 // Erreur pour l'opérateur de multiplication *
    DIV_ERR,                  // Erreur pour l'opérateur de division /
    VIR_ERR,                  // Erreur pour la virgule ,
    AFF_ERR,                  // Erreur pour l'opérateur d'affectation :=
    INF_ERR,                  // Erreur pour l'opérateur de comparaison <
    INFEG_ERR,                // Erreur pour l'opérateur de comparaison <=
    SUP_ERR,                  // Erreur pour l'opérateur de comparaison >
    SUPEG_ERR,                // Erreur pour l'opérateur de comparaison >=
    DIFF_ERR,                 // Erreur pour l'opérateur de comparaison !=
    PO_ERR,                   // Erreur pour la parenthèse ouvrante (
    PF_ERR,                   // Erreur pour la parenthèse fermante )
    FIN_ERR,                  // Erreur pour la fin du programme
    ERREUR_ERR,               // Erreur générique
    EOF_ERR,                  // Erreur pour la fin du fichier
    EG_ERR,                   // Erreur pour l'opérateur de comparaison ==
    CONST_VAR_BEGIN_ERR,      // Erreur pour CONST, VAR, BEGIN
    VAR_BEGIN_ERR,            // Erreur pour VAR, BEGIN
    REPEAT_ERR,               // Erreur pour le mot-clé REPEAT
    UNTIL_ERR,                // Erreur pour le mot-clé UNTIL
    FOR_ERR,                  // Erreur pour le mot-clé FOR
    ELSE_ERR,                 // Erreur pour le mot-clé ELSE
    CASE_ERR,                 // Erreur pour le mot-clé CASE
    OF_ERR,                   // Erreur pour le mot-clé OF
    INTO_ERR,                 // Erreur pour le mot-clé INTO
    DOWNTO_ERR,               // Erreur pour le mot-clé DOWNTO
    DDOT_ERR,                 // Erreur pour le double point :
    INST_PCODE_ERR,           // Erreur pour l'instruction PCode
    INTEGER_ERR,              // Erreur pour le type de données INTEGER
    FLOAT_ERR,                // Erreur pour le type de données FLOAT
    BOOLEAN_ERR,              // Erreur pour le type de données BOOLEAN
    STRING_ERR,               // Erreur pour le type de données STRING
    ARRAY_ERR,                // Erreur pour le type de données ARRAY
    INTEGER_DATA_ERR,         // Erreur pour les données de type INTEGER
    FLOAT_DATA_ERR,           // Erreur pour les données de type FLOAT
    BOOLEAN_DATA_ERR,         // Erreur pour les données de type BOOLEAN
    STRING_DATA_ERR,          // Erreur pour les données de type STRING
    ARRAY_DATA_ERR           // Erreur pour les données de type ARRAY
} CODES_ERR;

// La fonction getErrorMessage retourne un message d'erreur basé sur le code d'erreur donné
const char *getErrorMessage(CODES_ERR error_code);
const char *getErrorMessage(CODES_ERR error_code)
{
    switch (error_code)
    {
        case ID_ERR:
            return "Identifier error";  // Erreur d'identifiant
        case PROGRAM_ERR:
            return "Program error";  // Erreur de programme
        case CONST_ERR:
            return "Constant error";  // Erreur de constante
        case VAR_ERR:
            return "Variable error";  // Erreur de variable
        case BEGIN_ERR:
            return "Begin error";  // Erreur de BEGIN
        case END_ERR:
            return "End error";  // Erreur de END
        case IF_ERR:
            return "If error";  // Erreur de IF
        case THEN_ERR:
            return "Then error";  // Erreur de THEN
        case WHILE_ERR:
            return "While error";  // Erreur de WHILE
        case DO_ERR:
            return "Do error";  // Erreur de DO
        case READ_ERR:
            return "Read error";  // Erreur de READ
        case WRITE_ERR:
            return "Write error";  // Erreur de WRITE
        case PV_ERR:
            return "Semicolon error";  // Erreur de point-virgule
        case PT_ERR:
            return "Period error";  // Erreur de point
        case PLUS_ERR:
            return "Plus error";  // Erreur de plus
        case MOINS_ERR:
            return "Minus error";  // Erreur de moins
        case MULT_ERR:
            return "Multiplication error";  // Erreur de multiplication
        case DIV_ERR:
            return "Division error";  // Erreur de division
        case VIR_ERR:
            return "Comma error";  // Erreur de virgule
        case AFF_ERR:
            return "Assignment error";  // Erreur d'affectation
        case INF_ERR:
            return "Less than error";  // Erreur de moins que
        case INFEG_ERR:
            return "Less than or equal to error";  // Erreur de moins ou égal à
        case SUP_ERR:
            return "Greater than error";  // Erreur de plus que
        case SUPEG_ERR:
            return "Greater than or equal to error";  // Erreur de plus ou égal à
        case DIFF_ERR:
            return "Not equal to error";  // Erreur de différent de
        case PO_ERR:
            return "Opening parenthesis error";  // Erreur de parenthèse ouvrante
        case PF_ERR:
            return "Closing parenthesis error";  // Erreur de parenthèse fermante
        case FIN_ERR:
            return "End of file error";  // Erreur de fin de fichier
        case INTEGER_DATA_ERR:
            return "Number format error";  // Erreur de format numérique
        case ERREUR_ERR:
            return "General error";  // Erreur générale
        case EOF_ERR:
            return "End of file error";  // Erreur de fin de fichier
        case EG_ERR:
            return "Equality error";  // Erreur d'égalité
        case CONST_VAR_BEGIN_ERR:
            return "Constant/Variable/Begin declaration error";  // Erreur de déclaration CONST/VAR/BEGIN
        case VAR_BEGIN_ERR:
            return "Variable/Begin declaration error";  // Erreur de déclaration VAR/BEGIN
        case REPEAT_ERR:
            return "Repeat error";  // Erreur de REPEAT
        case UNTIL_ERR:
            return "Until error";  // Erreur de UNTIL
        case FOR_ERR:
            return "For error";  // Erreur de FOR
        case ELSE_ERR:
            return "Else error";  // Erreur de ELSE
        case CASE_ERR:
            return "Case error";  // Erreur de CASE
        case OF_ERR:
            return "Of error";  // Erreur de OF
        case INTO_ERR:
            return "Into error";  // Erreur de INTO
        case DOWNTO_ERR:
            return "Downto error";  // Erreur de DOWNTO
        case DDOT_ERR:
            return "Double dot error";  // Erreur de double point
        default:
            return "Unknown error";  // Erreur inconnue
    }
}

// Variable globale pour indiquer si la lecture est activée ou non
int isReadActivated = 0;

// Déclaration d'une structure nommée TSym_Cour
typedef struct
{
    CODES_LEX CODE;   // Variable de type CODES_LEX pour stocker le code lexical
    char NOM[20];     // Tableau de caractères pour stocker le nom (identifiant) associé au symbole courant
    int val;          // Variable entière pour stocker la valeur associée au symbole courant
} TSym_Cour;

// Déclaration des variables globales head et SYM_COUR de type TSym_Cour
TSym_Cour head;       // Variable représentant la tête (ou le début) d'une liste de symboles
TSym_Cour SYM_COUR;   // Variable représentant le symbole courant

// Déclaration d'un pointeur de fichier
FILE *fichier;   // Pointeur de fichier utilisé pour lire ou écrire des données dans un fichier

char Car_Cour; // caractère courant

// Définition d'une énumération pour les types de symboles
typedef enum
{
    TPROG,   // Programme
    TCONST,  // Constante
    TVAR     // Variable
} TSYM;

// Définition d'une structure pour représenter les identifiants dans une table
typedef struct
{
    TSYM TIDF;         // Type de l'identifiant (TPROG, TCONST, TVAR)
    char NOM[20];      // Nom de l'identifiant (maximum 20 caractères)
    int value;         // Valeur associée à l'identifiant
} T_TAB_IDF;

T_TAB_IDF *TAB_IDFS;  // Pointeur vers une table d'identifiants
int k = 0;             // Compteur pour la table d'identifiants

// Définition d'une énumération pour les régions
typedef enum
{
    RPROG,    // Programme
    RCONST,   // Section des constantes
    RVAR,     // Section des variables
    RBEGIN    // Début du bloc
} Region;

Region current_region = TPROG;  // Région actuelle (initialisée à TPROG)

TSYM lastType = TPROG;          // Dernier type rencontré (initialisé à TPROG)
char lastIdToken[20];           // Dernier identifiant rencontré (maximum 20 caractères)

// Définition d'une structure pour représenter les symboles
typedef struct
{
    char NOM[20];       // Nom du symbole (maximum 20 caractères)
    CODES_LEX CLASSE;   // Classe du symbole
    int ADRESSE;        // Adresse du symbole
} TSYMB;

TSYMB TABLESYM[TABLEINDEX];     // Table des symboles
int IND_DER_SYM_ACC = 0;         // Indice du dernier symbole accessible dans TABLESYM
int OFFSET = -1;                 // Décalage pour la gestion de la mémoire

int MEM[TAILLEMEM];              // Mémoire (Pile de la machine)
int SP;                          // Pointeur vers le sommet de la pile


// Définition de l'énumération pour les mnémoniques des instructions
typedef enum
{
    ADD,   // Addition
    SUB,   // Soustraction
    MUL,   // Multiplication
    DIV,   // Division
    EQL,   // Égal à
    NEQ,   // Différent de
    GTR,   // Supérieur à
    LSS,   // Inférieur à
    GEQ,   // Supérieur ou égal à
    LEQ,   // Inférieur ou égal à
    PRN,   // Affichage
    INN,   // Lecture d'un entier
    INT,   // Initialisation d'un entier
    LDI,   // Chargement d'une constante
    LDA,   // Chargement de l'adresse d'une variable
    LDV,   // Chargement de la valeur d'une variable
    STO,   // Stockage dans une variable
    BRN,   // Branchement inconditionnel
    BZE,   // Branchement conditionnel
    HLT    // Arrêt
} MNEMONIQUES;

// Définition de la structure pour représenter une instruction du PCode
typedef struct
{
    MNEMONIQUES MNE;  // Mnémonique de l'instruction
    int SUITE;        // Adresse de l'instruction suivante
} INSTRUCTION;

INSTRUCTION PCODE[TAILLECODE];  // Tableau d'instructions PCode

int LABEL_BRN;      // Étiquette pour les instructions BRN
int INDICE_BZE;     // Indice pour les instructions BZE
int IND_BZE;        // Indice pour les instructions BZE
int PC = 0;         // Compteur d'instructions

// Variables pour gérer les opérateurs et les boucles
int opRELOP = 0;
int opMULOP = 0;
int opADDOP = 0;
int opLoop = 0;

// Prototypes des fonctions à utiliser
// Fonction pour analyser les variables
void VARS();    // Fonction pour analyser les variables
void INSTS();   // Fonction pour analyser les instructions
void INST();    // Fonction pour analyser une instruction
void AFFEC();   // Fonction pour gérer l'affectation
void SI();      // Fonction pour gérer la structure SI (IF)
void TANTQUE(); // Fonction pour gérer la structure TANTQUE (WHILE)
void ECRIRE();  // Fonction pour gérer l'instruction ECRIRE (WRITE)
void LIRE();    // Fonction pour gérer l'instruction LIRE (READ)
void EXPR();    // Fonction pour analyser une expression
void TERM();    // Fonction pour analyser un terme
void FACT();    // Fonction pour analyser un facteur
void MULOP();   // Fonction pour analyser les opérateurs multiplicatifs
void ADDOP();   // Fonction pour analyser les opérateurs additifs
void RELOP();   // Fonction pour analyser les opérateurs de comparaison
void COND();    // Fonction pour analyser une condition
void Lire_Car();// Fonction pour lire un caractère du flux d'entrée
void Erreur(CODES_ERR code, char *origin);  // Fonction pour gérer les erreurs
void Test_Symbole(CODES_LEX cl, CODES_ERR COD_ERR); // Fonction pour tester le symbole courant
void PROGRAM(); // Fonction principale PROGRAM
void BLOCK();   // Fonction pour analyser un bloc de code
void CONSTS();  // Fonction pour gérer les constantes
void Sym_Suiv();// Fonction pour passer au symbole suivant
void lire_mot();// Fonctions pour lire des mots
void lire_nombre();// Fonctions pour lire des nombres
void CAS(); // Fonction pour gérer les cas (CASE)
void POUR();    // Fonction pour gérer les boucles FOR
void TYPE();    // Fonction pour gérer les types
void REPETER(); // Fonction pour gérer les boucles REPEAT
void Check();   // Déclaration de la fonction Check

// Section P CODE
// Fonctions pour générer des instructions P CODE
void GENERER1(MNEMONIQUES M);
void GENERER2(MNEMONIQUES M, int A);

void SaveInstToFile(FILE *FICH_SORTIE, INSTRUCTION INST, int i); // Fonction pour sauvegarder une instruction dans un fichier
void INTER_PCODE(); // Fonction principale pour interpréter le P CODE
void INTER_INST(INSTRUCTION INST); // Fonction pour interpréter une instruction


// Définition des fonctions à utiliser
void lire_mot()
{
    char mot[20]; // Déclaration d'un tableau de caractères pour stocker le mot lu
    int indice = 0; // Initialisation d'un indice pour suivre la position actuelle dans le tableau 'mot'

    // Lecture du premier caractère (lettre)
    mot[indice++] = Car_Cour; // Stockage du premier caractère dans le tableau 'mot'
    Lire_Car(); // Appel d'une fonction pour lire le caractère suivant

    // Lecture des caractères suivants (lettres ou chiffres)
    while (isalpha(Car_Cour) || isdigit(Car_Cour)) // Boucle tant que le caractère courant est une lettre ou un chiffre
    {
        mot[indice++] = Car_Cour; // Stockage du caractère courant dans le tableau 'mot'
        Lire_Car(); // Lecture du caractère suivant
    }

    // Ajout du caractère de fin de chaîne
    mot[indice] = '\0'; // Ajout du caractère nul pour marquer la fin de la chaîne de caractères 'mot'


    // Vérification si le mot est un mot-clé et attribution du code correspondant
    // Vérification si le mot est égal à "program", sans tenir compte de la casse
    if (stricmp(mot, "program") == 0)
    {
        SYM_COUR.CODE = PROGRAM_TOKEN; // Si oui, attribuer le code PROGRAM_TOKEN à SYM_COUR.CODE
    }
    else if (stricmp(mot, "const") == 0)
    {
        SYM_COUR.CODE = CONST_TOKEN; // Si oui, attribuer le code CONST_TOKEN à SYM_COUR.CODE
    }
    else if (stricmp(mot, "var") == 0)
    {
        SYM_COUR.CODE = VAR_TOKEN; // Si oui, attribuer le code VAR_TOKEN à SYM_COUR.CODE
    }
    else if (stricmp(mot, "begin") == 0) // Si le mot est "begin"
    {
        SYM_COUR.CODE = BEGIN_TOKEN; // Attribuer le code correspondant à BEGIN_TOKEN
    }
    else if (stricmp(mot, "end") == 0) // Si le mot est "end"
    {
        SYM_COUR.CODE = END_TOKEN; // Attribuer le code correspondant à END_TOKEN
    }
    else if (stricmp(mot, "if") == 0) // Si le mot est "if"
    {
        SYM_COUR.CODE = IF_TOKEN; // Attribuer le code correspondant à IF_TOKEN
    }
    else if (stricmp(mot, "then") == 0)
    {
        SYM_COUR.CODE = THEN_TOKEN; // Si oui, attribuer le code THEN_TOKEN à SYM_COUR.CODE
    }
    else if (stricmp(mot, "while") == 0) // Si le mot n'est pas "then", vérifier s'il est égal à "while"
    {
        SYM_COUR.CODE = WHILE_TOKEN; // Si oui, attribuer le code WHILE_TOKEN à SYM_COUR.CODE
    }
    else if (stricmp(mot, "do") == 0) // Si le mot n'est pas "while", vérifier s'il est égal à "do"
    {
        SYM_COUR.CODE = DO_TOKEN; // Si oui, attribuer le code DO_TOKEN à SYM_COUR.CODE
    }
    else if (stricmp(mot, "read") == 0) // Si le mot n'est pas "do", vérifier s'il est égal à "read"
    {
        SYM_COUR.CODE = READ_TOKEN; // Si oui, attribuer le code READ_TOKEN à SYM_COUR.CODE
        isReadActivated = 1; // Activer le drapeau pour indiquer que la lecture est activée
    }
    else if (stricmp(mot, "write") == 0) // Si le mot n'est pas "read", vérifier s'il est égal à "write"
    {
        SYM_COUR.CODE = WRITE_TOKEN; // Si oui, attribuer le code WRITE_TOKEN à SYM_COUR.CODE
    }
    else if (stricmp(mot, "else") == 0)
    {
        SYM_COUR.CODE = ELSE_TOKEN; // Si oui, attribuer le code ELSE_TOKEN à SYM_COUR.CODE
    }
    else if (stricmp(mot, "repeat") == 0)
    {
        SYM_COUR.CODE = REPEAT_TOKEN; // Si oui, attribuer le code REPEAT_TOKEN à SYM_COUR.CODE
    }
    else if (stricmp(mot, "until") == 0)
    {
        SYM_COUR.CODE = UNTIL_TOKEN; // Si oui, attribuer le code UNTIL_TOKEN à SYM_COUR.CODE
    }
    else if (stricmp(mot, "for") == 0)
    {
        SYM_COUR.CODE = FOR_TOKEN; // Si oui, attribuer le code FOR_TOKEN à SYM_COUR.CODE
    }
    else if (stricmp(mot, "to") == 0)
    {
        SYM_COUR.CODE = INTO_TOKEN; // Si oui, attribuer le code INTO_TOKEN à SYM_COUR.CODE
    }
    else if (stricmp(mot, "case") == 0)
    {
        SYM_COUR.CODE = CASE_TOKEN; // Si oui, attribuer le code CASE_TOKEN à SYM_COUR.CODE
    }
    else if (stricmp(mot, "of") == 0)
    {
        SYM_COUR.CODE = OF_TOKEN; // Si oui, attribuer le code OF_TOKEN à SYM_COUR.CODE
    }
    else if (stricmp(mot, "to") == 0)
    {
        SYM_COUR.CODE = INTO_TOKEN; // Si oui, attribuer le code INTO_TOKEN à SYM_COUR.CODE
    }
    else if (stricmp(mot, "downto") == 0)
    {
        SYM_COUR.CODE = DOWNTO_TOKEN; // Si oui, attribuer le code DOWNTO_TOKEN à SYM_COUR.CODE
    }
    else if (stricmp(mot, "integer") == 0)
    {
        SYM_COUR.CODE = INTEGER_TOKEN; // Si oui, attribuer le code INTEGER_TOKEN à SYM_COUR.CODE
    }
    else if (stricmp(mot, "float") == 0)
    {
        SYM_COUR.CODE = FLOAT_TOKEN; // Si oui, attribuer le code FLOAT_TOKEN à SYM_COUR.CODE
    }
    else if (stricmp(mot, "boolean") == 0)
    {
        SYM_COUR.CODE = BOOLEAN_TOKEN; // Si oui, attribuer le code BOOLEAN_TOKEN à SYM_COUR.CODE
    }
    else if (stricmp(mot, "string") == 0)
    {
        SYM_COUR.CODE = STRING_TOKEN; // Si oui, attribuer le code STRING_TOKEN à SYM_COUR.CODE
    }

    else if (stricmp(mot, "array") == 0) // Si le mot est "array"
    {
        SYM_COUR.CODE = ARRAY_TOKEN; // Attribuer le code correspondant à ARRAY_TOKEN
    }
    else if (stricmp(mot, "true") == 0) // Si le mot est "true"
    {
        SYM_COUR.CODE = BOOLEAN_DATA_TOKEN; // Attribuer le code correspondant à BOOLEAN_DATA_TOKEN
        SYM_COUR.val = 1; // Définir la valeur associée à vrai (1)
    }
    else if (stricmp(mot, "false") == 0) // Si le mot est "false"
    {
        SYM_COUR.CODE = BOOLEAN_DATA_TOKEN; // Attribuer le code correspondant à BOOLEAN_DATA_TOKEN
        SYM_COUR.val = 0; // Définir la valeur associée à faux (0)
    }
    // Si le mot n'est aucun des mots-clés prédéfinis, il est considéré comme un identifiant
    else
    {
        // Attribuer le code ID_TOKEN à SYM_COUR.CODE
        SYM_COUR.CODE = ID_TOKEN;
        // Stocker l'identifiant dans le jeton
        strcpy(SYM_COUR.NOM, mot);
        Check();
    }

    // Si le code n'est pas celui d'un identifiant, stocker à nouveau le mot dans NOM
    if (SYM_COUR.CODE != ID_TOKEN)
    {
        strcpy(SYM_COUR.NOM, mot); // Stockage du mot dans le champ NOM de la structure SYM_COUR
    }
}

void lire_nombre()
{
    char nombre[11]; // Tableau pour stocker le nombre, permettant jusqu'à 10 chiffres et un caractère de fin de chaîne
    int indice = 0; // Indice pour parcourir le tableau
    int isFloat = 0; // Variable pour indiquer si le nombre est un flottant

    // Lecture du premier chiffre
    nombre[indice++] = Car_Cour;
    Lire_Car();

    // Lecture des chiffres suivants et du point décimal
    while (isdigit(Car_Cour) || Car_Cour == '.')
    {
        if (Car_Cour == '.')
        {
            isFloat = 1; // Le nombre contient un point, donc c'est un flottant
        }
        nombre[indice++] = Car_Cour;
        Lire_Car();
    }

    // Ajout du caractère de fin de chaîne
    nombre[indice] = '\0';

    // Stockage du nombre dans le jeton
    if (isFloat)
    {
        SYM_COUR.CODE = FLOAT_DATA_TOKEN; // Attribuer le code FLOAT_DATA_TOKEN à SYM_COUR.CODE
        SYM_COUR.val = atof(nombre); // Convertir la chaîne en flottant et la stocker dans SYM_COUR.val
    }
    else
    {
        SYM_COUR.CODE = INTEGER_DATA_TOKEN; // Attribuer le code INTEGER_DATA_TOKEN à SYM_COUR.CODE
        SYM_COUR.val = atoi(nombre); // Convertir la chaîne en entier et la stocker dans SYM_COUR.val
    }

    strcpy(SYM_COUR.NOM, nombre); // Copier la chaîne dans SYM_COUR.NOM pour stockage
}

void Check()
{
    int r = 0; // Variable pour marquer si le symbole a déjà été déclaré
    int i; // Variable pour l'itération dans la boucle

    // Analyse de la région de code actuelle
    switch (current_region)
    {
    case RPROG: // Si la région est la région du programme
        // Vérification de doublons dans les identifiants
        for (i = 0; i < k; ++i)
        {
            if (strcmp(SYM_COUR.NOM, TAB_IDFS[i].NOM) == 0)
            {
                r = 1; // Marquer que le symbole a déjà été déclaré
                break;
            }
        }

        // Si le symbole est déjà déclaré
        if (r == 1)
        {
            if (TPROG == TAB_IDFS[i].TIDF)
            {
                printf("%s ----> Erreur:  L'ID du programme ne peut pas être réutilisé dans le programme.", SYM_COUR.NOM);
                exit(EXIT_FAILURE);
            }
            else
            {
                printf("%s ----> Erreur: AUCUN DOUBLE DECLARATIONS PERMIS.", SYM_COUR.NOM);
                exit(EXIT_FAILURE);
            }
        }
        // Si le symbole n'a pas déjà été déclaré
        strcpy(TAB_IDFS[k].NOM, SYM_COUR.NOM); // Copier le nom du symbole dans la table des identifiants
        TAB_IDFS[k].TIDF = TPROG; // Marquer le type de symbole comme un symbole de programme
        k++; // Augmenter le compteur d'identifiants
        break;

    case RCONST: // Si la région est la région des constantes
        // Vérification de doublons dans les identifiants
        for (i = 0; i < k; ++i)
        {
            if (strcmp(SYM_COUR.NOM, TAB_IDFS[i].NOM) == 0)
            {
                r = 1; // Marquer que le symbole a déjà été déclaré
                break;
            }
        }

        // Si le symbole est déjà déclaré
        if (r == 1)
        {
            if (TPROG == TAB_IDFS[i].TIDF)
            {
                printf("%s ----> Erreur:  L'identifiant du programme ne peut pas être réutilisé dans le programme.", SYM_COUR.NOM);
                exit(EXIT_FAILURE);
            }
            else
            {
                printf("%s ----> Erreur: AUCUN DOUBLE DECLARATIONS PERMIS.", SYM_COUR.NOM);
                exit(EXIT_FAILURE);
            }
        }
        // Si le symbole n'a pas déjà été déclaré
        else
        {
            strcpy(TAB_IDFS[k].NOM, SYM_COUR.NOM); // Copier le nom du symbole dans la table des identifiants
            TAB_IDFS[k].TIDF = TCONST; // Marquer le type de symbole comme une constante
            k++; // Augmenter le compteur d'identifiants
        }
        break;

    case RVAR: // Si la région est la région des variables
        // Vérification de doublons dans les identifiants
        for (i = 0; i < k; ++i)
        {
            if (strcmp(SYM_COUR.NOM, TAB_IDFS[i].NOM) == 0)
            {
                r = 1; // Marquer que le symbole a déjà été déclaré
                break;
            }
        }

        // Si le symbole est déjà déclaré
        if (r == 1)
        {
            if (TPROG == TAB_IDFS[i].TIDF)
            {
                printf("%s ----> Erreur:  L'ID du programme ne peut pas être réutilisé dans le programme.", SYM_COUR.NOM);
                exit(EXIT_FAILURE);
            }
            else
            {
                printf("%s ----> Erreur: AUCUN DOUBLE DECLARATIONS PERMIS.", SYM_COUR.NOM);
                exit(EXIT_FAILURE);
            }
        }
        // Si le symbole n'a pas déjà été déclaré
        else
        {
            strcpy(TAB_IDFS[k].NOM, SYM_COUR.NOM); // Copier le nom du symbole dans la table des identifiants
            TAB_IDFS[k].TIDF = TVAR; // Marquer le type de symbole comme une variable
            k++; // Augmenter le compteur d'identifiants
        }
        break;

    case RBEGIN: // Si la région est la région de début
        // Vérification de la déclaration de tous les symboles
        for (i = 0; i < k; ++i)
        {
            if (strcmp(SYM_COUR.NOM, TAB_IDFS[i].NOM) == 0)
            {
                r = 1; // Marquer que le symbole a déjà été déclaré
                break;
            }
        }

        // Si le symbole est déjà déclaré
        if (r == 1)
        {
            if (TPROG == TAB_IDFS[i].TIDF)
            {
                printf("%s ----> Erreur:  L'identifiant du programme ne peut pas être réutilisé dans le programme.", SYM_COUR.NOM);
                exit(EXIT_FAILURE);
            }
        }
        // Si tous les symboles ne sont pas déclarés
        else
        {
            printf("%s ----> Erreur:  Tous les symboles doivent déjà être déclarés.", SYM_COUR.NOM);
            exit(EXIT_FAILURE);
        }

        // Si l'opération de lecture est activée
        if (isReadActivated)
        {
            isReadActivated = 0; // Désactiver l'opération de lecture
            // Vérifier si la constante ne peut pas changer de valeur dans le programme
            if (TCONST == TAB_IDFS[i].TIDF)
            {
                printf("%s ----> Erreur:  Une constante ne peut pas changer de valeur dans le programme.", SYM_COUR.NOM);
                exit(EXIT_FAILURE);
            }
        }
        break;

    default:
        break;
    }

    lastType = TAB_IDFS[i].TIDF; // Enregistrer le dernier type d'identifiant vérifié
    strcpy(lastIdToken, TAB_IDFS[i].NOM); // Enregistrer le dernier jeton d'identifiant vérifié
}

// Fonction pour lire le prochain caractère du fichier
void Lire_Car()
{
    Car_Cour = fgetc(fichier); // Lire le caractère courant depuis le fichier
}

// Fonction pour obtenir le symbole suivant du programme
void Sym_Suiv()
{
    // Ignorer les espaces, les sauts de ligne et les tabulations
    while (Car_Cour == ' ' || Car_Cour == '\n' || Car_Cour == '\t')
    {
        Lire_Car(); // Lire le prochain caractère
    }

    // Identifier si le caractère est une lettre alphabétique
    if (isalpha(Car_Cour))
    {
        lire_mot(); // Lire le mot suivant
    }
    // Identifier si le caractère est un chiffre
    else if (isdigit(Car_Cour))
    {
        lire_nombre(); // Lire le nombre suivant
    }
    else
    {
        // Gérer les autres symboles
        switch (Car_Cour)
        {
            // Cas des symboles spéciaux
            case ';':
                SYM_COUR.CODE = PV_TOKEN; // Point-virgule
                Lire_Car(); // Lire le prochain caractère
                break;
            case '+':
                SYM_COUR.CODE = PLUS_TOKEN; // Plus
                Lire_Car(); // Lire le prochain caractère
                break;
            case '-':
                SYM_COUR.CODE = MOINS_TOKEN; // Moins
                Lire_Car(); // Lire le prochain caractère
                break;
            case '*':
                SYM_COUR.CODE = MULT_TOKEN; // Multiplication
                Lire_Car(); // Lire le prochain caractère
                break;
            case '/':
                SYM_COUR.CODE = DIV_TOKEN; // Division
                Lire_Car(); // Lire le prochain caractère
                break;
            case ',':
                SYM_COUR.CODE = VIR_TOKEN; // Virgule
                Lire_Car(); // Lire le prochain caractère
                break;
            case ':':
                Lire_Car(); // Lire le prochain caractère
                if (Car_Cour == '=')
                {
                    SYM_COUR.CODE = AFF_TOKEN; // Affectation
                    Lire_Car(); // Lire le prochain caractère
                }
                else
                {
                    SYM_COUR.CODE = DDOT_TOKEN; // Double point
                }
                break;
            case '<':
                Lire_Car(); // Lire le prochain caractère
                if (Car_Cour == '=')
                {
                    SYM_COUR.CODE = INFEG_TOKEN; // Inférieur ou égal
                    Lire_Car(); // Lire le prochain caractère
                }
                else if (Car_Cour == '>')
                {
                    SYM_COUR.CODE = DIFF_TOKEN; // Différent
                    Lire_Car(); // Lire le prochain caractère
                }
                else
                {
                    SYM_COUR.CODE = INF_TOKEN; // Inférieur
                }
                break;
            case '>':
                Lire_Car(); // Lire le prochain caractère
                if (Car_Cour == '=')
                {
                    SYM_COUR.CODE = SUPEG_TOKEN; // Supérieur ou égal
                    Lire_Car(); // Lire le prochain caractère
                }
                else
                {
                    SYM_COUR.CODE = SUP_TOKEN; // Supérieur
                }
                break;
            case '(':
                SYM_COUR.CODE = PO_TOKEN; // Parenthèse ouvrante
                Lire_Car(); // Lire le prochain caractère
                break;
            case ')':
                SYM_COUR.CODE = PF_TOKEN; // Parenthèse fermante
                Lire_Car(); // Lire le prochain caractère
                break;
            case '=':
                SYM_COUR.CODE = EG_TOKEN; // Égal
                Lire_Car(); // Lire le prochain caractère
                break;
            case '.':
                SYM_COUR.CODE = PT_TOKEN; // Point
                Lire_Car(); // Lire le prochain caractère
                break;
            case EOF:
                SYM_COUR.CODE = FIN_TOKEN; // Fin de fichier
                break;
            default:
                SYM_COUR.CODE = ERREUR_TOKEN; // Symbole inconnu (erreur)
                Lire_Car(); // Lire le prochain caractère
        }
        strcpy(SYM_COUR.NOM, &Car_Cour); // Copier le caractère courant dans le nom du symbole courant
    }

    // printf("Symbol: %s\n", SYM_COUR.NOM); // Afficher le symbole courant (décommenter pour le débogage)
}

// Fonction pour gérer les erreurs de syntaxe
void Erreur(CODES_ERR code, char *origin)
{
    // Afficher le message d'erreur
    printf("Syntaxic Error\n\tError: %s\n\tOrigin: %s\n\tToken number: %d\n", getErrorMessage(code), origin, numberOfTokens);
    exit(EXIT_FAILURE); // Sortir du programme avec un code d'erreur
}

// Fonction pour générer un code P avec une instruction à un opérande
void GENERER1(MNEMONIQUES M)
{
    // Vérifier si l'indice de programme a atteint la taille maximale
    if (PC == TAILLECODE)
    {
        exit(EXIT_FAILURE); // Quitter le programme avec un code d'erreur si la taille maximale est atteinte
    }
    PC++; // Incrémenter l'indice de programme
    PCODE[PC].MNE = M; // Stocker la mnémonique dans le code P
}

// Fonction pour générer un code P avec une instruction à deux opérandes
void GENERER2(MNEMONIQUES M, int A)
{
    // Vérifier si l'indice de programme a atteint la taille maximale
    if (PC == TAILLECODE)
    {
        exit(EXIT_FAILURE); // Quitter le programme avec un code d'erreur si la taille maximale est atteinte
    }
    PC++; // Incrémenter l'indice de programme
    PCODE[PC].MNE = M; // Stocker la mnémonique dans le code P
    PCODE[PC].SUITE = A; // Stocker l'opérande dans le code P
}

//----- Interpreteur -----//

// Fonction pour sauvegarder une instruction dans un fichier
void SaveInstToFile(FILE *FICH_SORTIE, INSTRUCTION INST, int i)
{
    switch (INST.MNE) // Commutation sur la mnémonique de l'instruction
    {
    case LDA: // Si l'instruction est LDA
        fprintf(FICH_SORTIE, "%s \t %d \n", "LDA", INST.SUITE); // Écrire dans le fichier la mnémonique et l'opérande associé
        break;
    case LDI: // Si l'instruction est LDI
        fprintf(FICH_SORTIE, "%s \t %d \n", "LDI", INST.SUITE); // Écrire dans le fichier la mnémonique et l'opérande associé
        break;
    case INT: // Si l'instruction est INT
        fprintf(FICH_SORTIE, "%s \t %d \n", "INT", INST.SUITE); // Écrire dans le fichier la mnémonique et l'opérande associé
        break;
    case BZE: // Si l'instruction est BZE
        fprintf(FICH_SORTIE, "%s \t %d \n", "BZE", INST.SUITE); // Écrire dans le fichier la mnémonique et l'opérande associé
        break;
    case BRN: // Si l'instruction est BRN
        fprintf(FICH_SORTIE, "%s \t %d \n", "BRN", INST.SUITE); // Écrire dans le fichier la mnémonique et l'opérande associé
        break;
    case LDV: // Si l'instruction est LDV
        fprintf(FICH_SORTIE, "%s \n", "LDV"); // Écrire dans le fichier seulement la mnémonique car LDV n'a pas d'opérande
        break;
    case ADD: // Si l'instruction est ADD
        fprintf(FICH_SORTIE, "%s \n", "ADD"); // Écrire dans le fichier seulement la mnémonique car ADD n'a pas d'opérande
        break;
    case SUB: // Si l'instruction est SUB
        fprintf(FICH_SORTIE, "%s \n", "SUB"); // Écrire dans le fichier seulement la mnémonique car SUB n'a pas d'opérande
        break;
    case MUL: // Si l'instruction est MUL
        fprintf(FICH_SORTIE, "%s \n", "MUL"); // Écrire dans le fichier seulement la mnémonique car MUL n'a pas d'opérande
        break;
    case DIV: // Si l'instruction est DIV
        fprintf(FICH_SORTIE, "%s \n", "DIV"); // Écrire dans le fichier seulement la mnémonique car DIV n'a pas d'opérande
        break;
    case LEQ: // Si l'instruction est LEQ
        fprintf(FICH_SORTIE, "%s \n", "LEQ"); // Écrire dans le fichier seulement la mnémonique car LEQ n'a pas d'opérande
        break;
    case GEQ: // Si l'instruction est GEQ
        fprintf(FICH_SORTIE, "%s \n", "GEQ"); // Écrire dans le fichier seulement la mnémonique car GEQ n'a pas d'opérande
        break;
    case NEQ: // Si l'instruction est NEQ
        fprintf(FICH_SORTIE, "%s \n", "NEQ"); // Écrire dans le fichier seulement la mnémonique car NEQ n'a pas d'opérande
        break;
    case LSS: // Si l'instruction est LSS
        fprintf(FICH_SORTIE, "%s \n", "LSS"); // Écrire dans le fichier seulement la mnémonique car LSS n'a pas d'opérande
        break;
    case GTR: // Si l'instruction est GTR
        fprintf(FICH_SORTIE, "%s \n", "GTR"); // Écrire dans le fichier seulement la mnémonique car GTR n'a pas d'opérande
        break;
    case HLT: // Si l'instruction est HLT
        fprintf(FICH_SORTIE, "%s \n", "HLT"); // Écrire dans le fichier seulement la mnémonique car HLT n'a pas d'opérande
        break;
    case STO: // Si l'instruction est STO
        fprintf(FICH_SORTIE, "%s \n", "STO"); // Écrire dans le fichier seulement la mnémonique car STO n'a pas d'opérande
        break;
    case INN: // Si l'instruction est INN
        fprintf(FICH_SORTIE, "%s \n", "INN"); // Écrire dans le fichier seulement la mnémonique car INN n'a pas d'opérande
        break;
    case PRN: // Si l'instruction est PRN
        fprintf(FICH_SORTIE, "%s \n", "PRN"); // Écrire dans le fichier seulement la mnémonique car PRN n'a pas d'opérande
        break;
    default:
        Erreur(INST_PCODE_ERR, "SaveInstToFile"); // En cas d'erreur, appeler la fonction Erreur
        break;
    }
}

// Fonction pour exécuter une instruction du P-CODE
void INTER_INST(INSTRUCTION INST)
{
    int val1, adr, val2; // Déclaration des variables locales

    switch (INST.MNE) // Commutation sur la mnémonique de l'instruction
    {
    case INT: // Si l'instruction est INT (Initialiser)
        OFFSET = SP = INST.SUITE; // Initialiser OFFSET et SP à la valeur de l'opérande
        PC++; // Aller à l'instruction suivante
        break;
    case LDI: // Si l'instruction est LDI (Charger une constante dans la pile)
        MEM[++SP] = INST.SUITE; // Placer la constante dans la pile
        PC++; // Aller à l'instruction suivante
        break;
    case LDA: // Si l'instruction est LDA (Charger l'adresse d'une variable dans la pile)
        MEM[++SP] = INST.SUITE; // Placer l'adresse dans la pile
        PC++; // Aller à l'instruction suivante
        break;
    case STO: // Si l'instruction est STO (Stocker une valeur dans une adresse)
        val1 = MEM[SP--]; // Récupérer la valeur à stocker
        adr = MEM[SP--]; // Récupérer l'adresse où stocker
        MEM[adr] = val1; // Stocker la valeur à l'adresse spécifiée
        PC++; // Aller à l'instruction suivante
        break;
    case LDV: // Si l'instruction est LDV (Charger une valeur depuis une adresse)
        adr = MEM[SP--]; // Récupérer l'adresse de la valeur à charger
        MEM[++SP] = MEM[adr]; // Charger la valeur depuis l'adresse et la placer dans la pile
        PC++; // Aller à l'instruction suivante
        break;
    case EQL: // Si l'instruction est EQL (Comparaison d'égalité)
        val1 = MEM[SP--]; // Récupérer la première valeur
        val2 = MEM[SP--]; // Récupérer la deuxième valeur
        MEM[++SP] = (val1 == val2); // Placer le résultat de la comparaison dans la pile
        PC++; // Aller à l'instruction suivante
        break;
    case LEQ: // Si l'instruction est LEQ (Comparaison de supériorité)
        val2 = MEM[SP--]; // Récupérer la deuxième valeur
        val1 = MEM[SP--]; // Récupérer la première valeur
        MEM[++SP] = (val1 <= val2); // Placer le résultat de la comparaison dans la pile
        PC++; // Aller à l'instruction suivante
        break;
    case BZE: // Si l'instruction est BZE (Branchement si zéro)
        if (MEM[SP--] == 0) // Vérifier si la valeur au sommet de la pile est zéro
            PC = INST.SUITE; // Si oui, sauter à l'adresse spécifiée
        else
            PC++; // Sinon, aller à l'instruction suivante
        break;
    case BRN: // Si l'instruction est BRN (Branchement inconditionnel)
        PC = INST.SUITE; // Sauter à l'adresse spécifiée
        break;
    }
}

// Fonction pour exécuter le P-CODE
void INTER_PCODE()
{
    PC = 0; // Initialiser le compteur d'instruction à zéro
    while (PCODE[PC].MNE != HLT) // Tant que l'instruction courante n'est pas HLT (Halt)
        INTER_INST(PCODE[PC]); // Exécuter l'instruction courante
}

// Fonction pour tester le symbole courant
void Test_Symbole(CODES_LEX cl, CODES_ERR COD_ERR)
{
    numberOfTokens++; // Incrémenter le nombre de jetons traités

    // Vérifier si le symbole courant correspond au code lexical attendu
    if (SYM_COUR.CODE == cl)
    {
        Sym_Suiv(); // Passer au symbole suivant
    }
    else
        Erreur(COD_ERR, "Test_Symbole"); // Sinon, signaler une erreur
}

// Fonction pour analyser une instruction PROGRAM
void PROGRAM()
{
    Test_Symbole(PROGRAM_TOKEN, PROGRAM_ERR); // Vérifier si le symbole courant est PROGRAM
    current_region = RPROG; // Définir la région courante comme région de programme
    Test_Symbole(ID_TOKEN, ID_ERR); // Vérifier si le symbole suivant est un identifiant
    Test_Symbole(PV_TOKEN, PV_ERR); // Vérifier si le symbole suivant est un point-virgule
    BLOCK(); // Analyser le bloc de programme
    GENERER1(HLT); // Générer une instruction HLT pour marquer la fin du programme
    Test_Symbole(PT_TOKEN, PT_ERR); // Vérifier si le symbole suivant est un point
}

void TYPE(int isIntitlized)
{
    Test_Symbole(DDOT_TOKEN, DDOT_ERR); // Vérifie si le symbole courant est un double point
    switch (SYM_COUR.CODE)
    {
    case FLOAT_TOKEN:
        Sym_Suiv(); // Passe au symbole suivant
        if (isIntitlized)
        {
            Test_Symbole(EG_TOKEN, EG_ERR); // Vérifie si le symbole suivant est un signe égal
            // Empile la valeur lue (correspondant à NUM_TOKEN)
            GENERER2(LDI, SYM_COUR.val); // Génère une instruction pour charger la valeur
            GENERER1(STO); // Génère une instruction pour stocker la valeur dans la mémoire
            IND_DER_SYM_ACC++; // Incrémente l'indice du dernier symbole accepté
            Test_Symbole(FLOAT_DATA_TOKEN, FLOAT_DATA_ERR); // Vérifie si le symbole suivant est une donnée de type flottant
            Test_Symbole(PV_TOKEN, PV_ERR); // Vérifie si le symbole suivant est un point-virgule
        }
        break;
    case INTEGER_TOKEN:
        Sym_Suiv(); // Passe au symbole suivant
        if (isIntitlized)
        {
            Test_Symbole(EG_TOKEN, EG_ERR); // Vérifie si le symbole suivant est un signe égal
            // Empile la valeur lue (correspondant à NUM_TOKEN)
            GENERER2(LDI, SYM_COUR.val); // Génère une instruction pour charger la valeur
            GENERER1(STO); // Génère une instruction pour stocker la valeur dans la mémoire
            IND_DER_SYM_ACC++; // Incrémente l'indice du dernier symbole accepté
            Test_Symbole(INTEGER_DATA_TOKEN, INTEGER_DATA_ERR); // Vérifie si le symbole suivant est une donnée de type entier
            Test_Symbole(PV_TOKEN, PV_ERR); // Vérifie si le symbole suivant est un point-virgule
        }
        break;
    case BOOLEAN_TOKEN:
        Sym_Suiv(); // Passe au symbole suivant
        if (isIntitlized)
        {
            Test_Symbole(BOOLEAN_DATA_TOKEN, BOOLEAN_DATA_ERR); // Vérifie si le symbole suivant est une donnée de type booléen
        }
        break;
    case STRING_TOKEN:
        Sym_Suiv(); // Passe au symbole suivant
        if (isIntitlized)
        {
            Test_Symbole(STRING_DATA_TOKEN, STRING_DATA_ERR); // Vérifie si le symbole suivant est une donnée de type chaîne de caractères
        }
        break;
    case ARRAY_TOKEN:
        Sym_Suiv(); // Passe au symbole suivant
        if (isIntitlized)
        {
            Test_Symbole(ARRAY_DATA_TOKEN, ARRAY_DATA_ERR); // Vérifie si le symbole suivant est une donnée de type tableau
        }
        break;
    default:
        Erreur(VAR_BEGIN_ERR, "VARS"); // Génère une erreur si le type n'est pas reconnu
        break;
    }
}

// Fonction pour analyser un bloc de programme
void BLOCK()
{
    current_region = RCONST; // Définir la région courante comme région de constantes
    CONSTS(); // Analyser les constantes
    current_region = RVAR; // Définir la région courante comme région de variables
    VARS(); // Analyser les variables
    current_region = RBEGIN; // Définir la région courante comme région de début de programme
    PCODE[0].MNE = INT; // Générer une instruction INT pour initialiser l'exécution du programme
    PCODE[0].SUITE = 2; // Définir le pointeur d'instruction sur 2
    INSTS(); // Analyser les instructions
}

void CONSTS()
{
    switch (SYM_COUR.CODE)
    {
    case CONST_TOKEN:
        // Si le prochain symbole est une déclaration de constante
        Sym_Suiv(); // Avance au prochain symbole

        // Définition d'une nouvelle constante en mémoire
        TABLESYM[IND_DER_SYM_ACC].CLASSE = ID_TOKEN; // Définit la classe de symbole comme un identifiant
        strcpy(TABLESYM[IND_DER_SYM_ACC].NOM, SYM_COUR.NOM); // Copie le nom de la constante dans la table des symboles
        TABLESYM[IND_DER_SYM_ACC].ADRESSE = ++OFFSET; // Incrémente l'offset et attribue l'adresse mémoire à la constante
        GENERER2(LDA, TABLESYM[IND_DER_SYM_ACC].ADRESSE); // Génère une instruction pour charger l'adresse de la constante

        Test_Symbole(ID_TOKEN, ID_ERR); // Vérifie si le prochain symbole est un identifiant
        TYPE(1); // Analyse le type de la constante

        // Boucle pour traiter les constantes suivantes tant que le prochain symbole est un identifiant
        while (SYM_COUR.CODE == ID_TOKEN)
        {
            // Redéfinition d'une nouvelle constante en mémoire comme précédemment
            TABLESYM[IND_DER_SYM_ACC].CLASSE = ID_TOKEN;
            strcpy(TABLESYM[IND_DER_SYM_ACC].NOM, SYM_COUR.NOM);
            TABLESYM[IND_DER_SYM_ACC].ADRESSE = ++OFFSET;
            GENERER2(LDA, TABLESYM[IND_DER_SYM_ACC].ADRESSE);

            Sym_Suiv(); // Avance au prochain symbole
            TYPE(1); // Analyse le type de la constante
        };
        break;
    case VAR_TOKEN:
        // Pas d'action spécifique car cette fonction est dédiée à l'analyse des constantes
        break;
    case BEGIN_TOKEN:
        // Pas d'action spécifique car cette fonction est dédiée à l'analyse des constantes
        break;
    default:
        // Erreur si le symbole courant n'est pas une constante, une variable ou le début d'un bloc
        Erreur(CONST_VAR_BEGIN_ERR, "CONSTS");
        break;
    }
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
void Codage_Lex(char mot[20])
{
    int indice_token = -1;
    indice_token = RechercherSym(mot); // Recherche le symbole dans la table des symboles
    if (indice_token != -1) {
        if ((AVANT_BEGIN == 1) && (indice_token > 10)) // Vérifie si nous sommes avant le début du programme et si le symbole est réservé
            ERREUR(DD_ERR); // Génère une erreur de double déclaration
        else {
            SYM_COUR.CLS = TABLESYM[indice_token].CLS; // Stocke la classe du symbole courant
            IND_DER_SYM_ACC = indice_token; // Stocke l'indice du dernier symbole accepté
        }
    }
    else {
        if (AVANT_BEGIN == 1) { // Vérifie si nous sommes avant le début du programme
            SYM_COUR.CLS = ID_TOKEN; // Définit la classe du symbole courant comme un identifiant
            IND_DER_SYM_ACC = index_Mots; // Stocke l'indice du dernier symbole accepté
            AJOUTER(); // Ajoute le symbole à la table des symboles
        }
        else
            ERREUR(ND_ERR); // Génère une erreur de symbole non déclaré
    }
}
*/
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void VARS()
{
    switch (SYM_COUR.CODE)
    {
    case VAR_TOKEN:
        Sym_Suiv(); // Passe au symbole suivant
        Test_Symbole(ID_TOKEN, ID_ERR); // Vérifie si le symbole suivant est un identifiant
        TYPE(0); // Analyse le type de la variable

        while (SYM_COUR.CODE == VIR_TOKEN) // Tant que le symbole suivant est une virgule
        {
            Sym_Suiv(); // Passe au symbole suivant
            Test_Symbole(ID_TOKEN, ID_ERR); // Vérifie si le symbole suivant est un identifiant
            TYPE(0); // Analyse le type de la variable
        }

        Test_Symbole(PV_TOKEN, PV_ERR); // Vérifie si le symbole suivant est un point-virgule
        break;
    case BEGIN_TOKEN:
        break;
    default:
        Erreur(VAR_BEGIN_ERR, "VARS"); // Génère une erreur si le symbole suivant n'est pas conforme à une déclaration de variables
        break;
    }
}

void INSTS()
{
    // begin INST { ; INST } end
    if (SYM_COUR.CODE == BEGIN_TOKEN) // Vérifie si le premier symbole est BEGIN_TOKEN
    {
        Sym_Suiv(); // Passe au symbole suivant
        INST(); // Analyse une instruction

        while (SYM_COUR.CODE == PV_TOKEN) // Tant que le symbole suivant est un point-virgule
        {
            Sym_Suiv(); // Passe au symbole suivant
            INST(); // Analyse une instruction
        }

        if (SYM_COUR.CODE == END_TOKEN) // Vérifie si le symbole suivant est END_TOKEN
        {
            Sym_Suiv(); // Passe au symbole suivant
            printf("Le programme est correcte!\n"); // Affiche un message de succès
        }
        else
        {
            Erreur(FIN_ERR, "INSTS"); // Génère une erreur si le symbole suivant n'est pas conforme à une fin de programme
        }
    }
    else
    {
        Erreur(BEGIN_ERR, "INSTS"); // Génère une erreur si le symbole suivant n'est pas conforme à un début de programme
    }
}

void INST()
{
    // INSTS | AFFEC | SI | TANTQUE | ECRIRE | LIRE | e
    switch (SYM_COUR.CODE)
    {
    case BEGIN_TOKEN:
        INSTS(); // Analyse une séquence d'instructions
        break;
    case ID_TOKEN:
        AFFEC(); // Analyse une affectation
        break;
    case IF_TOKEN:
        SI(); // Analyse une structure SI
        break;
    case WHILE_TOKEN:
        TANTQUE(); // Analyse une boucle TANT QUE
        break;
    case WRITE_TOKEN:
        ECRIRE(); // Analyse une instruction d'écriture
        break;
    case READ_TOKEN:
        LIRE(); // Analyse une instruction de lecture
        break;
    case REPEAT_TOKEN:
        REPETER(); // Analyse une boucle REPEAT
        break;
    case FOR_TOKEN:
        POUR(); // Analyse une boucle POUR
        break;
    case CASE_TOKEN:
        CAS(); // Analyse une structure CASE
        break;
    default:
        break;
    }
}

// Cette fonction analyse une instruction d'affectation
void AFFEC()
{
    // Définir une nouvelle variable en mémoire avec son nom, sa classe et son adresse
    strcpy(TABLESYM[IND_DER_SYM_ACC].NOM, SYM_COUR.NOM);
    TABLESYM[IND_DER_SYM_ACC].CLASSE = ID_TOKEN;
    TABLESYM[IND_DER_SYM_ACC].ADRESSE = ++OFFSET;

    // Empiler l'adresse de la variable pour l'affectation
    GENERER2(LDA, TABLESYM[IND_DER_SYM_ACC].ADRESSE);

    // Vérifier si l'identifiant correspond à une variable et non une constante
    if (TVAR != lastType)
    {
        printf("%s ----> Erreur:  Une constante ne peut changer de valeur dans le programme.", lastIdToken);
        exit(EXIT_FAILURE);
    }

    // Analyser l'expression à affecter à la variable
    Test_Symbole(ID_TOKEN, ID_ERR);
    Test_Symbole(AFF_TOKEN, AFF_ERR);
    EXPR();

    // Stocker la valeur de l'expression dans l'adresse de la variable
    GENERER1(STO);
}

// Cette fonction analyse une structure conditionnelle SI (IF)
void SI()
{
    Test_Symbole(IF_TOKEN, IF_ERR);
    COND(); // Analyser la condition du SI
    GENERER1(BZE); // Générer une instruction de branchement si la condition est fausse
    IND_BZE = PC; // Indiquer l'emplacement de la prochaine instruction après le SI
    Test_Symbole(THEN_TOKEN, THEN_ERR);
    INST(); // Analyser les instructions à exécuter si la condition est vraie
    PCODE[IND_BZE].SUITE = PC + 1; // Indiquer l'emplacement de la prochaine instruction après le SI
    if (SYM_COUR.CODE == ELSE_TOKEN) // Si un ELSE est présent
    {
        INST(); // Analyser les instructions à exécuter si la condition est fausse
    }
}

// Cette fonction analyse une boucle TANT QUE (WHILE)
void TANTQUE()
{
    Test_Symbole(WHILE_TOKEN, WHILE_ERR);
    LABEL_BRN = PC + 1; // Indiquer l'emplacement de la condition pour le branchement
    COND(); // Analyser la condition du TANT QUE
    GENERER1(BZE); // Générer une instruction de branchement si la condition est fausse
    INDICE_BZE = PC; // Indiquer l'emplacement de la prochaine instruction après le TANT QUE
    Test_Symbole(DO_TOKEN, DO_ERR);
    INST(); // Analyser les instructions à exécuter tant que la condition est vraie
    GENERER2(BRN, LABEL_BRN); // Générer une instruction de saut au début de la condition
    PCODE[INDICE_BZE].SUITE = PC + 1; // Indiquer l'emplacement de la prochaine instruction après le TANT QUE
}

// Cette fonction analyse une instruction d'affichage (WRITE)
void ECRIRE()
{
    Test_Symbole(WRITE_TOKEN, WRITE_ERR); // Vérifier si le symbole courant est WRITE_TOKEN
    Test_Symbole(PO_TOKEN, PO_ERR); // Vérifier si le symbole suivant est (
    EXPR(); // Analyser l'expression à afficher
    GENERER1(PRN); // Générer une instruction d'affichage de la valeur de l'expression

    // Tant qu'il y a des virgules après l'expression, analyser et afficher les valeurs des autres expressions
    while (SYM_COUR.CODE == VIR_TOKEN)
    {
        Sym_Suiv();
        EXPR(); // Analyser l'expression suivante
        GENERER1(PRN); // Générer une instruction d'affichage de la valeur de l'expression
    }

    Test_Symbole(PF_TOKEN, PF_ERR); // Vérifier si le symbole suivant est )
}

// Cette fonction analyse une instruction de lecture (READ)
void LIRE()
{
    Test_Symbole(READ_TOKEN, READ_ERR); // Vérifier si le symbole courant est READ_TOKEN
    Test_Symbole(PO_TOKEN, PO_ERR); // Vérifier si le symbole suivant est (

    // Définir une nouvelle variable en mémoire avec son nom, sa classe et son adresse
    strcpy(TABLESYM[IND_DER_SYM_ACC].NOM, SYM_COUR.NOM);
    TABLESYM[IND_DER_SYM_ACC].CLASSE = ID_TOKEN;
    TABLESYM[IND_DER_SYM_ACC].ADRESSE = ++OFFSET;

    // Charger l'adresse de la variable pour la lecture
    GENERER2(LDA, TABLESYM[IND_DER_SYM_ACC].ADRESSE);
    // Lire un entier depuis l'entrée standard et le stocker dans l'adresse de la variable
    GENERER1(INN);

    Test_Symbole(ID_TOKEN, ID_ERR); // Vérifier si le symbole suivant est un identifiant

    // Tant qu'il y a des virgules après l'identifiant, analyser et lire les valeurs dans les autres identifiants
    while (SYM_COUR.CODE == VIR_TOKEN)
    {
        Sym_Suiv();

        // Définir une nouvelle variable en mémoire avec son nom, sa classe et son adresse
        strcpy(TABLESYM[IND_DER_SYM_ACC].NOM, SYM_COUR.NOM);
        TABLESYM[IND_DER_SYM_ACC].CLASSE = ID_TOKEN;
        TABLESYM[IND_DER_SYM_ACC].ADRESSE = ++OFFSET;

        // Charger l'adresse de la variable pour la lecture
        GENERER2(LDA, TABLESYM[IND_DER_SYM_ACC].ADRESSE);
        // Lire un entier depuis l'entrée standard et le stocker dans l'adresse de la variable
        GENERER1(INN);

        Test_Symbole(ID_TOKEN, ID_ERR); // Vérifier si le symbole suivant est un identifiant
    }
    Test_Symbole(PF_TOKEN, PF_ERR); // Vérifier si le symbole suivant est )
}

// Cette fonction analyse une condition (COND)
void COND()
{
    if (SYM_COUR.CODE == BOOLEAN_DATA_TOKEN) // Si le symbole courant est un token de donnée booléenne
    {
        GENERER2(LDI, SYM_COUR.val); // Générer une instruction pour charger la valeur booléenne
        Sym_Suiv(); // Passer au symbole suivant
    }
    else // Sinon, s'il s'agit d'une expression conditionnelle
    {
        EXPR(); // Analyser la première expression
        RELOP(); // Analyser l'opérateur de comparaison
        EXPR(); // Analyser la deuxième expression

        // Générer l'instruction appropriée en fonction de l'opérateur de comparaison
        switch (opRELOP)
        {
        case 1:
            GENERER1(EQL); // Opérateur de comparaison: égalité
            break;
        case 2:
            GENERER1(NEQ); // Opérateur de comparaison: non égalité
            break;
        case 3:
            GENERER1(LSS); // Opérateur de comparaison: inférieur strict
            break;
        case 4:
            GENERER1(GTR); // Opérateur de comparaison: supérieur strict
            break;
        case 5:
            GENERER1(LEQ); // Opérateur de comparaison: inférieur ou égal
            break;
        case 6:
            GENERER1(GEQ); // Opérateur de comparaison: supérieur ou égal
            break;
        default:
            Erreur(ERREUR_ERR, "COND"); // En cas d'erreur, afficher une erreur
            break;
        }
    }
}

// Cette fonction analyse une expression arithmétique (EXPR)
void EXPR()
{
    // TERM { ADDOP TERM }
    TERM(); // Analyser le premier terme de l'expression

    // Tant que le symbole courant est un opérateur d'addition ou de soustraction
    while (SYM_COUR.CODE == PLUS_TOKEN || SYM_COUR.CODE == MOINS_TOKEN)
    {
        ADDOP(); // Analyser l'opérateur d'addition ou de soustraction
        TERM(); // Analyser le terme suivant de l'expression

        // Générer l'instruction appropriée en fonction de l'opérateur d'addition ou de soustraction
        switch (opADDOP)
        {
        case 1:
            GENERER1(ADD); // Opérateur d'addition
            break;
        case 2:
            GENERER1(SUB); // Opérateur de soustraction
            break;
        default:
            Erreur(ERREUR_ERR, "EXPR"); // En cas d'erreur, afficher une erreur
            break;
        }
    }
}

// Cette fonction analyse un terme (TERM)
void TERM()
{
    FACT(); // Analyser le premier facteur

    // Tant que le symbole courant est un opérateur de multiplication ou de division
    while (SYM_COUR.CODE == MULT_TOKEN || SYM_COUR.CODE == DIV_TOKEN)
    {
        MULOP(); // Analyser l'opérateur de multiplication ou de division
        FACT(); // Analyser le facteur suivant

        // Générer l'instruction appropriée en fonction de l'opérateur de multiplication ou de division
        switch (opMULOP)
        {
        case 1:
            GENERER1(MUL); // Opérateur de multiplication
            break;
        case 2:
            GENERER1(DIV); // Opérateur de division
            break;
        default:
            Erreur(ERREUR_ERR, "TERM"); // En cas d'erreur, afficher une erreur
            break;
        }
    }
}

// Cette fonction analyse un facteur (FACT)
void FACT()
{
    switch (SYM_COUR.CODE)
    {
    case ID_TOKEN:
        // Itérer sur la table des symboles pour trouver une correspondance des noms
        for (int i = 0; i < IND_DER_SYM_ACC; i++)
        {
            if (strcmp(TABLESYM[i].NOM, SYM_COUR.NOM) == 0)
            {
                // Empiler l'adresse de la constante ou de la variable trouvée
                GENERER2(LDA, TABLESYM[i].ADRESSE);
                // Remplacer cette adresse par sa valeur
                GENERER1(LDV);
                break;
            }
        }

        Test_Symbole(ID_TOKEN, ID_ERR); // Vérifier le symbole suivant
        break;
    case INTEGER_DATA_TOKEN:
        // Empiler la valeur trouvée
        GENERER2(LDI, SYM_COUR.val);

        Test_Symbole(INTEGER_DATA_TOKEN, INTEGER_DATA_ERR); // Vérifier le symbole suivant
        break;
    case PO_TOKEN:
        Test_Symbole(PO_TOKEN, PO_ERR);
        EXPR(); // Analyser une expression à l'intérieur des parenthèses
        Test_Symbole(PF_TOKEN, PF_ERR);
        break;
    default:
        Erreur(ERREUR_ERR, "FACT"); // En cas d'erreur, afficher une erreur
        break;
    }
}

// Cette fonction analyse un opérateur de comparaison (RELOP)
void RELOP()
{
    switch (SYM_COUR.CODE)
    {
    case EG_TOKEN:
        Test_Symbole(EG_TOKEN, EG_ERR);
        opRELOP = 1; // Opérateur de comparaison: égal
        break;
    case DIFF_TOKEN:
        Test_Symbole(DIFF_TOKEN, DIFF_ERR);
        opRELOP = 2; // Opérateur de comparaison: différent
        break;
    case INF_TOKEN:
        Test_Symbole(INF_TOKEN, INF_ERR);
        opRELOP = 3; // Opérateur de comparaison: inférieur
        break;
    case SUP_TOKEN:
        Test_Symbole(SUP_TOKEN, SUP_ERR);
        opRELOP = 4; // Opérateur de comparaison: supérieur
        break;
    case INFEG_TOKEN:
        Test_Symbole(INFEG_TOKEN, INFEG_ERR);
        opRELOP = 5; // Opérateur de comparaison: inférieur ou égal
        break;
    case SUPEG_TOKEN:
        Test_Symbole(SUPEG_TOKEN, SUPEG_ERR);
        opRELOP = 6; // Opérateur de comparaison: supérieur ou égal
        break;
    default:
        Erreur(ERREUR_ERR, "RELOP"); // En cas d'erreur, afficher une erreur
        break;
    }
}

// Cette fonction analyse un opérateur d'addition ou de soustraction (ADDOP)
void ADDOP()
{
    switch (SYM_COUR.CODE)
    {
    case PLUS_TOKEN:
        Test_Symbole(PLUS_TOKEN, PLUS_ERR);
        opADDOP = 1; // Opérateur d'addition
        break;
    case MOINS_TOKEN:
        Test_Symbole(MOINS_TOKEN, MOINS_ERR);
        opADDOP = 2; // Opérateur de soustraction
        break;
    default:
        Erreur(ERREUR_ERR, "ADDOP"); // En cas d'erreur, afficher une erreur
        break;
    }
}

// Cette fonction analyse un opérateur de multiplication ou de division (MULOP)
void MULOP()
{
    switch (SYM_COUR.CODE)
    {
    case MULT_TOKEN:
        Test_Symbole(MULT_TOKEN, MULT_ERR);
        opMULOP = 1; // Opérateur de multiplication
        break;
    case DIV_TOKEN:
        Test_Symbole(DIV_TOKEN, DIV_ERR);
        opMULOP = 2; // Opérateur de division
        break;
    default:
        Erreur(ERREUR_ERR, "MULOP"); // En cas d'erreur, afficher une erreur
        break;
    }
}

// Cette fonction analyse une boucle POUR (POUR)
void POUR()
{
    Test_Symbole(FOR_TOKEN, FOR_ERR); // Vérifier le token FOR

    // Définir une nouvelle variable en mémoire
    strcpy(TABLESYM[IND_DER_SYM_ACC].NOM, SYM_COUR.NOM);
    TABLESYM[IND_DER_SYM_ACC].CLASSE = ID_TOKEN;
    TABLESYM[IND_DER_SYM_ACC].ADRESSE = ++OFFSET;

    // Empiler l'adresse de cette nouvelle variable pour affectation
    GENERER2(LDA, TABLESYM[IND_DER_SYM_ACC].ADRESSE);

    // ID := EXPR
    Test_Symbole(ID_TOKEN, ID_ERR);
    if (TVAR != lastType)
    {
        printf("%s ----> Erreur: Une constante ne peut changer de valeur dans le programme.", lastIdToken);
        exit(EXIT_FAILURE);
    }
    Test_Symbole(AFF_TOKEN, AFF_ERR);

    Test_Symbole(INTEGER_DATA_TOKEN, INTEGER_DATA_ERR);
    GENERER2(LDI, SYM_COUR.val);
    GENERER1(STO);

    switch (SYM_COUR.CODE)
    {
    case DOWNTO_TOKEN:
        Sym_Suiv();
        opLoop = 1; // Opération de boucle décroissante
        break;
    case INTO_TOKEN:
        Sym_Suiv();
        opLoop = 2; // Opération de boucle croissante
        break;
    default:
        Erreur(ERREUR_ERR, "POUR"); // En cas d'erreur, afficher une erreur
        break;
    }

    // Calcul de la condition de la boucle selon l'opération définie
    if (opLoop == 1)
    {
        GENERER1(ADD);
    }
    else if (opLoop == 2)
    {
        GENERER1(SUB);
    }

    Test_Symbole(INTEGER_DATA_TOKEN, INTEGER_DATA_ERR); // Vérifier le token INTEGER_DATA_TOKEN

    GENERER2(LDI, SYM_COUR.val);
    GENERER1(NEQ);

    GENERER1(BZE); // Branchement conditionnel pour la fin de la boucle
    INDICE_BZE = PC;

    Test_Symbole(DO_TOKEN, DO_ERR); // Vérifier le token DO
    INST(); // Analyser les instructions à l'intérieur de la boucle

    GENERER2(BRN, LABEL_BRN); // Branchement inconditionnel au début de la boucle
    PCODE[INDICE_BZE].SUITE = PC + 1; // Mettre à jour la suite de l'instruction BZE
}

/*  REPEAT_TOKEN,UNTIL_TOKEN,FOR_TOKEN,ELSE_TOKEN,CASE_TOKEN,OF_TOKEN  */

// Cette fonction analyse une boucle REPETER (REPETER)
void REPETER()
{
    Test_Symbole(REPEAT_TOKEN, REPEAT_ERR); // Vérifier le token REPETER
    INST(); // Analyser les instructions à l'intérieur de la boucle
    Test_Symbole(UNTIL_TOKEN, UNTIL_ERR); // Vérifier le token UNTIL
    COND(); // Analyser la condition de sortie de la boucle
}

// Cette fonction analyse une instruction CAS (CAS)
void CAS()
{
    Test_Symbole(CASE_TOKEN, CASE_ERR); // Vérifier le token CASE
    Test_Symbole(ID_TOKEN, ID_ERR); // Vérifier le token ID

    // Vérifier le token OF
    Test_Symbole(OF_TOKEN, OF_TOKEN);

    // Analyser les instructions associées aux valeurs de cas
    Test_Symbole(INTEGER_DATA_TOKEN, INTEGER_DATA_ERR);
    Test_Symbole(DDOT_TOKEN, DDOT_ERR);
    INST();

    // Boucler sur toutes les valeurs de cas
    while (SYM_COUR.CODE == INTEGER_DATA_TOKEN)
    {
        Sym_Suiv();
        Test_Symbole(DDOT_TOKEN, DDOT_ERR);
        INST();
    }

    // Vérifier le token ELSE
    if (SYM_COUR.CODE == ELSE_TOKEN)
    {
        Sym_Suiv();
        INST();
    }

    // Vérifier le token END
    Test_Symbole(END_TOKEN, END_ERR);
}

// Cette fonction sauvegarde le code P dans un fichier (SavePCodeToFile)
void SavePCodeToFile(FILE *FICH_SORTIE);

// Cette fonction sauvegarde le code P dans un fichier (SavePCodeToFile)
void SavePCodeToFile(FILE *FICH_SORTIE)
{
    int i;
    for (i = 0; i <= PC; i++)
    {
        SaveInstToFile(FICH_SORTIE, PCODE[i], i); // Appeler la fonction pour sauvegarder chaque instruction dans le fichier de sortie
    }
}


int main()
{
    FILE *FICH_SORTIE;
    FICH_SORTIE = fopen("pcode.txt", "w"); // Ouvrir le fichier de sortie en mode écriture
    fichier = fopen("C:/Users/HP/Desktop/Mini-Compilateur-Pascal/test.p", "r"); // Ouvrir le fichier source en mode lecture

    if (fichier == NULL)
    {
        perror("Erreur lors de l'ouverture du fichier!"); // Afficher une erreur si l'ouverture du fichier source échoue
        return 1; // Quitter le programme avec un code d'erreur
    }

    // Initialiser TAB_IDFS
    TAB_IDFS = malloc(100 * sizeof(T_TAB_IDF));
    if (TAB_IDFS == NULL)
    {
        perror("Erreur lors de l'allocation de memoire pour TAB_IDFS!"); // Afficher une erreur si l'allocation de mémoire échoue
        return 1; // Quitter le programme avec un code d'erreur
    }

    Lire_Car(); // Lire le premier caractère du fichier source
    Sym_Suiv(); // Analyser le premier symbole

    PROGRAM(); // Analyser le programme principal

    printf("Execution du programme faite.\n"); // Afficher un message indiquant que l'exécution du programme est terminée

    SavePCodeToFile(FICH_SORTIE); // Sauvegarder le code P dans le fichier de sortie
    fclose(FICH_SORTIE); // Fermer le fichier de sortie

    fclose(fichier); // Fermer le fichier source
    free(TAB_IDFS); // Libérer la mémoire allouée pour TAB_IDFS

    return 0; // Terminer le programme avec un code de succès
}