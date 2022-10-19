
#include <iostream>
#include "Graphics.h"
#include "Class.h"
#include <stdio.h>



//template <class T>
//BinaryImg<T> DrawRectangle_0(int x1, int y1, int x2, int y2)
//{
//    x1--;
//    x2--;
//    y1--;
//    y2--;
//    if (x1 < 0 || y1 < 0 || x2 < 0 || y2 < 0) { throw EClassException("working with numbers greater than zero"); }
//
//    int firstX = x1, secondX = x2, firstY = y1, secondY = y2;
//    BinaryImg<T> res(secondX + 1, secondY + 1);
//
//    for (int i = firstX; i <= secondX; i++)
//    {
//        res(i, firstY) = true;
//        res(i, secondY) = true;
//    }
//
//    for (int i = firstY; i <= secondY; i++)
//    {
//        res(firstX, i) = true;
//        res(secondX, i) = true;
//    }
//
//    return res;
//}


template <class T>
void DrawRectangle(int x1, int y1, int x2, int y2, BinaryImg<T>& src)
{
    x1--;
    x2--;
    y1--;
    y2--;

    if (x1 < 0 || y1 < 0 || x2 < 0 || y2 < 0) { throw EClassException("working with numbers greater than zero"); }

    if (x1 >= src.GetRow() || x2 >= src.GetRow() || y1 >= src.GetCol() || y2 >= src.GetCol())
    {
        int firstX = x1, secondX = x2, firstY = y1, secondY = y2;
        BinaryImg<T> res(secondX + 1, secondY + 1);

        for (int i = firstX; i <= secondX; i++)
        {
            res(i, firstY) = true;
            res(i, secondY) = true;
        }

        for (int i = firstY; i <= secondY; i++)
        {
            res(firstX, i) = true;
            res(secondX, i) = true;
        }

        src = res;
        return;
    }
    
    int firstX = x1, secondX = x2, firstY = y1, secondY = y2;

    for (int i = firstX; i <= secondX; i++)
    {
        src(i, firstY) = true;
        src(i, secondY) = true;
    }

    for (int i = firstY; i <= secondY; i++)
    {
        src(firstX, i) = true;
        src(secondX, i) = true;
    }
}

void printMenu()
{
    system("cls");
    std::cout << "1. Fill the Imgae by yourself(access to each element in matrix)" << std::endl;
    std::cout << "2. Drow some squares" << std::endl;
    std::cout << "3. Check different type of image(bool, char, short, float)" << std::endl;
    std::cout << "4. Exit" << std::endl;
    std::cout << "choice: ";

}
void printMenu1()
{
    system("cls");
    std::cout << "1. Fill the img" << std::endl;
    std::cout << "2. Exit" << std::endl;
    std::cout << "choice: ";
}

void printMenu2()
{
    system("cls");
    std::cout << "1. Bool" << std::endl;
    std::cout << "2. Char" << std::endl;
    std::cout << "3. Short" << std::endl;
    std::cout << "4. Float" << std::endl;
    std::cout << "5. Exit" << std::endl;
    std::cout << "choice: ";
}
int main()
{

    int row = 0, col = 0;
    int choice = 0;
    bool exit = false;
    while (!exit)
    {
        printMenu();
        std::cin >> choice;
        switch (choice)
        {
        case(1):
            std::cout << "Enter dimenstion of your rectangle:" << std::endl;
            try
            {
                std::cout << "Enter row: ";
                std::cin >> row;
                std::cout << "Enter col: ";
                std::cin >> col;

                BinaryImg<bool> example(row, col);
                std::cout << example;
                system("pause");
                bool exit1 = false;
                int choice1 = 0;
                while (!exit1)
                {
                    printMenu1();
                    std::cin >> choice1;
                    switch (choice1)
                    {
                    case(1):
                        try
                        {
                            int x, y;
                            bool tmp = false;
                            std::cout << "Enter coordinates of element: " << std::endl;
                            std::cout << "enter x: ";
                            std::cin >> x;
                            std::cout << "enter y: ";
                            std::cin >> y;
                            std::cout << "Enter value: ";
                            std::cin >> tmp;

                            example(x, y) = tmp;
                            std::cout << example;

                        }
                        catch (EClassException& err)
                        {
                            err.Print();
                        }

                        break;
                    case(2):
                        exit1 = true;
                        break;
                    default:
                        std::cout << "Error";
                        break;
                    }
                }
            }
            catch (EClassException& err)
            {
                err.Print();
            }
            break;
        case(2):
            try
            {
                std::cout << "Enter dimenstion of your rectangle:" << std::endl;
                int x, y;
                std::cout << "Enter coordinates of element: " << std::endl;
                std::cout << "enter x: ";
                std::cin >> x;
                std::cout << "enter y: ";
                std::cin >> y;
                BinaryImg<bool> a(x, y);
                int one = 1, two = y - one;
                while (one <= two)
                {
                    DrawRectangle(one, one, two, two, a);
                    one += 2;
                    two -= 2;
                }
                std::cout << a; 
                system("pause");
            }
            catch (EClassException &err)
            {
                err.Print();
            }
            break;
        case(3):
            bool exit3 = false;
            int choice3 = 0;

            while (!exit3)
            {
                std::cout << "Enter";
                std::cin >> choice3;
                switch (choice3)
                {
                case(1):


                    break;

                case(2):


                    break;

                case(3):


                    break;

                case(4):


                    break;
                case(5):
                    exit3 = true;
                    break;
                default:
                    break;
                }
            }
            break;
        case(4):
            exit = true;
            break;
        default:
            std::cout << "Unable to recognize your request" << std::endl;
            break;
        }
    }


    return 1;
}


//int choice3 = 0;
//bool exit3 = false;
//while (!exit3)
//{
//    printMenu2();
//    std::cin >> choice3;
//    switch (choice3)
//    {
//    case(1)://bool
//        std::cout << "Enter dimenstion of your rectangle:" << std::endl;
//        try
//        {
//            std::cout << "Enter row: ";
//            std::cin >> row;
//            std::cout << "Enter col: ";
//            std::cin >> col;
//
//            BinaryImg<bool> example(row, col);
//            std::cout << example;
//            system("pause");
//            std::cout << example;
//            system("pause");
//            bool exit1 = false;
//            int choice1 = 0;
//            while (!exit1)
//            {
//                printMenu1();
//                std::cin >> choice1;
//                switch (choice1)
//                {
//                case(1):
//                    try
//                    {
//                        int x, y;
//                        bool tmp = false;
//                        std::cout << "Enter coordinates of element: " << std::endl;
//                        std::cout << "enter x: ";
//                        std::cin >> x;
//                        std::cout << "enter y: ";
//                        std::cin >> y;
//                        std::cout << "Enter value: ";
//                        std::cin >> tmp;
//
//                        example(x, y) = tmp;
//                        std::cout << example;
//
//                    }
//                    catch (EClassException& err)
//                    {
//                        err.Print();
//                    }
//
//                    break;
//                case(2):
//                    exit1 = true;
//                    break;
//                default:
//                    std::cout << "Error";
//                    break;
//                }
//            }
//        }
//        catch (EClassException& err)
//        {
//            err.Print();
//        }
//        break;
//    case(2)://char
//        std::cout << "Enter dimenstion of your rectangle:" << std::endl;
//        try
//        {
//            std::cout << "Enter row: ";
//            std::cin >> row;
//            std::cout << "Enter col: ";
//            std::cin >> col;
//
//            BinaryImg<char> example(row, col);
//            std::cout << example;
//            system("pause");
//            bool exit1 = false;
//            int choice1 = 0;
//            while (!exit1)
//            {
//                printMenu1();
//                std::cin >> choice1;
//                switch (choice1)
//                {
//                case(1):
//                    try
//                    {
//                        int x, y;
//                        char tmp = 0;
//                        std::cout << "Enter coordinates of element: " << std::endl;
//                        std::cout << "enter x: ";
//                        std::cin >> x;
//                        std::cout << "enter y: ";
//                        std::cin >> y;
//                        std::cout << "Enter value: ";
//                        std::cin >> tmp;
//
//                        example(x, y) = tmp;
//                        std::cout << example;
//
//                    }
//                    catch (EClassException& err)
//                    {
//                        err.Print();
//                    }
//
//                    break;
//                case(2):
//                    exit1 = true;
//                    break;
//                default:
//                    std::cout << "Error";
//                    break;
//                }
//            }
//        }
//        catch (EClassException& err)
//        {
//            err.Print();
//        }
//        break;
//    case(3)://short
//        std::cout << "Enter dimenstion of your rectangle:" << std::endl;
//        try
//        {
//            std::cout << "Enter row: ";
//            std::cin >> row;
//            std::cout << "Enter col: ";
//            std::cin >> col;
//
//            BinaryImg<short> example(row, col);
//            std::cout << example;
//            system("pause");
//            bool exit1 = false;
//            int choice1 = 0;
//            while (!exit1)
//            {
//                printMenu1();
//                std::cin >> choice1;
//                switch (choice1)
//                {
//                case(1):
//                    try
//                    {
//                        int x, y;
//                        short tmp = 0;
//                        std::cout << "Enter coordinates of element: " << std::endl;
//                        std::cout << "enter x: ";
//                        std::cin >> x;
//                        std::cout << "enter y: ";
//                        std::cin >> y;
//                        std::cout << "Enter value: ";
//                        std::cin >> tmp;
//
//                        example(x, y) = tmp;
//                        std::cout << example;
//
//                    }
//                    catch (EClassException& err)
//                    {
//                        err.Print();
//                    }
//
//                    break;
//                case(2):
//                    exit1 = true;
//                    break;
//                default:
//                    std::cout << "Error";
//                    break;
//                }
//            }
//        }
//        catch (EClassException& err)
//        {
//            err.Print();
//        }
//        break;
//    case(4)://float
//        std::cout << "Enter dimenstion of your rectangle:" << std::endl;
//        try
//        {
//            std::cout << "Enter row: ";
//            std::cin >> row;
//            std::cout << "Enter col: ";
//            std::cin >> col;
//
//            BinaryImg<float> example(row, col);
//            std::cout << example;
//            system("pause");
//            bool exit1 = false;
//            int choice1 = 0;
//            while (!exit1)
//            {
//                printMenu1();
//                std::cin >> choice1;
//                switch (choice1)
//                {
//                case(1):
//                    try
//                    {
//                        int x, y;
//                        float tmp = 0;
//                        std::cout << "Enter coordinates of element: " << std::endl;
//                        std::cout << "enter x: ";
//                        std::cin >> x;
//                        std::cout << "enter y: ";
//                        std::cin >> y;
//                        std::cout << "Enter value: ";
//                        std::cin >> tmp;
//
//                        example(x, y) = tmp;
//                        std::cout << example;
//
//                    }
//                    catch (EClassException& err)
//                    {
//                        err.Print();
//                    }
//
//                    break;
//                case(2):
//                    exit1 = true;
//                    break;
//                default:
//                    std::cout << "Error";
//                    break;
//                }
//            }
//        }
//        catch (EClassException& err)
//        {
//            err.Print();
//        }
//        break;
//    case(5):
//
//        exit3 = true;
//        break;
//    default:
//        std::cout << "Error";
//        break;
//    }
//}

