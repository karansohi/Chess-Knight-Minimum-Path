//Project Made by: Karanbir Singh
//Linkedin: https://www.linkedin.com/in/karanbir-singh-a35b90181/

/*Brief Description: This project consist is getting star and end position of the knight in a board and afterwards displays
 the minimun path taken from start to end.
 For further information please read the README.txt file
 */
//Update --> Reduction of space complexity by creating a class object for the knight where we can store indexes and moves
#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <queue>
#include <stack>
#include <vector>
using namespace std;

class Knight{
private:
    int row;
    int column;
    int noOfmoves;
public:
    Knight(int r, int c){
        row = r;
        column = c;
        noOfmoves = 0;
    }
    void setPostion_Move(int r1, int c1, int m1){
        row = r1;
        column = c1;
        noOfmoves = m1;
    }
    void trackMove(int r1, int c1){
        row = r1;
        column = c1;
    }
    int getRow(){return row;}
    int getColumn(){return column;}
    int getNoOfMoves(){return noOfmoves;}
};

bool moveIsValid(int board[][8], int r, int c){
    if((r >= 0) && (r < 8) && (c >= 0) && (c < 8) && (board[r][c] == 0)){
       return true;
    }
    return false;
}

void trackPath(int indexR[][8], int indexC[][8], int endR, int endC,int startR, int startC){
    stack<Knight> retrivePath;
    int r = endR;
    int c = endC;
    Knight k(r,c);
    cout << "Here is your path:" << endl;
    //we will push all the indexes from the reached destination until we get back to were we started
    while(r != startR || c!= startC){
        retrivePath.push(k);
        int r1 = indexR[r][c];
        int r2 = indexC[r][c];
        r = r1;
        c = r2;
        k.trackMove(r,c);
    }
    cout << startR << " " << startC << endl;
    //we will start popping out all the locations and display our path
    while(!retrivePath.empty())
    {
        k = retrivePath.top();
        int a = k.getRow();
        int b = k.getColumn();
        retrivePath.pop();
        cout << a << " " << b << endl;
    }
}

void knight_moves(int startRow, int startColumn, int board[][8], int endRow, int EndCol){
    Knight k(startRow,startColumn);
    int rowPosition[] = {2, -1, 1, 2, -2, -1, 1, -2};//array used for checking every row position that the knight can take
    int colPosition[] = {1, -2, -2, -1, 1, 2, 2, -1};//array used for checking every column position that the knight can take
    int trackR[8][8];//this matrix will store the index of the row of the previous move made by the knight
    int trackC[8][8];//this matrix will store the index of the row of the previous move made by the knight
    int r,c;//variables used for index of row and column
    //three stacks used for storing the index of row and column and also storing the count of the moves made to reach a destination
    queue<Knight> position;
    position.push(k);
    board[k.getRow()][k.getColumn()] = 1;
    trackR[k.getRow()][k.getColumn()] = k.getRow();
    trackC[k.getRow()][k.getColumn()] = k.getColumn();
    int newR,newC,W;
    while(!position.empty()){
        k = position.front();
        newR = k.getRow();
        newC = k.getColumn();
        W = k.getNoOfMoves();
        position.pop();
        //edge case which means that we found the shortest path
        if((newR == endRow) && (newC == EndCol))
            cout << "You made it in " << W << " moves from " << startRow<< "," << startColumn << " to " << endRow << "," << EndCol << endl;
        for(int i = 0; i < 8 ; i++){
            //keeping track of the previous positions
            r = newR + rowPosition[i];
            c = newC + colPosition[i];
            //if the move is within the given indexes and the knight has not already been to that particul place
            if(moveIsValid(board, r, c) == true){
                board[r][c] = 1;
                //we store the indexes
                k.setPostion_Move(r, c, W+1);
                position.push(k);
                trackR[r][c] = newR;
                trackC[r][c] = newC;
            }
        }
    }
    //once we have found the number of minimum moves we move to the next step which is tracking the part from end to start and displayin it form start to end
    trackPath(trackR, trackC, endRow, EndCol, startRow, startColumn);
}
int main(){
    int chessBoard[8][8];
    for(int i = 0; i < 8; i++)
        for(int j = 0; j < 8; j++)
            chessBoard[i][j] = 0;
    
    int startR,startC,endR,endC;
    cout << "Enter the current Knight’s location: ";
    cin>>startR>>startC;
    cout << "Enter the destination location: ";
    cin>>endR>>endC;
    knight_moves(startR, startC, chessBoard, endR, endC);
}


