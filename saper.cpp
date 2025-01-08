#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <stdlib.h>
#define chance 20 //setting chance of a bomb
#define size 15 //setting size of a side of square board

using namespace std;
                                        //To do: 1) Fix zero auto filler (line 31) 2) Write normal roles (line 67)
int boardHidden[size][size];
char boardShown[size][size];
int row;
int column;
bool value = true;

void Game(int x, int y){ //checking if player stepped on a bomb
    if(x < 0 || y < 0){ //checking for eventual negative coordinates
        return;
    }
    if(boardHidden[x][y] < 0){
        boardShown[x][y] = 'x';
        value = false;
    }
    else{
        switch (boardHidden[x][y])
        {
        case 0:
            boardShown[x][y] = '0';
            /*for(int i = -1; i < 2; i++){
                for(int j = -1; j < 2; j++){
                    if(i != 0 && j != 0 && boardShown[x + i][y + j] == ' '){ //FIX THE ZERO AUTO FILLER PROBLEM
                        Game(x + i, y + j);
                    }
                }
            }*/
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
        value = true;
    }
    return;
}

void rules(){ //self explanatory
    cout<<"-=-=-=-=-=-=-=-=-=-=-=-"<<endl;
    cout<<"Rules:"<<endl;
    cout<<"You are supposed to give integer values and only in "<<size<<" range, anyways, you are not stupid, figure it out yourself"<<endl;
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
    return;
}

void generatingboard(int banedI, int banedJ) { //generates accual and hidden board
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (rand() % 100 + 1 <= chance && banedI != i && banedJ != j)
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
    return;
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
    cout<<endl<<"   ";
    for(int i = 0; i < size; i++){
        (i > 8)? cout<<i+1<<" ":cout<<" "<<i+1<<" "; //if you finding this segment ugly, I understend you
    }
    cout<<"column"<<endl;
    for (int i = 0; i < size; i++) {
        (i > 8)? cout<<i+1<<"| " : cout<<i+1<<" | ";
        for (int j = 0; j < size; j++) {   
            cout<<boardShown[i][j]<<"| ";
        }
        cout<<endl;
    }
    cout<<"row"<<endl<<endl;
    return;
}

int main() {
    rules();
    Sleep(200);
    srand(time(NULL));
    clearingshownboard();
    ShowBoard();
    askForLocationToCheck();
    Game(row - 1, column - 1);        
    system("cls");
    generatingboard(row - 1, column - 1);
    //boardsExposer(); //only for debug
    ShowBoard();
    while(value){
        askForLocationToCheck();
        system("cls");
        Game(row - 1, column - 1);        
        ShowBoard();
    }
    cout<<"Unfortunatle, you steped on a bomb"<<endl;
    system("pause");
    return 0;
}