#include <stdio.h>
#include <stdlib.h>
typedef enum { 
    SOURCE, 
    USINE, 
    STOCKAGE, 
    JONCTION,
    RACCORDEMENT,
    USAGER
}Type;

typedef struct{
    Type type;
    char ID_Usine[51];
    char amont[51];
    char aval[51];
    int VolumeVersAval;
    float PourcentageFuite;
}Trancon;

int main()
{
    printf("Hello World");

    return 0;
}
