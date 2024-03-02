#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static int ligne_actuelle=1;

// Déclaration des Prototypes des fonctions à utiliser
void VARS();
void INSTS();
void INST();
void AFFEC();
void SI();
void TANTQUE();
void ECRIRE();
void LIRE();
void EXPR();
void TERM();
void FACT();
void MULOP();
void ADDOP();
void RELOP();
void COND();
void Lire_Car();
void PROGRAM();
void BLOCK();
void CONSTS();
void Sym_Suiv();
void lire_mot();
void lire_nombre();
void CAS();
void POUR();
void REPETER();

// Définition des codes lexicaux
typedef enum {
    ID_TOKEN,        // Identificateur
    PROGRAM_TOKEN,   // Mot-clé "program"
    CONST_TOKEN,     // Mot-clé "const"
    VAR_TOKEN,       // Mot-clé "var"
    BEGIN_TOKEN,     // Mot-clé "begin"
    END_TOKEN,       // Mot-clé "end"
    IF_TOKEN,        // Mot-clé "if"
    THEN_TOKEN,      // Mot-clé "then"
    WHILE_TOKEN,     // Mot-clé "while"
    DO_TOKEN,        // Mot-clé "do"
    READ_TOKEN,      // Mot-clé "read"
    WRITE_TOKEN,     // Mot-clé "write"
    PV_TOKEN,        // Point-virgule
    PT_TOKEN,        // Point
    PLUS_TOKEN,      // Opérateur d'addition
    MOINS_TOKEN,     // Opérateur de soustraction
    MULT_TOKEN,      // Opérateur de multiplication
    DIV_TOKEN,       // Opérateur de division
    VIR_TOKEN,       // Virgule
    AFF_TOKEN,       // Opérateur d'affectation
    INF_TOKEN,       // Opérateur de comparaison "inférieur à"
    INFEG_TOKEN,     // Opérateur de comparaison "inférieur ou égal à"
    SUP_TOKEN,       // Opérateur de comparaison "supérieur à"
    SUPEG_TOKEN,     // Opérateur de comparaison "supérieur ou égal à"
    DIFF_TOKEN,      // Opérateur de comparaison "différent de"
    PO_TOKEN,        // Parenthèse ouvrante
    PF_TOKEN,        // Parenthèse fermante
    FIN_TOKEN,       // Fin de programme
    NUM_TOKEN,       // Nombre entier
    ERREUR_TOKEN,    // Token d'erreur
    EOF_TOKEN,       // Fin de fichier
    EG_TOKEN,        // Opérateur de comparaison "égal à"
    REPEAT_TOKEN,    // Mot-clé "repeat"
    UNTIL_TOKEN,     // Mot-clé "until"
    FOR_TOKEN,       // Mot-clé "for"
    ELSE_TOKEN,      // Mot-clé "else"
    CASE_TOKEN,      // Mot-clé "case"
    OF_TOKEN,        // Mot-clé "of"
    INTO_TOKEN,      // Mot-clé "into"
    DOWNTO_TOKEN,    // Mot-clé "downto"
    DDOT_TOKEN       // Deux-points
} CODES_LEX;

// Définition des codes d'erreur
typedef enum {
    ID_ERR,             // Erreur sur l'identificateur
    PROGRAM_ERR,        // Erreur sur le mot-clé "program"
    CONST_ERR,          // Erreur sur le mot-clé "const"
    VAR_ERR,            // Erreur sur le mot-clé "var"
    BEGIN_ERR,          // Erreur sur le mot-clé "begin"
    END_ERR,            // Erreur sur le mot-clé "end"
    IF_ERR,             // Erreur sur le mot-clé "if"
    THEN_ERR,           // Erreur sur le mot-clé "then"
    WHILE_ERR,          // Erreur sur le mot-clé "while"
    DO_ERR,             // Erreur sur le mot-clé "do"
    READ_ERR,           // Erreur sur le mot-clé "read"
    WRITE_ERR,          // Erreur sur le mot-clé "write"
    PV_ERR,             // Erreur sur le point-virgule
    PT_ERR,             // Erreur sur le point
    PLUS_ERR,           // Erreur sur l'opérateur d'addition
    MOINS_ERR,          // Erreur sur l'opérateur de soustraction
    MULT_ERR,           // Erreur sur l'opérateur de multiplication
    DIV_ERR,            // Erreur sur l'opérateur de division
    VIR_ERR,            // Erreur sur la virgule
    AFF_ERR,            // Erreur sur l'opérateur d'affectation
    INF_ERR,            // Erreur sur l'opérateur de comparaison "inférieur à"
    INFEG_ERR,          // Erreur sur l'opérateur de comparaison "inférieur ou égal à"
    SUP_ERR,            // Erreur sur l'opérateur de comparaison "supérieur à"
    SUPEG_ERR,          // Erreur sur l'opérateur de comparaison "supérieur ou égal à"
    DIFF_ERR,           // Erreur sur l'opérateur de comparaison "différent de"
    PO_ERR,             // Erreur sur la parenthèse ouvrante
    PF_ERR,             // Erreur sur la parenthèse fermante
    FIN_ERR,            // Erreur de fin de programme
    NUM_ERR,            // Erreur sur le nombre
    ERREUR_ERR,         // Erreur générique
    EOF_ERR,            // Erreur de fin de fichier eof
    EG_ERR,             // Erreur sur l'opérateur de comparaison "égal à"
    CONST_VAR_BEGIN_ERR,// Erreur de début de déclaration de constantes ou de variables
    VAR_BEGIN_ERR,      // Erreur de début de déclaration de variables
    REPEAT_ERR,         // Erreur sur le mot-clé "repeat"
    UNTIL_ERR,          // Erreur sur le mot-clé "until"
    FOR_ERR,            // Erreur sur le mot-clé "for"
    ELSE_ERR,           // Erreur sur le mot-clé "else"
    CASE_ERR,           // Erreur sur le mot-clé "case"
    OF_ERR,             // Erreur sur le mot-clé "of"
    INTO_ERR,           // Erreur sur le mot-clé "into"
    DOWNTO_ERR,         // Erreur sur le mot-clé "downto"
    DDOT_ERR            // Erreur sur le deux-points
} CODES_ERR;

const char *erreurToString(CODES_ERR code_erreur) {
    switch (code_erreur) {
        case ID_ERR: return "Erreur d'identifiant"; // 1
        case PROGRAM_ERR: return "Erreur de programme PROGRAM"; // 2
        case CONST_ERR: return "Erreur de constante CONST"; // 3
        case VAR_ERR: return "Erreur de VAR"; // 4
        case BEGIN_ERR: return "Erreur dans BEGIN"; // 5
        case END_ERR: return "Erreur dans END"; // 6
        case IF_ERR: return "Erreur de IF"; // 7
        case THEN_ERR: return "Erreur de THEN"; // 8
        case WHILE_ERR: return "Erreur de WHILE"; // 9
        case DO_ERR: return "Erreur de DO"; // 10
        case READ_ERR: return "Erreur de READ"; // 11
        case WRITE_ERR: return "Erreur WRITE"; // 12
        case PV_ERR: return "Erreur de point-virgule PV"; // 13
        case PT_ERR: return "Erreur de point PT"; // 14
        case PLUS_ERR: return "Erreur de PLUS"; // 15
        case MOINS_ERR: return "Erreur de MOINS"; // 16
        case MULT_ERR: return "Erreur de multiplication MULT"; // 17
        case DIV_ERR: return "Erreur de division DIV"; // 18
        case VIR_ERR: return "Erreur de virgule VIR"; // 19
        case AFF_ERR: return "Erreur d'affectation AFF"; // 20
        case INF_ERR: return "Erreur d'inférieur INF"; // 21
        case INFEG_ERR: return "Erreur d'inférieur ou égal INFEG"; // 22
        case SUP_ERR: return "Erreur de supérieur SUP"; // 23
        case SUPEG_ERR: return "Erreur de supérieur ou égal SUPEG"; // 24
        case DIFF_ERR: return "Erreur de différent DIFF"; // 25
        case PO_ERR: return "Erreur de parenthèse ouvrante PO"; // 26
        case PF_ERR: return "Erreur de parenthèse fermante PF"; // 27
        case FIN_ERR: return "Erreur de fin de fichier FIN"; // 28
        case NUM_ERR: return "Erreur de nombre NUM"; // 29
        case ERREUR_ERR: return "Erreur-Generique ERREUR"; // 30
        case EOF_ERR: return "Erreur de fin de fichier EOF"; // 31
        case EG_ERR: return "Erreur d'égalité  EG"; // 32
        case CONST_VAR_BEGIN_ERR: return "Erreur de constante, de variable ou de début CONST_VAR_BRGIN"; // 33
        case VAR_BEGIN_ERR: return "Erreur de variable ou de début VAR_BEGIN"; // 34
        case REPEAT_ERR: return "Erreur de répétition REPEAT"; // 35
        case UNTIL_ERR: return "Erreur de jusqu'à UNTIL"; // 36
        case FOR_ERR: return "Erreur de pour FOR"; // 37
        case ELSE_ERR: return "Erreur de sinon ELSE"; // 38
        case CASE_ERR: return "Erreur de cas CASE"; // 39
        case OF_ERR: return "Erreur de OF"; // 40
        case INTO_ERR: return "Erreur de INTO"; // 41
        case DOWNTO_ERR: return "Erreur de décroissant DOWNTO"; // 42
        case DDOT_ERR: return "Erreur de deux points DDOT"; // 43
        default: return "Erreur inconnue"; // Si le code d'erreur est inconnu
    }
}

// Structure représentant un symbole courant
typedef struct {
    CODES_LEX CODE;   // Code lexical du symbole
    char NOM[20];     // Nom du symbole
    int val;          // Valeur du symbole (si c'est un nombre)
} TSym_Cour;

TSym_Cour head;        // Premier symbole de la liste
TSym_Cour SYM_COUR;    // Symbole courant
FILE * fichier;        // Fichier source
char Car_Cour;         // Caractère courant

// Fonction de lecture d'un mot
void lire_mot() {

    char mot[20];   // Variable pour stocker le mot lu
    int indice = 0; // Indice de la position dans le mot

    mot[indice++] = Car_Cour;  // Stocker le premier caractère du mot
    Lire_Car();                // Lire le caractère suivant

    // Tant que le caractère est une lettre ou un chiffre
    while (isalpha(Car_Cour) || isdigit(Car_Cour)) {
        mot[indice++] = Car_Cour;  // Stocker le caractère dans le mot
        Lire_Car();                // Lire le caractère suivant
    }

    mot[indice] = '\0';  // Terminer le mot avec un caractère nul

    // Identifier le mot et attribuer le bon code lexical
    if (stricmp(mot, "program") == 0) {
        SYM_COUR.CODE = PROGRAM_TOKEN;
    } else if (stricmp(mot, "const") == 0) {
        SYM_COUR.CODE = CONST_TOKEN;
    } else if (stricmp(mot, "var") == 0) {
        SYM_COUR.CODE = VAR_TOKEN;
    } else if (stricmp(mot, "begin") == 0) {
        SYM_COUR.CODE = BEGIN_TOKEN;
    } else if (stricmp(mot, "end") == 0) {
        SYM_COUR.CODE = END_TOKEN;
    } else if (stricmp(mot, "if") == 0) {
        SYM_COUR.CODE = IF_TOKEN;
    } else if (stricmp(mot, "then") == 0) {
        SYM_COUR.CODE = THEN_TOKEN;
    } else if (stricmp(mot, "while") == 0) {
        SYM_COUR.CODE = WHILE_TOKEN;
    } else if (stricmp(mot, "do") == 0) {
        SYM_COUR.CODE = DO_TOKEN;
    } else if (stricmp(mot, "read") == 0) {
        SYM_COUR.CODE = READ_TOKEN;
    } else if (stricmp(mot, "write") == 0) {
        SYM_COUR.CODE = WRITE_TOKEN;
    } else if (stricmp(mot, "else") == 0) {
        SYM_COUR.CODE = ELSE_TOKEN;
    } else if (stricmp(mot, "repeat") == 0) {
        SYM_COUR.CODE = REPEAT_TOKEN;
    } else if (stricmp(mot, "until") == 0) {
        SYM_COUR.CODE = UNTIL_TOKEN;
    } else if (stricmp(mot, "for") == 0) {
        SYM_COUR.CODE = FOR_TOKEN;
    } else if (stricmp(mot, "case") == 0) {
        SYM_COUR.CODE = CASE_TOKEN;
    } else if (stricmp(mot, "of") == 0) {
        SYM_COUR.CODE = OF_TOKEN;
    } else {
        SYM_COUR.CODE = ID_TOKEN;
    }
    strcpy(SYM_COUR.NOM, mot);  // Copier le mot dans le nom du symbole
}

// Fonction de lecture d'un nombre
void lire_nombre() {
    char nombre[11];  // Variable pour stocker le nombre lu
    int indice = 0;   // Indice de la position dans le nombre

    nombre[indice++] = Car_Cour;  // Stocker le premier chiffre du nombre
    Lire_Car();                   // Lire le caractère suivant

    // Tant que le caractère est un chiffre
    while (isdigit(Car_Cour)) {
        nombre[indice++] = Car_Cour;  // Stocker le chiffre dans le nombre
        Lire_Car();                   // Lire le caractère suivant
    }

    nombre[indice] = '\0';  // Terminer le nombre avec un caractère nul

    SYM_COUR.CODE = NUM_TOKEN;         // Attribuer le code lexical NUM_TOKEN
    strcpy(SYM_COUR.NOM, nombre);      // Copier le nombre dans le nom du symbole
    SYM_COUR.val = atoi(SYM_COUR.NOM); // Convertir le nombre en entier et le stocker dans val
}

// Fonction pour passer au symbole suivant
void Sym_Suiv() {
    // Ignorer les espaces, sauts de ligne et tabulations
    while (Car_Cour == ' ' || Car_Cour == '\n' || Car_Cour == '\t') {
        Lire_Car();
    }

    // Si le caractère est une lettre, lire un mot
    if (isalpha(Car_Cour)) {
        lire_mot();
    } 
    // Si le caractère est un chiffre, lire un nombre
    else if (isdigit(Car_Cour)) {
        lire_nombre();
    } 
    // Sinon, identifier le caractère
    else {
        switch (Car_Cour) {
            case ';':
                SYM_COUR.CODE = PV_TOKEN;
                Lire_Car();
                break;
            case '+':
                SYM_COUR.CODE = PLUS_TOKEN;
                Lire_Car();
                break;
            case '-':
                SYM_COUR.CODE = MOINS_TOKEN;
                Lire_Car();
                break;
            case '*':
                SYM_COUR.CODE = MULT_TOKEN;
                Lire_Car();
                break;
            case '/':
                SYM_COUR.CODE = DIV_TOKEN;
                Lire_Car();
                break;
            case ',':
                SYM_COUR.CODE = VIR_TOKEN;
                Lire_Car();
                break;
            case ':':
                Lire_Car();
                if (Car_Cour == '=') {
                    SYM_COUR.CODE = AFF_TOKEN;
                    Lire_Car();
                } else {
                    SYM_COUR.CODE = DDOT_TOKEN;
                }
                break;
            case '<':
                Lire_Car();
                if (Car_Cour == '=') {
                    SYM_COUR.CODE = INFEG_TOKEN;
                    Lire_Car();
                } else if (Car_Cour == '>') {
                    SYM_COUR.CODE = DIFF_TOKEN;
                    Lire_Car();
                } else {
                    SYM_COUR.CODE = INF_TOKEN;
                }
                break;
            case '>':
                Lire_Car();
                if (Car_Cour == '=') {
                    SYM_COUR.CODE = SUPEG_TOKEN;
                    Lire_Car();
                } else {
                    SYM_COUR.CODE = SUP_TOKEN;
                }
                break;
            case '(':
                SYM_COUR.CODE = PO_TOKEN;
                Lire_Car();
                break;
            case '=':
                SYM_COUR.CODE = EG_TOKEN;
                Lire_Car();
                break;
            case ')':
                SYM_COUR.CODE = PF_TOKEN;
                Lire_Car();
                break;
            case '.':
                SYM_COUR.CODE = PT_TOKEN;
                Lire_Car();
                break;
            case EOF:
                SYM_COUR.CODE = FIN_TOKEN;
                break;
            default:
                SYM_COUR.CODE = ERREUR_TOKEN;
                Lire_Car();
        }
        strcpy(SYM_COUR.NOM, &Car_Cour);  // Copier le caractère dans le nom du symbole
    }
}

// Fonction pour lire un caractère du fichier
void Lire_Car() {
    Car_Cour = fgetc(fichier);
        if (Car_Cour == '\n') {
        ligne_actuelle++; // Incrémenter la ligne actuelle lorsque nous rencontrons un saut de ligne
    }
}
// Fonction pour gérer les erreurs
void Erreur(CODES_ERR code) {
    printf("Erreur a la ligne %d: \n", ligne_actuelle); // Affichage de la ligne actuelle

    //afficher_erreur(code);
    printf("\t%s\n", erreurToString(code)); // Utilisation de la fonction erreurToString pour obtenir le nom de l'erreur
    printf("\tCurrent Token: %d\n", SYM_COUR.CODE);
    printf("\tCurrent Lexeme: %s\n", SYM_COUR.NOM);

   // afficher_erreur(code);
    exit(EXIT_FAILURE);  // Terminer le programme avec un code d'erreur
}

// Fonction pour tester si le symbole courant correspond au symbole attendu
void Test_Symbole(CODES_LEX cl, CODES_ERR COD_ERR) {
    if (SYM_COUR.CODE == cl) {
        Sym_Suiv();  // Passer au symbole suivant si le symbole courant correspond
    } else {
        Erreur(COD_ERR);  // Sinon, afficher une erreur
    }
}

// Fonction pour analyser le programme principal
void PROGRAM() {
    Test_Symbole(PROGRAM_TOKEN, PROGRAM_ERR); // Vérifier le symbole PROGRAM
    Test_Symbole(ID_TOKEN, ID_ERR); // Vérifier l'identifiant du programme
    Test_Symbole(PV_TOKEN, PV_ERR); // Vérifier le point-virgule
    BLOCK(); // Appeler la fonction pour traiter le bloc principal
    Test_Symbole(PT_TOKEN, PT_ERR); // Vérifier le point
}

// Fonction pour traiter un bloc de code
void BLOCK() {
    CONSTS(); // Traiter les constantes
    VARS(); // Traiter les variables
    INSTS(); // Traiter les instructions
}

// Fonction pour traiter les constantes
void CONSTS() {
    switch (SYM_COUR.CODE) {
        case CONST_TOKEN:
            Sym_Suiv();
            Test_Symbole(ID_TOKEN, ID_ERR);
            Test_Symbole(EG_TOKEN, EG_ERR);
            Test_Symbole(NUM_TOKEN, NUM_ERR);
            Test_Symbole(PV_TOKEN, PV_ERR);
            // Traiter les autres constantes s'il y en a
            while (SYM_COUR.CODE == ID_TOKEN) {
                Sym_Suiv();
                Test_Symbole(EG_TOKEN, EG_ERR);
                Test_Symbole(NUM_TOKEN, NUM_ERR);
                Test_Symbole(PV_TOKEN, PV_ERR);
            };
            break;
        case VAR_TOKEN:
            break;
        case BEGIN_TOKEN:
            break;
        default:
            Erreur(CONST_VAR_BEGIN_ERR);  // Afficher une erreur si le symbole n'est pas attendu
            break;
    }
}

// Fonction pour traiter les variables
void VARS() {
    switch (SYM_COUR.CODE) {
        case VAR_TOKEN:
            Sym_Suiv();
            Test_Symbole(ID_TOKEN, ID_ERR);
            // Traiter d'autres identifiants séparés par des virgules
            while (SYM_COUR.CODE == VIR_TOKEN) {
                Sym_Suiv();
                Test_Symbole(ID_TOKEN, ID_ERR);
            }
            Test_Symbole(PV_TOKEN, PV_ERR);  // Vérifier le point-virgule à la fin
            break;
        case BEGIN_TOKEN:
            break;
        default:
            Erreur(VAR_BEGIN_ERR);  // Afficher une erreur si le symbole n'est pas attendu
            break;
    }
}

// Fonction pour traiter les instructions
void INSTS() {
    // Vérifier le début des instructions
    if (SYM_COUR.CODE == BEGIN_TOKEN) {
        Sym_Suiv();
        INST();
        // Traiter d'autres instructions séparées par des points-virgules
        while (SYM_COUR.CODE == PV_TOKEN) {
            Sym_Suiv();
            INST();
        }
        // Vérifier la fin des instructions
        if (SYM_COUR.CODE == END_TOKEN) {
            Sym_Suiv();
            printf("Le programme est correct!\n");
        } else {
            Erreur(FIN_ERR);  // Afficher une erreur si le symbole de fin n'est pas trouvé
        }
    } else {
        Erreur(BEGIN_ERR);  // Afficher une erreur si le symbole de début n'est pas trouvé
    }
}

// Fonction pour traiter les différentes instructions
void INST() {
   //INSTS | AFFEC | SI | TANTQUE | ECRIRE | LIRE | e
    switch (SYM_COUR.CODE) {
        case BEGIN_TOKEN:
            INSTS();  // Appeler la fonction pour traiter les instructions
            break;
        case ID_TOKEN:
            AFFEC();  // Appeler la fonction pour l'affectation
            break;
        case IF_TOKEN:
            SI();  // Appeler la fonction pour traiter la structure conditionnelle SI
            break;
        case WHILE_TOKEN:
            TANTQUE();  // Appeler la fonction pour traiter la boucle TANT QUE
            break;
        case WRITE_TOKEN:
            ECRIRE();  // Appeler la fonction pour traiter l'instruction d'écriture
            break;
        case READ_TOKEN:
            LIRE();  // Appeler la fonction pour traiter l'instruction de lecture
            break;
        case REPEAT_TOKEN:
            REPETER();  // Appeler la fonction pour traiter la boucle REPETER
            break;
        case FOR_TOKEN:
            POUR();  // Appeler la fonction pour traiter la boucle POUR
            break;
        case CASE_TOKEN:
            CAS();  // Appeler la fonction pour traiter la structure de contrôle CAS
            break;
        default:
            break;
    }
}

// Fonction pour traiter l'affectation
void AFFEC() {
    // Vérifier l'identifiant suivi de :=  //ID := EXPR
    Test_Symbole(ID_TOKEN, ID_ERR);
    Test_Symbole(AFF_TOKEN, AFF_ERR);
    // Appeler la fonction pour traiter l'expression
    EXPR();
}

// Fonction pour traiter la structure conditionnelle SI
void SI() {
    Test_Symbole(IF_TOKEN, IF_ERR);  // Vérifier le token IF
    COND();  // Appeler la fonction pour traiter la condition
    Test_Symbole(THEN_TOKEN, THEN_ERR);  // Vérifier le token THEN
    INST();  // Appeler la fonction pour traiter l'instruction
    if (SYM_COUR.CODE == ELSE_TOKEN) {  // Vérifier s'il y a une instruction ELSE
        INST();  // Traiter l'instruction ELSE
    }
}

// Fonction pour traiter la boucle TANT QUE
void TANTQUE() {
    Test_Symbole(WHILE_TOKEN, WHILE_ERR);  // Vérifier le token WHILE
    COND();  // Appeler la fonction pour traiter la condition
    Test_Symbole(DO_TOKEN, DO_ERR);  // Vérifier le token DO
    INST();  // Appeler la fonction pour traiter l'instruction
}

// Fonction pour traiter l'instruction d'écriture
void ECRIRE() {
    Test_Symbole(WRITE_TOKEN, WRITE_ERR);  // Vérifier le token WRITE
    Test_Symbole(PO_TOKEN, PO_ERR);  // Vérifier le parenthèse ouvrante
    EXPR();  // Appeler la fonction pour traiter l'expression

    // Traiter d'autres expressions séparées par des virgules
    while (SYM_COUR.CODE == VIR_TOKEN) {
        Sym_Suiv();
        EXPR();
    }

    Test_Symbole(PF_TOKEN, PF_ERR);  // Vérifier le parenthèse fermante
    Test_Symbole(PV_TOKEN, PV_ERR);  // Vérifier le point virgule
}

// Fonction pour traiter l'instruction de lecture
void LIRE() {
    Test_Symbole(READ_TOKEN, READ_ERR);  // Vérifier le token READ
    Test_Symbole(PO_TOKEN, PO_ERR);  // Vérifier le parenthèse ouvrante
    Test_Symbole(ID_TOKEN, ID_ERR);  // Vérifier l'identifiant

    // Traiter d'autres identifiants séparés par des virgules
    while (SYM_COUR.CODE == VIR_TOKEN) {
        Sym_Suiv();
        Test_Symbole(ID_TOKEN, ID_ERR);
    }

    Test_Symbole(PF_TOKEN, PF_ERR);  // Vérifier le parenthèse fermante
    Test_Symbole(PV_TOKEN, PV_ERR);  // Vérifier le point virgule
}

// Fonction pour traiter la condition
void COND() {
    EXPR();  // Appeler la fonction pour traiter l'expression
    RELOP();  // Appeler la fonction pour traiter l'opérateur de relation
    EXPR();  // Appeler la fonction pour traiter l'expression
}

// Fonction pour traiter l'expression
void EXPR() {
    TERM();  // Appeler la fonction pour traiter le terme   //TERM { ADDOP TERM }

    // Traiter d'autres termes avec des opérateurs d'addition ou de soustraction
    while (SYM_COUR.CODE == PLUS_TOKEN || SYM_COUR.CODE == MOINS_TOKEN) {
        ADDOP();  // Appeler la fonction pour traiter l'opérateur d'addition ou de soustraction
        TERM();  // Appeler la fonction pour traiter le terme suivant
    }
}

// Fonction pour traiter un terme
void TERM() {
    FACT();  // Appeler la fonction pour traiter un facteur

    // Traiter d'autres facteurs avec des opérateurs de multiplication ou de division
    while (SYM_COUR.CODE == MULT_TOKEN || SYM_COUR.CODE == DIV_TOKEN) {
        MULOP();  // Appeler la fonction pour traiter l'opérateur de multiplication ou de division
        FACT();  // Appeler la fonction pour traiter le facteur suivant
    }
}

// Fonction pour traiter un facteur
void FACT() {
    switch (SYM_COUR.CODE) {
        case ID_TOKEN:
            Test_Symbole(ID_TOKEN, ID_ERR);  // Vérifier et consommer un identifiant
            break;
        case NUM_TOKEN:
            Test_Symbole(NUM_TOKEN, NUM_ERR);  // Vérifier et consommer un nombre
            break;
        case PO_TOKEN:
            Test_Symbole(PO_TOKEN, PO_ERR);  // Vérifier et consommer une parenthèse ouvrante
            EXPR();  // Appeler la fonction pour traiter une expression
            Test_Symbole(PF_TOKEN, PF_ERR);  // Vérifier et consommer une parenthèse fermante
            break;
        default:
            Erreur(ERREUR_ERR);  // En cas d'erreur, signaler une erreur
            break;
    }
}

// Fonction pour traiter l'opérateur de relation
void RELOP() {
    switch (SYM_COUR.CODE) {
        case EG_TOKEN:
        case DIFF_TOKEN:
        case INF_TOKEN:
        case SUP_TOKEN:
        case INFEG_TOKEN:
        case SUPEG_TOKEN:
            Test_Symbole(EG_TOKEN, EG_ERR);  // Vérifier et consommer un opérateur de relation
            break;
        default:
            Erreur(ERREUR_ERR);  // En cas d'erreur, signaler une erreur
            break;
    }
}

// Fonction pour traiter l'opérateur d'addition
void ADDOP() {
    switch (SYM_COUR.CODE) {
        case PLUS_TOKEN:
            Test_Symbole(PLUS_TOKEN, PLUS_ERR);  // Vérifier et consommer l'opérateur '+'
            break;
        case MOINS_TOKEN:
            Test_Symbole(MOINS_TOKEN, MOINS_ERR);  // Vérifier et consommer l'opérateur '-'
            break;
        default:
            Erreur(ERREUR_ERR);  // En cas d'erreur, signaler une erreur
            break;
    }
}

// Fonction pour traiter l'opérateur de multiplication
void MULOP() {
    switch (SYM_COUR.CODE) {
        case MULT_TOKEN:
            Test_Symbole(MULT_TOKEN, MULT_ERR);  // Vérifier et consommer l'opérateur '*'
            break;
        case DIV_TOKEN:
            Test_Symbole(DIV_TOKEN, DIV_ERR);  // Vérifier et consommer l'opérateur '/'
            break;
        default:
            Erreur(ERREUR_ERR);  // En cas d'erreur, signaler une erreur
            break;
    }
}

// Fonction pour traiter la boucle POUR
void POUR() {
    Test_Symbole(FOR_TOKEN, FOR_ERR);  // Vérifier et consommer le token FOR
    Test_Symbole(ID_TOKEN, ID_ERR);  // Vérifier et consommer un identifiant
    Test_Symbole(AFF_TOKEN, AFF_ERR);  // Vérifier et consommer l'opérateur d'affectation ':='

    // Vérifier et consommer l'opérateur de boucle (DOWNTO ou INTO)
    switch (SYM_COUR.CODE) {
        case DOWNTO_TOKEN:
            Test_Symbole(DOWNTO_TOKEN, DOWNTO_ERR);
            break;
        case INTO_TOKEN:
            Test_Symbole(INTO_TOKEN, INTO_ERR);
            break;
        default:
            Erreur(ERREUR_ERR);  // En cas d'erreur, signaler une erreur
            break;
    }

    Test_Symbole(NUM_TOKEN, NUM_ERR);  // Vérifier et consommer un nombre
    Test_Symbole(DO_TOKEN, DO_ERR);  // Vérifier et consommer le token DO
    INST();  // Appeler la fonction pour traiter une instruction
}

// Fonction pour traiter la boucle REPETER
void REPETER() {
    Test_Symbole(REPEAT_TOKEN, REPEAT_ERR);  // Vérifier et consommer le token REPEAT
    INST();  // Appeler la fonction pour traiter une instruction
    Test_Symbole(UNTIL_TOKEN, UNTIL_ERR);  // Vérifier et consommer le token UNTIL
    COND();  // Appeler la fonction pour traiter une condition
}

// Fonction pour traiter la structure de contrôle CAS
void CAS() {
    Test_Symbole(CASE_TOKEN, CASE_ERR);  // Vérifier et consommer le token CASE
    Test_Symbole(ID_TOKEN, ID_ERR);  // Vérifier et consommer un identifiant
    Test_Symbole(OF_TOKEN, OF_TOKEN);  // Vérifier et consommer le token OF
    Test_Symbole(NUM_TOKEN, NUM_ERR);  // Vérifier et consommer un nombre
    Test_Symbole(DDOT_TOKEN, DDOT_ERR);  // Vérifier et consommer le token DDOT
    INST();  // Appeler la fonction pour traiter une instruction

    // Traiter d'autres instructions pour les mêmes valeurs
    while (SYM_COUR.CODE == NUM_TOKEN) {
        Sym_Suiv();  // Passer au prochain token
        Test_Symbole(DDOT_TOKEN, DDOT_ERR);  // Vérifier et consommer le token DDOT
        INST();  // Appeler la fonction pour traiter une instruction
    }

    // Vérifier s'il y a une clause ELSE
    if (SYM_COUR.CODE == ELSE_TOKEN) {
        Sym_Suiv();  // Passer au prochain token
        INST();  // Appeler la fonction pour traiter une instruction
    }

    Test_Symbole(END_TOKEN, END_ERR);  // Vérifier et consommer le token END
}


int main() {
    // Ouvrir le fichier en mode lecture
    fichier = fopen("C:/Users/HP/Desktop/Mini-Compilateur-Pascal/test.p", "r");
    
    // Vérifier si l'ouverture du fichier a réussi
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier!"); // Afficher un message d'erreur si l'ouverture a échoué
        return 1;  // Quitter le programme avec un code d'erreur
    }
    
    Lire_Car(); // Lire le premier caractère du fichier
    Sym_Suiv(); // Passer au prochain symbole
    
    PROGRAM(); // Appeler la fonction principale pour analyser le programme

    printf("Execution du programme faite.\n");  // Afficher un message indiquant que l'exécution du programme est terminée 
    fclose(fichier); // Fermer le fichier

    return 0;  // Indiquer que le programme s'est terminé avec succès
}