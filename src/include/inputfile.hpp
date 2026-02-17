#ifndef INPUTFILE_HPP
#define INPUTFILE_HPP


#include <bits/stdc++.h>
#include "shape.hpp"
using namespace std;


Shape_Arr import_shapes_from_file(const string& filename);
vector<string> create_str_map_from_file(const string& filename);
#endif