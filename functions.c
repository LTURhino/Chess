#ifndef functions_c
#define functions_c
#include <time.h>
#include<stdio.h>
#include<stdlib.h>
#include "con_lib.h"

void delay(int milliSeconds)
{
    clock_t start_time = clock();
    while(clock()<start_time + milliSeconds)
        ;
}

struct COORDS
{
    int row;
    int collum;
};

char board[8][8] =
{
    'r','h','b','q','k','b','h','r',
    'p','p','p','p','p','p','p','p',
    ' ',' ',' ',' ',' ',' ',' ',' ',
    ' ',' ',' ',' ',' ',' ',' ',' ',
    ' ',' ',' ',' ',' ',' ',' ',' ',
    ' ',' ',' ',' ',' ',' ',' ',' ',
    'P','P','P','P','P','P','P','P',
    'R','H','B','Q','K','B','H','R'
};

//Creates a delay

//Creates whole board
int display()
{   struct COORDS pos;
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
    {   struct COORDS pos;
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
    struct COORDS pos;
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

//Tests for valid moves
int validMove(struct COORDS curr,struct COORDS neww)
{
    char unit,newunit;
    int color,row,collum,i,j;
    unit = board[curr.row][curr.collum];
    newunit = board[neww.row][neww.collum];
    if(isalpha(newunit)) // show if alphabetical returns 0 or 1
        color = islower(newunit); // shows if lower case then returns 1 otherwise 0
    else
        color = -1;
//Valid moves of White Pawn
    if(unit == 'P')
    {
        if(neww.row==curr.row-1 && neww.collum==curr.collum+1)
                if(color>0)
                    return 1;
                else
                    return 0;
        else if(neww.row==curr.row-1 && neww.collum==curr.collum-1)
                if(color>0)
                    return 1;
                else
                    return 0;
        else if(neww.row==curr.row-1 && neww.collum==curr.collum)
                if(color<0)
                    return 1;
                else
                    return 0;
        else if(neww.row==curr.row-2 && neww.collum==curr.collum && curr.row==6)
                if(color<0 && board[neww.row+1][neww.collum]==' ') //Can't jump over
                    return 1;
                else
                    return 0;
        else
                    return 0;

    }
//Valid moves of Black Pawn
    else if(unit == 'p')
    {
        if(neww.row==curr.row+1 && neww.collum==curr.collum+1)
                if(color==0)
                    return 1;
                else
                    return 0;
        else if(neww.row==curr.row+1 && neww.collum==curr.collum-1)
                if(color==0)
                    return 1;
                else
                    return 0;
        else if(neww.row==curr.row+1 && neww.collum==curr.collum)
                if(color<0)
                    return 1;
                else
                    return 0;
        else if(neww.row==curr.row+2 && neww.collum==curr.collum && curr.row==1)
                if(color<0 && board[neww.row-1][neww.collum] == ' ') //Can't jump over
                    return 1;
                else
                    return 0;
        else
                    return 0;
    }
//Valid moves of White Rook
    else if(unit == 'R')
    {
        if(neww.collum == curr.collum)
        {
            if(neww.row < curr.row)
            {
                for(row=curr.row-1; row>neww.row; --row)
                    if(board[row][curr.collum] != ' ')
                        return 0;
                if(color>0 || color<0)
                    return 1;
                else
                    return 0;
            }
            else if(neww.row > curr.row)
            {
                for(row=curr.row+1; row<neww.row; ++row)
                    if(board[row][curr.collum] != ' ')
                        return 0;
                if(color>0 || color<0)
                    return 1;
                else
                    return 0;
            }
            else
                return 0;
        }
        else if(neww.row == curr.row)
        {
            if(neww.collum < curr.collum)
            {
                for(collum=curr.collum-1; collum>neww.collum; --collum)
                    if(board[curr.row][collum] != ' ')
                        return 0;
                if(color>0 || color<0)
                    return 1;
                else
                    return 0;
            }
            else if(neww.collum > curr.collum)
            {
                for(collum=curr.collum+1; collum<neww.collum; ++collum)
                    if(board[curr.row][collum] != ' ')
                        return 0;
                if(color>0 || color<0)
                    return 1;
                else
                    return 0;
            }
            else
                return 0;
        }
        else
            return 0;
    }
//Valid moves of Black Rook
    else if(unit == 'r')
    {
            if(neww.collum == curr.collum)
            {   if(neww.row < curr.row)
                {   for(row=curr.row-1; row>neww.row; --row)
                        if(board[row][curr.collum] != ' ')
                                return 0;
                    if(color==0 || color<0)
                        return 1;
                    else
                        return 0;
                }
                else if(neww.row > curr.row)
                {   for(row=curr.row+1; row<neww.row; ++row)
                        if(board[row][curr.collum] != ' ')
                                return 0;
                    if(color==0 || color<0)
                        return 1;
                    else
                        return 0;
                }
                else
                    return 0;
            }
            else if(neww.row == curr.row)
            {   if(neww.collum < curr.collum)
                {   for(collum=curr.collum-1; collum>neww.collum; --collum)
                        if(board[curr.row][collum] != ' ')
                                return 0;
                    if(color==0 || color<0)
                        return 1;
                    else
                        return 0;
                }
                else if(neww.collum > curr.collum)
                {   for(collum=curr.collum+1; collum<neww.collum; ++collum)
                        if(board[curr.row][collum] != ' ')
                                return 0;
                    if(color==0 || color<0)
                        return 1;
                    else
                        return 0;
                }
                else
                    return 0;
            }
            else
                return 0;

    }
//Valid moves of White Knight
    else if(unit == 'H')
    {
        if((neww.row==curr.row-2) && (neww.collum==curr.collum+1) && color!=0)
                return 1;
        else if((neww.row==curr.row-2) && (neww.collum==curr.collum-1) && color!=0)
                return 1;
        else if((neww.row==curr.row-1) && (neww.collum==curr.collum-2) && color!=0)
                return 1;
        else if((neww.row==curr.row+1) && (neww.collum==curr.collum-2) && color!=0)
                return 1;
        else if((neww.row==curr.row+2) && (neww.collum==curr.collum-1) && color!=0)
                return 1;
        else if((neww.row==curr.row+2) && (neww.collum==curr.collum+1) && color!=0)
                return 1;
        else if((neww.row==curr.row+1) && (neww.collum==curr.collum+2) && color!=0)
                return 1;
        else if((neww.row==curr.row-1) && (neww.collum==curr.collum+2) && color!=0)
                return 1;
        else
                return 0;

    }
//Valid moves of Black Knight
    else if(unit == 'h')
    {
        if((neww.row==curr.row-2) && (neww.collum==curr.collum+1) && color<=0)
                return 1;
        else if((neww.row==curr.row-2) && (neww.collum==curr.collum-1) && color<=0)
                return 1;
        else if((neww.row==curr.row-1) && (neww.collum==curr.collum-2) && color<=0)
                return 1;
        else if((neww.row==curr.row+1) && (neww.collum==curr.collum-2) && color<=0)
                return 1;
        else if((neww.row==curr.row+2) && (neww.collum==curr.collum-1) && color<=0)
                return 1;
        else if((neww.row==curr.row+2) && (neww.collum==curr.collum+1) && color<=0)
                return 1;
        else if((neww.row==curr.row+1) && (neww.collum==curr.collum+2) && color<=0)
                return 1;
        else if((neww.row==curr.row-1) && (neww.collum==curr.collum+2) && color<=0)
                return 1;
        else
                return 0;

    }
//Valid moves of White Bishop
    else if(unit == 'B')
    {

        if(curr.row-neww.row == neww.collum-curr.collum)
        {
            if(neww.collum > curr.collum)
            {   for(row=curr.row-1, collum=curr.collum+1; row>neww.row; --row,++collum)
                        if(board[row][collum]==' ')
                                continue;
                        else
                                return 0;
                if(color != 0)
                        return 1;
                else
                        return 0;

            }
            else if(neww.collum < curr.collum)
            {   for(row=curr.row+1, collum=curr.collum-1; row<neww.row; ++row,--collum)
                        if(board[row][collum]==' ')
                                continue;
                        else
                                return 0;
                if(color != 0)
                        return 1;
                else
                        return 0;

            }
            else
                return 0;
        }
        else if(curr.row-neww.row == curr.collum-neww.collum)
        {
            if(neww.collum > curr.collum)
            {   for(row=curr.row+1, collum=curr.collum+1; row<neww.row; ++row, ++collum)
                        if(board[row][collum]==' ')
                                continue;
                        else
                                return 0;
                if(color != 0)
                        return 1;
                else
                        return 0;

            }
            else if(neww.collum < curr.collum)
            {   for(row=curr.row-1, collum=curr.collum-1; row>neww.row; --row, --collum)
                        if(board[row][collum]==' ')
                                continue;
                        else
                                return 0;
                if(color != 0)
                        return 1;
                else
                        return 0;

            }
            else
                return 0;
        }
        else
            return 0;
   }
//Valid moves of Black Bishop
   else if(unit == 'b')
   {

        if(curr.row-neww.row == neww.collum-curr.collum)
        {
            if(neww.collum > curr.collum)
            {   for(row=curr.row-1, collum=curr.collum+1; row>neww.row; --row, ++collum)
                        if(board[row][collum]==' ')
                                continue;
                        else
                                return 0;
                if(color <= 0)
                        return 1;
                else
                        return 0;

            }
            else if(neww.collum < curr.collum)
            {   for(row=curr.row+1, collum=curr.collum-1; row<neww.row; ++row, --collum)
                        if(board[row][collum]==' ')
                                continue;
                        else
                                return 0;
                if(color <= 0)
                        return 1;
                else
                        return 0;

            }
            else
                return 0;
        }
        else if(curr.row-neww.row == curr.collum-neww.collum)
        {
            if(neww.collum > curr.collum)
            {   for(row=curr.row+1, collum=curr.collum+1; row<neww.row; ++row, ++collum)
                        if(board[row][collum]==' ')
                                continue;
                        else
                                return 0;
                if(color <= 0)
                        return 1;
                else
                        return 0;

            }
            else if(neww.collum < curr.collum)
            {   for(row=curr.row-1, collum=curr.collum-1; row>neww.row; --row, --collum)
                        if(board[row][collum]==' ')
                                continue;
                        else
                                return 0;
                if(color <= 0)
                        return 1;
                else
                        return 0;

            }
            else
                return 0;
        }
        else
            return 0;
   }
//Valid moves of White Queen
   else if(unit == 'Q')
    {  board[curr.row][curr.collum] = 'R';
       i = validMove(curr,neww);

       board[curr.row][curr.collum] = 'B';
       j = validMove(curr,neww);

       board[curr.row][curr.collum] = 'Q';

       return i+j;
    }
//Valid moves of Black Queen
    else if(unit == 'q')
    {  board[curr.row][curr.collum] = 'r';
       i = validMove(curr,neww);

       board[curr.row][curr.collum] = 'b';
       j = validMove(curr,neww);

       board[curr.row][curr.collum] = 'q';

       return i+j;
    }
//Valid moves of White King
    else if(unit == 'K')
    {   if(neww.row==curr.row-1 && neww.collum==curr.collum && color!=0)
            return 1;
        else if(neww.row==curr.row-1 && neww.collum==curr.collum-1 && color!=0)
            return 1;
        else if(neww.row==curr.row && neww.collum==curr.collum-1 && color!=0)
            return 1;
        else if(neww.row==curr.row+1 && neww.collum==curr.collum-1 && color!=0)
            return 1;
        else if(neww.row==curr.row+1 && neww.collum==curr.collum && color!=0)
            return 1;
        else if(neww.row==curr.row+1 && neww.collum==curr.collum+1 && color!=0)
            return 1;
        else if(neww.row==curr.row && neww.collum==curr.collum+1 && color!=0)
            return 1;
        else if(neww.row==curr.row-1 && neww.collum==curr.collum+1 && color!=0)
            return 1;
        else
            return 0;
    }
// Valid moves of Black King
    else if(unit == 'k')
    {   if(neww.row==curr.row-1 && neww.collum==curr.collum && color<=0)
            return 1;
        else if(neww.row==curr.row-1 && neww.collum==curr.collum-1 && color<=0)
            return 1;
        else if(neww.row==curr.row && neww.collum==curr.collum-1 && color<=0)
            return 1;
        else if(neww.row==curr.row+1 && neww.collum==curr.collum-1 && color<=0)
            return 1;
        else if(neww.row==curr.row+1 && neww.collum==curr.collum && color<=0)
            return 1;
        else if(neww.row==curr.row+1 && neww.collum==curr.collum+1 && color<=0)
            return 1;
        else if(neww.row==curr.row && neww.collum==curr.collum+1 && color<=0)
            return 1;
        else if(neww.row==curr.row-1 && neww.collum==curr.collum+1 && color<=0)
            return 1;
        else
            return 0;
    }
}


#endif // functions_h
