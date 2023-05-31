#ifndef BRICK_H
#define BRICK_H
    typedef struct Brick
    {
        double a;
        double b;
        double c;
    } Brick;
    
   void setSize(Brick *B, double a, double b, double c);
   double getVolume(Brick *B);
    double getSurface(Brick *B);
    int CountOsSquares(Brick *B);
#endif