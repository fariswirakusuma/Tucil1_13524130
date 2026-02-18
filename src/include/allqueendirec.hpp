#ifndef ALLQUEENDIREC_HPP
#define ALLQUEENDIREC_HPP

#include <bits/stdc++.h>
#include "shape.hpp"
#include "outputarr.hpp"
#include "queenframe.hpp"
#include <wx/wx.h>
using namespace std;
#define VIEW_SPEED 729
bool diagonal_valid(const int_arr&checked_arr,int n);
void allpossibility(int_arr& allpos,vector<int_arr>&allpermute,int& jumlah_kasus);
bool cek_setiap_shape(const int_arr& pos, Shape_Arr& shapes, int n) ;
bool find_solution(Shape_Arr allshape, int_arr& allpos, vector<int_arr>& allpermute, int& jumlah_kasus, int_arr& valid_array, wxStaticText* output_label,vector<string> initboard, QueenFrame* frame);

#endif