#pragma once
#include <iostream>
#include "Graphics.h"
#include <math.h>
#include "Graphics.h"

#include <string>
#include <typeinfo>

#include <limits>
#define SCALE 10

template <class T>
class BinaryImg
{
private:
    T** array;
    int row;
    int col;
    void DrawDot(float x, float y) const;
    void DrawBlankDot(float x, float y) const;
    Graphics* screen;
    void Print();
    BinaryImg<T> And(T rhs) const;
    BinaryImg<T> Or(T rhs) const;
    BinaryImg<T> And(const BinaryImg<T>& rhs) const;
    BinaryImg<T> Or(const BinaryImg<T>& rhs) const;


public:
    BinaryImg(int x, int y);
    BinaryImg(const BinaryImg& src);
    ~BinaryImg();
    int GetRow() const;
    int GetCol() const;

    friend std::ostream& operator<<(std::ostream& os, BinaryImg<T>& obj)
    {
        obj.Print();
        return os;
    }

    bool operator==(const BinaryImg<T>& src) const;
    bool operator!=(const BinaryImg<T>& src) const;
    T& operator()(int x, int y);
    T operator()(int x, int y) const;
    BinaryImg operator+(const BinaryImg<T>& src) const;
    BinaryImg operator*(const BinaryImg<T>& src) const;
    BinaryImg operator+(T src) const;
    BinaryImg operator*(T src) const;
    BinaryImg operator!();
    BinaryImg& operator= (const BinaryImg& src);
    double AccumulationFactor() const;

    friend BinaryImg operator*(T rhs, /*const*/ BinaryImg<T>& src)
    {
        //BinaryImg<T> result(src.row, src.col);
        //for (int i = 0; i < src.row; i++)
        //{
        //    for (int j = 0; j < src.col; j++)
        //    {
        //        result.array[i][j] = src.array[i][j] * rhs;
        //    }
        //}
        //return result;

        return src.And(rhs);

    }

    friend BinaryImg operator+(T rhs, /*const*/ BinaryImg<T>& src)
    {
        //BinaryImg result(src.row, src.col);
        //for (int i = 0; i < src.row; i++)
        //{
        //    for (int j = 0; j < src.col; j++)
        //    {
        //        result.array[i][j] = src.array[i][j] + rhs;
        //    }
        //}
        //return result;
        return src.Or(rhs);
    }
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


#include "Class.h"
#include <math.h>
#include <iostream>
#include "Graphics.h"
#define SCALE 10

template <class T>
void BinaryImg<T>::DrawDot(float x, float y) const
{
    screen->DrawSquare(x, y);
}
template <class T>
void BinaryImg<T>::DrawBlankDot(float x, float y) const
{
    screen->DrawLine(x, y, x + SCALE, y);
    screen->DrawLine(x, y, x, y + SCALE);
    screen->DrawLine(x + SCALE, y, x + SCALE, y + SCALE);
    screen->DrawLine(x, y + SCALE, x + SCALE, y + SCALE);
}


template <class T>
BinaryImg<T>::BinaryImg(int x, int y)
{
    screen = NULL;
    if (x <= 0 || y <= 0) { throw EClassException("invalid dimension"); }
    row = x;
    col = y;
    array = new T * [row];
    for (int i = 0; i < row; i++)
    {
        array[i] = new T[col]{};
    }
}

// Specialization for char
template <> 
BinaryImg<char>::BinaryImg(int x, int y)
{
    screen = NULL;
    if (x <= 0 || y <= 0) { throw EClassException("invalid dimension"); }
    row = x;
    col = y;
    array = new char * [row];
    for (int i = 0; i < row; i++)
    {
        array[i] = new char[col];
    }
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            array[i][j] = '0';
        }
    }
}


template <class T>
BinaryImg<T>::BinaryImg(const BinaryImg& src)
{
    screen = NULL;
    row = src.row;
    col = src.col;
    array = new T * [row];
    for (int i = 0; i < row; i++)
    {
        array[i] = new T[col];
    }

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            array[i][j] = src.array[i][j];
        }
    }
}


template <class T>
BinaryImg<T>::~BinaryImg()
{
    for (int i = 0; i < row; i++)
    {
        delete[]array[i];
    }
    delete[]array;
}


template <class T>
int BinaryImg<T>::GetRow() const { return row; }
template <class T>
int BinaryImg<T>::GetCol() const { return col; }


template <class T>
bool BinaryImg<T>::operator==(const BinaryImg<T>& src) const
{
    if (row != src.row || col != src.col) { throw EClassException("Can't cmp imgs with different sizes"); } // probably more fair to trow exception 
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (array[i][j] != src.array[i][j]) { return false; }
        }
    }
    return true;
}


template <class T>
bool BinaryImg<T>::operator!=(const BinaryImg<T>& src) const
{
    return !(*this == src);
}


template <class T>
T& BinaryImg<T>::operator()(int x, int y)
{
    if ((x >= row || y >= col) || (x < 0 || y < 0))
    {
        throw EClassException("invalid index");
    }
    return array[x][y];
}


template <class T>
T BinaryImg<T>::operator()(int x, int y) const
{
    if ((x >= row || y >= col) || (x < 0 || y < 0))
    {
        throw EClassException("invalid index");
    }
    return array[x][y];
}


template <class T>
BinaryImg<T> BinaryImg<T>::operator+(const BinaryImg<T>& src) const
{
    //if (row != src.row || col != src.col) { throw EClassException("Invalid dimensions of imgs"); }
    //BinaryImg<T> result(row, col);
    //for (int i = 0; i < row; i++)
    //{
    //    for (int j = 0; j < col; j++)
    //    {
    //        result.array[i][j] = array[i][j] + src.array[i][j];
    //    }
    //}
    //return result;
    return this->Or(src);

}


template <class T>
BinaryImg<T> BinaryImg<T>::operator*(const BinaryImg<T>& src) const
{
    //if (row != src.row || col != src.col) { throw EClassException("Invalid dimensions of imgs"); }
    //BinaryImg<T> result(row, col);
    //for (int i = 0; i < row; i++)
    //{
    //    for (int j = 0; j < col; j++)
    //    {
    //        result.array[i][j] = array[i][j] * src.array[i][j];
    //    }
    //}
    //return result;

    return this->And(src);

}


template <class T>
BinaryImg<T> BinaryImg<T>::operator+(T src) const
{
    //BinaryImg<T> result(row, col);
    //for (int i = 0; i < row; i++)
    //{
    //    for (int j = 0; j < col; j++)
    //    {
    //        result.array[i][j] = array[i][j] + rhs;
    //    }
    //}
    //return result;
    return this->And(src);

}


template <class T>
BinaryImg<T> BinaryImg<T>::operator*(T src) const
{
    //BinaryImg result(row, col);
    //for (int i = 0; i < row; i++)
    //{
    //    for (int j = 0; j < col; j++)
    //    {
    //        result.array[i][j] = array[i][j] * rhs;
    //    }
    //}
    //return result;
    return this->Or(src);

}


template <class T>
BinaryImg<T> BinaryImg<T>::operator!()
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            array[i][j] = !array[i][j];
        }
    }
    return *this;
}


template <class T>
BinaryImg<T>& BinaryImg<T>::operator= (const BinaryImg<T>& src)
{
    if (this == (&src)) { return *this; }
    if (row == src.row && col == src.col)
    {
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                array[i][j] = src.array[i][j];
            }
        }
        return *this;
    }

    for (int i = 0; i < row; i++)
    {
        delete[]array[i];
    }
    delete[]array;

    row = src.row;
    col = src.col;

    array = new T * [row];
    for (int i = 0; i < row; i++)
    {
        array[i] = new T[col];
    }

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            array[i][j] = src.array[i][j];
        }
    }
    return *this;
}


//template <class T>
//std::ostream& operator<<(std::ostream& os, BinaryImg<T>& obj)
//{
//    obj.screen = new Graphics((obj.row * SCALE) + SCALE * 12, (obj.col * SCALE) + SCALE * 12);
//    for (int i = 0; i < obj.row; i++)
//    {
//        for (int j = 0; j < obj.col; j++)
//        {
//            obj.array[i][j] ? obj.DrawDot((float)(i * SCALE), (float)(j * SCALE)) : obj.DrawBlankDot((float)(i * SCALE), (float)(j * SCALE));
//        }
//    }
//    delete obj.screen;
//    return os;
//}


template <class T>
double BinaryImg<T>::AccumulationFactor() const
{
    int k = 0;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (array[i][j]) { k++; }
        }
    }
    return (double)k / ((double)row * (double)col);
}


template <class T>
void BinaryImg<T>::Print() 
{

    screen = new Graphics((row * SCALE) + SCALE * 12, (col * SCALE) + SCALE * 12);
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            array[i][j] ? DrawDot((float)(i * SCALE), (float)(j * SCALE)) : DrawBlankDot((float)(i * SCALE), (float)(j * SCALE));
        }
    }
    delete screen;
}


// Specialization for char
template <>
void BinaryImg<char>::Print() 
{
    screen = new Graphics((row * SCALE) + SCALE * 12, (col * SCALE) + SCALE * 12);
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            //array[i][j] ? DrawDot((float)(i * SCALE), (float)(j * SCALE)) : DrawBlankDot((float)(i * SCALE), (float)(j * SCALE));
            array[i][j] != '0' ? DrawDot((float)(i * SCALE), (float)(j * SCALE)) : DrawBlankDot((float)(i * SCALE), (float)(j * SCALE));
        }
    }
    delete screen;
}


template <class T>
BinaryImg<T> BinaryImg<T>::And(T src) const
{
    BinaryImg<T> result(row, col);
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if ((double)array[i][j] * src > std::numeric_limits<T>::max() || (double)array[i][j] * src < std::numeric_limits<T>::min())
            {
                result.array[i][j] = 0;
            }
            else
            {
                result.array[i][j] = array[i][j] * src;
            }
        }
    }
    return result;
}


template <class T>
BinaryImg<T> BinaryImg<T>::Or(T src) const
{
    BinaryImg<T> result(row, col);
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if ((double)array[i][j] + src > std::numeric_limits<T>::max() || (double)array[i][j] + src < std::numeric_limits<T>::min())
            {
                result.array[i][j] = 0;
            }
            else
            {
                result.array[i][j] = array[i][j] + src;
            }
        }
    }
    return result;
}


template <class T>
BinaryImg<T> BinaryImg<T>::And(const BinaryImg<T>& rhs) const
{
    if (row != rhs.row || col != rhs.col) { throw EClassException("Invalid dimensions of imgs"); }
    BinaryImg<T> result(row, col);
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {

            if ((double)array[i][j] * rhs.array[i][j] > std::numeric_limits<T>::max() || (double)array[i][j] * rhs.array[i][j] < std::numeric_limits<T>::min())
            {
                result.array[i][j] = 0;
            }
            else
            {
                result.array[i][j] = array[i][j] * rhs.array[i][j];
            }
        }
    }
    return result;
}


template <class T>
BinaryImg<T> BinaryImg<T>::Or(const BinaryImg<T>& rhs) const
{
    if (row != rhs.row || col != rhs.col) { throw EClassException("Invalid dimensions of imgs"); }
    BinaryImg<T> result(row, col);
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            double test1 = this->array[i][j];
            double test2 = rhs.array[i][j];

            if ((double)array[i][j] + rhs.array[i][j] > std::numeric_limits<T>::max() || (double)array[i][j] + rhs.array[i][j] < std::numeric_limits<T>::min())
            {
                result.array[i][j] = 0;
            }
            else
            {
                result.array[i][j] = array[i][j] + rhs.array[i][j];
            }
        }
    }
    return result;
}

//friend function
//template <class T>
//BinaryImg<T> operator+(T rhs, const BinaryImg<T>& src)
//{
//    BinaryImg<T> result(src.row, src.col);
//    for (int i = 0; i < src.row; i++)
//    {
//        for (int j = 0; j < src.col; j++)
//        {
//            result.array[i][j] = src.array[i][j] + rhs;
//        }
//    }
//    return result;
//}


//friend functin
//template <class T>
//BinaryImg<T> operator*(T rhs, const BinaryImg<T>& src)
//{
//    BinaryImg result(src.row, src.col);
//    for (int i = 0; i < src.row; i++)
//    {
//        for (int j = 0; j < src.col; j++)
//        {
//            result.array[i][j] = src.array[i][j] * rhs;
//        }
//    }
//    return result;
//}

EClassException::EClassException(const char* err)
{
    strncpy_s(_err, err, 255);
    _err[255] = 0;
}
void EClassException::Print()
{
    std::cout << _err << std::endl;
}
EClassException::~EClassException() {}