//Project Made by: Karanbir Singh
//Linkedin: https://www.linkedin.com/in/karanbir-singh-a35b90181/

/*Brief Description: This project consist is getting star and end position of the knight in a board and afterwards displays
 the minimun path taken from start to end.
 For further information please read the README.txt file
 */

#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <queue>
#include <stack>
#include <vector>
using namespace std;

//checking if the move made is within the limits and the knight has not visited that place already
bool moveIsValid(int board[][8], int r, int c){
    if((r >= 0) && (r < 8) && (c >= 0) && (c < 8) && (board[r][c] == 0)){
       return true;
    }
    return false;
}

/*indexR and indexC will contain all the paths taken from the knight to reach that particular destination
 Since we already know that the last position is the destination we will track back from there un order to get to the first position
 That will make sure that we have traced back to the start position and that we will than pop the positons out from start to end
 */
void trackPath(int indexR[][8], int indexC[][8], int endR, int endC,int startR, int startC ){
        stack<int> rw;
        stack<int> cl;
        int r = endR;
        int c = endC;
        cout << "Here is your path:" << endl;
    //we will push all the indexes from the reached destination until we get back to were we started
        while(r != startR || c!= startC){
            rw.push(r);
            cl.push(c);
            int r1 = indexR[r][c];
            int r2 = indexC[r][c];
            r = r1;
            c = r2;
        }
        cout << startR << " " << startC << endl;
        //we will start popping out all the locations and display our path
        while(!rw.empty() && !cl.empty())
        {
            int a = rw.top();
            int b = cl.top();
            rw.pop();
            cl.pop();
            cout << a << " " << b << endl;
        }
}
//trying all combinations of paths in order to find the shortest one, and then displaying the path
void knight_moves(int startRow, int startColumn, int board[][8], int endRow, int EndCol){
    int rowPosition[] = {2, -1, 1, 2, -2, -1, 1, -2};//array used for checking every row position that the knight can take
    int colPosition[] = {1, -2, -2, -1, 1, 2, 2, -1};//array used for checking every column position that the knight can take
    int trackR[8][8];//this matrix will store the index of the row of the previous move made by the knight
    int trackC[8][8];//this matrix will store the index of the row of the previous move made by the knight
    int r,c;//variables used for index of row and column
    //three stacks used for storing the index of row and column and also storing the count of the moves made to reach a destination
    queue<int> row;//queue for visiting row
    queue<int> col;//queue for visiting column
    queue<int> w;//queue for storing the number of moves
    row.push(startRow);
    col.push(startColumn);
    board[startRow][startColumn] = 1;//every seen position will be marked with one
    trackR[startRow][startColumn] = startRow;//storing the visited row position
    trackR[startRow][startColumn] = startColumn;//storing visited column position
    w.push(0);//push 0 as the no of moves
    int newR,newC,W;
    while(!row.empty() && !col.empty()){
        newR = row.front();
        newC = col.front();
        W = w.front();
        row.pop();
        col.pop();
        w.pop();
        //edge case which means that we found the shortest path
        if((newR == endRow) && (newC == EndCol))
            cout << "You made it in " << W << " moves from " << startRow<< "," << startColumn << " to "<< endRow << "," <<EndCol<<endl;
        for(int i = 0; i < 8 ; i++){
            //keeping track of the previous positions
            r = newR + rowPosition[i];
            c = newC + colPosition[i];
            //if the move is within the given indexes and the knight has not already been to that particul place
            if(moveIsValid(board, r, c) == true){
                board[r][c] = 1;
                //we store the indexes
                row.push(r);
                col.push(c);
                w.push(W+1);//increase the no of moves
                //keep track of the previous indexes of row and column
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


