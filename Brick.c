#include "Bridge.h"

void setSize(Brick *B, double a, double b, double c){
    B->a = a;
    B->b = b;
    B->c = c;
}
   double getVolume(Brick *B){
        return B->a*B->b*B->c;
   }
    double getSurface(Brick *B){
        double surface = 2*((B->a*B->a) + (B->b*B->b) + (B->c*B->c));
        return surface;
    }
    int CountOsSquares(Brick *B){
        int SquareFace;
        SquareFace = (B->a == B->b || B->a == B->c || B->b == B->c);
        return;
    }