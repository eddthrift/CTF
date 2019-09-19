#include "Field.h"

Field::Field(){
    oPositions.clear();
    oBlueFlagHeld = false;
    oRedFlagHeld = false;
}

Field::Field(int length, int width, double aSpeed, double dSpeed){
    oPositions.clear();
    oBlueFlagHeld = false;
    oRedFlagHeld = false;
    SetSize(width, length);
    SetSpeed(aSpeed, dSpeed);
}
