#ifndef SHAPE_HPP
#define SHAPE_HPP
#include <bits/stdc++.h>
using namespace std;

struct kord{
    int x;
    int y;
};
struct Shape {
    char key;
    vector<kord> point;
    bool isvalid = false;
};
#define Shape_Arr vector<Shape>
#define int_arr vector<int>
#endif