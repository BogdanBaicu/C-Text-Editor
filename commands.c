#include "commands.h"
#include "helpers.h"

caracter *position;

// Functii text
void init_text(Ttext **text)
{
    *text=malloc(sizeof(Ttext));
    (*text)->head=(*text)->tail=NULL;
}

void add_text(Ttext *text, char buff, int linie, int poz)
{
    caracter *nou=malloc(sizeof(caracter));
    nou->car=buff;
    nou->linie=linie;
    nou->pozitie=poz;
    // Daca lista este goala
    if(text->head==NULL)
    {
        nou->next=text->head;
        text->head=nou;
        text->tail=nou;
        nou->prev=NULL;
    }
    // Daca lista nu este goala
    else
    {
        nou->prev=text->tail;
        text->tail=nou;
        nou->prev->next=nou;
        nou->next=NULL;
    }
}

void delete_text(Ttext *text)
{
    // Daca elementul este primul
    if(position==text->head)
    {
        caracter *var=text->head;
        text->head=text->head->next;
        text->head->prev=NULL;
        position=text->head;
        free(var);
    }
    else 
        // Daca este ultimul
        if(position==text->tail)
        {
            printf("%c",text->tail->car);
            caracter *var=text->tail;
            text->tail=text->tail->prev;
            text->tail->next=NULL;
            position=text->tail;
            free(var);
        }
        // Daca nu este nici primul nici ultimul
        else
        {
            caracter *var=position;
            position->prev->next=position->next;
            position->next->prev=position->prev;
            position=position->next;
            free(var);
        }

}

void scrie_text(Ttext *text)
{
    int ok;
    FILE *fr;
    fr=fopen("editor.out","w");
    if(fr==NULL)
    {
        printf("Nu s-a putut deschide fisierul de iesire");
        return;
    }
    caracter *var=text->head;
    // Se scrie caracter cu caracter, iar daca se intalnesc
    // noua \n consecutive, nu se scrie decat unul
    while(var!=NULL)
    {
        ok=1;
        if(var->next!=NULL)
            if(var->car=='\n')
                if(var->next->car=='\n')
                    ok=0;
        if(ok==1)
            fputc(var->car,fr);
        var=var->next;
    }

    fclose(fr);
}

void free_text(Ttext **text)
{
    caracter *var1,*var2;
    var2=(*text)->head;
    while(var2!=NULL)
    {
        var1=var2;
        var2=var1->next;
        free(var1);
    }
    free(*text);
}

void decrement_line()
{
    caracter *var=position;
    while(var!=NULL)
    {
        var->linie--;
        var=var->next;
    }
}

void goto_line(Ttext *text, int lin)
{
    position=text->head;
    while(position->linie!=lin)
        position=position->next;
}

void delete_line(Ttext *text)
{
    int lin=position->linie;
    goto_line(text,lin);
    while(position->linie==lin)
        delete_text(text);
    decrement_line();
}

void goto_character(Ttext *text, int poz, int lin)
{
    goto_line(text,lin);
    while(position->pozitie!=poz)
        position=position->next;
}

void backspace(Ttext *text)
{
    delete_text(text);
    position=position->prev;
}

void delete(Ttext *text)
{
    position=position->next;
    delete_text(text);
}

void init_coada(Tcoada **coada)
{
    *coada=malloc(sizeof(Tcoada));
    (*coada)->head=(*coada)->tail=NULL;
}

void add_coada(Tcoada *coada, char *comand)
{
    comanda *new=malloc(sizeof(comanda));
    strcpy(new->com,comand);
    new->next=NULL;
    new->prev=NULL;
    // Adaugarea in cazul cozii goale
    if(coada->head==NULL)
    {
        coada->head=new;
        coada->tail=new;
    }
    // Adaugarea daca nu este goala coada
    else
    {
        new->prev=coada->tail;
        coada->tail->next=new;
        coada->tail=new;
    }
}

void free_coada(Tcoada **coada)
{
    comanda *var1,*var2;
    var2=(*coada)->head;
    while(var2!=NULL)
    {
        var1=var2;
        var2=var1->next;
        free(var1);
    }
    
    free(*coada);
}

int executa(Ttext *text, char *command)
{
    // Save si quit
    if(strncmp(command,"s",1)==0)
    {
        // Comanda de save
        int linie=1, position=1;
        // Se realizeaza o copie a textului
        Ttext *text_save;
        init_text(&text_save);
        caracter *var=text->head;
        while(var!=NULL)
        {
            add_text(text_save,var->car,linie,position);
            if(var->car=='\n')
            {
                linie++;
                position=1;
            }
            var=var->next;

        }
        // Este scris textul xopiat, apoi este eliberata memoria
        scrie_text(text_save);
        free_text(&text_save);
        return 1;
    }
    // Comanda de quit ce opreste programul 
    if(strncmp(command,"q",1)==0)
        return -1;
    
    // Goto line
    if(strncmp(command,"gl",2)==0)
    {
        goto_line(text,((int)command[3]-48));
        return 1;
    }

    // Delete line
    if(strncmp(command,"dl ",3)==0)
        {
            // Daca delete line primeste argument
            goto_line(text,((int)command[3]-48));
            delete_line(text);
            return 1;
        }
    if(strncmp(command,"dl",2)==0)
    {
        // Daca delete line nu primeste argument
        delete_line(text);
        return 1;
    }

    // Goto character
    if(strncmp(command,"gc ",3)==0)
    {
        if(command[4]==' ')
        {    
            // Daca goto character primeste si linia
            goto_character(text,(int)command[3]-48,(int)command[5]-48);
            return 0;
        }
        else
        {
            // Daca nu este prezent un parametru specific liniei
            int lin=position->linie;
            goto_character(text,(int)command[3]-48,lin);
            return 0;
        }
    }

    // Backspace
    if(strncmp(command,"b",1)==0)
    {   
        if(position==NULL)
            position=text->head;
        backspace(text);
        return 0;
    }

    // Delete
    if(strncmp(command,"d",1)==0)
    {
        if(command[1]==' ')
        {
            // Daca se sterg mai multe caractere
            int i;
            for(i=0;i<(int)command[2]-48;i++)
                delete(text);
            return 0;
        }
        else
        {
            // Daca se sterge doar un caracter
            delete(text);
            return 0;
        }   
    }

    return 0;
}

void read(Ttext *text, Tcoada *coada_com)
{
    // Se verifica fisierul de intrare
    FILE *fr;
    fr=fopen("editor.in","r");
    if(fr==NULL)
    {
        printf("Nu s-a putut deshide fisierul de intrare");
        return;
    }
    char buff,buff2,command[11];
    int insert_mode=0,i=0,car_lin=1,car_poz=1;
    // Se citeste din fisierul de intrare
    while((buff=fgetc(fr))!=EOF)
    {
        // Se verifica daca se introduce ::i si se schimba intre modul 
        // de inserare text si inserare comanda
        if(buff==':')
        {
            buff2=fgetc(fr);
            if(buff2==':')
            {
                if(insert_mode==0)
                    insert_mode++;
                else
                    insert_mode--;
                buff=fgetc(fr);
                buff=fgetc(fr);
                buff=fgetc(fr);
            }
        }
        if(insert_mode==0)
        { 
            // Se insereaza textul, actualizand pozitia caracterelor
            add_text(text,buff,car_lin,car_poz++);
            if(buff=='\n')
            {
                car_lin++;
                car_poz=1;
            }
        }
        if(insert_mode==1)
        {
            // Se adauga o comanda
            command[i++]=buff;
            if(buff=='\n')
            {
                command[i]='\0';
                add_coada(coada_com,command);
                // Se executa comanda introdusa, iar daca se returneaza -1,
                // specific quit, se iese din program
                if(executa(text,command)==-1)
                {
                    fclose(fr);
                    return;
                }
                i=0;
                strcpy(command,"");
            }
        }
    }
    
    fclose(fr);
}