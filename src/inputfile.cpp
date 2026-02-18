#include "inputfile.hpp"
#include <opencv2/opencv.hpp>
#include <fstream>
#include <map>

using namespace std;
using namespace cv;
vector<string> create_str_map_from_file(const string& filename) {
    vector<string> str_map;
    ifstream file(filename);
    
    if (!file.is_open()) {
        cerr << "Gagal membuka file: " << filename << endl;
        return str_map;
    }

    string line;
    while (getline(file, line)) {
        if (!line.empty() && line.back() == '\r') line.pop_back();
        if (line.empty()) continue;
        str_map.push_back(line);
    }
    file.close();
    return str_map;
}
pair<Shape_Arr, vector<string>> load_from_png(const string& path) {
    Mat img = imread(path);
    Shape_Arr shapes;
    vector<string> dummy_board(9, string(9, '.')); // Template kosong 9x9
    
    if (img.empty()) return {shapes, dummy_board};

    map<string, Shape> mp;
    int cellW = img.cols / 9;
    int cellH = img.rows / 9;

    for (int y = 0; y < 9; y++) {
        for (int x = 0; x < 9; x++) {
            // Ambil warna tepat di tengah cell supaya akurat
            Vec3b p = img.at<Vec3b>(y * cellH + cellH/2, x * cellW + cellW/2);
            string colorKey = to_string(p[0]) + "," + to_string(p[1]) + "," + to_string(p[2]);

            if (mp.find(colorKey) == mp.end()) {
                Shape s;
                s.key = 'A' + mp.size(); 
                s.isvalid = false;
                mp[colorKey] = s;
            }
            mp[colorKey].point.push_back({x, y});
            
            dummy_board[y][x] = mp[colorKey].key;
        }
    }

    for (auto const& [key, val] : mp) shapes.push_back(val);
    return {shapes, dummy_board};
}

Shape_Arr import_shapes_from_file(const string& filename) {
    ifstream file(filename);
    map<char, Shape> mp;
    string line;
    int y = 0;
    while (getline(file, line)) {
        if (!line.empty() && line.back() == '\r') line.pop_back(); // Handle Windows CRLF
        for (int x = 0; x < (int)line.size(); x++) {
            char c = line[x];
            if (isspace(c)) continue;
            if (mp.find(c) == mp.end()) {
                Shape s; s.key = c; s.isvalid = false; mp[c] = s;
            }
            mp[c].point.push_back({x, y});
        }
        y++;
    }
    Shape_Arr res;
    for (auto& p : mp) res.push_back(p.second);
    return res;
}