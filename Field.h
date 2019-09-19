#ifndef FIELD_H
#define FIELD_H
#include <vector>
#include "XYCoordinate.h"
#include "Player.h"

class Field {
public:
    Field();

    Field(int Length, int Width, double ASpeed, double DSpeed);

    virtual ~Field();

    void CreatePlayers(int);
    void PlayerMove(int);
    void Simulate();         //declaration of functions

    inline int GetPlayerNum() const;
    inline Player GetPlayer(int n) const;
    inline std::vector<Player> GetPlayers() const;
    inline int GetWidth() const;
    inline int GetLength() const;
    inline bool GetRun() const;
    inline bool GetBlueFlagHeld() const;
    inline bool GetRedFlagHeld() const;
    inline XYCoordinate GetBlueFlagPos() const;
    inline XYCoordinate GetRedFlagPos() const;
    inline bool GetBlueWin() const;
    inline bool GetRedWin() const;

    inline void SetPlayerNum(int);
    inline void SetSize(int,int);
    inline void SetSpeed(double, double);
    inline void SetRun(bool);

private:
    std::vector<Player> oPlayers;
    int oPlayerNum;
    int oLength, oWidth;
    double oASpeed, oDSpeed;
    XYCoordinate oBlueFlagPos;
    XYCoordinate oRedFlagPos;
    bool oBlueFlagHeld, oRedFlagHeld;
    bool oRun, oBlueWin, oRedWin;

};

inline int Field::GetPlayerNum() const {return oPlayerNum;}
inline Player Field::GetPlayer(int iN) const {return oPlayers[iN];}
inline std::vector<Player> Field::GetPlayers() const {return oPlayers;}
inline int Field::GetLength() const {return oLength;}
inline int Field::GetWidth() const {return oWidth;}
inline bool Field::GetRun() const {return oRun;}
inline bool Field::GetBlueFlagHeld() const {return oBlueFlagHeld;}
inline bool Field::GetRedFlagHeld() const {return oRedFlagHeld;}
inline XYCoordinate Field::GetBlueFlagPos() const {return oBlueFlagPos;}
inline XYCoordinate Field::GetRedFlagPos() const {return oRedFlagPos;}
inline bool Field::GetBlueWin() const {return oBlueWin;}
inline bool Field::GetRedWin() const {return oRedWin;}

inline void Field::SetPlayerNum(int iNum){oPlayerNum = iNum;}
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
inline void Field::SetRun(bool iRun){oRun = iRun;}

#endif // FIELD_H
