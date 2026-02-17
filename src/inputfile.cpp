

#include "inputfile.hpp"
using namespace std;

Shape_Arr import_shapes_from_file(const string& filename){
    ifstream file (filename);
    if (!file.is_open())cerr << "File Bermasalah";
    map<char, Shape> mp;
    string line;
    int y = 0;
    while (getline(file,line)){
        if (line.empty())continue;
        for (size_t x = 0; x < line.size(); ++x) {
            char c = line[x];
            if (mp.find(c) == mp.end()) {
                Shape s;
                s.key = c;
                mp.emplace(c, s);
            }

            mp[c].point.push_back({ static_cast<int>(x), y });
        }
        ++y;
    }
    file.close();
    Shape_Arr shapes;
    for (auto& p : mp){
        shapes.push_back(p.second);
    }
    return shapes;
}

vector<string> create_str_map_from_file(const string& filename){
    vector<string> str_map;
    ifstream file (filename);
    if (!file.is_open())cerr << "File Bermasalah";
    string line;
    while (getline(file,line)){
        if (line.empty())continue;
        str_map.push_back(line);
        
    }
    return str_map;
}