#include "sudoku.h"
#include "oswidget.h"
#include "graphics.hpp"
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <ctime>

using namespace genv;
using namespace std;

#define width 490
#define height 410

SUDOKU::SUDOKU(int _x,int _y):OSWIDGET(_x,_y)
{
    x=_x;
    y=_y;
    sudoku_int=1;
    s_vek.resize(81);
    s_vek4.resize(9);
    xo=0;
    yo=0;
    srand(time(0));
    betolt();
    aktiv1=false;
    szovegjelol=false;
}
void SUDOKU::sudoku_gombok(int a, int b,int c,string jel,event ev)
{
    stringstream ss;
    gout << move_to(x+408+a,y+28+b) << color(40,40,40) << box(c+4,34);
    gout << move_to(x+410+a,y+30+b) << color(255,255,220) << box(c,30);
    gout << move_to(x+421+a,y+47+b) << color(0,0,0) << text(jel);
    if(jel==sudoku_string)
    {
        gout << move_to(x+410+a,y+30+b) << color(255,255,100) << box(c,30);
        gout << move_to(x+421+a,y+47+b) << color(0,0,0) << text(jel);
    }

    if((jel!=sudoku_string) and 410+a+x<ev.pos_x and ev.pos_x<x+410+a+c and y+30+b<ev.pos_y and ev.pos_y<y+60+b)
    {
        gout << move_to(x+410+a,y+30+b) << color(111,183,255) << box(c,30);
        gout << move_to(x+421+a,y+47+b) << color(255,255,0) << text(jel);
        if(ev.button==btn_left)
        {
            if(jel=="+" and sudoku_int<9)
            {
                sudoku_int++;
            }
            if(jel=="-" and  sudoku_int>1)
            {
                sudoku_int--;
            }
            if(jel=="ADD HOZZA" and s_vek3[(yo*9)+xo]==" ")
            {
                s_vek[(yo*9)+xo]=sudoku_string;
                sudoku_int=1;
            }
            if(jel=="TOROLD KI" and s_vek3[(yo*9)+xo]==" ")
            {
                s_vek[(yo*9)+xo]=" ";
            }
            if(jel=="ELLENORIZD")
            {
                aktiv1=true;
            }
        }

    }
    ss<<sudoku_int;
    ss>>sudoku_string;
    ss.clear();
}

void SUDOKU::kirajzol(event ev)
{
    stringstream ss;
    for(int i=0; i<4; i++)
    {
        gout << move_to(x-2+i*126,y-2+0) << color(20,20,100) << box(2,380);
        gout << move_to(x-2+0,y-2+i*126) << color(20,20,100) << box(380,2);
    }
    for(int y_o=0; y_o<9; y_o++)
    {

        for(int x_o=0; x_o<9; x_o++)
        {

            gout << move_to(x+(x_o*42),y+(y_o)*42) << color(255,255,255) << box(40,40);
            if(ev.button==btn_left and x+(x_o*42)<ev.pos_x and ev.pos_x<x+40+(x_o*42) and y+(y_o*42)<ev.pos_y and ev.pos_y<y+40+(y_o*42))
            {
                xo=x_o;
                yo=y_o;
            }
            gout << move_to(x+16+(x_o*42),y+22+(y_o)*42) << color(0,0,255) << text(s_vek[(y_o*9)+x_o]);
            if(s_vek3[(y_o*9)+x_o]!=" ")
            {
                gout << move_to(x+(x_o*42),y+(y_o)*42) << color(100,100,100) << box(40,40);
                gout << move_to(x+16+(x_o*42),y+22+(y_o)*42) << color(230,230,230) << text(s_vek3[(y_o*9)+x_o]);
            }
        }
    }
    sudoku_gombok(0,0,30,"+",ev);
    sudoku_gombok(0,30,30,sudoku_string,ev);
    sudoku_gombok(0,60,30,"-",ev);
    sudoku_gombok(-25,120,95,"ADD HOZZA",ev);
    sudoku_gombok(-25,155,95,"TOROLD KI",ev);
    sudoku_gombok(-27,190,100,"ELLENORIZD",ev);
    if(ev.keycode==key_right)
    {
        xo++;
        xo=(xo+9)%9;
    }
    if(ev.keycode==key_left)
    {
        xo--;
        xo=(xo+9)%9;
    }
    if(ev.keycode==key_down)
    {
        yo++;
        yo=(yo+9)%9;
    }
    if(ev.keycode==key_up)
    {
        yo--;
        yo=(yo+9)%9;
    }
    if(ev.keycode==key_enter and s_vek3[(yo*9)+xo]==" ")
    {
        s_vek[(yo*9)+xo]=sudoku_string;
        sudoku_int=1;
        aktiv1=false;
    }
    if(ev.keycode==key_pgdn and sudoku_int>1)
    {
        sudoku_int--;
    }
    if(ev.keycode==key_pgup and sudoku_int<9)
    {
        sudoku_int++;
    }
    if(ev.keycode==key_delete and s_vek3[(yo*9)+xo]==" ")
    {
        s_vek[(yo*9)+xo]=" ";
    }
    if(s_vek3[yo*9+xo]==" ")
    {
        gout << move_to(x+(xo*42),y+(yo)*42) << color(255,255,0) << box(40,40);

        gout << move_to(x+16+(xo*42),y+22+(yo)*42) << color(0,0,255) << text(s_vek[(yo*9)+xo]);
    }


}
void SUDOKU::betolt()
{
    ifstream be("lista.txt");
    int RND;
    while(!be.eof())
    {
        RND=rand()%5;
        be >> sudoku_string;
        s_vek2.push_back(sudoku_string);
        if(RND==1)
        {
            s_vek3.push_back(sudoku_string);
        }
        else
        {
            s_vek3.push_back(" ");
        }
        s_vek=s_vek3;

    }
}

void SUDOKU::vizsgal()
{
    cout << "START:  \n";
    int sum=0;
    int oke=0;
    int snovel=0;
    for(int dy=0; dy<3; dy++)
    {
        for(int dx=0; dx<3; dx++)
        {
            for(int sy=0; sy<3; sy++)
            {
                for(int sx=0; sx<3; sx++)
                {
                    s_vek4[sy*3+sx]=s_vek[sy*9+sx+dx*3+dy*27];
                }
            }
            for(int t=0;t<9;t++)
            {
                cout << s_vek4[t] << " ";
                /*if(s_vek4[t]!=" " and s_vek4[t]==s_vek4[dy*3+dx])
                {
                    cout << s_vek4[t] << " ";
                }*/
            }
            cout << endl;
        }
    }

    for(int i=0; i<9; i++)
    {
        for(int j=0; j<9; j++)
        {
            if(s_vek2[i*9+j]==s_vek[i*9+j])
            {
                oke++;
            }
            for(int t=0; t<9; t++)
            {
                if(s_vek[i*9+j]==s_vek[i*9+t])
                {
                    sum++;
                }
                if(s_vek[i*9+j]==s_vek[t*9+j])
                {
                    sum++;
                }
            }
            if(sum>2)
            {
                gout << move_to(x+16+(j*42),y+22+(i)*42) << color(255,130,0) << text(s_vek[(i*9)+j]);
            }
            sum=0;
        }
    }
    if(oke==81 and aktiv1)
    {
        //nyertel();
        cout << "NYERTEL!!! :) \n";
    }
    if(oke<81 and aktiv1)
    {
        cout << "VALAHOL HIBA VAN :( \n";
    }
    aktiv1=false;

}
void SUDOKU::nyertel()
{
    gout << move_to(x-2,y-2) << color(255,130,0) << box(width-x,height-y);

}
