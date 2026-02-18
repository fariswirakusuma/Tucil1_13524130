#ifndef INPUTFILE_HPP
#define INPUTFILE_HPP


#include <bits/stdc++.h>
#include <opencv2/opencv.hpp>
#include "shape.hpp"

using namespace std;
using namespace cv;
#include "inputfile.hpp"
#include <opencv2/opencv.hpp>
#include <fstream>
#include <map>

using namespace std;
using namespace cv;
vector<string> create_str_map_from_file(const string& filename) ;
pair<Shape_Arr, vector<string>> load_from_png(const string& path);

Shape_Arr import_shapes_from_file(const string& filename);
#endif