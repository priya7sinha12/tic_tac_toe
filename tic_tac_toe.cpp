#include <iostream>
#include <bits/stdc++.h>
using namespace std;

#define userMove 'X'
#define computerMove 'O'
#define n 3

char board[n][n];

void beginGame(){
    cout<<"\n\t\t\tGame Begins....."<<endl;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            board[i][j]=' ';
        }
    }
    cout<<"Rules:\n\nTic Tac Toe is a classic game played on a 3x3 grid. Two players take turns marking X or O in empty cells. The objective is to form a line of three symbols horizontally, vertically, or diagonally. The first player to achieve this wins. The game starts with an empty grid, and players alternate turns. Each turn, a player chooses an unoccupied cell and places their symbol. If all cells are filled without a winner, the game ends in a draw. No cell can be occupied twice. The game continues until there is a winner, a draw, or all cells are filled."<<endl<<endl;
    cout<<"Choose the respective cell number to fill in that cell"<<endl<<endl;
    cout<<"\t\t\t1 | 2 | 3\n";
    cout<<"\t\t\t---------\n";
    cout<<"\t\t\t4 | 5 | 6\n";
    cout<<"\t\t\t---------\n";
    cout<<"\t\t\t7 | 8 | 9\n\n\n";
}

void showBoard(){
    cout<<"\n\t\t\t"<<board[0][0]<<" | "<<board[0][1]<<" | "<<board[0][2]<<endl;
    cout<<"\t\t\t---------\n";
    cout<<"\t\t\t"<<board[1][0]<<" | "<<board[1][1]<<" | "<<board[1][2]<<endl;
    cout<<"\t\t\t---------\n";
    cout<<"\t\t\t"<<board[2][0]<<" | "<<board[2][1]<<" | "<<board[2][2]<<endl<<endl;
}

bool isWinnerFound(){
    for(int i=0;i<n;i++){
        if(board[i][0]==board[i][1]&&board[i][1]==board[i][2]&&board[i][1]!=' '){  //to check in row
            return true;
        }
        if(board[0][i]==board[1][i]&&board[1][i]==board[2][i]&&board[1][i]!=' '){ //to check in column
            //cout<<"hiii";
            return true;
        }
    }

    if(board[0][0]==board[1][1]&&board[1][1]==board[2][2]&&board[1][1]!=' '){
        return true;
    } 
    if(board[0][2]==board[1][1]&&board[1][1]==board[2][0]&&board[1][1]!=' '){
        return true;
    }

    return false;
}

int findBestScore(int filledCell,bool isComputerTurn){
    int bestScore=0;
    if(isWinnerFound()==true){
        if(isComputerTurn==true){
            return -100;
        }
        else if(isComputerTurn==false){
            return 100;
        }
        else{
            return 0;
        }
    }
    if(filledCell<9){
        if(isComputerTurn==true){
            bestScore=INT_MIN;
            for(int i=0;i<n;i++){
                for(int j=0;j<n;j++){
                    if(board[i][j]==' '){
                        board[i][j]=computerMove;
                        int score=findBestScore(filledCell+1,false);
                        board[i][j]=' ';
                        if(score>bestScore){
                            bestScore=score;
                        }
                    }
                }
            }
            return bestScore;
        }
        else if(isComputerTurn==false){
            bestScore=INT_MAX;
            for(int i=0;i<n;i++){
                for(int j=0;j<n;j++){
                    if(board[i][j]==' '){
                        board[i][j]=userMove;
                        int score=findBestScore(filledCell+1,true);
                        board[i][j]=' ';
                        if(score<bestScore){
                            bestScore=score;
                        }
                    }
                }
            }
            return bestScore;
        }
    }
    return 0;
}

int bestMove(int filledCell){
    int bestScore=INT_MIN;
    int x=-1,y=-1;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(board[i][j]==' '){
                board[i][j]=computerMove;
                int score=findBestScore(filledCell+1,false);
                board[i][j]=' ';
                if(score>bestScore){
                    bestScore=score;
                    x=i;
                    y=j;
                }
            }
        }
    }
    return (x*3)+y;
}

void playGame(char move){
    int movesPlayed=0;
    beginGame();
    while(isWinnerFound()==false&&movesPlayed<n*n){
        int pos;
        int x,y;
        if(move==computerMove){
            pos=bestMove(movesPlayed);
            x=pos/n;
            y=pos%n;
            board[x][y]=computerMove;
            cout<<"\nComputer has put O in cell "<<pos+1<<endl;
            showBoard();
            movesPlayed++;
            move=userMove;
        }
        else if(move==userMove){
            cout<<"You can insert in following cells :\n";
            for(int i=0;i<n;i++){
                for(int j=0;j<n;j++){
                    if(board[i][j]==' '){
                        cout<<(i*3)+j+1<<" ";
                    }
                }
            }
            cout<<endl<<"Enter your cell choice : ";
            cin>>pos;
            pos--;
            x=pos/3;
            y=pos%3;
            if(board[x][y]==' '&&pos>=0&&pos<9){
                board[x][y]=userMove;
                cout<<"\nUser has put X in cell "<<pos+1<<endl;
                showBoard();
                movesPlayed++;
                move=computerMove;
            }
            else if(board[x][y]!=' '&&pos>=0&&pos<9){
                cout<<"Enter another cell, it is occupied\n";
            }
            else{
                cout<<"Invalid Choice\n";
            }
        }
    }
    if(isWinnerFound()==false&&movesPlayed==n*n) cout<<"It's a draw...\n";
    else if(isWinnerFound()){
        if(move==computerMove){
            cout<<"Congrats!!!!\nYou won\n";
        }
        else if(move==userMove){
            cout<<"You Lose!!!!\nBetter luck next time\n";
        }
    }
}

int main(){
    cout<<endl<<endl<<"\t\t\tWELCOME TO TIC TAC TOE"<<endl<<endl<<endl;
    while(1){
        char choice;
        cout<<"Would you like to take the lead and begin? (y/n)"<<endl;
        cin>>choice;
        if(choice=='y') playGame(userMove);
        else if(choice=='n') playGame(computerMove);
        else{
            cout<<"Please enter a valid choice"<<endl;
            continue;
        }
        char ch;
        label:
        cout<<"Do you want to play again? (y/n)"<<endl;
        cin>>ch;
        if(ch=='n'){
            cout<<"See you soon!!!!"<<endl;
            break;
        }
        else if(ch!='y'){
            cout<<"Please enter a valid choice"<<endl;
            goto label;
        }
    }
    return 0;
}