#include <string>
#include <iostream>
#include <sstream>
#include <new>
#include <limits>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
#include "fx.hpp"
board::board(int r, int c,string s){
  string *p=new string[3];
  p[0]=" ";
  p[1]="X";
  p[2]="O";
  players=p;
  row=r;
  column=c;
  serial=s;
  //dynamic memory alloc with <new>
  int ** ary=new int*[r];
  for(int i=0;i<r;++i)
    ary[i]= new int[c];
  //fill ary with 0 values
  for(int i=0; i<r;++i)
    for(int j=0;j<c;++j)
      ary[i][j]=0;
  b=ary;
  if (serial!=""){
    int play=0;
    for(int i=0; i<serial.length();i++){
     play=pswitch(play); 
     board::move(charint(serial[i]),play,true);
    }
  }  
}
board::~board(){}
string board::gserial(){
   return serial;
}
void board::print(){
  string out="";
  out+="Player1:"+players[1]+"|Connect 4|"+"Player2:"+players[2]+"\n";
  //make divs
  string div="";
  for(int j=0;j<column;++j)
    div+="+---";
  div+="+\n";
 //first div in out
  out+=div;
  //matrix 
  for(int i=0;i<row;++i){
    for(int j=0;j<column;++j)
      out+="| "+players[b[i][j]]+" ";
    out+="|\n"+div;
  }
  //column line
  cout<<'\n';
  for(int j=0;j<column;++j){
    stringstream ss;
    ss<<"| "<<j<<" ";
    out+=ss.str();
    out+="|\n"+div;
  }
  cout<<out;
}
void board::usermove(int p){
  int c=0;
  while (!(c>=1&&c<=7)){
    while (cout<<players[p]<<", choose a column (1-7):"&&!(cin>>c)){
     cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout<<"Invalid input.\n";
    }
  }
  if(!board::move(c,p)){
    cout<<"Column full.\n";
    board::usermove(p);
  }
}
bool board::move(int c,int p,bool cn){  
  if (!cn){
    stringstream s;
    s<<c;
    serial+=s.str();
  }
  c--;
  int i=0;
  for (i=0;i<row;++i){
    if(b[i][c]!=0){
      --i;
      break;
    }
    else if (i==row-1){
      break;
    }        
  }
  if(i<0){
    return false;
  }
  b[i][c]=p;
  return true;
}

bool board::win(int p){
  //all cout is dianostics
  int count=0;
  //check for vert wins (4)
  for (int j=0;j<column;++j)
    for(int i=0;i<(row-1)/2+1;++i)
      if(b[i][j]==p&&b[i+1][j]==p&&b[i+2][j]==p&&b[i+3][j]==p)
        return true;
  //horiz wins (4)
  for (int i=0;i<row;++i)
    for(int j=0;j<(column-1)/2+1;++j)
      if(b[i][j]==p&&b[i][j+1]==p&&b[i][j+2]==p&&b[i][j+3]==p)
        return true;
  //forward slash (4)
  for(int i=(row-1)/2+1;i<row;i++)
    for( int j=(column-1)/2+1;j<column;j++)
      if(b[i][j]==p&&b[i-1][j+1]==p&&b[i-2][j+2]==p&&b[i-3][j+3]==p)
        return true;
  //backslash (4)
  for(int i=0;i<(row-1)/2+1;i++)
    for( int j=0;j<(column-1)/2+1;j++)
      if(b[i][j]==p&&b[i+1][j+1]==p&&b[i+2][j+2]==p&&b[i+3][j+3]==p)
        return true;
  
  return false;    
}
int board::grow(){
  return row;
}
int board::gcolumn(){
  return column;
}
int negamax(board b1,int c,int depth, int a, int b,int p){
  //have to get dimensions of parent board via function in parent board.
  //c is initial choice. 
  board temp(b1.grow(),b1.gcolumn(),b1.gserial());
  board t(b1.grow(),b1.gcolumn(),b1.gserial());
  t.move(c,p);
  if (depth==0||temp.win(p)){
    return 1000;
  }
  //playable moves
  int moves[b1.gcolumn()];
  for(int i=0;i<b1.gcolumn();i++){
  }
    

  int value=-1000;
  //cycle thru children get value
  for(int i=0; i<b1.gcolumn();i++){
    t.move(i,p);
    value=max(value,-negamax(t,i,depth-1,-b,-a,pswitch(p)));
    a=max(a,value);
    //need to add, if sustain value, decrement
    if (a>=b)
      break;
    //if true max prune
    t=temp;
  }
  return value;
}
int pswitch(int a){
  a++;
  if (a>2){
    a=1;
  }
  return a;
}
int charint(char c){
  int out=c-'0';
  return out;  
}