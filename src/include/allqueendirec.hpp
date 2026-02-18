#ifndef ALLQUEENDIREC_HPP
#define ALLQUEENDIREC_HPP

#include <bits/stdc++.h>
#include "shape.hpp"
#include "outputarr.hpp"
#include "queenframe.hpp"
#include <wx/wx.h>
using namespace std;
#define VIEW_SPEED 729
bool diagonal_valid(const int_arr &checked_arr);

void allpossibility(int_arr& allpos,vector<int_arr>&allpermute,int& jumlah_kasus);

// bool find_valid_array(const vector<int_arr>& allpermute,Shape_Arr allshape,int_arr& valid_array,int& jumlah_kasus)
bool find_solution(Shape_Arr allshape, int_arr& allpos, std::vector<int_arr>& allpermute, int& jumlah_kasus, int_arr& valid_array, wxStaticText* output_label, std::vector<std::string> initboard, QueenFrame* frame);

#endif