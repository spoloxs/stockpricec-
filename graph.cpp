#include <iostream>

void drawupperline(float high, float open, float close, float length)
{
    if(close > open)
    {
        float height = abs(high/length - close/length);
        for (int i = 0; i < height; i++)
        {
            std::cout << "│" << std::endl;
        }
    }
    else
    {
        float height = abs(high/length - open/length);
        for (int i = 0; i < height; i++)
        {
            std::cout << "│" << std::endl;
        }
    }
}

void drawbody(float open, float close, float length)
{
    float height = abs(close/length - open/length);
    for (double i = 0; i < height; i+=0.5)
    {
        std::cout << "░" << std::endl;
    }
    if ((int) height == 0)
    {
        std::cout << "─" << std::endl;
    }
}

void drawlowerline(float low, float open, float close, float length)
{
    if(close > open)
    {
        float height = abs(close/length -  low/length);
        for (int i = 0; i < height; i++)
        {
            std::cout << "│" << std::endl;
        }
    }
    else
    {
        float height = abs(open/length - low/length);
        for (int i = 0; i < height; i++)
        {
            std::cout << "│" << std::endl;
        }
    }
}