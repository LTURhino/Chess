#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "con_lib.h"
#include "functions.c"


int main()
{   int turn=0;
    struct COORDS curr,neww;
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
                curr.row=c1-48;
                curr.collum=c2-48;
            }
            while(curr.row<0 || curr.row>7 || curr.collum<0 || curr.collum>7 || c3!=' ');



            do{
                scanf("%c",&c4);
                printf("\nEnter where to go: ");
                scanf("%c%c%c",&c1,&c3,&c2);
                neww.row=c1-48;
                neww.collum=c2-48;
            }
            while(neww.row<0 || neww.row>7 || neww.collum<0 || neww.collum>7 || c3!=' ');
            if(isupper(board[curr.row][curr.collum])>0)
            {   if(validMove(curr,neww))
                {
                    board[neww.row][neww.collum] = board[curr.row][curr.collum];
                    board[curr.row][curr.collum] = ' ';
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
        {   char c1,c2,c3,c4;
            do{
                scanf("%c",&c4); //Nesuprantu kodel cia reikia?????
                printf("\nEnter Blacks position row and collum: ");
                scanf("%c%c%c",&c1,&c3,&c2);
                curr.row=c1-48;
                curr.collum=c2-48;
            }
            while(curr.row<0 || curr.row>7 || curr.collum<0 || curr.collum>7 || c3!=' ');
            do{
                scanf("%c",&c4);
                printf("\nEnter where to go: ");
                scanf("%c%c%c",&c1,&c3,&c2);
                neww.row=c1-48;
                neww.collum=c2-48;
            }
            while(neww.row<0 || neww.row>7 || neww.collum<0 || neww.collum>7 || c3!=' ');
            if(islower(board[curr.row][curr.collum])>0)
            {   if(validMove(curr,neww))
                {
                    board[neww.row][neww.collum] = board[curr.row][curr.collum];
                    board[curr.row][curr.collum] = ' ';
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
    return 0;
}
