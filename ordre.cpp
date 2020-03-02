#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
#define NMOTS 5
#define MAXMOT 30
 
int fonc(const void* p1,const void* p2)
{
    const char* ch1 = (const char*)p1;
    const char* ch2 = (const char*)p2;
    return strcmp(ch1,ch2);
}
 
int main()
{
    int i;
    char mots[NMOTS][MAXMOT];
    for(i=0;i<NMOTS;i++)
    {
        printf("entrer mot %d : ",i);
        fgets(mots[i],MAXMOT,stdin);
    }
    printf("\nTri.\n");
    qsort(mots,NMOTS,MAXMOT,fonc);
    for(i=0;i<NMOTS;i++)
        printf("%s\n",mots[i]);
    system("pause");
    return 0;
}
