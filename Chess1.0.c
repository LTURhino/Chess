#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "con_lib.h"
#include "functions.c"
struct coords
{
    int row;
    int collum;
};

char board[8][8] =
{
    'r','h','b','q','k','b','h','r',
    'p','p','p','p','p','p','p','p',
    '\ ','\ ','\ ','\ ','\ ','\ ','\ ','\ ',
    '\ ','\ ','\ ','\ ','\ ','\ ','\ ','\ ',
    '\ ','\ ','\ ','\ ','\ ','\ ','\ ','\ ',
    '\ ','\ ','\ ','\ ','\ ','\ ','\ ','\ ',
    'P','P','P','P','P','P','P','P',
    'R','H','B','Q','K','B','H','R'
};
//Creates a delay

//Creates whole board
int display()
{   struct coords pos;
    printf("\n");
    printf("       0  1  2  3  4  5  6  7\n");
    for(pos.row=0;pos.row<8;++pos.row)
    {
        printf("    %d |",pos.row);
        for(pos.collum=0;pos.collum<8;++pos.collum)
        {
            printf("%-2c|",board[pos.row][pos.collum]);
        }
        printf("\n");
    }
    return 0;
}

//Saves progress
void autoSave()
{
    FILE *gameSave;
    gameSave=fopen("saved.bin","wb");
    if(!gameSave)
    {
            printf("Error opening a file");
    }
    else
    {   struct coords pos;
        for(pos.row=0;pos.row<8;++pos.row)
        {
            for(pos.collum=0;pos.collum<8;++pos.collum)
            {
                fwrite(&board[pos.row][pos.collum],sizeof(board[pos.row][pos.collum]),1,gameSave);
            }

        }


        fclose(gameSave);
    }
}

//Loads a saved game
void load()
{
    FILE *gameLoad;
    gameLoad=fopen("saved.bin","rb");
    if(!gameLoad)
    {
        printf("Error opening a file");
    }
    struct coords pos;
    printf("\nGame was loaded\n");
    printf("\n");
    printf("       0  1  2  3  4  5  6  7\n");
    for( pos.row = 0; pos.row<8;++pos.row)
    {
        printf("    %d |",pos.row);
        for( pos.collum = 0; pos.collum<8; ++pos.collum)
        {
            fread(&board[pos.row][pos.collum],sizeof(board[pos.row][pos.collum]),1,gameLoad);
            printf("%-2c|",board[pos.row][pos.collum]);
        }
        printf("\n");
    }
    fclose(gameLoad);
    delay(1000);


}
int playersOption()
{   int choice;
    printf("\n    1:New game\n    2:Load game\n    3:Small Rules\n    Any other character:Quit\n    Your choice:");
    scanf(" %d",&choice);
    if(choice==1)
    {   con_clear();
        display();
    }
    else if(choice==2)
    {   con_clear();
        load();
    }
    else if(choice==3)
    {   //con_clear();
       // help();
    }
    else
    {
        printf("Quiting...");
        delay(2000);
        exit(0);
    }
}

int main()
{   int turn=0;
    struct coords Curr,New;
    playersOption();
    while(1)
    {
        if(turn%2==0)
        {
            char c1,c2,c3,c4;

            do{
                scanf("%c",&c4);
                printf("\nEnter Whites position row and collum: ");
                scanf("%c%c%c",&c1,&c3,&c2);
                Curr.row=c1-48;
                Curr.collum=c2-48;
            }
            while(Curr.row<0 || Curr.row>7 || Curr.collum<0 || Curr.collum>7 || c3!=' ');



            do{
                scanf("%c",&c4);
                printf("\nEnter where to go: ");
                scanf("%c%c%c",&c1,&c3,&c2);
                New.row=c1-48;
                New.collum=c2-48;
            }
            while(New.row<0 || New.row>7 || New.collum<0 || New.collum>7 || c3!=' ');
            if(isupper(board[Curr.row][Curr.collum])>0)
            {
                board[New.row][New.collum] = board[Curr.row][Curr.collum];
                board[Curr.row][Curr.collum] = '\ ';
            }
            else
            {   ++turn;
                printf("\nIt's White turn! Try Again\n");
                delay(2000);
            }
            con_clear();
            display();
            ++turn;
        }
        else
        {   char c1,c2,c3,c4;
            do{
                scanf("%c",&c4); //Nesuprantu kodel cia reikia?????
                printf("\nEnter Blacks position row and collum: ");
                scanf("%c%c%c",&c1,&c3,&c2);
                Curr.row=c1-48;
                Curr.collum=c2-48;
            }
            while(Curr.row<0 || Curr.row>7 || Curr.collum<0 || Curr.collum>7 || c3!=' ');
            do{
                scanf("%c",&c4);
                printf("\nEnter where to go: ");
                scanf("%c%c%c",&c1,&c3,&c2);
                New.row=c1-48;
                New.collum=c2-48;
            }
            while(New.row<0 || New.row>7 || New.collum<0 || New.collum>7 || c3!=' ');
            if(islower(board[Curr.row][Curr.collum])>0)
            {
                board[New.row][New.collum] = board[Curr.row][Curr.collum];
                board[Curr.row][Curr.collum] = '\ ';
            }
            else
            {   printf("\nIt's Black turn! Try Again\n");
                delay(2000);
            }
            con_clear();
            display();
            ++turn;
        }
        autoSave();
    }
    return 0;
}
