
#ifndef OUTPUTARR_HPP
#define OUTPUTARR_HPP

#include <bits/stdc++.h>
#include "shape.hpp"
#include "inputfile.hpp"
#include <opencv2/opencv.hpp>
#include <wx/image.h>
#include <wx/bitmap.h> 
#include "queenframe.hpp"

vector<string> output_str(const vector<int>& pos, const vector<string>& initboard);
wxImage MatToWxImage(Mat& mat);
Mat renderToMat(const vector<string>& vstr, const vector<string>& initboard);
void update_position(wxStaticText* label, const vector<int>& pos, const vector<string>& initboard, int kasus, QueenFrame* frame);
void renderToImage(const vector<string>& vstr, const vector<string>& initboard, string fileName);
#endif

