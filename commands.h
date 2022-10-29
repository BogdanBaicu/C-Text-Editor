#ifndef _COMMANDS_
#define _COMMANDS_

#include "helpers.h"

// Definire structuri
typedef struct caracter{
    char car;
    int linie;
    int pozitie;
    struct caracter *next,*prev;
}caracter;

typedef struct Ttext{
    caracter *head;
    caracter *tail;
}Ttext;

typedef struct comanda{
    char com[11];
    struct comanda *next,*prev;
}comanda;

typedef struct Tcoada{
    comanda *head,*tail;
}Tcoada;

// Fucntie ce aloca memorie unei structuri de tip Ttext
void init_text(Ttext **text);

// Functie ce adauga un caracter intr-o lista de tip TText
void add_text(Ttext *text, char buff, int linie, int poz);

// Fucntie ce elimina un caracter dintr-o lista de tip Ttext
void delete_text(Ttext *text);

// Functie ce realizeaza scrierea in fisier
void scrie_text(Ttext *text);

// Functie ce realizeaza eliberarea de memorie pentru Ttext
void free_text(Ttext **text);

// Functie ce decrementeaza numarul liniilor incepand cu pozitia cursorului
void decrement_line();

// Functie ce deplaseaza cursorul pe linia specificata
void goto_line(Ttext *text, int lin);

// Functie ce deplaseaza cursorul pe o linie, iar apoi o sterge caracter cu caracter
void delete_line(Ttext *text);

// Functie ce deplaseaza cursorul pe o anumita pozitie
void goto_character(Ttext *text, int poz, int lin);

// Functie ce realizeaza operatia backspace
void backspace(Ttext *text);

// Functie ce realizeaza operatia delete
void delete(Ttext *text);

// Functie ce aloca memorie cozii
void init_coada(Tcoada **coada);

// Functie ce adauga un element in coada
void add_coada(Tcoada *coada, char *comand);

// Functie ce elibereaza memoria cozii
void free_coada(Tcoada **coada);

int executa(Ttext *text, char *command);

void read(Ttext *text, Tcoada *coada_com);

#endif