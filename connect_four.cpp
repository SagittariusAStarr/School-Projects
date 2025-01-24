#include <iostream>
#include <stdlib.h>
#include <time.h>

#define NumberOfColumns 7
#define NumberOfRows 6

using namespace std;

string Board[NumberOfRows][NumberOfColumns];
int row;
int column;
int turn;
string character;
bool ValueForInnerWhile = true;

void FillBoardWithEmptySlots(){
    for(int i = 0; i < NumberOfRows; i++){
        for(int j = 0; j < NumberOfColumns; j++){
            Board[i][j] = " ";
        }
    }
    return;
}

void DisplayBoard(){
    cout<<" ";
    for(int i = 0; i < NumberOfColumns; i++){
        cout<<i+1<<" ";
    }
    cout<<endl;
    for(int j = 0; j < NumberOfRows; j++){
        cout<<"|";
        for(int k = 0; k < NumberOfColumns; k++){
            cout<<Board[j][k]<<"|";
        }
        cout<<endl;
    }
    return;
}

void DrowWhoStartsFirst(){
    srand(time(NULL));
    turn = rand()%2;
    return;
}

void PlayerChoice(){
    cout<<"Its "<<(turn == 1 ? "X":"O")<<" turn, choose which column you want to put your coin"<<endl;
    cin>>column;
    if(column > NumberOfColumns || column < 1){
        system("cls");
        DisplayBoard();
        cout<<"Wrong value, try again"<<endl;
        PlayerChoice();
        return;
    }
    return;
}

bool PutCoinsInBoard(){
    for(int i = NumberOfRows - 1; i > -1; i--){
        if(Board[i][column - 1] == " "){
            row = i + 1;
            Board[i][column - 1] = (turn == 1 ? "X":"O");
            character = Board[i][column - 1];
            turn == 1 ? turn = 0: turn = 1;
            return false;
        }
    }
    cout<<"This column is full, choose another one"<<endl;
    return true;
}

//TO DO: Finish CheckForWin because... it's... kinda working... but... accualy no
int CheckForWin(int r, int c){ 
    r--;
    c--;
    int stack = 0;
    for(int i = -3; i < 4; i++){
        if(stack == 4){
            return 1;
        }
        if(r + i > -1 && r + i < NumberOfRows){
            if(Board[r - i][c] == character){
                stack++;
            }
            else{
                stack = 0;
            }
        }
    }
    stack = 0;
    for(int i = -3; i < 4; i++){
        if(stack == 4){
            return 1;
        }
        if(r + i > -1 && r + i < NumberOfRows){
            if(Board[r][c + i] == character){
                stack++;
            }
            else{
                stack = 0;
            }
        }
    }
    stack = 0;
    for(int i = -3; i < 4; i++){
        if(stack == 4){
            return 1;
        }
        if(r + i > -1 && r + i < NumberOfRows && c + i > -1 && c + i < NumberOfColumns){
            if(Board[r + i][c + i] == character){
                stack++;
            }
            else{
                stack = 0;
            }
        }
    }
    stack = 0;
    for(int i = -3; i < 4; i++){
        if(stack == 4){
            return 1;
        }
        if(r + i > -1 && r + i < NumberOfRows && c + i > -1 && c + i < NumberOfColumns){
            if(Board[r - i][c + i] == character){
                stack++;
            }
            else{
                stack = 0;
            }
        }
    }
    stack = 0;
    return 0;
}

int main(){
    system("pause");
    system("cls");
    DrowWhoStartsFirst();
    FillBoardWithEmptySlots();
    DisplayBoard();
    while(true){
        while(ValueForInnerWhile){
            PlayerChoice();
            system("cls");
            ValueForInnerWhile = PutCoinsInBoard();
            DisplayBoard();
        }
        ValueForInnerWhile = true;
        if(CheckForWin(row, column) == 1){
            break;
        }
    }
    system("cls");
    cout<<(turn == 1 ? "O":"X")<<" has won"<<endl;
    system("pause");
    return 0;
}