//
// Created by user on 11.12.21.
//

#ifndef CHECKERS_FIGURES_H
#define CHECKERS_FIGURES_H

class TFigure
{
protected:
    int theCenterX,theCenterY;//центр фигуры

public:
    TFigure(int tCenterX, int tCenterY);
    virtual void Show()=0;//отобразить
};
#endif //CHECKERS_FIGURES_H