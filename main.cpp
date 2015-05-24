//SZALOKI ADAM
#include "graphics.hpp"
#include "oswidget.h"
#include "sudoku.h"
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
//&
using namespace std;
using namespace genv;

#define width 490
#define height 410

#define clr gout << move_to(0,0) <<color(220,220,220) <<box(width,height);
#define logo gout << move_to(0,0) << color(140,140,140) << box(width,30) << move_to(10,20) << color(255,255,0) << text(" Szaloki Adam  -  SUDOKU_2015");

int main()
{
    gout.open(width,height);
    event ev;
    SUDOKU sobj(2,32);
    clr;
    logo;
    while(gin >> ev and ev.keycode!=key_escape)
    {
        sobj.kirajzol(ev);
        sobj.vizsgal();
        gout << refresh;
    }
    return 0;
}
