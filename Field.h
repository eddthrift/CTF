#ifndef GAME_H
#define GAME_H

#include "XYCoordinate.h"
#include <vector>


class Field{
public:
    Field();

    Field(int Length, int Width, double ASpeed, double DSpeed);

    Field(const Field &);

    inline int GetWidth() const;
    inline int GetLength() const;
    inline double GetASpeed() const;
    inline double GetDSpeed() const;
    inline int GetPlayerNum() const;

    inline void SetSize(int,int);
    inline void SetSpeed(double, double);

    inline int AddPlayerPosition(XYCoordinate);
    inline void UpdatePlayerPosition(int, XYCoordinate);
    inline XYCoordinate GetPlayerPosition(int);

    bool oBlueFlagHeld, oRedFlagHeld;
    XYCoordinate oBlueFlagPos, oRedFlagPos;

private:
    std::vector<XYCoordinate> oPositions;
    int oPlayerNum;
    int oLength, oWidth;
    double oASpeed, oDSpeed;
};

inline int Field::GetLength() const {return oLength;}
inline int Field::GetWidth() const {return oWidth;}
inline double Field::GetASpeed() const {return oASpeed;}
inline double Field::GetDSpeed() const {return oDSpeed;}
inline int Field::GetPlayerNum() const {return oPositions.size();}

inline void Field::SetSize(int iWidth, int iLength){
    oWidth = iWidth;
    oLength = iLength;
    oBlueFlagPos.SetXY(95*oWidth/100, oLength/2);
    oRedFlagPos.SetXY(5*oWidth/100, oLength/2);
}
inline void Field::SetSpeed(double iASpeed, double iDSpeed){
    oASpeed = 0.01 * iASpeed;
    oDSpeed = 0.01 * iASpeed * iDSpeed;
}

inline int Field::AddPlayerPosition(XYCoordinate position){
    int index = oPositions.size();
    oPositions.push_back(position);
    return index;
}
inline void Field::UpdatePlayerPosition(int i, XYCoordinate position){
    oPositions[i] = position;
};
inline XYCoordinate Field::GetPlayerPosition(int i){
    return oPositions[i];
}
#endif // GAME_H
