#include "outputarr.hpp"
using namespace std;
vector<string> output_str(const int_arr& iarr,vector<string> vstr){
    vector<string> result;
    // for (size_t y=0;y<vstr.size();y++){
    //     string line;
    //     for (size_t x)
    // }

    for (int iy=0;iy<9;iy++){
        string line;
        for (int ix=0;ix<9;ix++){
            if (ix==iarr[iy])line.push_back('#');
            else line.push_back(vstr[iy][ix]);
            line.push_back(' ');
        }
        result.push_back(line);
    }

    // for (auto& s:sa){
    //     string line;
    //     for (size_t i=0;i<s.point.size();i++){
    //         bool has_queen = false;
    //         for (size_t j=0;j<iarr.size();j++){
    //             if(iarr[j]==s.point[i].x&&j==s.point[i].y){
    //                 has_queen = true;
    //             }
    //         }
    //         if (has_queen)line.push_back('#');
    //         else line.push_back(s.key);
    //     }
    //     result.push_back(line);
    // }
    return result;
}