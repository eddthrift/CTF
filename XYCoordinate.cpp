#include "XYCoordinate.h"
#include <iostream>

XYCoordinate::XYCoordinate()
    :oX(0.0), oY(0.0){}

XYCoordinate::XYCoordinate(double x, double y)
    :oX(x), oY(y){}

XYCoordinate::XYCoordinate(const XYCoordinate & p)
: oX(p.oX), oY(p.oY) {}

XYCoordinate::~XYCoordinate(){}

void XYCoordinate::Print() const{
    std::cout<< "X: " << oX << " Y: " << oY << std::endl;
}

double XYCoordinate::Mag() const {
    return sqrt(oX*oX + oY*oY);
}

XYCoordinate operator + (const XYCoordinate & A, const XYCoordinate & B) {
   return XYCoordinate(A.GetX() + B.GetX(), A.GetY() + B.GetY());
}

XYCoordinate operator - (const XYCoordinate & A, const XYCoordinate & B) {
   return XYCoordinate(A.GetX() - B.GetX(), A.GetY() - B.GetY());
}

 XYCoordinate operator * (const XYCoordinate & A, double B) {
   return XYCoordinate(A.GetX() * B, A.GetY() * B);
}

XYCoordinate operator * (double A, const XYCoordinate & B) {
   return XYCoordinate(A * B.GetX(), A * B.GetY());
}

XYCoordinate operator / (const XYCoordinate & A, double B) {
   return XYCoordinate(A.GetX() / B, A.GetY() / B);
}
