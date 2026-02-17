
#include "allqueendirec.hpp"

using namespace std;

bool diagonal_valid(const int_arr &checked_arr){
    for (int i=0;i<9;i++) {
        for (int j = i+1; j < 9; j++) {
            if (abs(checked_arr[i]-checked_arr[j]) == abs(i-j)) {
                return false; 
            }
        }
    }
    return true;
}

bool find_solution(Shape_Arr allshape, int_arr& allpos, std::vector<int_arr>& allpermute, int& jumlah_kasus, int_arr& valid_array, wxStaticText* output_label, std::vector<std::string> initboard){
    for (int i=0;i<9;i++)allpos.push_back(i);
    allpermute.clear();
    jumlah_kasus = 0;
    for (int b1=0;b1<9;b1++){
        for (int b2=0;b2<9;b2++){
            for (int b3=0;b3<9;b3++){
                for (int b4=0;b4<9;b4++){
                    for (int b5=0;b5<9;b5++){
                        for (int b6=0;b6<9;b6++){
                            for (int b7=0;b7<9;b7++){
                                for (int b8=0;b8<9;b8++){
                                    for (int b9=0;b9<9;b9++){


                                        allpos[0]=b1;
                                        allpos[1]=b2;
                                        allpos[2]=b3;
                                        allpos[3]=b4;
                                        allpos[4]=b5;
                                        allpos[5]=b6;
                                        allpos[6]=b7;
                                        allpos[7]=b8;
                                        allpos[8]=b9;


                                        if (diagonal_valid(allpos)) {
                                            allpermute.push_back(allpos);
                                            jumlah_kasus++;

                                            if (jumlah_kasus % 1000 == 0 && output_label != nullptr) {
                                                std::vector<std::string> temp_board = output_str(allpos, initboard);
                                                wxString live_display;
                                                for (const auto& line : temp_board) live_display << line << "\n";
                                                live_display << wxString::Format("\nChecking Case: %d", jumlah_kasus);
                                                output_label->SetLabel(live_display);
                                                wxSafeYield();
                                            }
                                            for (int i=0;i<(int)allshape.size();i++) {
                                                allshape[i].isvalid = false;
                                            }
                                            for (int y=0;y<9;y++) {
                                                int x = allpos[y];
                                                for (int i=0;i<(int)allshape.size();i++) {
                                                    for (const auto& p:allshape[i].point) {
                                                        if (p.x == x && p.y == y) {
                                                            allshape[i].isvalid = true;
                                                            break;
                                                        }
                                                    }
                                                }
                                            }
                                            bool ok = true;
                                            for (const Shape& s:allshape) {
                                                if (!s.isvalid) {
                                                    ok = false;
                                                    break;
                                                }
                                            }

                                            if (ok) {
                                                valid_array = allpos;
                                                return true;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return false;
}

// bool find_valid_array(const vector<int_arr>& allpermute,Shape_Arr allshape,int_arr& valid_array,int& jumlah_kasus)
// {
//     for (const auto& current_arr : allpermute) {
//         int used = 0;
//         for (Shape& s : allshape){
//             if (s.isvalid) used++;
//         }
//         // static int best = 0;
//         // best = max(best, used);
//         // cout << "used = " << used << ", best = " << best << endl;
//         for (int y = 0; y < (int)current_arr.size(); y++) {
//             int x = current_arr[y];

//             for (Shape& s : allshape) {
//                 for (kord& p : s.point) {
//                     if (p.x == x && p.y == y) {
//                         s.isvalid = true;
//                         break;
//                     }
//                 }
//             }
//         }
//         bool ok = true;
//         for (const Shape& s : allshape) {
//             if (!s.isvalid) {
//                 ok = false;
//                 break;
//             }
//         }

//         if (ok) {
//             valid_array = current_arr;
//             return true;
//         }
//         jumlah_kasus++;
//     }
//     return false;
// }

