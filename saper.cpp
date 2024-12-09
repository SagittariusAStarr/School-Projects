#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <stdlib.h>
#define chance 20 //setting chance of a bomb
#define size 15 //setting size of a side of square board

using namespace std;

int boardHidden[size][size];
char boardShown[size][size];
int row;
int column;
bool value = true;

bool Game(int x, int y){ //checking if player stepped on a bomb
    system("cls");
    if(boardHidden[x][y] < 0){
        boardShown[x][y] = 'x';
        return false;
    }
    else{
        switch (boardHidden[x][y])
        {
        case 0:
            boardShown[x][y] = '0';
            break;
        case 1:
            boardShown[x][y] = '1';
            break;
        case 2:
            boardShown[x][y] = '2';
            break;
        case 3:
            boardShown[x][y] = '3';
            break;
        case 4:
            boardShown[x][y] = '4';
            break;
        case 5:
            boardShown[x][y] = '5';
            break;
        case 6:
            boardShown[x][y] = '6';
            break;
        case 7:
            boardShown[x][y] = '7';
            break;
        case 8:
            boardShown[x][y] = '8';
            break;
        }
        return true;
    }
}

void rules(){ //sefl explanatory
    cout<<"-=-=-=-=-=-=-=-=-=-=-=-"<<endl;
    cout<<"Rules:"<<endl;
    cout<<"You are suppose to give integer values and only in "<<size<<" range, anyway, you are not stupid find out yourself"<<endl;
    cout<<"-=-=-=-=-=-=-=-=-=-=-=-"<<endl;
    system("pause");
    system("cls");
    return;
}

void askForLocationToCheck(){ //asks for coordinates of palce player wonts to check
    cout<<"Insert number of a row and column"<<endl;
    cout<<"Row: ";
    cin>>row;
    if(row < 1 || row > size){
        cout<<"You went out of range, silly"<<endl;
        Sleep(1000);
        askForLocationToCheck();
        return;
    }
    cout<<"Column: ";
    cin>>column;
    if(column < 1 || column > size){
        cout<<"You went out of range, silly"<<endl;
        Sleep(1000);
        askForLocationToCheck();
        return;
    }
    cout<<endl;
    return;
}

void clearingshownboard(){ //generates clear board
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            boardShown[i][j] = ' ';
        }
    }
}

void generatingboard() { //generates accual and hidden board
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (rand() % 100 + 1 <= chance)
                boardHidden[i][j] = -9;
            else
                boardHidden[i][j] = 0;
        }
    }

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (boardHidden[i][j] < 0) {
                for (int x = i - 1; x <= i + 1; x++) {
                    for (int y = j - 1; y <= j + 1; y++) {
                        if (x >= 0 && x < size && y >= 0 && y < size)
                            boardHidden[x][y] = boardHidden[x][y] + 1;
                    }
                }
            }
        }
    }
}

void boardsExposer() { //expose whole board with all fields already shown, only for debug
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {   
            if(boardHidden[i][j] < 0){
                cout<<"| x|";
            }
            else{
                cout<<"| "<<boardHidden[i][j]<<"|";
            }
        }
        cout<<endl;
    }
    return;
}

void ShowBoard(){ //self explanatory
    cout<<endl;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {   
            cout<<"| "<< boardShown[i][j]<<"|";
        }
        cout<<endl;
    }
}

int main() {
    rules();
    Sleep(200);
    srand(time(NULL));
    generatingboard();
    clearingshownboard();
    //boardsExposer(); //only for debug
    while(value){
        ShowBoard();
        askForLocationToCheck();
        value = Game(row - 1, column - 1);        
    }
    ShowBoard();
    cout<<"Unfortunatle, you steped on a bomb"<<endl;
    system("pause");
    system("cls");
    return 0;
}