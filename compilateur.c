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
