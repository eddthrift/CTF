#ifndef XYCOORDINATE_H
#define XYCOORDINATE_H
#include <math.h>

class XYCoordinate
{
public:
    XYCoordinate();
    XYCoordinate(const XYCoordinate &);

    XYCoordinate(double x, double y);

    virtual ~XYCoordinate();

    void Print() const;

    inline void SetX(double);
    inline void SetY(double);
    inline void SetXY(double, double);

    inline double GetX() const;
    inline double GetY() const;

    double Mag() const;

private:
    double oX, oY;
};




inline void XYCoordinate::SetX(double iX){oX = iX;}
inline void XYCoordinate::SetY(double iY){oY = iY;}
inline void XYCoordinate::SetXY(double iX, double iY){
    oX = iX;
    oY = iY;
}

XYCoordinate operator + (const XYCoordinate &, const XYCoordinate &);
XYCoordinate operator - (const XYCoordinate &, const XYCoordinate &);
XYCoordinate operator * (const XYCoordinate &, double);
XYCoordinate operator * (double, const XYCoordinate &);
XYCoordinate operator / (const XYCoordinate &, double);

inline double XYCoordinate::GetX() const {return oX;}
inline double XYCoordinate::GetY() const {return oY;}

#endif // XYCOORDINATE_H
