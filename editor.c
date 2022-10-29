#include "helpers.h"

int main()
{
    Ttext *text;
    init_text(&text);
    Tcoada *coada_com;
    init_coada(&coada_com);
    read(text,coada_com);

    free_text(&text);    
    free_coada(&coada_com);
    return 0;
}