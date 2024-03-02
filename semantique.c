#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Définition des codes lexicaux
typedef enum {
 ID_TOKEN,           // Identificateur
    PROGRAM_TOKEN,      // Mot-clé PROGRAM
    CONST_TOKEN,        // Mot-clé CONST
    VAR_TOKEN,          // Mot-clé VAR
    BEGIN_TOKEN,        // Mot-clé BEGIN
    END_TOKEN,          // Mot-clé END
    IF_TOKEN,           // Mot-clé IF
    THEN_TOKEN,         // Mot-clé THEN
    WHILE_TOKEN,        // Mot-clé WHILE
    DO_TOKEN,           // Mot-clé DO
    READ_TOKEN,         // Mot-clé READ
    WRITE_TOKEN,        // Mot-clé WRITE
    PV_TOKEN,           // Point-virgule
    PT_TOKEN,           // Point
    PLUS_TOKEN,         // Opérateur d'addition
    MOINS_TOKEN,        // Opérateur de soustraction
    MULT_TOKEN,         // Opérateur de multiplication
    DIV_TOKEN,          // Opérateur de division
    VIR_TOKEN,          // Virgule
    AFF_TOKEN,          // Opérateur d'affectation
    INF_TOKEN,          // Opérateur inférieur
    INFEG_TOKEN,        // Opérateur inférieur ou égal
    SUP_TOKEN,          // Opérateur supérieur
    SUPEG_TOKEN,        // Opérateur supérieur ou égal
    DIFF_TOKEN,         // Opérateur de différence
    PO_TOKEN,           // Parenthèse ouvrante
    PF_TOKEN,           // Parenthèse fermante
    FIN_TOKEN,          // Fin de programme
    NUM_TOKEN,          // Nombre
    ERREUR_TOKEN,       // Erreur
    EOF_TOKEN,          // Fin de fichier
    EG_TOKEN,           // Opérateur d'égalité
    REPEAT_TOKEN,       // Mot-clé REPEAT
    UNTIL_TOKEN,        // Mot-clé UNTIL
    FOR_TOKEN,          // Mot-clé FOR
    ELSE_TOKEN,         // Mot-clé ELSE
    CASE_TOKEN,         // Mot-clé CASE
    OF_TOKEN,           // Mot-clé OF
    INTO_TOKEN,         // Mot-clé INTO
    DOWNTO_TOKEN,       // Mot-clé DOWNTO
    DDOT_TOKEN,         // Double point
    TO_TOKEN            // Mot-clé TO
} CODES_LEX;

// Définition des codes d'erreur
typedef enum {
    ID_ERR,             // Erreur d'identificateur
    PROGRAM_ERR,        // Erreur de mot-clé PROGRAM
    CONST_ERR,          // Erreur de mot-clé CONST
    VAR_ERR,            // Erreur de mot-clé VAR
    BEGIN_ERR,          // Erreur de mot-clé BEGIN
    END_ERR,            // Erreur de mot-clé END
    IF_ERR,             // Erreur de mot-clé IF
    THEN_ERR,           // Erreur de mot-clé THEN
    WHILE_ERR,          // Erreur de mot-clé WHILE
    DO_ERR,             // Erreur de mot-clé DO
    READ_ERR,           // Erreur de mot-clé READ
    WRITE_ERR,          // Erreur de mot-clé WRITE
    PV_ERR,             // Erreur de point-virgule
    PT_ERR,             // Erreur de point
    PLUS_ERR,           // Erreur d'opérateur d'addition
    MOINS_ERR,          // Erreur d'opérateur de soustraction
    MULT_ERR,           // Erreur d'opérateur de multiplication
    DIV_ERR,            // Erreur d'opérateur de division
    VIR_ERR,            // Erreur de virgule
    AFF_ERR,            // Erreur d'opérateur d'affectation
    INF_ERR,            // Erreur d'opérateur inférieur
    INFEG_ERR,          // Erreur d'opérateur inférieur ou égal
    SUP_ERR,            // Erreur d'opérateur supérieur
    SUPEG_ERR,          // Erreur d'opérateur supérieur ou égal
    DIFF_ERR,           // Erreur d'opérateur de différence
    PO_ERR,             // Erreur de parenthèse ouvrante
    PF_ERR,             // Erreur de parenthèse fermante
    FIN_ERR,            // Erreur de fin de programme
    NUM_ERR,            // Erreur de nombre
    ERREUR_ERR,         // Erreur générale
    EOF_ERR, // Erreur de fin de fichier (End of File). 
    EG_ERR, // Erreur d'opérateur d'égalité 
    CONST_VAR_BEGIN_ERR, // Erreur liée aux mots-clés `CONST` et `VAR`
    VAR_BEGIN_ERR, // Erreur spécifique au mot-clé `VAR`
    REPEAT_ERR, // Erreur liée au mot-clé `REPEAT`
    UNTIL_ERR, // Erreur liée au mot-clé `UNTIL`
    FOR_ERR, // Erreur liée au mot-clé `FOR`
    ELSE_ERR, // Erreur liée au mot-clé `ELSE`
    CASE_ERR, // Erreur liée au mot-clé `CASE`
    OF_ERR, // Erreur liée au mot-clé `OF` dans une structure `CASE`
    INTO_ERR, // Erreur liée au mot-clé `INTO`
    DOWNTO_ERR, // Erreur liée au mot-clé `DOWNTO` dans une boucle `FOR`
    DDOT_ERR, // Erreur liée au double point (`..`)
} CODES_ERR;

// Structure pour stocker le symbole courant
typedef struct {
    CODES_LEX CODE;     // Code lexical (par exemple, ID_TOKEN, PROGRAM_TOKEN, etc.)
    char NOM[20];       // Nom de l'identificateur ou du mot-clé
    int val;            // Valeur associée (utilisée pour les nombres)
} TSym_Cour;

// Variables globales
TSym_Cour SYM_COUR;    // Symbole courant
FILE *fichier;         // Fichier source
char Car_Cour;         // Caractère courant

// Fonction pour lire le caractère suivant dans le fichier source
void Lire_Car();

// Fonction pour mettre à jour le symbole courant
void Sym_Suiv();

// Fonctions pour la reconnaissance des mots et des nombres
void lire_mot();
void lire_nombre();

// Fonction pour gérer la table des identificateurs
void table_id();

// Fonctions pour stocker les différents types de symboles
void store_prog();     // Stocker le programme
void store_const();    // Stocker les constantes
void store_var();      // Stocker les variables

// Fonction pour afficher le symbole courant
void affich();

// Règles de vérification syntaxique
void regle1();         // Vérification de la structure du programme
void check();          // Vérification des règles spécifiques
void regle2();         // Vérification des affectations
void regle3();         // Vérification des expressions conditionnelles
void regle4();         // Vérification des boucles
void regle5();         // Vérification des instructions de lecture et d'écriture

// Definition des fonctions à utiliser
void lire_mot()
{
    // Tableau pour stocker le mot courant
    char mot[20];
    int indice = 0;

    // Lecture du premier caractère (lettre)
    mot[indice++] = Car_Cour;
    Lire_Car();

    // Lecture des caractères suivants (lettres ou chiffres)
    while (isalpha(Car_Cour) || isdigit(Car_Cour))
    {
        mot[indice++] = Car_Cour;
        Lire_Car();
    }

    // Ajout du caractère de fin de chaîne
    mot[indice] = '\0';

    // Vérification si le mot est un mot-clé
    if (stricmp(mot, "program") == 0)
    {
        // Si le mot est "program", attribuer le code PROGRAM_TOKEN au jeton courant
        SYM_COUR.CODE = PROGRAM_TOKEN;
    }
    else if (stricmp(mot, "const") == 0)
    {
        // Si le mot est "const", attribuer le code CONST_TOKEN au jeton courant
        SYM_COUR.CODE = CONST_TOKEN;
    }
    else if (stricmp(mot, "var") == 0)
    {
        // Si le mot est "var", attribuer le code VAR_TOKEN au jeton courant
        SYM_COUR.CODE = VAR_TOKEN;
    }
    else if (stricmp(mot, "begin") == 0)
    {
        // Si le mot est "begin", attribuer le code BEGIN_TOKEN au jeton courant
        SYM_COUR.CODE = BEGIN_TOKEN;
    }
    else if (stricmp(mot, "end") == 0)
    {
        // Si le mot est "end", attribuer le code END_TOKEN au jeton courant
        SYM_COUR.CODE = END_TOKEN;
    }
    else if (stricmp(mot, "if") == 0)
    {
        // Si le mot est "if", attribuer le code IF_TOKEN au jeton courant
        SYM_COUR.CODE = IF_TOKEN;
    }
    else if (stricmp(mot, "then") == 0)
    {
        // Si le mot est "then", attribuer le code THEN_TOKEN au jeton courant
        SYM_COUR.CODE = THEN_TOKEN;
    }
    else if (stricmp(mot, "while") == 0)
    {
        // Si le mot est "while", attribuer le code WHILE_TOKEN au jeton courant
        SYM_COUR.CODE = WHILE_TOKEN;
    }
    else if (stricmp(mot, "do") == 0)
    {
        // Si le mot est "do", attribuer le code DO_TOKEN au jeton courant
        SYM_COUR.CODE = DO_TOKEN;
    }
    else if (stricmp(mot, "to") == 0)
    {
        // Si le mot est "to", attribuer le code TO_TOKEN au jeton courant
        SYM_COUR.CODE = TO_TOKEN;
    }
    else if (stricmp(mot, "downto") == 0)
    {
        // Si le mot est "downto", attribuer le code DOWNTO_TOKEN au jeton courant
        SYM_COUR.CODE = DOWNTO_TOKEN;
    }
    else if (stricmp(mot, "read") == 0)
    {
        // Si le mot est "read", attribuer le code READ_TOKEN au jeton courant
        SYM_COUR.CODE = READ_TOKEN;
    }
    else if (stricmp(mot, "write") == 0)
    {
        // Si le mot est "write", attribuer le code WRITE_TOKEN au jeton courant
        SYM_COUR.CODE = WRITE_TOKEN;
    }
    else if (stricmp(mot, "else") == 0)
    {
        // Si le mot est "else", attribuer le code ELSE_TOKEN au jeton courant
        SYM_COUR.CODE = ELSE_TOKEN;
    }
    else if (stricmp(mot, "repeat") == 0)
    {
        // Si le mot est "repeat", attribuer le code REPEAT_TOKEN au jeton courant
        SYM_COUR.CODE = REPEAT_TOKEN;
    }
    else if (stricmp(mot, "until") == 0)
    {
        // Si le mot est "until", attribuer le code UNTIL_TOKEN au jeton courant
        SYM_COUR.CODE = UNTIL_TOKEN;
    }
    else if (stricmp(mot, "for") == 0)
    {
        // Si le mot est "for", attribuer le code FOR_TOKEN au jeton courant
        SYM_COUR.CODE = FOR_TOKEN;
    }
    else if (stricmp(mot, "case") == 0)
    {
        // Si le mot est "case", attribuer le code CASE_TOKEN au jeton courant
        SYM_COUR.CODE = CASE_TOKEN;
    }
    else if (stricmp(mot, "of") == 0)
    {
        // Si le mot est "of", attribuer le code OF_TOKEN au jeton courant
        SYM_COUR.CODE = OF_TOKEN;
    }
    else
    {
        // Si ce n'est pas un mot-clé, c'est un identifiant
        SYM_COUR.CODE = ID_TOKEN;
    }

    // Stockage du mot dans le jeton
    strcpy(SYM_COUR.NOM, mot);
}

void lire_nombre()
{
    // Tableau pour stocker le nombre
    char nombre[11];
    int indice = 0;

    // Lecture du premier chiffre
    nombre[indice++] = Car_Cour;
    Lire_Car();

    // Lecture des chiffres suivants
    while (isdigit(Car_Cour))
    {
        // Ajout du chiffre au tableau
        nombre[indice++] = Car_Cour;
        Lire_Car();
    }

    // Ajout du caractère de fin de chaîne
    nombre[indice] = '\0';

    // Stockage du nombre dans le jeton
    // Attribution du code NUM_TOKEN au jeton courant
    SYM_COUR.CODE = NUM_TOKEN;
    // Copie du nombre dans le champ NOM du jeton courant
    strcpy(SYM_COUR.NOM, nombre);
    // Conversion du nombre en entier et stockage dans le champ val du jeton courant
    SYM_COUR.val = atoi(SYM_COUR.NOM);
}

void Sym_Suiv()
{
    // Ignorer les espaces, les sauts de ligne et les tabulations
    while (Car_Cour == ' ' || Car_Cour == '\n' || Car_Cour == '\t')
    {
        Lire_Car(); // Appel de la fonction pour lire le caractère suivant
    }

    // Identifier le type de symbole suivant
    if (isalpha(Car_Cour)) // Si le caractère est une lettre
    {
        lire_mot(); // Appel de la fonction pour lire un mot
    }
    else if (isdigit(Car_Cour)) // Si le caractère est un chiffre
    {
        lire_nombre(); // Appel de la fonction pour lire un nombre
    }
    else // Si le caractère est un symbole spécial
    {
        switch (Car_Cour)
        {
            case ';':
                SYM_COUR.CODE = PV_TOKEN; // Définition du code du symbole point-virgule
                Lire_Car(); // Appel de la fonction pour lire le caractère suivant
                break;

            case '+':
                SYM_COUR.CODE = PLUS_TOKEN; // Définition du code du symbole plus
                Lire_Car(); // Appel de la fonction pour lire le caractère suivant
                break;

            case '-':
                SYM_COUR.CODE = MOINS_TOKEN; // Définition du code du symbole moins
                Lire_Car(); // Appel de la fonction pour lire le caractère suivant
                break;

            case '*':
                SYM_COUR.CODE = MULT_TOKEN; // Définition du code du symbole multiplication
                Lire_Car(); // Appel de la fonction pour lire le caractère suivant
                break;

            case '/':
                SYM_COUR.CODE = DIV_TOKEN; // Définition du code du symbole division
                Lire_Car(); // Appel de la fonction pour lire le caractère suivant
                break;

            case ',':
                SYM_COUR.CODE = VIR_TOKEN; // Définition du code du symbole virgule
                Lire_Car(); // Appel de la fonction pour lire le caractère suivant
                break;

            case ':':
                Lire_Car(); // Lecture du caractère suivant
                if (Car_Cour == '=') // Si le symbole est ':='
                {
                    SYM_COUR.CODE = AFF_TOKEN; // Définition du code du symbole affectation
                    Lire_Car(); // Appel de la fonction pour lire le caractère suivant
                }
                else // Sinon, c'est juste ':'
                {
                    SYM_COUR.CODE = DDOT_TOKEN; // Définition du code du symbole double point
                }
                break;

            case '<':
                Lire_Car(); // Lecture du caractère suivant
                if (Car_Cour == '=') // Si le symbole est '<='
                {
                    SYM_COUR.CODE = INFEG_TOKEN; // Définition du code du symbole inférieur ou égal
                    Lire_Car(); // Appel de la fonction pour lire le caractère suivant
                }
                else if (Car_Cour == '>') // Si le symbole est '<>'
                {
                    SYM_COUR.CODE = DIFF_TOKEN; // Définition du code du symbole différent
                    Lire_Car(); // Appel de la fonction pour lire le caractère suivant
                }
                else // Sinon, c'est juste '<'
                {
                    SYM_COUR.CODE = INF_TOKEN; // Définition du code du symbole inférieur
                }
                break;

            case '>':
                Lire_Car(); // Lecture du caractère suivant
                if (Car_Cour == '=') // Si le symbole est '>='
                {
                    SYM_COUR.CODE = SUPEG_TOKEN; // Définition du code du symbole supérieur ou égal
                    Lire_Car(); // Appel de la fonction pour lire le caractère suivant
                }
                else // Sinon, c'est juste '>'
                {
                    SYM_COUR.CODE = SUP_TOKEN; // Définition du code du symbole supérieur
                }
                break;

            case '(':
                SYM_COUR.CODE = PO_TOKEN; // Définition du code du symbole parenthèse ouvrante
                Lire_Car(); // Appel de la fonction pour lire le caractère suivant
                break;

            case '=':
                SYM_COUR.CODE = EG_TOKEN; // Définition du code du symbole égal
                Lire_Car(); // Appel de la fonction pour lire le caractère suivant
                break;

            case ')':
                SYM_COUR.CODE = PF_TOKEN; // Définition du code du symbole parenthèse fermante
                Lire_Car(); // Appel de la fonction pour lire le caractère suivant
                break;

            case '.':
                SYM_COUR.CODE = PT_TOKEN; // Définition du code du symbole point
                Lire_Car(); // Appel de la fonction pour lire le caractère suivant
                break;

            case EOF:
                SYM_COUR.CODE = FIN_TOKEN; // Définition du code du symbole de fin de fichier
                break;

            default:
                SYM_COUR.CODE = ERREUR_TOKEN; // Symbole inconnu
                Lire_Car(); // Appel de la fonction pour lire le caractère suivant
        }
        // Stockage du symbole dans le jeton
        strcpy(SYM_COUR.NOM, &Car_Cour);
    }
    // Affichage du symbole (débogage)
    //printf("Symbol: %s\n", SYM_COUR.NOM);
}

void Lire_Car()
{
    Car_Cour = fgetc(fichier); // Lire le caractère suivant depuis le fichier
}

// Définition des types d'identificateurs
typedef enum {
    TPROG,    // Programme
    TCONST,   // Constante
    TVAR      // Variable
} TSYM;

// Structure pour stocker les identificateurs
typedef struct {
    TSYM TIDF;        // Type de l'identificateur
    char NOM[20];     // Nom de l'identificateur
    int value;        // Valeur associée à l'identificateur (pour les constantes)
} T_TAB_IDF;

T_TAB_IDF * TAB_IDFS; // Table des identificateurs

int k = 0; // Compteur pour la table des identificateurs
int Y = 0; // Variable Y, but inconnu

// Déclaration et implémentation de la fonction pour gérer la table des identifiants
void table_id() {
    // Analyse du symbole courant et appel des fonctions appropriées en fonction du symbole
    switch(SYM_COUR.CODE) {
        case PROGRAM_TOKEN : 
            Sym_Suiv(); // Passage au prochain symbole
            store_prog(); // Stockage des identifiants de programme
            break;
        case CONST_TOKEN : 
            Sym_Suiv(); // Passage au prochain symbole
            store_const(); // Stockage des identifiants de constante
            break;
        case VAR_TOKEN : 
            Sym_Suiv(); // Passage au prochain symbole
            store_var(); // Stockage des identifiants de variable
            break;
        default : 
            ; // Cas par défaut, aucune action
            break;
    }
}

// Implémentation de la fonction pour stocker les identifiants de programme
void store_prog() {
	while((SYM_COUR.CODE != CONST_TOKEN) && (SYM_COUR.CODE != VAR_TOKEN) && (SYM_COUR.CODE != BEGIN_TOKEN)) {
		if(SYM_COUR.CODE == ID_TOKEN) {
			strcpy((TAB_IDFS+k)->NOM, SYM_COUR.NOM); // Copie du nom de l'identifiant
			(TAB_IDFS+k)->TIDF = TPROG; // Définition du type d'identifiant comme programme
            k++; // Passage à l'index suivant dans la table des identifiants
		}
		Sym_Suiv(); // Passage au prochain symbole
	}
    table_id(); // Appel récursif pour continuer l'analyse
}

// Implémentation de la fonction pour stocker les identifiants de constante
void store_const() {
	while((SYM_COUR.CODE != PROGRAM_TOKEN) && (SYM_COUR.CODE != VAR_TOKEN) && (SYM_COUR.CODE != BEGIN_TOKEN)) {
		if(SYM_COUR.CODE == ID_TOKEN) {
			strcpy((TAB_IDFS+k)->NOM, SYM_COUR.NOM); // Copie du nom de l'identifiant
			(TAB_IDFS+k)->TIDF = TCONST; // Définition du type d'identifiant comme constante
			Sym_Suiv(); // Passage au prochain symbole
			if(SYM_COUR.CODE == EG_TOKEN) {
				Sym_Suiv(); // Passage au prochain symbole
			    (TAB_IDFS+k)->value = SYM_COUR.val; // Stockage de la valeur de la constante
		    }
            k++; // Passage à l'index suivant dans la table des identifiants
		}
		Sym_Suiv(); // Passage au prochain symbole
		Sym_Suiv(); // Passage au symbole suivant pour éviter les répétitions
	}
	table_id(); // Appel récursif pour continuer l'analyse
}

// Implémentation de la fonction pour stocker les identifiants de variable
void store_var() {
	while((SYM_COUR.CODE != CONST_TOKEN) && (SYM_COUR.CODE != PROGRAM_TOKEN) && (SYM_COUR.CODE != BEGIN_TOKEN)) {
		if(SYM_COUR.CODE == ID_TOKEN) {
            regle2(); // Vérification de la règle 2
            printf("La regle 2 est verifiee.\n");
			strcpy((TAB_IDFS+k)->NOM, SYM_COUR.NOM); // Copie du nom de l'identifiant
			(TAB_IDFS+k)->TIDF = TVAR; // Définition du type d'identifiant comme variable
            k++; // Passage à l'index suivant dans la table des identifiants
		}
		Sym_Suiv(); // Passage au prochain symbole
	}
	table_id(); // Appel récursif pour continuer l'analyse
}

/* ------------------------------ REGLES SPECIFIQUES ---------------------------- */

// Implémentation de la fonction d'affichage et de vérification sémantique
void affich() {
	//Lire_Car();
    //Sym_Suiv();
	regle1();
	printf("La regle 1 est verifiee.\n");
	regle3();
	printf("La regle 3 est verifiee.\n");
	regle4();
	printf("La regle 4 est verifiee.\n");
	regle5();
	printf("La regle 5 est verifiee.\n");

	if(Y == 0) {
		printf("La semantique est correcte!\n"); // Affichage si la sémantique est correcte
	}
    else
        printf("La semantique est erronee!\n");	 // Affichage si la sémantique est incorrecte
}

// Implémentation de la règle sémantique 1
// Règle 1 : Vérification des identifiants utilisés dans le programme pour s'assurer qu'ils ont été déclarés au préalable.
void regle1() {
	fseek(fichier, 0, SEEK_SET); // Retour au début du fichier
	Lire_Car(); // Lecture du premier caractère
	Sym_Suiv(); // Passage au prochain symbole
	while(SYM_COUR.CODE != BEGIN_TOKEN) { // Tant que le début du programme n'est pas atteint
		if(SYM_COUR.CODE == ID_TOKEN) { // Si le symbole est un identifiant
			check(); // Vérifier le symbole actuel
		}
		Sym_Suiv(); // Passage au prochain symbole
	}
}

// La fonction check sert à vérifier l'unicité des identifiants
// Check : Vérifie si l'identifiant courant est déjà déclaré ou non
// Implémentation de la fonction de vérification de l'existence d'un identifiant dans la table des identifiants
void check() {
	int r = 0; // Variable pour indiquer si l'identifiant a été trouvé dans la table
	int i;
	for (i = 0; i < k; ++i) {
		if(strcmp(SYM_COUR.NOM, (TAB_IDFS+i)->NOM) == 0) {
			r = 1; // Si l'identifiant est trouvé dans la table, r est mis à 1
		}
	}

	if(r == 0) {
		printf("%s ----> Erreur declaration hors CONST et VAR 1!\n", SYM_COUR.NOM); // Affichage de l'erreur si l'identifiant n'est pas trouvé
		Y = 1; // Indication qu'une erreur sémantique a été trouvée
	} else {
		// Pas d'erreur, aucune action nécessaire
	}
	
}

// Implémentation de la règle sémantique 2
// Règle 2 : Vérification qu'un identifiant n'a pas été déclaré plus d'une fois (doublons d'identifiants).
void regle2() {
	int r = 0; // Variable pour indiquer si l'identifiant existe déjà dans la table des identifiants
	int i;
	for (i = 0; i < k; ++i) {
		if(strcmp(SYM_COUR.NOM, (TAB_IDFS+i)->NOM) == 0) {
			r = 1; // Si l'identifiant est déjà présent dans la table, r est mis à 1
		}
	}

	if(r == 1) {
		printf("%s ----> Erreur variable deja declaree!\n ", SYM_COUR.NOM); // Affichage de l'erreur si l'identifiant existe déjà
		Y = 1; // Indication qu'une erreur sémantique a été trouvée
	} else {
		// Pas d'erreur, aucune action nécessaire
	}
}

// Implémentation de la règle sémantique 3
//Règle 3 : Vérification que les identifiants utilisés dans les instructions sont bien déclarés.
void regle3() {
	fseek(fichier, 0, SEEK_SET); // Retour au début du fichier
	Lire_Car(); // Lecture du premier caractère
	Sym_Suiv(); // Passage au prochain symbole
	while(SYM_COUR.CODE != BEGIN_TOKEN) Sym_Suiv(); // Avancer jusqu'au début du programme

	while(SYM_COUR.CODE != PT_TOKEN) { // Tant que le point virgule de fin de déclaration n'est pas atteint
		if(SYM_COUR.CODE == ID_TOKEN) { // Si le symbole est un identifiant
            int r = 0; // Variable pour indiquer si l'identifiant a été trouvé dans la table
            int i;
            for (i = 0; i < k; ++i) {
                if(strcmp(SYM_COUR.NOM, (TAB_IDFS+i)->NOM) == 0) {
                    r = 1; // Si l'identifiant est trouvé dans la table, r est mis à 1
                }
            }

            if(r == 0) {
                printf("%s ----> Erreur, variable non declaree!\n", SYM_COUR.NOM); // Affichage de l'erreur si l'identifiant n'est pas trouvé
                Y = 1; // Indication qu'une erreur sémantique a été trouvée
            }
        }
        Sym_Suiv(); // Passage au prochain symbole
	}
}


// Implémentation de la règle sémantique 4
// Règle 4 : Vérification que les constantes ne changent pas de valeur après leur déclaration et que les constantes ne peuvent pas être modifiées par des instructions de lecture (READ).
void regle4() {
	fseek(fichier, 0, SEEK_SET); // Retour au début du fichier
	Lire_Car(); // Lecture du premier caractère
	Sym_Suiv(); // Passage au prochain symbole
    while(SYM_COUR.CODE != BEGIN_TOKEN) Sym_Suiv(); // Avancer jusqu'au début du programme
    while(SYM_COUR.CODE != PT_TOKEN) { // Tant que le point virgule de fin de déclaration n'est pas atteint
        if(SYM_COUR.CODE == ID_TOKEN) { // Si le symbole est un identifiant
        	int i;
            for (i = 0; i < k; ++i) {
                if((TAB_IDFS+i)->TIDF == 1 && strcmp(SYM_COUR.NOM, (TAB_IDFS+i)->NOM) == 0) { // Si l'identifiant est une constante
                    Sym_Suiv(); // Passage au prochain symbole
                    if(SYM_COUR.CODE == AFF_TOKEN) { // Si le symbole suivant est un signe d'affectation
                        Sym_Suiv(); // Passage au prochain symbole
                        if(SYM_COUR.val != (TAB_IDFS+i)->value) { // Vérification de la valeur affectée à la constante
                            printf("%s ----> Erreur, une constante ne peut pas changer de valeur dans le programme!\n", SYM_COUR.NOM); // Affichage de l'erreur
                            Y = 1; // Indication qu'une erreur sémantique a été trouvée
                        }
                    }    
                }
            }
        }

        if(SYM_COUR.CODE == READ_TOKEN) { // Si le symbole est une instruction de lecture
            Sym_Suiv(); // Passage au prochain symbole
            Sym_Suiv(); // Passage au prochain symbole
            if(SYM_COUR.CODE == ID_TOKEN) { // Si le symbole suivant est un identifiant
            	int i;
                for (i = 0; i < k; ++i) {
                    if(strcmp(SYM_COUR.NOM, (TAB_IDFS+i)->NOM) == 0 && (TAB_IDFS+i)->TIDF == 1) { // Si l'identifiant est une constante
                        printf("%s ----> Erreur, une constante ne peut pas changer de valeur a partir de READ!\n", SYM_COUR.NOM); // Affichage de l'erreur
                        Y = 1; // Indication qu'une erreur sémantique a été trouvée
                    }
                }
            }
        }
        Sym_Suiv(); // Passage au prochain symbole
    }
}

// Implémentation de la règle sémantique 5
//Règle 5 : Vérification que le nom du programme principal n'est pas utilisé comme identifiant ailleurs dans le code.
void regle5() {
	fseek(fichier, 0, SEEK_SET); // Retour au début du fichier
	Lire_Car(); // Lecture du premier caractère
	Sym_Suiv(); // Passage au prochain symbole
	while(SYM_COUR.CODE != BEGIN_TOKEN) Sym_Suiv(); // Avancer jusqu'au début du programme
	while(SYM_COUR.CODE != PT_TOKEN) { // Tant que le point virgule de fin de déclaration n'est pas atteint
        if(SYM_COUR.CODE == ID_TOKEN) { // Si le symbole est un identifiant
        	int i;
            for (i = 0; i < k; ++i) {
                if(strcmp(SYM_COUR.NOM, (TAB_IDFS+i)->NOM) == 0) { // Si l'identifiant est présent dans la table
                    if((TAB_IDFS+i)->TIDF == 0) { // Si l'identifiant est un nom de programme
                        printf("%s ----> Nom de programme non autorise!\n", SYM_COUR.NOM); // Affichage de l'erreur
                        Y = 1; // Indication qu'une erreur sémantique a été trouvée
                    }
                }
            }
        }
        Sym_Suiv(); // Passage au prochain symbole
	}
}

int main() {
    fichier = fopen("C:/Users/HP/Desktop/Mini-Compilateur-Pascal/test.p", "r"); // Ouverture du fichier source
    //fichier = fopen("C:/Users/HP/Desktop/Mini-Compilateur-Pascal/tests/test1.p", "r"); // Ouverture du fichier source
    if (fichier == NULL)
    {
        perror("Erreur lors de l'ouverture du fichier!"); // Affichage de l'erreur si l'ouverture du fichier échoue
        return 1; // Arrêt du programme avec un code d'erreur
    }

    Lire_Car(); // Lecture du premier caractère
    Sym_Suiv(); // Détermination du premier symbole
    TAB_IDFS = (T_TAB_IDF *)malloc(sizeof(T_TAB_IDF) * 100); // Allocation dynamique de mémoire pour la table des identifiants
    table_id(); // Analyse sémantique de la table des identifiants
    affich(); // Vérification des règles sémantiques et affichage des résultats

    fclose(fichier); // Fermeture du fichier source

    printf("Execution du programme faite.\n"); // Affichage de la fin de l'exécution du programme
    return 0; // Fin du programme avec succès
}