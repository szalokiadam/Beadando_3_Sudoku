#ifndef OSWIDGET_H
#define OSWIDGET_H

#include <vector>
#include <string>


class OSWIDGET
{
public:
    OSWIDGET(int _x, int _y);
    std::vector<std::string> szavak;
    bool aktiv1,aktiv2,szovegjelol;
    int sima_szel, sima_mag;
protected:
    int x,y;
private:
};

#endif // OSWIDGET_H
