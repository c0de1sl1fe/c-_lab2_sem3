#pragma once
#include <iostream>
#include "Graphics.h"
template <class T>
class BinaryImg
{
private:
    //bool** array;
    T** array;
    int row;
    int col;
    void DrawDot(float x, float y) const;
    void DrawBlankDot(float x, float y) const;
    Graphics* screen;

public:
    BinaryImg(int x, int y);
    BinaryImg(const BinaryImg& src);
    ~BinaryImg();
    int GetRow() const;
    int GetCol() const;

    //test prints 
    void Print() const;
    void Print(int i);

    friend std::ostream& operator<<(std::ostream& os, BinaryImg<T>& obj);
    bool operator==(const BinaryImg<T>& src) const;
    bool operator!=(const BinaryImg<T>& src) const;
    T& operator()(int x, int y);
    T operator()(int x, int y) const;
    BinaryImg operator+(const BinaryImg<T>& src) const;
    BinaryImg operator*(const BinaryImg<T>& src) const;
    BinaryImg operator+(T rhs) const; 
    BinaryImg operator*(T rhs) const;
    BinaryImg operator!();
    BinaryImg& operator= (const BinaryImg & src);
    double AccumulationFactor() const;
    friend BinaryImg operator*(T rhs, const BinaryImg<T>& src);
    friend BinaryImg operator+(T rhs, const BinaryImg<T>& src);
};


class EClassException
{
protected:
    char _err[256];
public:
    EClassException(const char* err);
    virtual void Print();
    virtual ~EClassException();
};
