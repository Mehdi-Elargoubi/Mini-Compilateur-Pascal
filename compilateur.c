#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Définition des tailles de table
#define TABLEINDEX 100 // Taille de l'index de la table des symboles
#define TAILLEMEM 100 // Taille de la mémoire
#define TAILLECODE 100 // Taille du code P

// Définition des codes lexicaux
typedef enum
{
    // Tokens lexicaux pour les mots-clés du langage
    ID_TOKEN,               // Identificateur
    PROGRAM_TOKEN,          // Mot-clé 'PROGRAM'
    CONST_TOKEN,            // Mot-clé 'CONST'
    VAR_TOKEN,              // Mot-clé 'VAR'
    BEGIN_TOKEN,            // Mot-clé 'BEGIN'
    END_TOKEN,              // Mot-clé 'END'
    IF_TOKEN,               // Mot-clé 'IF'
    THEN_TOKEN,             // Mot-clé 'THEN'
    WHILE_TOKEN,            // Mot-clé 'WHILE'
    DO_TOKEN,               // Mot-clé 'DO'
    READ_TOKEN,             // Mot-clé 'READ'
    WRITE_TOKEN,            // Mot-clé 'WRITE'
    PV_TOKEN,               // Point-virgule ';'
    PT_TOKEN,               // Point '.'
    PLUS_TOKEN,             // Opérateur '+'
    MOINS_TOKEN,            // Opérateur '-'
    MULT_TOKEN,             // Opérateur '*'
    DIV_TOKEN,              // Opérateur '/'
    VIR_TOKEN,              // Virgule ','
    AFF_TOKEN,              // Opérateur d'affectation ':='
    INF_TOKEN,              // Opérateur de comparaison '<'
    INFEG_TOKEN,            // Opérateur de comparaison '<='
    SUP_TOKEN,              // Opérateur de comparaison '>'
    SUPEG_TOKEN,            // Opérateur de comparaison '>='
    DIFF_TOKEN,             // Opérateur de comparaison '!='
    PO_TOKEN,               // Parenthèse ouvrante '('
    PF_TOKEN,               // Parenthèse fermante ')'
    FIN_TOKEN,              // Fin de fichier
    ERREUR_TOKEN,           // Erreur générale
    EOF_TOKEN,              // Fin de fichier
    EG_TOKEN,               // Opérateur de comparaison '='
    REPEAT_TOKEN,           // Mot-clé 'REPEAT'
    UNTIL_TOKEN,            // Mot-clé 'UNTIL'
    FOR_TOKEN,              // Mot-clé 'FOR'
    ELSE_TOKEN,             // Mot-clé 'ELSE'
    CASE_TOKEN,             // Mot-clé 'CASE'
    OF_TOKEN,               // Mot-clé 'OF'
    INTO_TOKEN,             // Mot-clé 'INTO'
    DOWNTO_TOKEN,           // Mot-clé 'DOWNTO'
    DDOT_TOKEN,             // Double point '..'
    INTEGER_TOKEN,          // Type de données 'INTEGER'
    FLOAT_TOKEN,            // Type de données 'FLOAT'
    BOOLEAN_TOKEN,          // Type de données 'BOOLEAN'
    STRING_TOKEN,           // Type de données 'STRING'
    ARRAY_TOKEN,            // Type de données 'ARRAY'
    INTEGER_DATA_TOKEN,     // Donnée de type 'INTEGER'
    FLOAT_DATA_TOKEN,       // Donnée de type 'FLOAT'
    BOOLEAN_DATA_TOKEN,     // Donnée de type 'BOOLEAN'
    STRING_DATA_TOKEN,      // Donnée de type 'STRING'
    ARRAY_DATA_TOKEN,       // Donnée de type 'ARRAY'
    ERROR_TOKEN,            // Erreur générale
    QMARK_TOKEN,            // Point d'interrogation '?'
    SQUARE_BRACKET_OPEN_TOKEN,  // Crochet ouvrant '['
    SQUARE_BRACKET_CLOSE_TOKEN, // Crochet fermant ']'
    ECRIRE_LN_TOKEN,            // Mot-clé 'ECRIRE_LN'
    READ_LN_TOKEN,              // Mot-clé 'READ_LN'
} CODES_LEX;

// erreur types
typedef enum
{
    // Types d'erreur possibles dans le programme
    ID_ERR,                     // Erreur d'identificateur
    PROGRAM_ERR,                // Erreur de programme
    CONST_ERR,                  // Erreur de constante
    VAR_ERR,                    // Erreur de variable
    BEGIN_ERR,                  // Erreur de bloc 'BEGIN'
    END_ERR,                    // Erreur de bloc 'END'
    IF_ERR,                     // Erreur dans une structure 'IF'
    THEN_ERR,                   // Erreur dans une structure 'THEN'
    WHILE_ERR,                  // Erreur dans une boucle 'WHILE'
    DO_ERR,                     // Erreur dans une boucle 'DO'
    READ_ERR,                   // Erreur dans la fonction 'READ'
    WRITE_ERR,                  // Erreur dans la fonction 'WRITE'
    PV_ERR,                     // Erreur de point-virgule ';'
    PT_ERR,                     // Erreur de point '.'
    PLUS_ERR,                   // Erreur d'opérateur '+'
    MOINS_ERR,                  // Erreur d'opérateur '-'
    MULT_ERR,                   // Erreur d'opérateur '*'
    DIV_ERR,                    // Erreur d'opérateur '/'
    VIR_ERR,                    // Erreur de virgule ','
    AFF_ERR,                    // Erreur d'opérateur d'affectation ':='
    INF_ERR,                    // Erreur d'opérateur de comparaison '<'
    INFEG_ERR,                  // Erreur d'opérateur de comparaison '<='
    SUP_ERR,                    // Erreur d'opérateur de comparaison '>'
    SUPEG_ERR,                  // Erreur d'opérateur de comparaison '>='
    DIFF_ERR,                   // Erreur d'opérateur de comparaison '!='
    PO_ERR,                     // Erreur de parenthèse ouvrante '('
    PF_ERR,                     // Erreur de parenthèse fermante ')'
    FIN_ERR,                    // Erreur de fin de fichier
    ERREUR_ERR,                 // Erreur générale
    EOF_ERR,                    // Erreur de fin de fichier
    EG_ERR,                     // Erreur d'opérateur de comparaison '='
    CONST_VAR_BEGIN_ERR,        // Erreur de déclaration 'CONST/VAR/BEGIN'
    VAR_BEGIN_ERR,              // Erreur de déclaration 'VAR/BEGIN'

    REPEAT_ERR,     // Erreur de boucle 'REPEAT'
    UNTIL_ERR,      // Erreur de condition 'UNTIL'
    FOR_ERR,        // Erreur dans une boucle 'FOR'
    ELSE_ERR,       // Erreur dans la structure 'ELSE'
    CASE_ERR,       // Erreur dans la structure 'CASE'
    OF_ERR,         // Erreur dans la structure 'OF'
    INTO_ERR,       // Erreur dans la structure 'INTO'
    DOWNTO_ERR,     // Erreur dans la structure 'DOWNTO'
    DDOT_ERR,       // Erreur de double point ':'
    INST_PCODE_ERR, // Erreur d'instruction dans le code P
    INTEGER_ERR,    // Erreur dans les données de type 'INTEGER'
    FLOAT_ERR,      // Erreur dans les données de type 'FLOAT'
    BOOLEAN_ERR,    // Erreur dans les données de type 'BOOLEAN'
    STRING_ERR,     // Erreur dans les données de type 'STRING'
    ARRAY_ERR,      // Erreur dans les données de type 'ARRAY'
    INTEGER_DATA_ERR,  // Erreur dans les données de type 'INTEGER'
    FLOAT_DATA_ERR,    // Erreur dans les données de type 'FLOAT'
    BOOLEAN_DATA_ERR,  // Erreur dans les données de type 'BOOLEAN'
    STRING_DATA_ERR,   // Erreur dans les données de type 'STRING'
    ARRAY_DATA_ERR,    // Erreur dans les données de type 'ARRAY'
    QMARK_ERR,         // Erreur de quote '
    SQUARE_BRACKET_OPEN_ERR, // Erreur de crochet ouvrant '['
    SQUARE_BRACKET_CLOSE_ERR,   // Erreur de crochet fermant ']'
    ECRIRE_LN_ERR,              // Erreur dans la fonction 'ECRIRE_LN'
    READ_LN_ERR,                // Erreur dans la fonction 'READ_LN'
} CODES_ERR;

int LOOP_LOGIC = 0; // Variable pour la logique de boucle

// Déclaration de fonctions
void TYPE(int isIntitlized);

const char *getErrorMessage(CODES_ERR error_code);
// Cette fonction renvoie un message d'erreur correspondant à un code d'erreur donné.
const char *getErrorMessage(CODES_ERR error_code)
{
    switch (error_code)
    {
    case ID_ERR:
        return "Identifier error"; // Erreur d'identifiant
    case PROGRAM_ERR:
        return "Program error"; // Erreur de programme
    case CONST_ERR:
        return "Constant error"; // Erreur de constante
    case VAR_ERR:
        return "Variable error"; // Erreur de variable
    case BEGIN_ERR:
        return "Begin error"; // Erreur de début
    case END_ERR:
        return "End error"; // Erreur de fin
    case IF_ERR:
        return "If error"; // Erreur de condition 'IF'
    case THEN_ERR:
        return "Then error"; // Erreur de condition 'THEN'
    case WHILE_ERR:
        return "While error"; // Erreur de boucle 'WHILE'
    case DO_ERR:
        return "Do error"; // Erreur de 'DO'
    case READ_ERR:
        return "Read error"; // Erreur de lecture
    case WRITE_ERR:
        return "Write error"; // Erreur d'écriture
    case PV_ERR:
        return "Semicolon error"; // Erreur de point-virgule
    case PT_ERR:
        return "Period error"; // Erreur de point
    case PLUS_ERR:
        return "Plus error"; // Erreur de plus
    case MOINS_ERR:
        return "Minus error"; // Erreur de moins
    case MULT_ERR:
        return "Multiplication error"; // Erreur de multiplication
    case DIV_ERR:
        return "Division error"; // Erreur de division
    case VIR_ERR:
        return "Comma error"; // Erreur de virgule
    case AFF_ERR:
        return "Assignment error"; // Erreur d'affectation
    case INF_ERR:
        return "Less than error"; // Erreur de inférieur à
    case INFEG_ERR:
        return "Less than or equal to error"; // Erreur de inférieur ou égal à
    case SUP_ERR:
        return "Greater than error"; // Erreur de supérieur à
    case SUPEG_ERR:
        return "Greater than or equal to error"; // Erreur de supérieur ou égal à
    case DIFF_ERR:
        return "Not equal to error"; // Erreur de différent de
    case PO_ERR:
        return "Opening parenthesis error"; // Erreur de parenthèse ouvrante
    case PF_ERR:
        return "Closing parenthesis error"; // Erreur de parenthèse fermante
    case FIN_ERR:
        return "End of file error"; // Erreur de fin de fichier
    case INTEGER_DATA_ERR:
        return "Integer format error"; // Erreur de format entier
    case FLOAT_DATA_ERR:
        return "Float format error"; // Erreur de format flottant
    case BOOLEAN_DATA_ERR:
        return "Boolean format error"; // Erreur de format booléen
    case STRING_DATA_ERR:
        return "String format error"; // Erreur de format de chaîne de caractères
    case ARRAY_DATA_ERR:
        return "Array format error"; // Erreur de format de tableau
    case ERREUR_ERR:
        return "General error"; // Erreur générale
    case EOF_ERR:
        return "End of file error"; // Erreur de fin de fichier
    case EG_ERR:
        return "Equality error"; // Erreur d'égalité
    case CONST_VAR_BEGIN_ERR:
        return "Constant/Variable/Begin declaration error"; // Erreur de déclaration de constante/variable/début
    case VAR_BEGIN_ERR:
        return "Variable/Begin declaration error"; // Erreur de déclaration de variable/début
    case INTEGER_ERR:
        return "Integer error"; // Erreur d'entier
    case FLOAT_ERR:
        return "Float error"; // Erreur de flottant
    case BOOLEAN_ERR:
        return "Boolean error"; // Erreur de booléen
    case STRING_ERR:
        return "String error"; // Erreur de chaîne de caractères
    case ARRAY_ERR:
        return "Array error"; // Erreur de tableau
    case REPEAT_ERR:
        return "Repeat error"; // Erreur de répétition
    case UNTIL_ERR:
        return "Until error"; // Erreur de condition 'UNTIL'
    case FOR_ERR:
        return "For error"; // Erreur de boucle 'FOR'
    case ELSE_ERR:
        return "Else error"; // Erreur dans la structure 'ELSE'
    case CASE_ERR:
        return "Case error"; // Erreur dans la structure 'CASE'
    case OF_ERR:
        return "Of error"; // Erreur dans la structure 'OF'
    case INTO_ERR:
        return "Into error"; // Erreur dans la structure 'INTO'
    case DOWNTO_ERR:
        return "Downto error"; // Erreur dans la structure 'DOWNTO'
    case DDOT_ERR:
        return "Double dot error"; // Erreur de double point '..'
    default:
        return "Unknown error"; // Erreur inconnue
    }
}

// Variable pour activer ou désactiver la lecture
int isReadActivated = 0;

// Structure représentant un symbole courant
typedef struct
{
    CODES_LEX CODE; // Code du symbole
    char NOM[255]; // Nom du symbole
    int val; // Valeur du symbole (le cas échéant)
} TSym_Cour;

TSym_Cour head; // Tête de la liste des symboles courants
TSym_Cour SYM_COUR; // Symbole courant

FILE *fichier; // Pointeur vers le fichier source

char Car_Cour; // Caractère courant

// Types de symboles
typedef enum
{
    TPROG, // Programme
    T_INTEGER_CONST, // Constante entière
    T_INTEGER_VAR, // Variable entière
    T_FLOAT_CONST, // Constante flottante
    T_FLOAT_VAR, // Variable flottante
    T_BOOLEAN_CONST, // Constante booléenne
    T_BOOLEAN_VAR, // Variable booléenne
    T_STRING_CONST, // Constante chaîne de caractères
    T_STRING_VAR, // Variable chaîne de caractères
    T_ARRAY_CONST, // Constante tableau
    T_ARRAY_VAR // Variable tableau
} TSYM;

// Structure représentant un identifiant
typedef struct
{
    TSYM TIDF; // Type de l'identifiant
    char NOM[20]; // Nom de l'identifiant
    int value; // Valeur de l'identifiant (le cas échéant)
} T_TAB_IDF;

T_TAB_IDF *TAB_IDFS; // Tableau des identifiants

int k = 0; // Compteur


// Énumération représentant les différentes régions du programme
typedef enum
{
    RPROG, // Programme principal
    RCONST, // Section des constantes
    RVAR, // Section des variables
    RBEGIN // Section du corps du programme
} Region;

Region current_region = TPROG; // Région courante

// Dernier type rencontré lors de l'analyse syntaxique
TSYM lastType = TPROG;
// Dernier jeton identifiant rencontré lors de l'analyse syntaxique
char lastIdToken[20];

// Structure représentant un symbole
typedef struct
{
    char NOM[20]; // Nom du symbole
    CODES_LEX CLASSE; // Classe du symbole
    int ADRESSE; // Adresse du symbole
} TSYMB;

TSYMB TABLESYM[TABLEINDEX]; // Table des symboles
int IND_DER_SYM_ACC = 0; // Index dans TABLESYM
int OFFSET = -1; // Offset

int MEM[TAILLEMEM]; // Mémoire (Pile de la machine)
int SP; // Pointeur vers le sommet de la pile

// Énumération représentant les différentes instructions de la machine
typedef enum
{
    ADD, // Addition
    SUB, // Soustraction
    MUL, // Multiplication
    DIV, // Division
    EQL, // Égal
    NEQ, // Différent
    GTR, // Supérieur
    LSS, // Inférieur
    GEQ, // Supérieur ou égal
    LEQ, // Inférieur ou égal
    PRN, // Imprimer
    INN, // Lire
    INT, // Initialise SP
    LDI, // Charge la constante
    LDA, // Charge l'adresse
    LDV, // Charge la valeur
    STO, // Stocke la valeur
    BRN, // Branchement inconditionnel
    BZE, // Branchement si zéro
    HLT, // Arrêt
    INF // Instruction invalide
} MNEMONIQUES;


// Structure représentant une instruction de la machine virtuelle
typedef struct
{
    MNEMONIQUES MNE; // Mnémonique de l'instruction
    int SUITE;       // Index de l'instruction suivante
} INSTRUCTION;

INSTRUCTION PCODE[TAILLECODE]; // Programme (Code) de la machine virtuelle

int LABEL_BRN; // Étiquette pour les branchements
int INDICE_BZE; // Indice pour les instructions BZE
int IND_BZE; // Indice pour les instructions BZE
int INDICE_BRN; // Indice pour les instructions BRN

int PC = 0; // Compteur d'instructions

int opRELOP = 0; // Opérateur de comparaison
int opMULOP = 0; // Opérateur de multiplication
int opADDOP = 0; // Opérateur d'addition
int opLoop = 0; // Type de boucle (pour FOR)

// Prototypes des fonctions à utiliser
void VARS(); // Analyse des variables
void INSTS(); // Analyse des instructions
void INST(); // Analyse d'une instruction
void AFFEC(); // Analyse d'une affectation
void SI(); // Analyse d'une structure conditionnelle SI
void TANTQUE(); // Analyse d'une boucle TANTQUE
void ECRIRE(); // Analyse de l'instruction ECRIRE
void LIRE(); // Analyse de l'instruction LIRE
void EXPR(); // Analyse d'une expression
void TERM(); // Analyse d'un terme
void FACT(); // Analyse d'un facteur
void MULOP(); // Analyse d'un opérateur de multiplication
void ADDOP(); // Analyse d'un opérateur d'addition
void RELOP(); // Analyse d'un opérateur de comparaison
void COND(); // Analyse d'une condition
void Lire_Car(); // Lecture d'un caractère
void Erreur(CODES_ERR code, char *origin); // Affichage d'une erreur
void Test_Symbole(CODES_LEX cl, CODES_ERR COD_ERR); // Teste un symbole
void PROGRAM(); // Analyse du programme principal
void BLOCK(); // Analyse d'un bloc
void CONSTS(); // Analyse des constantes
void Sym_Suiv(); // Passage au symbole suivant
void lire_mot(); // Lecture d'un mot
void lire_string(); // Lecture d'une chaîne de caractères
void lire_nombre(); // Lecture d'un nombre
void CAS(); // Analyse de la structure CASE
void POUR(); // Analyse de la boucle POUR
void REPETER(); // Analyse de la boucle REPETER
void Check(); // Vérification

// P CODE section
void GENERER1(MNEMONIQUES M); // Génère une instruction à un seul paramètre
void GENERER2(MNEMONIQUES M, int A); // Génère une instruction à deux paramètres
void SaveInstToFile(FILE *FICH_SORTIE, INSTRUCTION INST, int i); // Sauvegarde une instruction dans un fichier
void INTER_PCODE(); // Interprète le programme P-code
void INTER_INST(INSTRUCTION INST); // Interprète une instruction du P-code

// Définition des fonctions de lecture des chaînes de caractères et des mots

// Lecture d'une chaîne de caractères
void lire_string()
{
    // Taille de la chaîne
    char mot[255];
    int indice = 0;

    // Lecture du premier caractère (guillemet)
    mot[indice++] = Car_Cour;
    Lire_Car();

    // Lecture des caractères suivants jusqu'au prochain guillemet
    while (Car_Cour != '"')
    {
        mot[indice++] = Car_Cour;
        Lire_Car();
    }

    // Ajout du caractère de fin de chaîne
    mot[indice] = '\0';

    // Attribution du code TOKEN pour une chaîne de caractères
    SYM_COUR.CODE = STRING_DATA_TOKEN;

    // Stockage de la chaîne dans le jeton
    strcpy(SYM_COUR.NOM, mot);
}

void lire_mot()
{
    char mot[20]; // Tableau pour stocker le mot lu
    int indice = 0; // Indice pour parcourir le tableau de caractères

    // Lecture du premier caractère (lettre)
    mot[indice++] = Car_Cour;
    Lire_Car(); // Appel à la fonction de lecture du caractère suivant

    // Lecture des caractères suivants (lettres ou chiffres) jusqu'à ce qu'un caractère spécial soit rencontré
    while (isalpha(Car_Cour) || isdigit(Car_Cour))
    {
        mot[indice++] = Car_Cour; // Stockage du caractère dans le tableau
        Lire_Car(); // Appel à la fonction de lecture du caractère suivant
    }

    // Ajout du caractère de fin de chaîne pour former une chaîne de caractères valide
    mot[indice] = '\0';

    // Vérification si le mot est un mot-clé et attribution du code TOKEN correspondant
    if (stricmp(mot, "program") == 0)
    {
        SYM_COUR.CODE = PROGRAM_TOKEN;
    }
    else if (stricmp(mot, "const") == 0)
    {
        SYM_COUR.CODE = CONST_TOKEN;
    }
    else if (stricmp(mot, "var") == 0)
    {
        // Si le mot lu est "var", alors il s'agit d'un jeton VAR_TOKEN
        SYM_COUR.CODE = VAR_TOKEN;
    }
    else if (stricmp(mot, "begin") == 0)
    {
        // Si le mot lu est "begin", alors il s'agit d'un jeton BEGIN_TOKEN
        SYM_COUR.CODE = BEGIN_TOKEN;
    }
    else if (stricmp(mot, "end") == 0)
    {
        // Si le mot lu est "end", alors il s'agit d'un jeton END_TOKEN
        SYM_COUR.CODE = END_TOKEN;
    }
    else if (stricmp(mot, "if") == 0)
    {
        // Si le mot lu est "if", alors il s'agit d'un jeton IF_TOKEN
        SYM_COUR.CODE = IF_TOKEN;
    }
    else if (stricmp(mot, "then") == 0)
    {
        // Si le mot lu est "then", alors il s'agit d'un jeton THEN_TOKEN
        SYM_COUR.CODE = THEN_TOKEN;
    }
    else if (stricmp(mot, "while") == 0)
    {
        // Si le mot lu est "while", alors il s'agit d'un jeton WHILE_TOKEN
        SYM_COUR.CODE = WHILE_TOKEN;
    }
    else if (stricmp(mot, "do") == 0)
    {
        // Si le mot lu est "do", alors il s'agit d'un jeton DO_TOKEN
        SYM_COUR.CODE = DO_TOKEN;
    }
    else if (stricmp(mot, "read") == 0)
    {
        // Si le mot lu est "read", alors il s'agit d'un jeton READ_TOKEN
        SYM_COUR.CODE = READ_TOKEN;
        // Activation de la lecture
        isReadActivated = 1;
    }
    else if (stricmp(mot, "readln") == 0)
    {
        // Si le mot lu est "readln", alors il s'agit d'un jeton READ_LN_TOKEN
        SYM_COUR.CODE = READ_LN_TOKEN;
        // Activation de la lecture
        isReadActivated = 1;
    }
    else if (stricmp(mot, "write") == 0)
    {
        // Si le mot lu est "write", alors il s'agit d'un jeton WRITE_TOKEN
        SYM_COUR.CODE = WRITE_TOKEN;
    }
    else if (stricmp(mot, "writeln") == 0)
    {
        // Si le mot lu est "writeln", alors il s'agit d'un jeton ECRIRE_LN_TOKEN
        SYM_COUR.CODE = ECRIRE_LN_TOKEN;
    }
    else if (stricmp(mot, "else") == 0)
    {
        // Si le mot lu est "else", alors il s'agit d'un jeton ELSE_TOKEN
        SYM_COUR.CODE = ELSE_TOKEN;
    }
    else if (stricmp(mot, "repeat") == 0)
    {
        // Si le mot lu est "repeat", alors il s'agit d'un jeton REPEAT_TOKEN
        SYM_COUR.CODE = REPEAT_TOKEN;
    }
    else if (stricmp(mot, "until") == 0)
    {
        // Si le mot lu est "until", alors il s'agit d'un jeton UNTIL_TOKEN
        SYM_COUR.CODE = UNTIL_TOKEN;
    }
    else if (stricmp(mot, "for") == 0)
    {
        // Si le mot lu est "for", alors il s'agit d'un jeton FOR_TOKEN
        SYM_COUR.CODE = FOR_TOKEN;
    }
    else if (stricmp(mot, "to") == 0)
    {
        // Si le mot lu est "to", alors il s'agit d'un jeton INTO_TOKEN
        SYM_COUR.CODE = INTO_TOKEN;
    }
    else if (stricmp(mot, "case") == 0)
    {
        // Si le mot lu est "case", alors il s'agit d'un jeton CASE_TOKEN
        SYM_COUR.CODE = CASE_TOKEN;
    }
    else if (stricmp(mot, "of") == 0)
    {
        // Si le mot lu est "of", alors il s'agit d'un jeton OF_TOKEN
        SYM_COUR.CODE = OF_TOKEN;
    }
    else if (stricmp(mot, "downto") == 0)
    {
        // Si le mot lu est "downto", alors il s'agit d'un jeton DOWNTO_TOKEN
        SYM_COUR.CODE = DOWNTO_TOKEN;
    }
    else if (stricmp(mot, "integer") == 0)
    {
        // Si le mot lu est "integer", alors il s'agit d'un jeton INTEGER_TOKEN
        SYM_COUR.CODE = INTEGER_TOKEN;
    }
    else if (stricmp(mot, "float") == 0)
    {
        // Si le mot lu est "float", alors il s'agit d'un jeton FLOAT_TOKEN
        SYM_COUR.CODE = FLOAT_TOKEN;
    }
    else if (stricmp(mot, "boolean") == 0)
    {
        // Si le mot lu est "boolean", alors il s'agit d'un jeton BOOLEAN_TOKEN
        SYM_COUR.CODE = BOOLEAN_TOKEN;
    }
    else if (stricmp(mot, "string") == 0)
    {
        // Si le mot lu est "string", alors il s'agit d'un jeton STRING_TOKEN
        SYM_COUR.CODE = STRING_TOKEN;
    }
    else if (stricmp(mot, "array") == 0)
    {
        // Si le mot lu est "array", alors il s'agit d'un jeton ARRAY_TOKEN
        SYM_COUR.CODE = ARRAY_TOKEN;
    }
    else if (stricmp(mot, "true") == 0)
    {
        // Si le mot lu est "true", alors il s'agit d'un jeton BOOLEAN_DATA_TOKEN avec une valeur de 1
        SYM_COUR.CODE = BOOLEAN_DATA_TOKEN;
        SYM_COUR.val = 1;
    }
    else if (stricmp(mot, "false") == 0)
    {
        // Si le mot lu est "false", alors il s'agit d'un jeton BOOLEAN_DATA_TOKEN avec une valeur de 0
        SYM_COUR.CODE = BOOLEAN_DATA_TOKEN;
        SYM_COUR.val = 0;
    }
    else
    {
        // Si le mot n'est pas un mot-clé prédéfini, il s'agit d'un identifiant
        SYM_COUR.CODE = ID_TOKEN;
        // Stockage du mot dans le jeton
        strcpy(SYM_COUR.NOM, mot);
        // Vérification de la validité de l'identifiant
        Check();
    }

    // Stockage du mot dans le jeton si ce n'est pas un ID_TOKEN
    if (SYM_COUR.CODE != ID_TOKEN)
    {
        strcpy(SYM_COUR.NOM, mot);
    }
}

// Cette fonction lit un nombre depuis le flux d'entrée caractère par caractère et le convertit en jeton.
void lire_nombre()
{
    char nombre[32]; // Tableau pour stocker le nombre en tant que chaîne de caractères
    int indice = 0; // Indice de position dans le tableau nombre
    int isFloat = 0; // Variable pour indiquer si le nombre est un flottant

    // Lecture du premier chiffre
    nombre[indice++] = Car_Cour; // Stockage du premier caractère du nombre
    Lire_Car(); // Lecture du caractère suivant

    // Lecture des chiffres suivants et du point décimal (s'il y en a)
    while (isdigit(Car_Cour) || Car_Cour == '.') // Tant que le caractère courant est un chiffre ou un point décimal
    {
        if (Car_Cour == '.') // Si le caractère courant est un point décimal
        {
            isFloat = 1; // Le nombre contient un point, donc c'est un flottant
        }
        nombre[indice++] = Car_Cour; // Stockage du chiffre ou du point décimal dans le tableau nombre
        Lire_Car(); // Lecture du caractère suivant
    }

    // Ajout du caractère de fin de chaîne pour indiquer la fin du nombre
    nombre[indice] = '\0';

    // Stockage du nombre dans le jeton en fonction de son type (entier ou flottant)
    if (isFloat)
    {
        SYM_COUR.CODE = FLOAT_DATA_TOKEN; // Définition du code du jeton comme flottant
        SYM_COUR.val = atof(nombre); // Conversion de la chaîne en flottant et stockage dans le champ val du jeton
    }
    else
    {
        SYM_COUR.CODE = INTEGER_DATA_TOKEN; // Définition du code du jeton comme entier
        SYM_COUR.val = atoi(nombre); // Conversion de la chaîne en entier et stockage dans le champ val du jeton
    }

    strcpy(SYM_COUR.NOM, nombre); // Copie du nombre converti dans le champ NOM du jeton
}


// Cette fonction gère la déclaration des types de variables et effectue les actions associées en fonction du type spécifié.
void TYPE(int isIntitlized)
{ 
    Test_Symbole(DDOT_TOKEN, DDOT_ERR); // Vérifie si le symbole suivant est bien un double point (:), sinon génère une erreur

    switch (SYM_COUR.CODE) // Commence le traitement en fonction du code du symbole courant
    {
    case FLOAT_TOKEN: // Si le type est flottant
        Sym_Suiv(); // Avance au symbole suivant
        if (isIntitlized) // Si la variable est initialisée
        {
            Test_Symbole(EG_TOKEN, EG_ERR); // Vérifie si le symbole suivant est bien un signe égal (=), sinon génère une erreur

            // Empile la valeur lue (correspondant à NUM_TOKEN)
            GENERER2(LDI, SYM_COUR.val); // Génère l'instruction pour charger la valeur dans la mémoire
            GENERER1(STO); // Génère l'instruction pour stocker la valeur dans la mémoire

            IND_DER_SYM_ACC++; // Incrémente l'index dans la table des symboles

            Test_Symbole(FLOAT_DATA_TOKEN, FLOAT_DATA_ERR); // Vérifie si le symbole suivant est bien un flottant, sinon génère une erreur
            Test_Symbole(PV_TOKEN, PV_ERR); // Vérifie si le symbole suivant est bien un point-virgule (;), sinon génère une erreur
        }
        break;
    case INTEGER_TOKEN: // Si le type est entier
        Sym_Suiv(); // Avance au symbole suivant
        if (isIntitlized) // Si la variable est initialisée
        {
            Test_Symbole(EG_TOKEN, EG_ERR); // Vérifie si le symbole suivant est bien un signe égal (=), sinon génère une erreur

            // Empile la valeur lue (correspondant à NUM_TOKEN)
            GENERER2(LDI, SYM_COUR.val); // Génère l'instruction pour charger la valeur dans la mémoire
            GENERER1(STO); // Génère l'instruction pour stocker la valeur dans la mémoire

            IND_DER_SYM_ACC++; // Incrémente l'index dans la table des symboles

            Test_Symbole(INTEGER_DATA_TOKEN, INTEGER_DATA_ERR); // Vérifie si le symbole suivant est bien un entier, sinon génère une erreur
            Test_Symbole(PV_TOKEN, PV_ERR); // Vérifie si le symbole suivant est bien un point-virgule (;), sinon génère une erreur
        }
        break;
    case BOOLEAN_TOKEN: // Si le type est booléen
        Sym_Suiv(); // Avance au symbole suivant
        if (isIntitlized) // Si la variable est initialisée
        {
            Test_Symbole(EG_TOKEN, EG_ERR); // Vérifie si le symbole suivant est bien un signe égal (=), sinon génère une erreur

            GENERER2(LDI, SYM_COUR.val); // Empile la valeur lue (correspondant à NUM_TOKEN)
            GENERER1(STO); // Génère l'instruction pour stocker la valeur dans la mémoire

            IND_DER_SYM_ACC++; // Incrémente l'index dans la table des symboles

            Test_Symbole(BOOLEAN_DATA_TOKEN, BOOLEAN_DATA_ERR); // Vérifie si le symbole suivant est bien un booléen, sinon génère une erreur
            Test_Symbole(PV_TOKEN, PV_ERR); // Vérifie si le symbole suivant est bien un point-virgule (;), sinon génère une erreur
        }
        break;
    case STRING_TOKEN: // Si le type est une chaîne de caractères
        Sym_Suiv(); // Avance au symbole suivant
        if (isIntitlized) // Si la variable est initialisée
        {
            Test_Symbole(EG_TOKEN, EG_ERR); // Vérifie si le symbole suivant est bien un signe égal (=), sinon génère une erreur

            lire_string(); // Appel de la fonction pour lire une chaîne de caractères
            Test_Symbole(STRING_DATA_TOKEN, STRING_DATA_ERR); // Vérifie si le symbole suivant est bien une chaîne de caractères, sinon génère une erreur

            Test_Symbole(QMARK_TOKEN, QMARK_ERR); // Vérifie si le symbole suivant est bien un point d'interrogation (?), sinon génère une erreur
            Test_Symbole(PV_TOKEN, PV_ERR); // Vérifie si le symbole suivant est bien un point-virgule (;), sinon génère une erreur
        }
        break;
    case ARRAY_TOKEN: // Si le type est un tableau
        Sym_Suiv(); // Avance au symbole suivant
        if (isIntitlized) // Si la variable est initialisée
        {
            Test_Symbole(EG_TOKEN, EG_ERR); // Vérifie si le symbole suivant est bien un signe égal (=), sinon génère une erreur

            Test_Symbole(SQUARE_BRACKET_OPEN_TOKEN, SQUARE_BRACKET_OPEN_ERR); // Vérifie si le symbole suivant est bien une parenthèse ouvrante ([), sinon génère une erreur
            Test_Symbole(INTEGER_DATA_TOKEN, INTEGER_DATA_ERR); // Vérifie si le symbole suivant est bien un entier, sinon génère une erreur
            while (SYM_COUR.CODE == VIR_TOKEN) // Tant que le symbole suivant est une virgule (,)
            {
                Sym_Suiv(); // Avance au symbole suivant
                Test_Symbole(INTEGER_DATA_TOKEN, INTEGER_DATA_ERR); // Vérifie si le symbole suivant est bien un entier, sinon génère une erreur
            }
            Test_Symbole(SQUARE_BRACKET_CLOSE_TOKEN, SQUARE_BRACKET_CLOSE_ERR); // Vérifie si le symbole suivant est bien une parenthèse fermante (]), sinon génère une erreur

            // Test_Symbole(ARRAY_DATA_TOKEN, ARRAY_DATA_ERR); // Vérifie si le symbole suivant est bien un jeton de données de tableau, sinon génère une erreur
            Test_Symbole(PV_TOKEN, PV_ERR); // Vérifie si le symbole suivant est bien un point-virgule (;), sinon génère une erreur
        }
        break;
    default: // Si aucun des cas précédents n'est rencontré
        Erreur(VAR_BEGIN_ERR, "VARS"); // Génère une erreur indiquant une déclaration de variable incorrecte
        break;
    }
}


// Cette fonction vérifie la validité des identificateurs déclarés dans le programme et génère des erreurs si nécessaire.
void Check()
{
    int r = 0; // Variable de contrôle pour vérifier si l'identificateur a déjà été déclaré
    int i;

    switch (current_region) // Commence le traitement en fonction de la région courante du programme
    {
    case RPROG: // Si la région courante est la région du programme principal
        for (i = 0; i < k; ++i) // Parcourt la table des identificateurs déclarés
        {
            if (strcmp(SYM_COUR.NOM, TAB_IDFS[i].NOM) == 0) // Vérifie si l'identificateur courant est déjà présent dans la table
            {
                r = 1; // Indique que l'identificateur est déjà présent
                break; // Sort de la boucle
            }
        }

        if (r == 1) // Si l'identificateur est déjà présent dans la table
        {
            if (TPROG == TAB_IDFS[i].TIDF) // Si c'est le nom du programme principal
            {
                printf("%s ----> Erreur:  Le ID du programme ne peut être utilisé dans le programme.", SYM_COUR.NOM); // Affiche une erreur indiquant que le nom du programme principal ne peut pas être utilisé
                exit(EXIT_FAILURE); // Termine le programme avec un code d'erreur
            }
            else
            {
                printf("%s ----> Erreur: PAS DE DOUBLE DECLARATIONS.", SYM_COUR.NOM); // Affiche une erreur indiquant qu'il ne peut y avoir de déclarations en double
                exit(EXIT_FAILURE); // Termine le programme avec un code d'erreur
            }
        }
        strcpy(TAB_IDFS[k].NOM, SYM_COUR.NOM); // Copie le nom de l'identificateur dans la table des identificateurs
        TAB_IDFS[k].TIDF = TPROG; // Affecte le type du symbole à celui du programme principal
        k++; // Incrémente l'indice de la table des identificateurs
        break;

    case RCONST: // Si la région courante est la région des constantes
        for (i = 0; i < k; ++i) // Parcourt la table des identificateurs déclarés
        {
            if (strcmp(SYM_COUR.NOM, TAB_IDFS[i].NOM) == 0) // Vérifie si l'identificateur courant est déjà présent dans la table
            {
                r = 1; // Indique que l'identificateur est déjà présent
                break; // Sort de la boucle
            }
        }

        if (r == 1) // Si l'identificateur est déjà présent dans la table
        {
            if (TPROG == TAB_IDFS[i].TIDF) // Si c'est le nom du programme principal
            {
                printf("%s ----> Erreur:  Le ID du programme ne peut être utilisé dans le programme.", SYM_COUR.NOM); // Affiche une erreur indiquant que le nom du programme principal ne peut pas être utilisé
                exit(EXIT_FAILURE); // Termine le programme avec un code d'erreur
            }
            else
            {
                printf("%s ----> Erreur: PAS DE DOUBLE DECLARATIONS.", SYM_COUR.NOM); // Affiche une erreur indiquant qu'il ne peut y avoir de déclarations en double
                exit(EXIT_FAILURE); // Termine le programme avec un code d'erreur
            }
        }
        else
        {
            strcpy(TAB_IDFS[k].NOM, SYM_COUR.NOM); // Copie le nom de l'identificateur dans la table des identificateurs
            TAB_IDFS[k].TIDF = T_INTEGER_CONST; // Affecte le type du symbole à celui d'une constante entière
            k++; // Incrémente l'indice de la table des identificateurs
        }
        break;

    case RVAR: // Si la région courante est la région des variables
        for (i = 0; i < k; ++i) // Parcourt la table des identificateurs déclarés
        {
            if (strcmp(SYM_COUR.NOM, TAB_IDFS[i].NOM) == 0) // Vérifie si l'identificateur courant est déjà présent dans la table
            {
                r = 1; // Indique que l'identificateur est déjà présent
                break; // Sort de la boucle
            }
        }

        if (r == 1) // Si l'identificateur est déjà présent dans la table
        {
            if (TPROG == TAB_IDFS[i].TIDF) // Si c'est le nom du programme principal
            {
                printf("%s ----> Erreur:  Le ID du programme ne peut être utilisé dans le programme.", SYM_COUR.NOM); // Affiche une erreur indiquant que le nom du programme principal ne peut pas être utilisé
                exit(EXIT_FAILURE); // Termine le programme avec un code d'erreur
            }
            else
            {
                printf("%s ----> Erreur: PAS DE DOUBLE DECLARATIONS.", SYM_COUR.NOM); // Affiche une erreur indiquant qu'il ne peut y avoir de déclarations en double
                exit(EXIT_FAILURE); // Termine le programme avec un code d'erreur
            }
        }
        else
        {
            strcpy(TAB_IDFS[k].NOM, SYM_COUR.NOM); // Copie le nom de l'identificateur dans la table des identificateurs
            TAB_IDFS[k].TIDF = T_INTEGER_VAR; // Affecte le type du symbole à celui d'une variable entière
            k++; // Incrémente l'indice de la table des identificateurs
        }
        break;

    case RBEGIN: // Si la région courante est la région du bloc de code
        for (i = 0; i < k; ++i) // Parcourt la table des identificateurs déclarés
        {
            if (strcmp(SYM_COUR.NOM, TAB_IDFS[i].NOM) == 0) // Vérifie si l'identificateur courant est déjà présent dans la table
            {
                r = 1; // Indique que l'identificateur est déjà présent
                break; // Sort de la boucle
            }
        }

        if (r == 1) // Si l'identificateur est déjà présent dans la table
        {
            if (TPROG == TAB_IDFS[i].TIDF) // Si c'est le nom du programme principal
            {
                printf("%s ----> Erreur:  Le ID du programme ne peut être utilisé dans le programme.", SYM_COUR.NOM); // Affiche une erreur indiquant que le nom du programme principal ne peut pas être utilisé
                exit(EXIT_FAILURE); // Termine le programme avec un code d'erreur
            }
        }
        else
        {
            printf("%s ----> Erreur:  Tous les symboles doivent être déjà déclarés.", SYM_COUR.NOM); // Affiche une erreur indiquant que tous les symboles doivent être déjà déclarés
            exit(EXIT_FAILURE); // Termine le programme avec un code d'erreur
        }

        if (isReadActivated) // Si l'activation de la lecture est activée
        {
            isReadActivated = 0; // Désactive l'activation de la lecture
            if (T_INTEGER_CONST == TAB_IDFS[i].TIDF) // Si le type de l'identificateur est une constante entière
            {
                printf("%s ----> Erreur:  Une constante ne peut changer de valeur dans le programme.", SYM_COUR.NOM); // Affiche une erreur indiquant qu'une constante ne peut changer de valeur
                exit(EXIT_FAILURE); // Termine le programme avec un code d'erreur
            }
        }
        break;

    default:
        break;
    }

    lastType = TAB_IDFS[i].TIDF; // Stocke le dernier type d'identificateur dans une variable globale
    strcpy(lastIdToken, TAB_IDFS[i].NOM); // Copie le nom du dernier identificateur analysé dans une variable globale
}


// Cette fonction lit un caractère à partir du fichier en cours de lecture et le stocke dans la variable globale Car_Cour.
void Lire_Car()
{
    Car_Cour = fgetc(fichier); // Utilise la fonction fgetc() pour lire un caractère à partir du fichier et le stocke dans Car_Cour
}


// Cette fonction analyse le caractère courant (Car_Cour) et détermine le symbole suivant en fonction de ce caractère.

void Sym_Suiv()
{
    // Ignorer les espaces, les sauts de ligne et les tabulations
    while (Car_Cour == ' ' || Car_Cour == '\n' || Car_Cour == '\t')
    {
        Lire_Car(); // Passer au caractère suivant
    }

    // Si le caractère est une lettre, appeler la fonction lire_mot() pour analyser le mot
    if (isalpha(Car_Cour))
    {
        lire_mot();
    }
    // Si le caractère est un chiffre, appeler la fonction lire_nombre() pour analyser le nombre
    else if (isdigit(Car_Cour))
    {
        lire_nombre();
    }
    else
    {
        // Sinon, déterminer le symbole suivant en fonction du caractère courant
        switch (Car_Cour)
        {
        case '#':
            // Gestion du commentaire de type #...#
            Lire_Car(); // Passer au caractère suivant après le #
            while (Car_Cour != '\n')
            {
                Lire_Car(); // Ignorer les caractères du commentaire
            }
            Lire_Car(); // Passer au caractère suivant après le commentaire
            Sym_Suiv(); // Analyser le prochain symbole après le commentaire
            break;
        case '$':
            // Gestion du commentaire de type $...$
            Lire_Car(); // Passer au caractère suivant après le $
            while (Car_Cour != '$')
            {
                Lire_Car(); // Ignorer les caractères du commentaire
            }
            Lire_Car(); // Passer au caractère suivant après le commentaire
            Sym_Suiv(); // Analyser le prochain symbole après le commentaire
            break;
        case ';':
            // Point-virgule
            SYM_COUR.CODE = PV_TOKEN;
            Lire_Car(); // Passer au caractère suivant
            break;
        case '+':
            // Opérateur d'addition
            SYM_COUR.CODE = PLUS_TOKEN;
            Lire_Car(); // Passer au caractère suivant
            break;
        case '-':
            // Opérateur de soustraction
            SYM_COUR.CODE = MOINS_TOKEN;
            Lire_Car(); // Passer au caractère suivant
            break;
        case '*':
            // Opérateur de multiplication
            SYM_COUR.CODE = MULT_TOKEN;
            Lire_Car(); // Passer au caractère suivant
            break;
        case '/':
            // Opérateur de division
            SYM_COUR.CODE = DIV_TOKEN;
            Lire_Car(); // Passer au caractère suivant
            break;
        case ',':
            // Virgule
            SYM_COUR.CODE = VIR_TOKEN;
            Lire_Car(); // Passer au caractère suivant
            break;
        case ':':
            Lire_Car(); // Passer au caractère suivant après le :
            if (Car_Cour == '=')
            {
                // Opérateur d'affectation :=
                SYM_COUR.CODE = AFF_TOKEN;
                Lire_Car(); // Passer au caractère suivant après le =
            }
            else
            {
                // Deux points
                SYM_COUR.CODE = DDOT_TOKEN;
            }
            break;
        case '<':
            Lire_Car(); // Passer au caractère suivant après le <
            if (Car_Cour == '=')
            {
                // Opérateur "inférieur ou égal à" (<=)
                SYM_COUR.CODE = INFEG_TOKEN;
                Lire_Car(); // Passer au caractère suivant après le =
            }
            else if (Car_Cour == '>')
            {
                // Opérateur "différent de" (<>)
                SYM_COUR.CODE = DIFF_TOKEN;
                Lire_Car(); // Passer au caractère suivant après le >
            }
            else
            {
                // Opérateur "inférieur à" (<)
                SYM_COUR.CODE = INF_TOKEN;
            }
            break;
        case '>':
            Lire_Car(); // Passer au caractère suivant après le >
            if (Car_Cour == '=')
            {
                // Opérateur "supérieur ou égal à" (>=)
                SYM_COUR.CODE = SUPEG_TOKEN;
                Lire_Car(); // Passer au caractère suivant après le =
            }
            else
            {
                // Opérateur "supérieur à" (>)
                SYM_COUR.CODE = SUP_TOKEN;
            }
            break;
        case '(':
            // Parenthèse ouvrante
            SYM_COUR.CODE = PO_TOKEN;
            Lire_Car(); // Passer au caractère suivant
            break;
        case '=':
            // Opérateur d'égalité
            SYM_COUR.CODE = EG_TOKEN;
            Lire_Car(); // Passer au caractère suivant
            break;
        case ')':
            // Parenthèse fermante
            SYM_COUR.CODE = PF_TOKEN;
            Lire_Car(); // Passer au caractère suivant
            break;
        case '.':
            // Point
            SYM_COUR.CODE = PT_TOKEN;
            Lire_Car(); // Passer au caractère suivant
            break;
        case '"':
            // Guillemet
            SYM_COUR.CODE = QMARK_TOKEN;
            Lire_Car(); // Passer au caractère suivant
            break;
        case '[':
            // Crochet ouvrant
            SYM_COUR.CODE = SQUARE_BRACKET_OPEN_TOKEN;
            Lire_Car(); // Passer au caractère suivant
            break;
        case ']':
            // Crochet fermant
            SYM_COUR.CODE = SQUARE_BRACKET_CLOSE_TOKEN;
            Lire_Car(); // Passer au caractère suivant
            break;
        case EOF:
            // Fin de fichier
            SYM_COUR.CODE = FIN_TOKEN;
            break;
        default:
            // Si le caractère n'est associé à aucun symbole connu, signaler une erreur
            SYM_COUR.CODE = ERREUR_TOKEN;
            Lire_Car(); // Passer au caractère suivant
        }
        // Copier le caractère courant dans le nom du symbole (peut être utilisé pour les symboles d'un seul caractère)
        strcpy(SYM_COUR.NOM, &Car_Cour);
    }
}


void Erreur(CODES_ERR code, char *origin)
{
    // Affichage de l'erreur syntaxique avec son origine
    printf("Syntaxic error: %s  + origin: %s\n", getErrorMessage(code), origin);
    // Sortie du programme avec un code d'erreur
    exit(EXIT_FAILURE);
}

// Fonctions de génération du P-CODE

void GENERER1(MNEMONIQUES M)
{
    // Vérifier si le compteur de programme atteint la taille maximale
    if (PC == TAILLECODE)
    {
        // Si oui, sortir du programme avec un code d'erreur
        exit(EXIT_FAILURE);
    }
    // Incrémenter le compteur de programme
    PC++;
    // Affecter le mnémonique à la position actuelle du compteur de programme
    PCODE[PC].MNE = M;
}

void GENERER2(MNEMONIQUES M, int A)
{
    // Vérifier si le compteur de programme atteint la taille maximale
    if (PC == TAILLECODE)
    {
        // Si oui, sortir du programme avec un code d'erreur
        exit(EXIT_FAILURE);
    }
    // Incrémenter le compteur de programme
    PC++;
    // Affecter le mnémonique et l'opérande à la position actuelle du compteur de programme
    PCODE[PC].MNE = M;
    PCODE[PC].SUITE = A;
}


//--------------- Interpreteur ---------------//

void SaveInstToFile(FILE *FICH_SORTIE, INSTRUCTION INST, int i)
{
    // Sélection de l'action à effectuer en fonction du mnémonique de l'instruction
    switch (INST.MNE)
    {
    case LDA:
        // Écriture dans le fichier de sortie avec le mnémonique et l'opérande
        fprintf(FICH_SORTIE, "%s \t %d \n", "LDA", INST.SUITE);
        break;
    case LDI:
        fprintf(FICH_SORTIE, "%s \t %d \n", "LDI", INST.SUITE);
        break;
    case INT:
        fprintf(FICH_SORTIE, "%s \t %d \n", "INT", INST.SUITE);
        break;
    case BZE:
        fprintf(FICH_SORTIE, "%s \t %d \n", "BZE", INST.SUITE);
        break;
    case BRN:
        fprintf(FICH_SORTIE, "%s \t %d \n", "BRN", INST.SUITE);
        break;
    case LDV:
        fprintf(FICH_SORTIE, "%s \n", "LDV");
        break;
    case ADD:
        fprintf(FICH_SORTIE, "%s \n", "ADD");
        break;
    case SUB:
        fprintf(FICH_SORTIE, "%s \n", "SUB");
        break;
    case MUL:
        fprintf(FICH_SORTIE, "%s \n", "MUL");
        break;
    case DIV:
        fprintf(FICH_SORTIE, "%s \n", "DIV");
        break;
    case LEQ:
        fprintf(FICH_SORTIE, "%s \n", "LEQ");
        break;
    case GEQ:
        fprintf(FICH_SORTIE, "%s \n", "GEQ");
        break;
    case NEQ:
        fprintf(FICH_SORTIE, "%s \n", "NEQ");
        break;
    case LSS:
        fprintf(FICH_SORTIE, "%s \n", "LSS");
        break;
    case GTR:
        fprintf(FICH_SORTIE, "%s \n", "GTR");
        break;
    case EQL:
        fprintf(FICH_SORTIE, "%s \n", "EQL");
        break;
    case HLT:
        fprintf(FICH_SORTIE, "%s \n", "HLT");
        break;
    case STO:
        fprintf(FICH_SORTIE, "%s \n", "STO");
        break;
    case INN:
        fprintf(FICH_SORTIE, "%s \n", "INN");
        break;
    case PRN:
        fprintf(FICH_SORTIE, "%s \n", "PRN");
        break;

    default:
        // En cas d'instruction non reconnue, afficher une erreur
        Erreur(INST_PCODE_ERR, "SaveInstToFile");
        break;
    }
}

//---------------------------------------------//

void INTER_PCODE()
{
    // Initialisation du compteur de programme
    PC = 0;
    
    // Boucle d'exécution des instructions jusqu'à ce qu'une instruction HLT soit rencontrée
    while (PCODE[PC].MNE != HLT)
        INTER_INST(PCODE[PC]);
}


void INTER_INST(INSTRUCTION INST)
{
    int val1, adr, val2;
    // Sélection de l'action à effectuer en fonction du mnémonique de l'instruction
    switch (INST.MNE)
    {
    // Cas d'une instruction d'allocation de mémoire (INT)
    case INT:
        // Définit la valeur de l'offset et la position du pointeur de pile (SP) à partir de l'opérande de l'instruction
        OFFSET = SP = INST.SUITE;
        // Passe à l'instruction suivante
        PC++;
        break;
    // Cas d'une instruction de chargement d'une constante dans la pile (LDI)
    case LDI:
        // Place la valeur de l'opérande de l'instruction sur la pile
        MEM[++SP] = INST.SUITE;
        // Passe à l'instruction suivante
        PC++;
        break;
    // Cas d'une instruction de chargement d'une adresse dans la pile (LDA)
    case LDA:
        // Place l'adresse de l'opérande de l'instruction sur la pile
        MEM[++SP] = INST.SUITE;
        // Passe à l'instruction suivante
        PC++;
        break;
    // Cas d'une instruction de stockage (STO)
    case STO:
        // Récupère la valeur et l'adresse à partir de la pile
        val1 = MEM[SP--];
        adr = MEM[SP--];
        // Stocke la valeur à l'adresse spécifiée
        MEM[adr] = val1;
        // Passe à l'instruction suivante
        PC++;
        break;
    // Cas d'une instruction de chargement d'une valeur (LDV)
    case LDV:
        // Récupère l'adresse à partir de la pile
        adr = MEM[SP--];
        // Place la valeur située à cette adresse sur la pile
        MEM[++SP] = MEM[adr];
        // Passe à l'instruction suivante
        PC++;
        break;
    // Cas d'une instruction de comparaison d'égalité (EQL)
    case EQL:
        // Récupère deux valeurs à partir de la pile
        val1 = MEM[SP--];
        val2 = MEM[SP--];
        // Place le résultat de la comparaison sur la pile
        MEM[++SP] = (val1 == val2);
        // Passe à l'instruction suivante
        PC++;
        break;
    // Cas d'une instruction de comparaison inférieure ou égal (LEQ)
    case LEQ:
        // Récupère deux valeurs à partir de la pile
        val2 = MEM[SP--];
        val1 = MEM[SP--];
        // Place le résultat de la comparaison sur la pile
        MEM[++SP] = (val1 <= val2);
        // Passe à l'instruction suivante
        PC++;
        break;
    // Cas d'une instruction de comparaison supérieure ou égal (GEQ)
    case GEQ:
        // Récupère deux valeurs à partir de la pile
        val2 = MEM[SP--];
        val1 = MEM[SP--];
        // Place le résultat de la comparaison sur la pile
        MEM[++SP] = (val1 >= val2);
        // Passe à l'instruction suivante
        PC++;
        break;
    // Cas d'une instruction de comparaison inférieure (LSS)
    case LSS:
        // Récupère deux valeurs à partir de la pile
        val2 = MEM[SP--];
        val1 = MEM[SP--];
        // Place le résultat de la comparaison sur la pile
        MEM[++SP] = (val1 < val2);
        // Passe à l'instruction suivante
        PC++;
        break;
    // Cas d'une instruction de comparaison supérieure (GTR)
    case GTR:
        // Récupère deux valeurs à partir de la pile
        val2 = MEM[SP--];
        val1 = MEM[SP--];
        // Place le résultat de la comparaison sur la pile
        MEM[++SP] = (val1 > val2);
        // Passe à l'instruction suivante
        PC++;
        break;
    // Cas d'une instruction de comparaison de non-égalité (NEQ)
    case NEQ:
        // Récupère deux valeurs à partir de la pile
        val2 = MEM[SP--];
        val1 = MEM[SP--];
        // Place le résultat de la comparaison sur la pile
        MEM[++SP] = (val1 != val2);
        // Passe à l'instruction suivante
        PC++;
        break;
    // Cas d'une instruction de lecture d'un entier depuis l'entrée standard (INN)
    case INN:
        // Lit un entier depuis l'entrée standard et le stocke à l'adresse spécifiée par l'opérande de l'instruction
        scanf("%d", &val1);
        adr = MEM[SP--];
        MEM[adr] = val1;
        // Passe à l'instruction suivante
        PC++;
        break;
    // Cas d'une instruction de lecture d'un flottant depuis l'entrée standard (INF)
    case INF:
        // Lit un flottant depuis l'entrée standard et le stocke à l'adresse spécifiée par l'opérande de l'instruction
        scanf("%f", &val1);
        adr = MEM[SP--];
        MEM[adr] = val1;
        // Passe à l'instruction suivante
        PC++;
        break;
    // Cas d'une instruction de saut si zéro (BZE)
    case BZE:
        // Si la valeur au sommet de la pile est égale à zéro, saute à l'instruction spécifiée par l'opérande de l'instruction
        if (MEM[SP--] == 0)
            PC = INST.SUITE;
        else
            // Sinon, passe à l'instruction suivante
            PC++;
        break;
    // Cas d'une instruction de saut inconditionnel (BRN)
    case BRN:
        // Saut inconditionnel à l'instruction spécifiée par l'opérande de l'instruction
        PC = INST.SUITE;
        break;
    // Cas d'une instruction d'arrêt (HLT)
    case HLT:
        // Passe à l'instruction suivante
        PC++;
        break;
    // Cas d'une instruction d'addition (ADD)
    case ADD:
        // Récupère deux valeurs à partir de la pile, les additionne, et place le résultat sur la pile
        val1 = MEM[SP--];
        val2 = MEM[SP--];
        MEM[++SP] = val1 + val2;
        // Passe à l'instruction suivante
        PC++;
        break;
    // Cas d'une instruction de soustraction (SUB)
    case SUB:
        // Récupère deux valeurs à partir de la pile, les soustrait, et place le résultat sur la pile
        val1 = MEM[SP--];
        val2 = MEM[SP--];
        MEM[++SP] = val1 - val2;
        // Passe à l'instruction suivante
        PC++;
        break;
    // Cas d'une instruction de multiplication (MUL)
    case MUL:
        // Récupère deux valeurs à partir de la pile, les multiplie, et place le résultat sur la pile
        val1 = MEM[SP--];
        val2 = MEM[SP--];
        MEM[++SP] = val1 * val2;
        // Passe à l'instruction suivante
        PC++;
        break;
    // Cas d'une instruction de division (DIV)
    case DIV:
        // Récupère deux valeurs à partir de la pile, les divise, et place le résultat sur la pile
        val1 = MEM[SP--];
        val2 = MEM[SP--];
        MEM[++SP] = val1 / val2;
        // Passe à l'instruction suivante
        PC++;
        break;
    // Cas d'une instruction d'affichage (PRN)
    case PRN:
        // Affiche la valeur au sommet de la pile
        printf("%d\n", MEM[SP--]);
        // Passe à l'instruction suivante
        PC++;
        break;
    }

}


void Test_Symbole(CODES_LEX cl, CODES_ERR COD_ERR)
{
    // Vérifie si le symbole courant correspond au code lexial attendu
    if (SYM_COUR.CODE == cl)
    {
        // Avance au symbole suivant
        Sym_Suiv();
    }
    else
        // En cas d'erreur, génère une erreur avec le code d'erreur spécifié
        Erreur(COD_ERR, "Test_Symbole");
}

void PROGRAM()
{
    // Vérifie le symbole de programme et avance au symbole suivant
    Test_Symbole(PROGRAM_TOKEN, PROGRAM_ERR);
    // Définit la région courante comme la région du programme
    current_region = RPROG;
    // Vérifie le symbole d'identificateur et avance au symbole suivant
    Test_Symbole(ID_TOKEN, ID_ERR);
    // Vérifie le point-virgule et avance au symbole suivant
    Test_Symbole(PV_TOKEN, PV_ERR);
    // Appel de la fonction pour traiter le bloc principal
    BLOCK();
    // Génère une instruction d'arrêt (HALT) dans le code P
    GENERER1(HLT);
    // Vérifie le point (.) et avance au symbole suivant
    Test_Symbole(PT_TOKEN, PT_ERR);
}

void BLOCK()
{
    // Définit la région courante comme la région des constantes
    current_region = RCONST;
    // Appel de la fonction pour traiter les constantes
    CONSTS();
    // Définit la région courante comme la région des variables
    current_region = RVAR;
    // Appel de la fonction pour traiter les variables
    VARS();
    // Définit la région courante comme la région du début
    current_region = RBEGIN;
    // Initialise le code P avec une instruction d'allocation de mémoire (INT) et une taille spécifiée
    PCODE[0].MNE = INT;
    PCODE[0].SUITE = 10;
    // Appel de la fonction pour traiter les instructions
    INSTS();
}

//----------------------
void CONSTS()
{
    // Commence par vérifier le type de symbole courant
    switch (SYM_COUR.CODE)
    {
    case CONST_TOKEN:
        // Si le symbole courant est une constante, on avance au prochain symbole
        Sym_Suiv();

        // Définit une nouvelle constante en mémoire avec son adresse
        TABLESYM[IND_DER_SYM_ACC].CLASSE = ID_TOKEN;
        strcpy(TABLESYM[IND_DER_SYM_ACC].NOM, SYM_COUR.NOM);
        TABLESYM[IND_DER_SYM_ACC].ADRESSE = ++OFFSET;

        // Génère une instruction de chargement de l'adresse de la constante
        GENERER2(LDA, TABLESYM[IND_DER_SYM_ACC].ADRESSE);

        // Vérifie le symbole d'identificateur et le type de la constante
        Test_Symbole(ID_TOKEN, ID_ERR);
        TYPE(1);

        // Continue à définir de nouvelles constantes jusqu'à la fin de la liste
        while (SYM_COUR.CODE == ID_TOKEN)
        {
            // Définit une nouvelle constante en mémoire avec son adresse
            TABLESYM[IND_DER_SYM_ACC].CLASSE = ID_TOKEN;
            strcpy(TABLESYM[IND_DER_SYM_ACC].NOM, SYM_COUR.NOM);
            TABLESYM[IND_DER_SYM_ACC].ADRESSE = ++OFFSET;

            // Génère une instruction de chargement de l'adresse de la constante
            GENERER2(LDA, TABLESYM[IND_DER_SYM_ACC].ADRESSE);

            // Avance au prochain symbole et vérifie son type
            Sym_Suiv();
            TYPE(1);
        };
        break;
    case VAR_TOKEN:
        // Cas où il n'y a pas de constantes déclarées, on passe au traitement des variables
        break;
    case BEGIN_TOKEN:
        // Cas où il n'y a pas de constantes ni de variables déclarées, on passe au bloc principal
        break;
    default:
        // En cas d'erreur, génère une erreur avec le code d'erreur spécifié
        Erreur(CONST_VAR_BEGIN_ERR, "CONSTS");
        break;
    }
}

void VARS()
{
    // Commence par vérifier le type de symbole courant
    switch (SYM_COUR.CODE)
    {
    case VAR_TOKEN:
        // Si le symbole courant est une variable, on avance au prochain symbole
        Sym_Suiv();

        // Vérifie le symbole d'identificateur et son type
        Test_Symbole(ID_TOKEN, ID_ERR);
        TYPE(0);

        // Continue à définir de nouvelles variables jusqu'à la fin de la liste
        while (SYM_COUR.CODE == VIR_TOKEN)
        {
            // Avance au prochain symbole
            Sym_Suiv();
            // Vérifie le symbole d'identificateur et son type
            Test_Symbole(ID_TOKEN, ID_ERR);
            TYPE(0);
        }

        // Vérifie le point-virgule indiquant la fin de la déclaration des variables
        Test_Symbole(PV_TOKEN, PV_ERR);
        break;
    case BEGIN_TOKEN:
        // Cas où il n'y a pas de variables déclarées, on passe au bloc principal
        break;
    default:
        // En cas d'erreur, génère une erreur avec le code d'erreur spécifié
        Erreur(VAR_BEGIN_ERR, "VARS");
        break;
    }
}

//----------------------


void INSTS()
{
    // Vérifie si le bloc commence par le mot-clé BEGIN
    if (SYM_COUR.CODE == BEGIN_TOKEN)
    {
        Sym_Suiv(); // Avance au prochain symbole

        // Traite les instructions dans le bloc
        INST();

        // Continue à traiter les instructions séparées par des points-virgules
        while (SYM_COUR.CODE == PV_TOKEN)
        {
            Sym_Suiv(); // Avance au prochain symbole
            INST(); // Traite l'instruction suivante
        }

        // Vérifie si le bloc se termine par le mot-clé END
        if (SYM_COUR.CODE == END_TOKEN)
        {
            Sym_Suiv(); // Avance au prochain symbole
            // Le bloc est terminé avec succès
        }
        else
        {
            // Erreur : le bloc doit se terminer par END
            Erreur(FIN_ERR, "INSTS");
        }
    }
    else
    {
        // Erreur : le bloc doit commencer par BEGIN
        Erreur(BEGIN_ERR, "INSTS");
    }
}

void INST()
{
    // Traite les différentes instructions possibles
    switch (SYM_COUR.CODE)
    {
    case BEGIN_TOKEN:
        // Cas où l'instruction est un bloc d'instructions
        INSTS();
        break;
    case ID_TOKEN:
        // Cas où l'instruction est une affectation
        AFFEC();
        break;
    case IF_TOKEN:
        // Cas où l'instruction est une instruction conditionnelle SI
        SI();
        break;
    case WHILE_TOKEN:
        // Cas où l'instruction est une boucle TANT QUE
        TANTQUE();
        break;
    case ECRIRE_LN_TOKEN:
    case WRITE_TOKEN:
        // Cas où l'instruction est une instruction d'affichage ECRIRE
        ECRIRE();
        break;
    case READ_LN_TOKEN:
    case READ_TOKEN:
        // Cas où l'instruction est une instruction de lecture LIRE
        LIRE();
        break;
    case REPEAT_TOKEN:
        // Cas où l'instruction est une boucle REPETER
        REPETER();
        break;
    case FOR_TOKEN:
        // Cas où l'instruction est une boucle POUR
        POUR();
        break;
    case CASE_TOKEN:
        // Cas où l'instruction est une instruction CASE
        CAS();
        break;
    default:
        break;
    }
}

void AFFEC()
{
    int i;
    int exists = 0;

    // Vérifie si la variable existe déjà dans la table des symboles
    for (i = 0; i < TABLEINDEX; i++)
    {
        if (strcmp(TABLESYM[i].NOM, SYM_COUR.NOM) == 0)
        {
            // Empile l'adresse de la variable trouvée
            GENERER2(LDA, TABLESYM[i].ADRESSE);
            exists = 1;
            break;
        }
    }

    if (!exists)
    {
        // Si la variable n'existe pas, la déclare et lui attribue une adresse
        strcpy(TABLESYM[IND_DER_SYM_ACC].NOM, SYM_COUR.NOM);
        TABLESYM[IND_DER_SYM_ACC].CLASSE = ID_TOKEN;
        TABLESYM[IND_DER_SYM_ACC].ADRESSE = ++OFFSET;
        // Empile l'adresse de la nouvelle variable pour l'affectation
        GENERER2(LDA, TABLESYM[IND_DER_SYM_ACC].ADRESSE);
        IND_DER_SYM_ACC++;
    }

    // Traite l'expression après le signe :=
    Test_Symbole(ID_TOKEN, ID_ERR); // Vérifie le symbole d'identificateur
    if (T_INTEGER_VAR != lastType)
    {
        printf("%s ----> Erreur:  Une constante ne peut changer de valeur dans le programme.", lastIdToken);
        exit(EXIT_FAILURE);
    }
    Test_Symbole(AFF_TOKEN, AFF_ERR); // Vérifie le signe :=
    EXPR(); // Traite l'expression à affecter à la variable
    // Stocke la valeur au sommet de la pile dans l'adresse indiquée au sous-sommet
    GENERER1(STO);
}

void SI()
{
    // Vérifie si le symbole courant est IF
    Test_Symbole(IF_TOKEN, IF_ERR);

    // Traite la condition de l'instruction SI
    COND();

    // Génère une instruction de branchement si la condition est fausse
    GENERER1(BZE);
    IND_BZE = PC;

    // Vérifie si le symbole courant est THEN
    Test_Symbole(THEN_TOKEN, THEN_ERR);

    // Traite l'instruction suivant le THEN
    INST();

    // Génère une instruction de branchement inconditionnel pour sortir du bloc SI
    GENERER1(BRN);
    INDICE_BRN = PC;

    // Met à jour l'instruction de branchement si une clause ELSE est présente
    PCODE[IND_BZE].SUITE = PC + 1;

    // Vérifie si le symbole courant est ELSE
    if (SYM_COUR.CODE == ELSE_TOKEN)
    {
        Sym_Suiv(); // Avance au prochain symbole
        // Traite l'instruction suivant le ELSE
        INST();
        // Met à jour l'instruction de branchement pour sortir du bloc SI
        PCODE[INDICE_BRN].SUITE = PC + 1;
    }
}

void TANTQUE()
{
    // Vérifie si le symbole courant est WHILE
    Test_Symbole(WHILE_TOKEN, WHILE_ERR);

    // Étiquette de branchement pour revenir à la condition du TANTQUE
    LABEL_BRN = PC + 1;

    // Traite la condition de la boucle TANTQUE
    COND();

    // Génère une instruction de branchement si la condition est fausse
    GENERER1(BZE);
    INDICE_BZE = PC;

    // Vérifie si le symbole courant est DO
    Test_Symbole(DO_TOKEN, DO_ERR);

    // Traite les instructions dans la boucle TANTQUE
    INST();

    // Génère une instruction de branchement inconditionnel pour retourner à la condition du TANTQUE
    GENERER2(BRN, LABEL_BRN);

    // Met à jour l'instruction de branchement si la condition est fausse
    PCODE[INDICE_BZE].SUITE = PC + 1;
}

void ECRIRE()
{
    // Avance au prochain symbole (après ECRIRE)
    Sym_Suiv();

    // Vérifie si le symbole courant est (
    Test_Symbole(PO_TOKEN, PO_ERR);

    // Traite l'expression à afficher
    EXPR();

    // Génère une instruction de sortie
    GENERER1(PRN);

    // Traite les autres expressions séparées par des virgules
    while (SYM_COUR.CODE == VIR_TOKEN)
    {
        Sym_Suiv(); // Avance au prochain symbole
        EXPR(); // Traite l'expression suivante
        GENERER1(PRN); // Génère une instruction de sortie pour cette expression
    }

    // Vérifie si le symbole courant est )
    Test_Symbole(PF_TOKEN, PF_ERR);
}

void LIRE()
{
    // Avance au prochain symbole (après LIRE)
    Sym_Suiv();

    // Vérifie si le symbole courant est (
    Test_Symbole(PO_TOKEN, PO_ERR);

    // Parcourt la table des symboles pour trouver les adresses des variables à lire
    int i;
    int exists = 0;
    for (i = 0; i < TABLEINDEX; i++)
    {
        // Si le nom de la variable est trouvé dans la table des symboles
        if (strcmp(TABLESYM[i].NOM, SYM_COUR.NOM) == 0)
        {
            // Empile l'adresse de la variable trouvée
            GENERER2(LDA, TABLESYM[i].ADRESSE);
            exists = 1;
            break;
        }
    }

    // Si la variable n'existe pas, la déclare et lui assigne une adresse
    if (exists == 0)
    {
        strcpy(TABLESYM[IND_DER_SYM_ACC].NOM, SYM_COUR.NOM);
        TABLESYM[IND_DER_SYM_ACC].CLASSE = ID_TOKEN;
        TABLESYM[IND_DER_SYM_ACC].ADRESSE = ++OFFSET;

        GENERER2(LDA, TABLESYM[IND_DER_SYM_ACC].ADRESSE);

        IND_DER_SYM_ACC++;
    }

    // Lit un entier depuis l'entrée standard et le stocke à l'adresse du sommet de la pile
    GENERER1(INN);

    // Vérifie si le symbole courant est un identificateur
    Test_Symbole(ID_TOKEN, ID_ERR);

    // Lit les valeurs des autres variables séparées par des virgules
    while (SYM_COUR.CODE == VIR_TOKEN)
    {
        Sym_Suiv(); // Avance au prochain symbole

        // Parcourt la table des symboles pour trouver les adresses des variables à lire
        int i;
        int exists = 0;
        for (i = 0; i < TABLEINDEX; i++)
        {
            // Si le nom de la variable est trouvé dans la table des symboles
            if (strcmp(TABLESYM[i].NOM, SYM_COUR.NOM) == 0)
            {
                // Empile l'adresse de la variable trouvée
                GENERER2(LDA, TABLESYM[i].ADRESSE);
                exists = 1;
                break;
            }
        }

        // Si la variable n'existe pas, la déclare et lui assigne une adresse
        if (exists == 0)
        {
            strcpy(TABLESYM[IND_DER_SYM_ACC].NOM, SYM_COUR.NOM);
            TABLESYM[IND_DER_SYM_ACC].CLASSE = ID_TOKEN;
            TABLESYM[IND_DER_SYM_ACC].ADRESSE = ++OFFSET;

            GENERER2(LDA, TABLESYM[IND_DER_SYM_ACC].ADRESSE);

            IND_DER_SYM_ACC++;
        }

        // Lit un entier depuis l'entrée standard et le stocke à l'adresse du sommet de la pile
        GENERER1(INN);

        // Vérifie si le symbole courant est un identificateur
        Test_Symbole(ID_TOKEN, ID_ERR);
    }

    // Vérifie si le symbole courant est )
    Test_Symbole(PF_TOKEN, PF_ERR);
}

void COND()
{
    EXPR(); // Évalue la première expression de la condition
    RELOP();// Analyse l'opérateur de comparaison
    EXPR();// Évalue la deuxième expression de la condition

    // Génère les instructions P-CODE correspondantes à l'opérateur de comparaison
    switch (opRELOP)
    {
    case 1: // Opérateur de comparaison '!=' (différent de)
        if (LOOP_LOGIC)
        {
            GENERER1(NEQ);
            LOOP_LOGIC = 0;
        }
        else        
        {
            GENERER1(EQL);
        }
        break;
    case 2: // Opérateur de comparaison '=' (égal à)
        if (LOOP_LOGIC)
        {
            GENERER1(EQL);
            LOOP_LOGIC = 0;
        }
        else
        {
            GENERER1(NEQ);
        }
        break;
    case 3: // Opérateur de comparaison '>=' (supérieur ou égal à)
        if (LOOP_LOGIC)
        {
            GENERER1(GEQ);
            LOOP_LOGIC = 0;
        }
        else
        {
            GENERER1(LSS);
        }
        break;
    case 4: // Opérateur de comparaison '<=' (inférieur ou égal à)
        if (LOOP_LOGIC)
        {
            GENERER1(LEQ);
            LOOP_LOGIC = 0;
        }
        else
        {
            GENERER1(GTR);
        }
        break;
    case 5: // Opérateur de comparaison '>' (strictement supérieur à)
        if (LOOP_LOGIC)
        {
            GENERER1(GTR);
            LOOP_LOGIC = 0;
        }
        else
        {
            GENERER1(LEQ);
        }
        break;
    case 6: // Opérateur de comparaison '<' (strictement inférieur à)
        if (LOOP_LOGIC)
        {
            GENERER1(LSS);
            LOOP_LOGIC = 0;
        }
        else
        {
            GENERER1(GEQ);
        }
        break;
    default: // Erreur si l'opérateur de comparaison est inconnu
        Erreur(ERREUR_ERR, "COND");
        break;
    }
}

void EXPR()
{
    // Évalue le premier terme de l'expression
    TERM();

    // Évalue les opérateurs d'addition ou de soustraction suivis de leurs termes
    while (SYM_COUR.CODE == PLUS_TOKEN || SYM_COUR.CODE == MOINS_TOKEN)
    {
        ADDOP(); // Analyse l'opérateur d'addition ou de soustraction
        TERM();  // Évalue le terme suivant

        // Génère les instructions P-CODE correspondantes à l'opérateur d'addition ou de soustraction
        switch (opADDOP)
        {
        case 1: // Opérateur d'addition '+'
            GENERER1(ADD);
            break;
        case 2: // Opérateur de soustraction '-'
            GENERER1(SUB);
            break;
        default: // Erreur si l'opérateur d'addition ou de soustraction est inconnu
            Erreur(ERREUR_ERR, "EXPR");
            break;
        }
    }
}

void TERM()
{
    FACT();  // Évalue le premier facteur de la expression

    // Évalue les opérateurs de multiplication ou de division suivis de leurs facteurs
    while (SYM_COUR.CODE == MULT_TOKEN || SYM_COUR.CODE == DIV_TOKEN)
    {
        MULOP(); // Analyse l'opérateur de multiplication ou de division
        FACT();  // Évalue le facteur suivant

        // Génère les instructions P-CODE correspondantes à l'opérateur de multiplication ou de division
        switch (opMULOP)
        {
        case 1: // Opérateur de multiplication '*'
            GENERER1(MUL);
            break;
        case 2: // Opérateur de division '/'
            GENERER1(DIV);
            break;
        default: // Erreur si l'opérateur de multiplication ou de division est inconnu
            Erreur(ERREUR_ERR, "TERM");
            break;
        }
    }
}

void FACT()
{
    int i;

    // Itère sur la table des symboles pour trouver une correspondance des noms
    switch (SYM_COUR.CODE)
    {
    case ID_TOKEN:
        // Recherche dans la table des symboles pour trouver l'adresse de la variable
        for (i = 0; i < TABLEINDEX; i++)
        {
            if (strcmp(TABLESYM[i].NOM, SYM_COUR.NOM) == 0)
            {
                // Empile l'adresse de la constante ou de la variable trouvée
                GENERER2(LDA, TABLESYM[i].ADRESSE);
                // Remplace cette adresse par sa valeur
                GENERER1(LDV);
                break;
            }
        }
        Test_Symbole(ID_TOKEN, ID_ERR);
        break;

    case BOOLEAN_DATA_TOKEN:
    case INTEGER_DATA_TOKEN:
        // Empile la valeur trouvée
        GENERER2(LDI, SYM_COUR.val);
        Test_Symbole(SYM_COUR.CODE, SYM_COUR.CODE == BOOLEAN_DATA_TOKEN ? BOOLEAN_DATA_ERR : INTEGER_DATA_ERR);
        break;

    case PO_TOKEN:
        Test_Symbole(PO_TOKEN, PO_ERR);
        EXPR();
        Test_Symbole(PF_TOKEN, PF_ERR);
        break;

    default:
        Erreur(ERREUR_ERR, "FACT");
        break;
    }
}

void RELOP()
{
    // Analyse le symbole courant pour déterminer l'opérateur de comparaison
    switch (SYM_COUR.CODE)
    {
    case EG_TOKEN: // Opérateur d'égalité '=='
        Test_Symbole(EG_TOKEN, EG_ERR); // Vérifie et avance le symbole courant
        opRELOP = 1; // Stocke le code de l'opérateur d'égalité
        break;
    case DIFF_TOKEN: // Opérateur de différence '!='
        Test_Symbole(DIFF_TOKEN, DIFF_ERR); // Vérifie et avance le symbole courant
        opRELOP = 2; // Stocke le code de l'opérateur de différence
        break;
    case INF_TOKEN: // Opérateur d'infériorité '<'
        Test_Symbole(INF_TOKEN, INF_ERR); // Vérifie et avance le symbole courant
        opRELOP = 3; // Stocke le code de l'opérateur d'infériorité
        break;
    case SUP_TOKEN: // Opérateur de supériorité '>'
        Test_Symbole(SUP_TOKEN, SUP_ERR); // Vérifie et avance le symbole courant
        opRELOP = 4; // Stocke le code de l'opérateur de supériorité
        break;
    case INFEG_TOKEN: // Opérateur d'infériorité ou égalité '<='
        Test_Symbole(INFEG_TOKEN, INFEG_ERR); // Vérifie et avance le symbole courant
        opRELOP = 5; // Stocke le code de l'opérateur d'infériorité ou égalité
        break;
    case SUPEG_TOKEN: // Opérateur de supériorité ou égalité '>='
        Test_Symbole(SUPEG_TOKEN, SUPEG_ERR); // Vérifie et avance le symbole courant
        opRELOP = 6; // Stocke le code de l'opérateur de supériorité ou égalité
        break;
    default:
        Erreur(ERREUR_ERR, "RELOP"); // Erreur si le symbole courant ne correspond à aucun opérateur de comparaison
        break;
    }
}

void ADDOP()
{
    // Analyse le symbole courant pour déterminer l'opérateur d'addition ou de soustraction
    switch (SYM_COUR.CODE)
    {
    case PLUS_TOKEN: // Opérateur d'addition '+'
        Test_Symbole(PLUS_TOKEN, PLUS_ERR); // Vérifie et avance le symbole courant
        opADDOP = 1; // Stocke le code de l'opérateur d'addition
        break;
    case MOINS_TOKEN: // Opérateur de soustraction '-'
        Test_Symbole(MOINS_TOKEN, MOINS_ERR); // Vérifie et avance le symbole courant
        opADDOP = 2; // Stocke le code de l'opérateur de soustraction
        break;
    default:
        Erreur(ERREUR_ERR, "ADDOP"); // Erreur si le symbole courant ne correspond à aucun opérateur d'addition ou de soustraction
        break;
    }
}

void MULOP()
{
    // Analyse le symbole courant pour déterminer l'opérateur de multiplication ou de division
    switch (SYM_COUR.CODE)
    {
    case MULT_TOKEN: // Opérateur de multiplication '*'
        Test_Symbole(MULT_TOKEN, MULT_ERR); // Vérifie et avance le symbole courant
        opMULOP = 1; // Stocke le code de l'opérateur de multiplication
        break;
    case DIV_TOKEN: // Opérateur de division '/'
        Test_Symbole(DIV_TOKEN, DIV_ERR); // Vérifie et avance le symbole courant
        opMULOP = 2; // Stocke le code de l'opérateur de division
        break;
    default:
        Erreur(ERREUR_ERR, "MULOP"); // Erreur si le symbole courant ne correspond à aucun opérateur de multiplication ou de division
        break;
    }
}

void POUR()
{
    Test_Symbole(FOR_TOKEN, FOR_ERR); // Vérifie et avance le symbole courant

    // Définir une nouvelle variable en mémoire
    strcpy(TABLESYM[IND_DER_SYM_ACC].NOM, SYM_COUR.NOM);
    TABLESYM[IND_DER_SYM_ACC].CLASSE = ID_TOKEN;
    int offset = ++OFFSET;
    TABLESYM[IND_DER_SYM_ACC].ADRESSE = offset;
    IND_DER_SYM_ACC++;

    // Empiler l'adresse de cette nouvelle variable pour but d'affectation (Voir FACT())
    GENERER2(LDA, offset);

    // ID := EXPR
    Test_Symbole(ID_TOKEN, ID_ERR); // Vérifie et avance le symbole courant
    if (T_INTEGER_VAR != lastType) // Vérifie le type de la variable
    {
        printf("%s ----> Erreur:  Une constante ne peut changer de valeur dans le programme.", lastIdToken);
        exit(EXIT_FAILURE);
    }
    Test_Symbole(AFF_TOKEN, AFF_ERR); // Vérifie et avance le symbole courant

    // Stockage de la valeur initiale
    GENERER2(LDI, SYM_COUR.val);
    GENERER1(STO);

    Test_Symbole(INTEGER_DATA_TOKEN, INTEGER_DATA_ERR); // Vérifie et avance le symbole courant

    // Détermination de l'opération de boucle (DOWNTO ou INTO)
    switch (SYM_COUR.CODE)
    {
    case DOWNTO_TOKEN: // Boucle DECOMPTER
        Sym_Suiv();
        opLoop = 1;
        break;
    case INTO_TOKEN: // Boucle INCREMENTER
        Sym_Suiv();
        opLoop = 2;
        break;
    default:
        Erreur(ERREUR_ERR, "POUR");
        break;
    }

    LABEL_BRN = PC + 1;

    // Générer le code pour vérifier la condition de boucle
    GENERER2(LDA, offset);
    GENERER1(LDV);
    GENERER2(LDI, SYM_COUR.val);
    if (opLoop == 1)
    {
        GENERER2(LDI, -1);
        GENERER1(ADD);
    }
    else if (opLoop == 2)
    {
        GENERER2(LDI, 1);
        GENERER1(ADD);
    }
    GENERER1(NEQ);

    Test_Symbole(INTEGER_DATA_TOKEN, INTEGER_DATA_ERR); // Vérifie et avance le symbole courant

    GENERER1(BZE); // Sauter à la fin de la boucle si la condition n'est pas remplie
    INDICE_BZE = PC;

    Test_Symbole(DO_TOKEN, DO_ERR); // Vérifie et avance le symbole courant

    INST(); // Analyser les instructions à exécuter dans la boucle

    // Mettre à jour la variable de boucle
    GENERER2(LDA, offset);
    GENERER2(LDA, offset); // Double LDA car LDV écrase l'adresse et la remplace par sa valeur
    GENERER1(LDV);
    if (opLoop == 1)
    {
        GENERER2(LDI, -1);
        GENERER1(ADD);
    }
    else if (opLoop == 2)
    {
        GENERER2(LDI, 1);
        GENERER1(ADD);
    }
    GENERER1(STO);

    // Sauter au début de la boucle pour une nouvelle itération
    GENERER2(BRN, LABEL_BRN);

    // Mettre à jour le saut conditionnel avec la nouvelle adresse de la fin de la boucle
    PCODE[INDICE_BZE].SUITE = PC + 1;
}

// REPEAT_TOKEN,UNTIL_TOKEN,FOR_TOKEN,ELSE_TOKEN,CASE_TOKEN,OF_TOKEN
void REPETER()
{
    LOOP_LOGIC = 1; // Indique que la condition est inversée (la boucle s'exécute au moins une fois)
    Test_Symbole(REPEAT_TOKEN, REPEAT_ERR); // Vérifie et avance le symbole courant
    LABEL_BRN = PC + 1; // Stocke l'adresse de départ de la boucle
    INST(); // Analyse et exécute les instructions à l'intérieur de la boucle
    Test_Symbole(UNTIL_TOKEN, UNTIL_ERR); // Vérifie le symbole de fin de boucle
    COND(); // Analyse la condition de sortie de la boucle
    GENERER1(BZE); // Sauter à la fin de la boucle si la condition est remplie
    INDICE_BZE = PC; // Stocke l'adresse actuelle du code généré pour la condition
    GENERER2(BRN, LABEL_BRN); // Sauter au début de la boucle pour une nouvelle itération
    PCODE[INDICE_BZE].SUITE = PC + 1; // Met à jour le saut conditionnel avec la nouvelle adresse de fin de boucle
}

void CAS()
{
    Test_Symbole(CASE_TOKEN, CASE_ERR); // Vérifie et avance le symbole courant
    Test_Symbole(ID_TOKEN, ID_ERR); // Vérifie et avance le symbole courant
    Test_Symbole(OF_TOKEN, OF_TOKEN); // Vérifie et avance le symbole courant
    Test_Symbole(INTEGER_DATA_TOKEN, INTEGER_DATA_ERR); // Vérifie et avance le symbole courant
    Test_Symbole(DDOT_TOKEN, DDOT_ERR); // Vérifie et avance le symbole courant
    INST(); // Analyse et exécute les instructions du cas
    while (SYM_COUR.CODE == INTEGER_DATA_TOKEN) // Tant qu'il y a des valeurs de cas
    {
        Sym_Suiv(); // Avance au symbole suivant
        Test_Symbole(DDOT_TOKEN, DDOT_ERR); // Vérifie et avance le symbole courant
        INST(); // Analyse et exécute les instructions du cas
    }
    if (SYM_COUR.CODE == ELSE_TOKEN) // Si un cas par défaut est défini
    {
        Sym_Suiv(); // Avance au symbole suivant
        INST(); // Analyse et exécute les instructions du cas par défaut
    }
    Test_Symbole(END_TOKEN, END_ERR); // Vérifie et avance le symbole courant
}

// Sauvegarder le code intermédiaire dans un fichier
void SavePCodeToFile(FILE *FICH_SORTIE);
void SavePCodeToFile(FILE *FICH_SORTIE)
{
    int i;
    for (i = 0; i <= PC; i++) // Parcourt tous les éléments du code intermédiaire jusqu'à l'indice PC
    {
        SaveInstToFile(FICH_SORTIE, PCODE[i], i); // Appelle la fonction SaveInstToFile pour sauvegarder chaque instruction dans le fichier de sortie
    }
}

int main()
{
    FILE *FICH_SORTIE; // Déclaration d'un pointeur de fichier pour le fichier de sortie
    FICH_SORTIE = fopen("pcode.txt", "w"); // Ouverture du fichier de sortie en mode écriture
    fichier = fopen("C:/Users/HP/Desktop/Mini-Compilateur-Pascal/test.p", "r"); // Ouverture du fichier source en mode lecture

    if (fichier == NULL)
    {
        perror("Erreur lors de l'ouverture du fichier!"); // Affichage d'une erreur si le fichier source n'a pas pu être ouvert
        return 1; // Quitte le programme avec un code d'erreur
    }

    // Initialisation de TAB_IDFS
    TAB_IDFS = malloc(100 * sizeof(T_TAB_IDF)); // Allocation de mémoire pour la table des identificateurs
    if (TAB_IDFS == NULL)
    {
        perror("Erreur lors de l'allocation de memoire pour TAB_IDFS!"); // Affichage d'une erreur si l'allocation de mémoire a échoué
        return 1; // Quitte le programme avec un code d'erreur
    }

    Lire_Car(); // Lecture du premier caractère du fichier source
    Sym_Suiv(); // Analyse du premier symbole

    PROGRAM(); // Appel de la fonction PROGRAM pour commencer l'analyse syntaxique du programme Pascal

    printf("Le code Pascal a ete compile avec succes!\n"); // Affichage d'un message de réussite de la compilation

    // INTER_PCODE(); // Appel de la fonction pour interpréter le code intermédiaire (décommenter si nécessaire)

    SavePCodeToFile(FICH_SORTIE); // Appel de la fonction pour sauvegarder le code intermédiaire dans le fichier de sortie
    fclose(FICH_SORTIE); // Fermeture du fichier de sortie

    fclose(fichier); // Fermeture du fichier source
    free(TAB_IDFS); // Libération de la mémoire allouée pour la table des identificateurs

    return 0; // Quitte le programme avec un code de succès
}
