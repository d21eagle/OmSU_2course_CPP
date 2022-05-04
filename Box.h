#pragma once
#include <iostream>
using namespace std;

namespace Boxes
{
    class Box {
    public:
        int length;
        int width;
        int height;
        double weight;
        int value;

        Box(int length, int width, int height, double weight, int value);
        [[nodiscard]] int getLength() const;
        [[nodiscard]] int getWidth() const;
        [[nodiscard]] int getHeight() const;
        [[nodiscard]] double getWeight() const;
        [[nodiscard]] int getValue() const;
        void setLength(int length);
        void setWidth(int width);
        void setHeight(int height);
        void setWeight(double weight);
        void setValue(int value);

        static int totalValue(Box boxes[], int size);

        static bool notExceedValue(Box boxes[], int size, int res);

        static double maxWeight(Box boxes[], int size, int maxV);

        static bool boxInBox(Box boxes[], int size);
    };

    bool operator == (Box& boxes1, Box& boxes2);
    istream& operator >> (istream& in, Box& box);
    ostream& operator << (ostream& out, Box& box);
}

