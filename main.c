#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

HANDLE  hConsole;
const int tam=7, limite=7;
char mar[7][7], marpc[7][7], marex[7][7];
int i, j, posx, posy, nav=0, navpc=0, derrubados=0, derrubadospc=0;

int Geramar()
{
/*Gera o Mar do jogador e do computador*/
        for (i=0; i<tam; i++){
            for (j=0; j<tam; j++){
                mar[i][j]='-';
                marpc[i][j]='-';
                marex[i][j]='#';
            }
        }
}

int Mostrar()
{
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 10);
    printf("%6d", 0);
    for (i=1; i<tam; i++){
        SetConsoleTextAttribute(hConsole, 10);
        printf("%3d", i);
    }
    printf("\n");
    printf("   ");
    for (i=0; i<3*tam; i++){
        SetConsoleTextAttribute(hConsole, 10);
        printf("-");
    }
    printf("\n");
    for (i=0; i <tam; i++){
        SetConsoleTextAttribute(hConsole, 10);
        printf("%2d|", i);
        SetConsoleTextAttribute(hConsole, 7);
        for(j=0; j <tam; j++){
            if (mar[i][j]=='*'){
                SetConsoleTextAttribute(hConsole, 9);
                printf("%3c", mar[i][j]);
                SetConsoleTextAttribute(hConsole, 7);
            }
            else if (mar[i][j]=='N'){
                SetConsoleTextAttribute(hConsole, 14);
                printf("%3c", mar[i][j]);
                SetConsoleTextAttribute(hConsole, 7);
            }
            else if (mar[i][j]=='X'){
                SetConsoleTextAttribute(hConsole, 12);
                printf("%3c", mar[i][j]);
                SetConsoleTextAttribute(hConsole, 7);
            }
            else {
                printf("%3c", mar[i][j]);
            }
        }
    printf("\n");
    }
    /*Mar do computador*/
    printf("\n");
    SetConsoleTextAttribute(hConsole, 10);
    printf("%6d", 0);
    for (i=1; i<tam; i++){
        SetConsoleTextAttribute(hConsole, 10);
        printf("%3d", i);
    }
    printf("\n");
    printf("   ");
    for (i=0; i<3*tam; i++){
        SetConsoleTextAttribute(hConsole, 10);
        printf("-");
    }
    printf("\n");
    for (i=0; i<tam; i++){
        SetConsoleTextAttribute(hConsole, 10);
        printf("%2d|", i);
        SetConsoleTextAttribute(hConsole, 7);
        for(j=0; j<tam; j++){
            if (marpc[i][j]=='*'){
                SetConsoleTextAttribute(hConsole, 9);
                printf("%3c", marex[i][j]);
                SetConsoleTextAttribute(hConsole, 7);
            }
            else if (marpc[i][j]=='X'){
                SetConsoleTextAttribute(hConsole, 12);
                printf("%3c", marex[i][j]);
                SetConsoleTextAttribute(hConsole, 7);
            }
            else {
                printf("%3c", marex[i][j]);
            }
        }
    printf("\n");
    }
}

int orgnavios()
{
    while (nav<10){
        printf("\n");
        printf("Para jogar defina as coordenadas de seus navios (Ex: x=2 y=6)\n");
        scanf("%d%d", &posx, &posy);
        if (posx<7 && posx>=0 && posy<7 && posy>=0){
            if (mar[posx][posy]=='N'){
                system("cls");
                Mostrar();
                printf("\n");
                printf("Ja existe um navio nesta posicao!!!\n");

            }
            else{
                mar[posx][posy]='N';
                system("cls");
                Mostrar();
                nav++;
            }
        }
        else{
            system("cls");
            Mostrar();
            printf("\n");
            printf("Nao coloque alem dos limites!!!\n");
        }
    }
}

int naviospc()
{
    while (navpc<10){
        posx=rand()%limite;
        posy=rand()%limite;
        if (marpc[posx][posy]=='N'){
            naviospc();
        }
        else{
            marpc[posx][posy]='N';
            navpc++;
        }
    }
}

int tiro()
{
    if (derrubados<10 && derrubadospc<10){
        printf("Agora ja colocou seus navios, para atirar escreva as posicoes (Ex: x=1 y=6)\n");
        scanf("%d%d", &posx, &posy);
        if (posy>7 || posx>7){
            system("cls");
            Mostrar();
            printf("\n");
            printf("Nao passe dos limites!!!!\n");
            printf("\n");
            tiro();
        }
        else{
    /*Se eu errar por ex, ele vai chamar a função tiro do computador*/
                if (marpc[posx][posy]=='-'){
                    marex[posx][posy]='*';
                    marpc[posx][posy]='*';
                    system("cls");
                    Mostrar();
                    printf("\n");
                    printf("Voce errou!!\n");
                    printf("\n");
                }
    /*Se eu acertar, chama a função tiro devolta*/
                else if (marpc[posx][posy]=='N'){
                    marex[posx][posy]='X';
                    marpc[posx][posy]='X';
                    system("cls");
                    Mostrar();
                    printf("\n");
                    printf("Voce acertou!!\n");
                    printf("\n");
                    derrubados++;
                    tiro();
                }
    /*se eu acertar uma posição que ja joguei, eu jogo denovo*/
                else if (marpc[posx][posy]=='*' || marpc[posx][posy]=='#'){
                    system("cls");
                    Mostrar();
                    printf("\n");
                    printf("Voce ja atirou nesta posicao, tente denovo!!\n");
                    printf("\n");
                    tiro();
                }
                else{
                    system("cls");
                    Mostrar();
                    printf("\n");
                    printf("Nao passe dos limites!!!!\n");
                    printf("\n");
                    tiro();
                }
            }
    }
}

int tiropc()
{
    /*Mesmas rotinas, so que do computador*/
    if (derrubadospc<10 && derrubados<10){
            posx=rand()%limite;
            posy=rand()%limite;
            if (mar[posx][posy]=='-'){
                mar[posx][posy]='*';
                system("cls");
                Mostrar();
                printf("\n");
                printf("O computador errou!!!\n");
                printf("\n");
            }
            else if (mar[posx][posy]=='N'){
                mar[posx][posy]='X';
                system("cls");
                Mostrar();
                printf("\n");
                printf("O computador acertou!!!\n");
                printf("\n");
                derrubadospc++;
                tiropc();
            }
            else{
            system("cls");
            Mostrar();
            tiropc();
        }

    }

}

int main()
{
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    srand(time(NULL));
    Geramar();
    Mostrar();
    /*Coloca os navios*/
    naviospc();
    orgnavios();
    /*Começa o Jogo*/
    while (derrubados<10 && derrubadospc<10){
        tiro();
        tiropc();
    }
    if (derrubados==10){
         SetConsoleTextAttribute(hConsole, 13);
        printf("VOCE VENCEU :D \n");
         SetConsoleTextAttribute(hConsole, 7);
    }
    if (derrubadospc==10){
         SetConsoleTextAttribute(hConsole, 6);
        printf("VOCE PERDEU :( \n");
         SetConsoleTextAttribute(hConsole, 7);

    }
}



