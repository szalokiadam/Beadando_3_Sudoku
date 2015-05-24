#ifndef SUDOKU_H
#define SUDOKU_H
#include "oswidget.h"
#include "graphics.hpp"
#include <vector>


class SUDOKU:public OSWIDGET
{
    public:
        SUDOKU(int _x,int _y);
    int temp_int;
        void kirajzol(genv::event ev);
        void sudoku_gombok(int a, int b,int c,std::string jel,genv::event ev);
        std::string sudoku_string;
        int sudoku_int;
        std::string temp_string;
        int xo,yo;
        std::vector<std::string>s_vek;
        std::vector<std::string>s_vek2;
        std::vector<std::string>s_vek3;
        std::vector<std::string>s_vek4;
        std::vector<SUDOKU> vektor_sud;
        void betolt();
        void vizsgal();
        void nyertel();

    protected:
    private:
};

#endif // SUDOKU_H
