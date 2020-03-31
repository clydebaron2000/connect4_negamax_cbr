#include<iostream>
using namespace std;
class board {
  private:
    string serial;
    int **b;
    string* players;
    int row;
    int column;
  public:
    board(int r, int c,string s="");
    ~board();
    void print();
    void usermove(int p);
    bool move(int c,int p,bool cn=false);
    bool win(int p);
    string gserial();
    int grow();
    int gcolumn();
};
int negamax(board b1,int col, int depth, int a, int b,int p);    
int pswitch(int a);
int charint(char c);