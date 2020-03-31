#include <iostream>
#include "fx.hpp"
using namespace std;
#define row 6
#define column 7
//when compiling pls use:
//g++ main.cpp fx.cpp if not on repl.it
int main() {
  board b(row,column,"412335561662211");
  int p=0;
  do{
    p=pswitch(p);
    cout<<p<<'\n';
    cout<<b.gserial();  
    b.print();  
    b.usermove(p);   
  }while(!b.win(p));
  b.print();
  cout<<p<<" wins!";
}