/* Annika Daniels
 * COP3330 Section 11
 * Assignment 4
 * Function definitions of the Grid Class
 */

#include <iostream>
#include "grid.h"
#include <ctime>
#include <cstdlib>

using namespace std;

Grid::Grid(){
    rows= 1;
    cols= 1;
    rowPos= 1;
    colPos= 1;
    direction= 3;
    pathShown= true;
}

Grid::Grid(int r, int c) {
    rows= r;
    cols= c;
    //fix size if too small or large
    if(rows<3)
        rows= 3;
    if(cols<3)
        cols= 3;
    if(rows>40)
        rows= 40;
    if(cols>40)
        cols= 40;

    //create grid
    for(int i=0; i<rows; i++){
        for(int j=0; j<cols; j++){
            if(i==0 || i==rows-1 || j==0 || j==cols-1)
                arr[i][j]= '#';
            else
                arr[i][j]= '.';
        }
    }
    //seed rng
    srand(time(0));

    //create exit
    int wall= rand()%10;
    while(wall>3)
        wall= rand()%10;
    int exit= rand()%rows;
    //if on top or bot
    if(wall==0 || wall==2){
        while(exit==0 || exit==rows-1)
            exit= rand()%rows;
    }
    //if on side walls
    else{
        exit= rand()%cols;
        while(exit==0 || exit==cols-1)
            exit= rand()%cols;
    }
    //make spot empty
    arr[wall][exit]= '.';

    //create direction
    int dir= rand()%10;
    while(dir>3)
        dir= rand()%10;
    direction= dir;

    //decide position
    int curR= rand()%rows;
    while(curR==0 || curR==rows-1)
        curR= rand()%rows;
    int curC= rand()%cols;
    while(curC==0 || curC==cols-1)
        curC= rand()%cols;
    rowPos= curR;
    colPos= curC;

    pathShown= true;
}

Grid::Grid(int r, int c, int mr, int mc, int d) {
    rows= r;
    cols= c;
    if(r<1)
        rows=1;
    if(c<1)
        cols=1;
    if(rows>40)
        rows= 40;
    if(cols>40)
        cols= 40;

    rowPos= mr;
    colPos= mc;

    if(rowPos<0)
        rowPos= 0;
    if(colPos<0)
        colPos= 0;
    if(rowPos>=rows)
        rowPos= rows-1;
    if(colPos>=cols)
        colPos= cols-1;

    direction= d;
    pathShown= true;

}

void Grid::Display() const {
    for(int i=0; i<rows; i++){
        for(int j=0; j<cols; j++){
            if(!pathShown)
                cout<<arr[i][j]<<" ";
            else{
                //if moved through, print out a space
                if(arr[i][j]== '*')
                    cout<<" "<<" ";
                else
                    cout<<arr[i][j]<<" ";
            }
        }
        cout<<endl;
    }
}

void Grid::TogglePath() {
    //invert boolean
    pathShown= !pathShown;
}

//accessors
int Grid::GetRow() const{
    return rowPos;
}
int Grid::GetCol() const{
    return colPos;
}
int Grid::GetNumRows() const {
    return rows;
}
int Grid::GetNumCols() const{
    return cols;
}

//predicate functions
bool Grid::FrontIsClear() const {
    //north
    if(direction==0){
        //if not on grid
        if(rowPos-1<0)
            return false;
        //if blocked
        if(arr[rowPos-1][colPos]== '#')
            return false;
        return true;
    }
    //west
    if(direction==1){
        //if not on grid
        if(colPos-1<0)
            return false;
        if(arr[rowPos][colPos-1]== '#')
            return false;
        return true;
    }
    //south
    if(direction==2){
        //if not on grid
        if(rowPos+1>=rows)
            return false;
        if(arr[rowPos+1][colPos]== '#')
            return false;
        return true;
    }
    //east
    if(direction==3){
        //if not on grid
        if(colPos+1>=cols)
            return false;
        if(arr[rowPos][colPos]== '#')
            return false;
        return true;
    }
    return false;
}

bool Grid::RightIsClear() const {
    //north
    if(direction==0){
        //if not on grid
        if(colPos+1>=cols)
            return false;
        //if blocked
        if(arr[rowPos][colPos+1]== '#')
            return false;
        return true;
    }
    //west
    if(direction==1){
        //if not on grid
        if(rowPos-1<0)
            return false;
        if(arr[rowPos-1][colPos]== '#')
            return false;
        return true;
    }
    //south
    if(direction==2){
        //if not on grid
        if(colPos-1<0)
            return false;
        if(arr[rowPos][colPos-1]== '#')
            return false;
        return true;
    }
    //east
    if(direction==3){
        //if not on grid
        if(rowPos+1>=rows)
            return false;
        if(arr[rowPos+1][colPos]== '#')
            return false;
        return true;
    }
    return false;
}

//placing blocks/items

void Grid::PutDown() {
    arr[rowPos][colPos]= '0';
}

bool Grid::PutDown(int r, int c) {
    if(r<rows && c<cols){
        //if not blocked
        if(arr[r][c]== '#')
            return false;
        //if an item is already there
        if(arr[r][c]== '0')
            return false;
        arr[r][c]= '0';
        return true;
    }
    return false;
}

bool Grid::PlaceBlock(int r, int c) {
    if(r<rows && c<cols){
        //if not current position
        if(r==rowPos && c==colPos)
            return false;
        //if not blocked
        if(arr[r][c]== '#')
            return false;
        //if not containing item
        if(arr[r][c]== '0')
            return false;
        arr[r][c]= '#';
        return true;
    }
    return false;
}

bool Grid::PickUp() {
    //if theres an item
    if(arr[rowPos][colPos]== '0'){
        //make spot theoretically empty
        arr[rowPos][colPos]= '.';
        return true;
    }
    return false;
}

//first check if in bounds of array based on rows/cols
//then check if spot is blocked
//if not, move
bool Grid::Move(int s){
    //facing north
    if(direction==0){
        if(rowPos-s<0)
            return false;
        if(arr[rowPos-s][colPos]!= '#'){
            //mark spot as moved through
            for(int i=0; i<s; i++)
                arr[rowPos-i][colPos]= '*';
            rowPos= rowPos-s;
            return true;
        }
    }
    //facing west
    else if(direction==1){
        if(colPos-s<0)
            return false;
        if(arr[rowPos][colPos-s]!= '#'){
            //mark spot as moved through
            for(int i=0; i<s; i++)
                arr[rowPos][colPos-i]= '*';
            colPos= colPos-s;
            return true;
        }
    }
    //facing south
    else if(direction==2){
        if(rowPos+s>rows)
            return false;
        if(arr[rowPos+s][colPos]!= '#'){
            //mark spots as moved through
            for(int i=0; i<s; i++)
                arr[rowPos+i][colPos]= '*';
            rowPos= rowPos+s;
            return true;
        }
    }
    //facing east
    else{
        if(colPos+s>cols)
            return false;
        if(arr[rowPos][colPos+s]!= '#'){
            //mark spots as moved through
            for(int i=0; i<s; i++)
                arr[rowPos][colPos+i]= '*';
            colPos= colPos+s;
            return true;
        }
    }
    return false;
}

void Grid::TurnLeft(){
    //turn left 90 degrees
    if(direction<3)
        direction++;
    //reset to north from east
    else
        direction= 0;
}

void Grid::Grow(int gr, int gc) {
    rows= rows+gr;
    cols= cols+gc;
    //if exceed max of 40, default to 40
    if(rows>40)
        rows= 40;
    if(cols>40)
        cols= 40;
}


