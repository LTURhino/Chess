//INFO2_Rokas_Sireikis_ND1
//Chess B12
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "con_lib.h"
#include "functions.c"


int main()
{

    FILE *logOpen = fopen("log.txt","w");
    FILE *highscore = fopen("highscore.txt","r+");
    int round = 1;
    int turn=0;
    COORDSS curr,neww;
    char player1,player2;
    playersOption();
    int size=8;
    while(1)
    {
        if(turn%2 == 0)
        {
            printf("\n        %s turn\n",player1);
            curr.row=currentPosRow();
            curr.collum=currentPosCollum();
            neww.row=newPosRow();
            neww.collum=newPosCollum();
            log(round,turn,curr.row,curr.collum,neww.row,neww.collum,&logOpen);
            if(isupper(board[curr.row][curr.collum])>0)
            {   if(validMove2(curr,neww))
                {
                    board[neww.row][neww.collum] = board[curr.row][curr.collum];
                    board[curr.row][curr.collum] = ' ';
                    whitePromote();
                    blackCheckmate();
                    blackStalemate();
                    blackCheck();
                }
                else
                {
                    printf("\nInvalid move!");
                    delay(1000);
                    ++turn;
                }
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
        {
            printf("\n        Blacks turn\n");
            curr.row=currentPosRow();
            curr.collum=currentPosCollum();
            neww.row=newPosRow();
            neww.collum=newPosCollum();
            log(round,turn,curr.row,curr.collum,neww.row,neww.collum,&logOpen);
            if(islower(board[curr.row][curr.collum])>0)
            {   if(validMove2(curr,neww))
                {
                    board[neww.row][neww.collum] = board[curr.row][curr.collum];
                    board[curr.row][curr.collum] = ' ';
                    blackPromote();
                    whiteCheckmate();
                    whiteStalemate();
                    whiteCheck();
                }
                else
                {
                    printf("\nInvalid move!");
                    delay(1000);
                    ++turn;
                }
            }
            else
            {
                ++turn;
                printf("\nIt's Black turn! Try Again\n");
                delay(2000);
            }
            con_clear();
            display();
            ++turn;
        }
        autoSave();
    }
    fclose(logOpen);
    return 0;
}
