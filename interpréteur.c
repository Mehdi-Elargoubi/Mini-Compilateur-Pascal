#include <stdio.h>

// Définition des constantes pour la taille de la mémoire et du code
#define TAILLEMEM 1000
#define TAILLECODE 1000

// Énumération des classes lexicales pour les instructions
typedef enum {
    ADD, SUB, MUL, DIV, EQL, NEQ, GTR, LSS, GEQ, LEQ, PRN, INN, INT, LDI, LDA, LDV, STO, BRN, BZE, HLT, NUM
} CLASS_LEX;


// Structure pour représenter une instruction
typedef struct {
    CLASS_LEX MNE; // Mnémonique de l'instruction
    int SUITE;     // Valeur associée à l'instruction (adresse, valeur, etc.)
} INSTRUCTION;


// Mémoire et Programme
int MEM[TAILLEMEM];           // Mémoire pour stocker les données
INSTRUCTION PCODE[TAILLECODE];// Programme en code intermédiaire
int SP = -1;                   // Pointeur de pile
int PC = -1;                   // Compteur de programme
int OFFSET;                    // Décalage pour la pile


// Fonction pour écrire une instruction sans argument dans le programme en code intermédiaire
void ECRIRE1(CLASS_LEX M) {
    if (PC == TAILLECODE) // Vérifie si le programme en code intermédiaire a atteint sa taille maximale
        printf("Erreur: TAILLECODE atteinte\n");
    PC++; // Incrémente le compteur de programme
    PCODE[PC].MNE = M; /// Affecte le mnémonique de l'instruction au programme en code intermédiaire
}


// Fonction pour écrire une instruction avec un argument dans le programme en code intermédiaire
void ECRIRE2(CLASS_LEX M, int A) {
    // Vérifie si le programme en code intermédiaire a atteint sa taille maximale
    if (PC == TAILLECODE)
        printf("Erreur: TAILLECODE atteinte\n");
    // Incrémente le compteur de programme
    PC++;
    // Affecte le mnémonique et la valeur associée de l'instruction au programme en code intermédiaire
    PCODE[PC].MNE = M;
    PCODE[PC].SUITE = A;
}


// Fonction pour exécuter une instruction à partir du programme en code intermédiaire
void INTER_INST(INSTRUCTION INST) {
    int val1, adr, val2;
    switch (INST.MNE) {
        case INT:
            // Initialise le décalage et le pointeur de pile
            OFFSET = SP = INST.SUITE;
            // Passe à l'instruction suivante
            PC++;
            break;
        case LDI:
            // Charge une valeur immédiate dans la pile
            MEM[++SP] = INST.SUITE;
            // Passe à l'instruction suivante
            PC++;
            break;
        case LDA:
            // Charge une adresse dans la pile
            MEM[++SP] = INST.SUITE;
            // Passe à l'instruction suivante
            PC++;
            break;
        case STO:
            // Stocke une valeur dans la mémoire
            val1 = MEM[SP--];
            adr = MEM[SP--];
            MEM[adr] = val1;
            // Passe à l'instruction suivante
            PC++;
            break;
        case LDV:
            // Charge une valeur depuis la mémoire
            adr = MEM[SP--];
            MEM[++SP] = MEM[adr];
            // Passe à l'instruction suivante
            PC++;
            break;
        case EQL:
            // Vérifie si deux valeurs sont égales
            val1 = MEM[SP--];
            val2 = MEM[SP--];
            MEM[++SP] = (val1 == val2);
            // Passe à l'instruction suivante
            PC++;
            break;
        case LEQ:
            // Vérifie si une valeur est inférieure ou égale à une autre
            val2 = MEM[SP--];
            val1 = MEM[SP--];
            MEM[++SP] = (val1 <= val2);
            // Passe à l'instruction suivante
            PC++;
            break;
        case BZE:
            // Effectue un branchement si la valeur au sommet de la pile est zéro
            if (MEM[SP--] == 0)
                PC = INST.SUITE;
            else
                PC++;
            break;
        case BRN:
            // Effectue un branchement inconditionnel
            PC = INST.SUITE;
            break;
        // Ajoutez les autres cas ici
    }
}


// Fonction pour exécuter le programme en code intermédiaire
void INTER_PCODE() {
    // Initialise le compteur de programme
    PC = 0;
    // Exécute les instructions jusqu'à ce que l'instruction de fin soit atteinte
    while (PCODE[PC].MNE != HLT)
        INTER_INST(PCODE[PC]);
}


// Fonction principale
int main() {
    
    INTER_PCODE(); // Appel de la fonction pour exécuter le programme en code intermédiaire
    
  return 0;
}
