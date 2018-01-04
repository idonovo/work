
#include <stdio.h>
#include <stdlib.h>

int x = 4;

typedef struct Ad Ad;

struct Ad
{
   char m_char;
   int m_r;
};

int main(){

    int* c = malloc(sizeof(int));
    *c = 45;
    double t = 45.34;
    Ad* ad = malloc(sizeof(Ad));
    ad->m_char = 'g';
    ad->m_r = 12;
    
    printf("%p\n", x);
    printf("%p\n", ad->m_char);
    printf("%p\n", ad->m_r);
    printf("%p\n", c);
    printf("%p\n", t);
    free(c);
    free(ad);
    return 0;
    


}
