
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
void update_position(wxStaticText* label, const std::vector<int>& allpos, const std::vector<std::string>& initboard, int jumlah_kasus){
    if (label != nullptr) {
        vector<string> temp_board = output_str(allpos, initboard);
        stringstream ss;
        for (const auto& line : temp_board) ss << line << "\n";
        ss << wxString::Format("\nCek Kasus: %d", jumlah_kasus);
        label->SetLabel(wxString(ss.str()));
        wxSafeYield();
    }
}
bool find_solution(Shape_Arr allshape, int_arr& allpos, std::vector<int_arr>& allpermute, int& jumlah_kasus, int_arr& valid_array, wxStaticText* output_label, std::vector<std::string> initboard){
    
    allpos.assign(9, 0); // Inisialisasi ukuran array
    allpermute.clear();
    jumlah_kasus = 0;

    for (int b1=0;b1<9;b1++){
        allpos[0]=b1;
        for (int b2=0;b2<9;b2++){
            allpos[1]=b2;
            jumlah_kasus++;
            if(jumlah_kasus % VIEW_SPEED == 0) update_position(output_label,allpos,initboard,jumlah_kasus);
            if (b2 == b1) continue;
            for (int b3=0;b3<9;b3++){
                allpos[2]=b3;
                jumlah_kasus++;
                if(jumlah_kasus % VIEW_SPEED == 0) update_position(output_label,allpos,initboard,jumlah_kasus);
                if (b3 == b1 || b3 == b2) continue;
                for (int b4=0;b4<9;b4++){
                    allpos[3]=b4;
                    jumlah_kasus++;
                    if(jumlah_kasus % VIEW_SPEED == 0) update_position(output_label,allpos,initboard,jumlah_kasus);
                    if (b4 == b1 || b4 == b2 || b4 == b3) continue;
                    for (int b5=0;b5<9;b5++){
                        allpos[4]=b5;
                        jumlah_kasus++;
                        if(jumlah_kasus % VIEW_SPEED == 0) update_position(output_label,allpos,initboard,jumlah_kasus);
                        if (b5 == b1 || b5 == b2 || b5 == b3 || b5 == b4) continue;
                        for (int b6=0;b6<9;b6++){
                            allpos[5]=b6;
                            jumlah_kasus++;
                            if(jumlah_kasus % VIEW_SPEED == 0) update_position(output_label,allpos,initboard,jumlah_kasus);
                            if (b6 == b1 || b6 == b2 || b6 == b3 || b6 == b4 || b6 == b5) continue;
                            for (int b7=0;b7<9;b7++){
                                allpos[6]=b7;
                                jumlah_kasus++;
                                if(jumlah_kasus % VIEW_SPEED == 0) update_position(output_label,allpos,initboard,jumlah_kasus);
                                if (b7 == b1 || b7 == b2 || b7 == b3 || b7 == b4 || b7 == b5 || b7 == b6) continue;
                                for (int b8=0;b8<9;b8++){
                                    allpos[7]=b8;
                                    jumlah_kasus++;
                                    if(jumlah_kasus % VIEW_SPEED == 0) update_position(output_label,allpos,initboard,jumlah_kasus);
                                    if (b8 == b1 || b8 == b2 || b8 == b3 || b8 == b4 || b8 == b5 || b8 == b6 || b8 == b7) continue;
                                    for (int b9=0;b9<9;b9++){
                                        allpos[8]=b9;
                                        jumlah_kasus++;
                                        if(jumlah_kasus % VIEW_SPEED == 0) update_position(output_label,allpos,initboard,jumlah_kasus);
                                        // Cek b9 terhadap semua indeks sebelumnya
                                        if (b9 == b1 || b9 == b2 || b9 == b3 || b9 == b4 || b9 == b5 || b9 == b6 || b9 == b7 || b9 == b8) continue;

                                        if (diagonal_valid(allpos)) {
                                            allpermute.push_back(allpos);
                                            
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
                                                update_position(output_label,allpos,initboard,jumlah_kasus);
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

