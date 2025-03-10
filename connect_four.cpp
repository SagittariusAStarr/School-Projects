/*
I forgot to add comms, therefore good luck finding out what is what
or not 'couse it is accualy simple code and project I guess (ofc if I didn't fucked it up somewhere)
but it's working, I guess (I should stop overuse "I guess")
*/

/*
EDIT: 2 To do:
(DONE)Bug #1 when someone put char insted of int when choosing column, 
game crashes (obviusly, 'couse I'm dump and forgor about that), I suppose
(DONE) Add marker to show where four has been connected
(DONE) Add settings with board customisation
(IDEA) Add something that can detect when board is full an settle draw
*/


#include <iostream>
#include <string>
#include <conio.h>
#include <windows.h>

#define NumberOfColumnsS 15
#define NumberOfRowsS 20

using namespace std;

string Board[NumberOfRowsS][NumberOfColumnsS], character;
int row, column, turn, onoff, NumberOfRows = 6, NumberOfColumns = 7, intHolder;
char choice;
bool ValueForInnerWhile = true, boolean1;

void FillBoardWithEmptySlots(){
    for(int i = 0; i < NumberOfRows; i++){
        for(int j = 0; j < NumberOfColumns; j++){
            Board[i][j] = " ";
        }
    }
    return;
}

void Menu(){
    system("cls");
    boolean1 = true;
    onoff = 0;
    while(boolean1){
        system("cls");
        cout<<"-=-=-=-<MENU>-=-=-=-"<<endl;
        cout<<'\t'<<"1) Play"<<endl;
        cout<<'\t'<<"2) Settings"<<endl;
        cout<<'\t'<<"3) Exit game"<<endl;
        cout<<"-=-=-=-=-><-=-=-=-=-"<<endl;
        choice = getch();
        switch(choice){
            case '1':
                boolean1 = false;
                onoff = 1;
                break;
            case '2':
                boolean1 = false;
                onoff = 2;
                break;
            case '3':
                exit(0);
                break;
            default:
                cout<<"You stupid, did it by mistake or fuckin' with me?"<<endl<<"Choose again";
                Sleep(1000);
                system("cls");
                break;
        }
    }
    system("cls");
    return;
}

void SettingsMenu(){
    system("cls");
    boolean1 = true;
    onoff = 0;
    while(boolean1){
        system("cls");
        cout<<"-=-=-=-=-<SETTINGS>-=-=-=-=-"<<endl;
        cout<<'\t'<<"1) Change max row number"<<endl;
        cout<<'\t'<<"2) Change max column number"<<endl;
        cout<<'\t'<<"3) Exit settings"<<endl;
        cout<<"-=-=-=-=-=-=-><-=-=-=-=-=-=-"<<endl;
        choice = getch();
        switch(choice){
            case '1':
                boolean1 = false;
                onoff = 1;
                break;
            case '2':
                boolean1 = false;
                onoff = 2;
                break;
            case '3':
                boolean1 = false;
                onoff = 3;
                break;
            default:
                cout<<"You stupid, did it by mistake or fuckin' with me?"<<endl<<"Choose again";
                Sleep(1000);
                system("cls");
                break;
        }
    }
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
    cout<<"Its ";
    turn == 1 ? cout<<"\033[31m"<<"X"<<"\033[0m" : cout<<"\033[34m"<<"O"<<"\033[0m";
    cout<<" turn, choose which column you want to put your coin"<<endl;
    if(!(cin>>column)){
        cin.clear();
        cin.ignore(INT_MAX, '\n'); 
        /*Previous 2 lines clears input, idk how exacly, but its work and 
        Stack Overflow said so, therefore I wont ask questions, I suppose */
        system("cls");
        DisplayBoard();
        cout<<"Wrong type, insert integer"<<endl;
        PlayerChoice();
        return;
    }
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
            Board[i][column - 1] = (turn == 1 ? "\033[31mX\033[0m":"\033[34mO\033[0m");
            character = Board[i][column - 1];
            turn == 1 ? turn = 0: turn = 1;
            return false;
        }
    }
    cout<<"This column is full, choose another one"<<endl;
    return true;
}

int CheckForWin(int r, int c){ 
    r--;
    c--;
    int x = r;
    int y = c;
    int stack = 0;
    int StR, StC, mark = 0;
    for(int i = 0; i < NumberOfColumns; i++){
        if(Board[r][i] == character){
            stack++;
            if(mark == 0){
                StC = i;
                mark = 1;
            }
        }
        else{
            stack = 0;
            mark = 0;
        }
        if(stack == 4){
            for(int j = StC; j < StC + 4; j++){
                Board[r][j] = (turn == 1 ? "\033[34m-\033[0m":"\033[31m-\033[0m");
            }
            return 1;
        }
    }
    mark = 0;
    stack = 0;
    for(int i = NumberOfRows - 1; i >= 0; i--){
        if(Board[i][c] == character){
            stack++;
            if(mark == 0){
                StR = i;
                mark = 1;
            }
        }
        else{
            stack = 0;
            mark = 0;
        }
        if(stack == 4){
            for(int j = StR; j > StR - 4; j--){
                Board[j][c] = (turn == 1 ? "\033[34m|\033[0m":"\033[31m|\033[0m");
            }
            return 1;
        }
    }
    stack = 0;
    mark = 0;
    while(true){
        if(x == 0 || y == 0) break;
        x--;
        y--;
    }
    while(x != NumberOfRows && y != NumberOfColumns){
        if(Board[x][y] == character){
            stack++;
            if(mark == 0){
                StR = x;
                StC = y;
                mark = 1;
            }
        }
        else{
            stack = 0;
            mark = 0;
        }
        if(stack == 4){
            for(int i = 0; i < 4; i++){
                Board[StR + i][StC + i] = (turn == 1 ? "\033[34m\\\033[0m":"\033[31m\\\033[0m");
            }
            return 1;
        }
        x++;
        y++;
    }
    stack = 0;
    mark = 0;
    x = r;
    y = c;
    while(true){
        if(x == NumberOfRows || y == 0) break;
        x++;
        y--;
    }
    while(x != 0 && y != NumberOfColumns){
        if(Board[x][y] == character){
            stack++;
            if(mark == 0){
                StR = x;
                StC = y;
                mark = 1;
            }
        }
        else{
            stack = 0;
            mark = 0;
        }
        if(stack == 4){
            for(int i = 0; i < 4; i++){
                Board[StR - i][StC + i] = (turn == 1 ? "\033[34m/\033[0m":"\033[31m/\033[0m");
            }
            return 1;
        }
        x--;
        y++;
    }
    return 0;
}

void EndingMessage(){
    cout<<endl<<"-=-=-=-=-=-=-=-=-"<<endl;
    cout<<(turn == 1 ? "\033[34mO\033[0m":"\033[31mX\033[0m")<<" has won"<<endl;
    cout<<"-=-=-=-=-=-=-=-=-"<<endl;
    return;
}

void SetMaxColumn(){
    system("cls");
    cout<<"-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-"<<endl;
    cout<<"\t Set max column number (range: 4-9, current: "<<NumberOfColumns<<"): ";
    if(!(cin>>intHolder)){
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout<<endl<<"-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-"<<endl;
        cout<<"Wrong variability";
        Sleep(1500);
        return;
    }
    cout<<endl<<"-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-"<<endl;
    if(intHolder >= 4 && intHolder <= 9){
        NumberOfColumns = intHolder;
        cout<<"Successfuly changed max column number to "<<NumberOfColumns<<endl;
        system("pause");
    }
    else{
        cout<<"Out of range"<<endl;
        system("pause");
    }
    return;
}

void SetMaxRow(){
    system("cls");
    cout<<"-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-"<<endl;
    cout<<"\t Set max row number (range 4-20, current: "<<NumberOfRows<<"): ";
    if(!(cin>>intHolder)){
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout<<endl<<"-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-"<<endl;
        cout<<"Wrong variability";
        Sleep(1500);
        return;
    }
    cout<<endl<<"-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-"<<endl;
    if(intHolder >= 4 && intHolder <= 20){
        NumberOfRows = intHolder;
        cout<<"Successfuly changed max row number to "<<NumberOfRows<<endl;
        system("pause");
    }
    else{
        cout<<"Out of range"<<endl;
        system("pause");
    }
    return;
}

int main(){
    while(true){
        Menu();
        if(onoff == 1){
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
            DisplayBoard();
            EndingMessage();
            system("pause");
        }
        else if(onoff == 2){
            while(true){
                SettingsMenu();
                if(onoff == 1){
                    system("cls");
                    SetMaxRow();
                }
                else if(onoff == 2){
                    system("cls");
                    SetMaxColumn();
                }
                else if(onoff == 3){
                    break;
                }
                else{
                    system("cls");
                    cout<<"Something went wrong"<<endl;
                    Sleep(2500);
                    system("cls");
                }
            }
        }
        else{
            system("cls");
            cout<<"Something went wrong"<<endl;
            Sleep(2500);
            system("cls");
        }
    }
    return 0;
}