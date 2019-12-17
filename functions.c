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

typedef struct COORDS
{
    int row;
    int collum;
}COORDSS;

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
{   COORDSS pos;
    printf("\n");
    printf("       0  1  2  3  4  5  6  7\n");
    for(pos.row=0; pos.row<8; ++pos.row)
    {
        printf("    %d |",pos.row);
        for(pos.collum=0; pos.collum<8; ++pos.collum)
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
    {   COORDSS pos;
        for(pos.row=0; pos.row<8; ++pos.row)
        {
            for(pos.collum=0; pos.collum<8; ++pos.collum)
            {
                fwrite(&board[pos.row][pos.collum], sizeof(board[pos.row][pos.collum]), 1, gameSave);
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
    COORDSS pos;
    printf("\nGame was loaded\n");
    printf("\n");
    printf("       0  1  2  3  4  5  6  7\n");
    for( pos.row = 0; pos.row<8;++pos.row)
    {
        printf("    %d |",pos.row);
        for( pos.collum = 0; pos.collum<8; ++pos.collum)
        {
            fread(&board[pos.row][pos.collum], sizeof(board[pos.row][pos.collum]), 1, gameLoad);
            printf("%-2c|",board[pos.row][pos.collum]);
        }
        printf("\n");
    }
    fclose(gameLoad);
    delay(1000);


}

char * currentPosRow()
{
    char c1;
    do
    {
        printf("\nEnter current row ");
        scanf("%c",&c1);
        getchar();
        saveGame(c1);
        mainMenu(c1);
        c1-=48;
    }while(c1<0 || c1>7);
    return c1;
}
char * currentPosCollum()
{
    char c1;
    do
    {
        printf("\nEnter current collum ");
        scanf("%c",&c1);
        getchar();
        saveGame(c1);
        mainMenu(c1);
        c1-=48;
    }
    while(c1<0 || c1>7);

    return c1;

}

char * newPosRow()
{
    char c1;
    do
    {
        printf("\nEnter row where to go: ");
        scanf("%c",&c1);
        getchar();
        saveGame(c1);
        mainMenu(c1);
        c1-=48;
    }while(c1<0 || c1>7);
    return c1;
}

char * newPosCollum()
{
    char c1;
    do
    {
        printf("\nEnter collum where to go: ");
        scanf("%c",&c1);
        getchar();
        saveGame(c1);
        mainMenu(c1);
        c1-=48;
    }while(c1<0 || c1>7);

    return c1;
}

void mainMenu(int c1)
{
    if(c1 == 'm')
    {
        con_clear();
        autoSave();
        playersOption();
    }
    return;

}

void saveGame(int c1)
{
    if(c1 == 's')
    {
        printf("Game saved");
        delay(1000);
        autoSave();
        con_clear();
        display();
    }

}

char newGame(char player1, char player2)
{

    printf("Enter 1st players name\n");
    scanf("%s",&player1);
    printf("Enter 2nd palyers name\n");
    scanf("%s",&player2);
    return player1, player2;
}

void counting(int begin,int end)
{
    double elapsed = (double)(end - begin)/ CLOCKS_PER_SEC;
    printf("\nRun time of Program :%f s",elapsed);
}

int playersOption()
{   clock_t begin = clock();
    int choice;
    char player1,player2;
    printf("\n    1:New game\n    2:Load game\n    3:Small Rules\n    Any other character:Quit\n    Your choice:");
    scanf(" %d",&choice);
    getchar();
    if(choice==1)
    {
        newGame(player1,player2);
        con_clear();
        display();
    }
    else if(choice==2)
    {   con_clear();
        load();
    }
    else if(choice==3)
    {   con_clear();
        help();
    }
    else
    {
        printf("Quiting...");
        delay(2000);
        clock_t end = clock();
        counting(begin,end);
        exit(0);
    }
}

void help()
{   FILE *helpOpen;
    helpOpen = fopen("ReadMe.txt", "r");
    int c;
    while((c = getc(helpOpen)) != EOF)
        printf("%c", c);
    printf("Type anything to return to main menu:");
    char x;
    scanf("%c",&x);
    con_clear();
    playersOption();
}


void highScore(FILE **highscore)
{
    if(!highscore)
    {
        printf("Error opening a file");
    }

}

void log(int round,int turn,char x,char x1, char x2, char x3,FILE **logOpen)
{

    if(!log)
    {
        printf("Error opening a file");
    }
    else if(turn%2 == 0)
        {
            fprintf(*logOpen,"%d move\nWhites moves:\nCurrent row: %d collum : %d\nNew row: %d collum : %d\n",round,x,x1,x2,x3);
        }
        else
            fprintf(*logOpen,"%d move\nBlacks moves:\nCurrent row: %d collum : %d\nNew row: %d collum : %d\n",round,x,x1,x2,x3);
++round;
}
//Tests for valid moves
int validMove(COORDSS curr, COORDSS neww)
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

int validMove2(COORDSS curr, COORDSS neww)
{
    int s;
    char unit,newunit;
    COORDSS pos;

    unit = board[curr.row][curr.collum];
    newunit = board[neww.row][neww.collum];

    s = validMove(curr,neww);

    if(s == 0)
        return 0;
    else if(s == 1)
    {
        if(islower(unit) == 0)
        {   board[neww.row][neww.collum] = unit;
            board[curr.row][curr.collum] = ' ';
            for(pos.row=0; pos.row<8; ++pos.row)
                for(pos.collum=0; pos.collum<8; ++pos.collum)
                    if(whiteKingUnderattack2(pos))
                    {   board[neww.row][neww.collum] = newunit;
                        board[curr.row][curr.collum] = unit;
                        return 0;
                    }
             board[neww.row][neww.collum] = newunit;
             board[curr.row][curr.collum] = unit;
             return 1;
        }
        else if(islower(unit) > 0)
        {   board[neww.row][neww.collum] = unit;
            board[curr.row][curr.collum] = ' ';
            for(pos.row=0; pos.row<8; ++pos.row)
                for(pos.collum=0; pos.collum<8; ++pos.collum)
                    if(blackKingUnderattack2(pos))
                    {   board[neww.row][neww.collum] = newunit;
                        board[curr.row][curr.collum] = unit;
                        return 0;
                    }
             board[neww.row][neww.collum] = newunit;
             board[curr.row][curr.collum] = unit;
             return 1;
        }


    }


}

int whiteTotalValidMoves()
{
    int noValidMoves = 0;
    COORDSS curr,neww;

    for(curr.row=0; curr.row<8; ++curr.row)
        for(curr.collum=0; curr.collum<8; ++curr.collum)
            if(isupper(board[curr.row][curr.collum]) > 0)
                for(neww.row=0; neww.row<8; ++neww.row)
                    for(neww.collum=0; neww.collum<8; ++neww.collum)
                        if(validMove2(curr,neww))
                            ++noValidMoves;


    printf("\n%d validmoves\n", noValidMoves);
    return noValidMoves;
}

int blackTotalValidMoves()
{
    int noValidMoves = 0;
    COORDSS curr,neww;

    for(curr.row=0; curr.row<8; ++curr.row)
        for(curr.collum=0; curr.collum<8; ++curr.collum)

            if(islower(board[curr.row][curr.collum]) > 0)

                for(neww.row=0; neww.row<8; ++neww.row)
                    for(neww.collum=0; neww.collum<8; ++neww.collum)

                        if(validMove2(curr,neww))
                            ++noValidMoves;


    printf("\n%d validmoves\n", noValidMoves);
    return noValidMoves;
}

void whiteCheckmate()
{
    if(whiteKingUnderattack()==1 && whiteTotalValidMoves()==0)
    {       printf("\nIt's Checkmate!!Black Wins\n");
            exit(0);
    }

}

void blackCheckmate()
{
    if(blackKingUnderattack()==1 && blackTotalValidMoves()==0)
    {       printf("\nIt's Checkmate!!White Wins\n");
            exit(0);
    }

}

void whiteCheck()
{
    if(whiteKingUnderattack()==1 && whiteTotalValidMoves()>0)
            printf("\nIt's Check\n");
            delay(2000);

}

void blackCheck()
{
    if(blackKingUnderattack()==1 && blackTotalValidMoves()>0)
            printf("\nIt's Check\n");
            delay(2000);

}

void whiteStalemate()
{
    if(whiteKingUnderattack()==0 && whiteTotalValidMoves()==0)
    {   printf("\nIts Draw!!Stalemate\n");
        exit(0);
    }

}

void blackStalemate()
{
    if(blackKingUnderattack()==0 && blackTotalValidMoves()==0)
    {   printf("\nIts Draw!!Stalemate\n");
        exit(0);
    }

}

int blackKingUnderattack2(COORDSS curr)
{
    int i,j,row,collum;
    char unit;
    COORDSS bkpos;

    for(i=0; i<8; ++i)
        for(j=0; j<8; ++j)
            if(board[i][j] == 'k')
                    goto out;
    out:
    bkpos.row=i;
    bkpos.collum=j;

    unit=board[curr.row][curr.collum];

    if(unit == 'K')
    {   if(bkpos.row==curr.row-1 && bkpos.collum==curr.collum)
            return 1;
        else if(bkpos.row==curr.row-1 && bkpos.collum==curr.collum-1)
            return 1;
        else if(bkpos.row==curr.row && bkpos.collum==curr.collum-1)
            return 1;
        else if(bkpos.row==curr.row+1 && bkpos.collum==curr.collum-1)
            return 1;
        else if(bkpos.row==curr.row+1 && bkpos.collum==curr.collum)
            return 1;
        else if(bkpos.row==curr.row+1 && bkpos.collum==curr.collum+1)
            return 1;
        else if(bkpos.row==curr.row && bkpos.collum==curr.collum+1)
            return 1;
        else if(bkpos.row==curr.row-1 && bkpos.collum==curr.collum+1)
            return 1;
        else
            return 0;
    }

    else if(unit == 'Q')
    {   board[curr.row][curr.collum] = 'R';
        i=blackKingUnderattack2(curr);

        board[curr.row][curr.collum] = 'B';
        j=blackKingUnderattack2(curr);

        board[curr.row][curr.collum] = 'Q';

        return i+j;
    }

    else if(unit == 'P')
    {
        if(bkpos.row==curr.row-1 && bkpos.collum==curr.collum+1)
                return 1;
        else if(bkpos.row==curr.row-1 && bkpos.collum==curr.collum-1)
                return 1;
        else
                return 0;
    }

    else if(unit == 'R')
    {
            if(bkpos.collum == curr.collum)
            {   if(bkpos.row < curr.row)
                {   for(row=curr.row-1; row>bkpos.row; --row)
                        if(board[row][curr.collum] == ' ')
                                continue;
                        else
                                return 0;
                    return 1;
                }
                else if(bkpos.row > curr.row)
                {   for(row=curr.row+1; row<bkpos.row; ++row)
                        if(board[row][curr.collum] == ' ')
                                continue;
                        else
                                return 0;
                    return 1;
                }

            }
            else if(bkpos.row == curr.row)
            {   if(bkpos.collum < curr.collum)
                {   for(collum=curr.collum-1; collum>bkpos.collum; --collum)
                        if(board[curr.row][collum] == ' ')
                                continue;
                        else
                                return 0;
                    return 1;
                }
                else if(bkpos.collum > curr.collum)
                {   for(collum=curr.collum+1; collum<bkpos.collum; ++collum)
                        if(board[curr.row][collum] == ' ')
                                continue;
                        else
                                return 0;
                    return 1;
                }

            }
            else
                return 0;

    }

    else if(unit == 'H')
    {
        if(bkpos.row==curr.row-2 && bkpos.collum==curr.collum+1)
                return 1;
        else if(bkpos.row==curr.row-2 && bkpos.collum==curr.collum-1)
                return 1;
        else if(bkpos.row==curr.row-1 && bkpos.collum==curr.collum-2)
                return 1;
        else if(bkpos.row==curr.row+1 && bkpos.collum==curr.collum-2)
                return 1;
        else if(bkpos.row==curr.row+2 && bkpos.collum==curr.collum-1)
                return 1;
        else if(bkpos.row==curr.row+2 && bkpos.collum==curr.collum+1)
                return 1;
        else if(bkpos.row==curr.row+1 && bkpos.collum==curr.collum+2)
                return 1;
        else if(bkpos.row==curr.row-1 && bkpos.collum==curr.collum+2)
                return 1;
        else
                return 0;

    }

    else if(unit == 'B')
    {

        if(curr.row-bkpos.row == bkpos.collum-curr.collum)
        {
            if(bkpos.collum > curr.collum)
            {   for(row=curr.row-1, collum=curr.collum+1; row>bkpos.row; --row, ++collum)
                        if(board[row][collum] == ' ')
                                continue;
                        else
                                return 0;
                return 1;

            }
            else if(bkpos.collum < curr.collum)
            {   for(row=curr.row+1, collum=curr.collum-1; row<bkpos.row; ++row, --collum)
                        if(board[row][collum] == ' ')
                                continue;
                        else
                                return 0;
                return 1;

            }

        }
        else if(curr.row-bkpos.row == curr.collum-bkpos.collum)
        {
            if(bkpos.collum > curr.collum)
            {   for(row=curr.row+1, collum=curr.collum+1; row<bkpos.row; ++row, ++collum)
                        if(board[row][collum] == ' ')
                                continue;
                        else
                                return 0;
                return 1;

            }
            else if(bkpos.collum < curr.collum)
            {   for(row=curr.row-1, collum=curr.collum-1; row>bkpos.row; --row, --collum)
                        if(board[row][collum] == ' ')
                                continue;
                        else
                                return 0;
                return 1;

            }

        }
        else
            return 0;
    }

    else
        return 0;


}

int whiteKingUnderattack2(COORDSS curr)
{
    int i,j,row,collum;
    char unit;
    COORDSS wkpos;

    for(i=0; i<8; ++i)
        for(j=0; j<8; ++j)
            if(board[i][j] == 'K')
                    goto out2;
    out2:
    wkpos.row=i;
    wkpos.collum=j;

    unit=board[curr.row][curr.collum];

    if(unit == 'k')
    {   if(wkpos.row==curr.row-1 && wkpos.collum==curr.collum)
            return 1;
        else if(wkpos.row==curr.row-1 && wkpos.collum==curr.collum-1)
            return 1;
        else if(wkpos.row==curr.row && wkpos.collum==curr.collum-1)
            return 1;
        else if(wkpos.row==curr.row+1 && wkpos.collum==curr.collum-1)
            return 1;
        else if(wkpos.row==curr.row+1 && wkpos.collum==curr.collum)
            return 1;
        else if(wkpos.row==curr.row+1 && wkpos.collum==curr.collum+1)
            return 1;
        else if(wkpos.row==curr.row && wkpos.collum==curr.collum+1)
            return 1;
        else if(wkpos.row==curr.row-1 && wkpos.collum==curr.collum+1)
            return 1;
        else
            return 0;
    }

    else if(unit == 'q')
    {   board[curr.row][curr.collum] = 'r';
        i=whiteKingUnderattack2(curr);

        board[curr.row][curr.collum] = 'b';
        j=whiteKingUnderattack2(curr);

        board[curr.row][curr.collum] = 'q';

        return i+j;
    }

    else if(unit == 'p')
    {
        if(wkpos.row==curr.row+1 && wkpos.collum==curr.collum+1)
                return 1;
        else if(wkpos.row==curr.row+1 && wkpos.collum==curr.collum-1)
                return 1;
        else
                return 0;
    }

    else if(unit == 'r')
    {
            if(wkpos.collum == curr.collum)
            {   if(wkpos.row < curr.row)
                {   for(row=curr.row-1; row>wkpos.row; --row)
                        if(board[row][curr.collum] == ' ')
                                continue;
                        else
                                return 0;
                    return 1;
                }
                else if(wkpos.row > curr.row)
                {   for(row=curr.row+1; row<wkpos.row; ++row)
                        if(board[row][curr.collum] == ' ')
                                continue;
                        else
                                return 0;
                    return 1;
                }

            }
            else if(wkpos.row == curr.row)
            {   if(wkpos.collum < curr.collum)
                {   for(collum=curr.collum-1; collum>wkpos.collum; --collum)
                        if(board[curr.row][collum] == ' ')
                                continue;
                        else
                                return 0;
                    return 1;
                }
                else if(wkpos.collum > curr.collum)
                {   for(collum=curr.collum+1; collum<wkpos.collum; ++collum)
                        if(board[curr.row][collum] == ' ')
                                continue;
                        else
                                return 0;
                    return 1;
                }

            }
            else
                return 0;

    }

    else if(unit == 'h')
    {
        if(wkpos.row==curr.row-2 && wkpos.collum==curr.collum+1)
                return 1;
        else if(wkpos.row==curr.row-2 && wkpos.collum==curr.collum-1)
                return 1;
        else if(wkpos.row==curr.row-1 && wkpos.collum==curr.collum-2)
                return 1;
        else if(wkpos.row==curr.row+1 && wkpos.collum==curr.collum-2)
                return 1;
        else if(wkpos.row==curr.row+2 && wkpos.collum==curr.collum-1)
                return 1;
        else if(wkpos.row==curr.row+2 && wkpos.collum==curr.collum+1)
                return 1;
        else if(wkpos.row==curr.row+1 && wkpos.collum==curr.collum+2)
                return 1;
        else if(wkpos.row==curr.row-1 && wkpos.collum==curr.collum+2)
                return 1;
        else
                return 0;

    }


    else if(unit == 'b')
    {

        if(curr.row-wkpos.row == wkpos.collum-curr.collum)
        {
            if(wkpos.collum > curr.collum)
            {   for(row=curr.row-1, collum=curr.collum+1; row>wkpos.row; --row, ++collum)
                        if(board[row][collum] == ' ')
                                continue;
                        else
                                return 0;
                return 1;

            }
            else if(wkpos.collum < curr.collum)
            {   for(row=curr.row+1, collum=curr.collum-1; row<wkpos.row; ++row, --collum)
                        if(board[row][collum] == ' ')
                                continue;
                        else
                                return 0;
                return 1;

            }

        }
        else if(curr.row-wkpos.row == curr.collum-wkpos.collum)
        {
            if(wkpos.collum > curr.collum)
            {   for(row=curr.row+1, collum=curr.collum+1; row<wkpos.row; ++row, ++collum)
                        if(board[row][collum] == ' ')
                                continue;
                        else
                                return 0;
                return 1;

            }
            else if(wkpos.collum < curr.collum)
            {   for(row=curr.row-1, collum=curr.collum-1; row>wkpos.row; --row, --collum)
                        if(board[row][collum] == ' ')
                                continue;
                        else
                                return 0;
                return 1;

            }

        }
        else
            return 0;
    }

    else
        return 0;


}

int whiteKingUnderattack()
{   COORDSS pos;

    for(pos.row=0; pos.row<8; ++pos.row)
                for(pos.collum=0; pos.collum<8; ++pos.collum)
                    if(whiteKingUnderattack2(pos))
                        return 1;
    return 0;
}

int blackKingUnderattack()
{   COORDSS pos;

    for(pos.row=0; pos.row<8; ++pos.row)
                for(pos.collum=0; pos.collum<8; ++pos.collum)
                    if(blackKingUnderattack2(pos))
                        return 1;
    return 0;
}

void whitePromote()
{   int i=0,j;
    char unit;
    for(j=0; j<8; ++j)
        if(board[i][j] == 'P')
           while(1)
            {    printf("\nPromote your pawn to any one of these:(Q R B H) ");fflush(stdin);
                 scanf("%c",&unit);
                 switch(unit)
                 {   case 'Q': board[i][j]='Q';
                               return;
                     case 'R': board[i][j]='R';
                               return;
                     case 'B': board[i][j]='B';
                               return;
                     case 'H': board[i][j]='H';
                               return;
                     default : printf("Invalid choice Try Again!!");

                 }

            }


}

void blackPromote()
{   int i=7,j;
    char unit;
    for(j=0; j<8; ++j)
        if(board[i][j] == 'p')
           while(1)
            {    printf("\nPromote your pawn to any one of these:(q r b h) ");fflush(stdin);
                 scanf("%c",&unit);
                 switch(unit)
                 {   case 'q': board[i][j]='q';
                               return;
                     case 'r': board[i][j]='r';
                               return;
                     case 'b': board[i][j]='b';
                               return;
                     case 'h': board[i][j]='h';
                               return;
                     default : printf("Invalid choice Try Again!!");
                 }

            }


}


#endif // functions_h
