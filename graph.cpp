#include <iostream>
#include <bits/stdc++.h>

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
    if ((int) height < 0 || (int) height == 0) 
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

void draw_axis(std::vector<float> arrayyy)
{   
    int size = 60;
    arrayyy.erase(
    std::remove(arrayyy.begin(), arrayyy.end(), 0),
    arrayyy.end());
    // std::cout << *(arrayyy.end() - 1) << std::endl;
    float y_min = *std::min_element(arrayyy.end() - size, arrayyy.end()) ;
    float y_max = *std::max_element(arrayyy.end() - size, arrayyy.end()) ;
    // std::cout << y_max << std::endl;
    float div = (y_max - y_min) / 15;
    std::vector<std::vector<std::string>> printmatrix;
    // std::cout << arrayyy[arrayyy.size() - 1] << std::endl;
    // std::cout << div << std::endl;
    for(float y = y_max + div; y >= y_min - div; y -= div)
    {
        // std::cout << y << " |";
        std::vector<std::string> temp;
        temp.push_back(std::to_string(y));
        temp.push_back(" |");
        for(int i = 0; i < size; i++)
        {
            if(arrayyy[arrayyy.size() - size + i] <= y && arrayyy[arrayyy.size() - size + i] > (y - div))
            {
                temp.push_back("-");
            }
            else
            {
                temp.push_back(" ");
            }
        }
        printmatrix.push_back(temp);
    }
    // std::cout << printmatrix.size() << std::endl;
    float y = y_max + div;
    for(int i = 0; i < printmatrix.size(); i++)
    {
        // std::cout << std::fixed << std::setprecision(3) << y << " |";
        for(int j = 0; j < printmatrix[i].size(); j++)
        {
            std::cout << std::fixed << std::setprecision(3) << printmatrix[i][j] << " ";
        }
        std::cout << std::endl;
        y -= div;
    }
}