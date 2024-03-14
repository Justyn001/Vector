
#include <iostream>
#include <memory>
#include "Wektor.h"
#include "test.cpp"
#include <gtest/gtest.h>

using namespace std;

int main(int argc, char* argv[])
{
    //testing::InitGoogleTest(&argc, argv);
    //return RUN_ALL_TESTS();

    Wektor<int> wektor;
    Wektor<int> wektor2(10);

    wektor.push_back(1);
    wektor.push_back(2);
    wektor.push_back(3);

    cout << wektor.at(0) << endl;
    cout << wektor.at(1) << endl;
    cout << wektor.at(2) << endl;

    wektor.assign(2, 10);
    cout << wektor.at(2) << endl;

    cout << wektor[0];

    std::cout << std::endl;

    for (auto it = wektor.begin(); it != wektor.end(); it++)
    {
        std::cout << *it << std::endl;
    }

    wektor[0] = 20;

    std::cout << wektor[0] << std::endl;

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;

    for (auto it = wektor.begin(); it != wektor.end(); it++)
    {
        std::cout << *it << std::endl;
    }



    for (int i = 0; i < wektor.getcurrent(); i++)
    {
        wektor[i] = i;
        std::cout << wektor[i];
    }

    for (auto i : wektor)
    {
        std::cout << i << std::endl;
    }
