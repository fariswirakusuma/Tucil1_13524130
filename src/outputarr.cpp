#include "outputarr.hpp"
using namespace std;
using namespace cv;

// --- 1. Fungsi Warna ---
Scalar getShapeColor(char ch) {
    static map<char, Scalar> colorMap = {
        {'A', Scalar(150, 200, 255)}, {'B', Scalar(150, 255, 150)}, 
        {'C', Scalar(255, 200, 150)}, {'D', Scalar(200, 150, 255)},
        {'E', Scalar(255, 255, 150)}, {'F', Scalar(150, 255, 255)},
        {'G', Scalar(255, 150, 150)}, {'H', Scalar(200, 200, 200)}
    };
    if (colorMap.count(ch)) return colorMap[ch];
    return Scalar(240, 240, 240); 
}

// --- 2. Konversi Mat ke wxImage ---
wxImage MatToWxImage(Mat& mat) {
    if (mat.empty()) return wxImage();
    Mat rgb;
    cvtColor(mat, rgb, COLOR_BGR2RGB);
    unsigned char* data = (unsigned char*)malloc(rgb.rows * rgb.cols * 3);
    if (!data) return wxImage();
    memcpy(data, rgb.data, rgb.rows * rgb.cols * 3);
    return wxImage(rgb.cols, rgb.rows, data, false);
}

// --- 3. Logika Penanda Queen ---
vector<string> output_str(const vector<int>& pos, const vector<string>& initboard) {
    vector<string> result = initboard;
    for (int r = 0; r < (int)pos.size(); r++) {
        int c = pos[r];
        if (r < (int)result.size() && c >= 0 && c < (int)result[r].size()) {
            result[r][c] = '#'; 
        }
    }
    return result;
}

// --- 4. Render Mat (Anti-Crash) ---
Mat renderToMat(const vector<string>& vstr, const vector<string>& initboard) {
    if (vstr.empty()) return Mat();
    int n = vstr.size();
    int cellSize = 60;
    Mat board(n * cellSize, n * cellSize, CV_8UC3, Scalar(255, 255, 255));
    Mat q = imread("test/queen.png", IMREAD_UNCHANGED);
    if (q.empty()) q = imread("queen.png", IMREAD_UNCHANGED);
    if (q.empty()) q = imread("bin/test/queen.png", IMREAD_UNCHANGED);
    if (q.empty()) q = imread("../test/queen.png", IMREAD_UNCHANGED);
    if (!q.empty()) {
        resize(q, q, Size(cellSize - 10, cellSize - 10));
    }

    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            Rect box(c * cellSize, r * cellSize, cellSize, cellSize);
            rectangle(board, box, getShapeColor(initboard[r][c]), -1);
            rectangle(board, box, Scalar(80, 80, 80), 1);

            if (vstr[r][c] == '#') {
                if (!q.empty()) {
                    int x_off = c * cellSize + 5;
                    int y_off = r * cellSize + 5;
                    Mat roi = board(Rect(x_off, y_off, q.cols, q.rows));
                    
                    if (q.channels() == 4) {
                        Mat bgra[4]; 
                        split(q, bgra);
                        Mat color; 
                        merge(vector<Mat>{bgra[0], bgra[1], bgra[2]}, color);
                        // Alpha blending supaya transparan
                        color.copyTo(roi, bgra[3]); 
                    } else {
                        q.copyTo(roi);
                    }
                } else {
                    circle(board, Point(c * cellSize + 30, r * cellSize + 30), 20, Scalar(0, 0, 255), -1);
                }
            }
        }
    }
    return board;
}
void update_position(wxStaticText* label, const vector<int>& pos, const vector<string>& initboard, int kasus, QueenFrame* frame) {
    if (kasus % 50 == 0) {
        label->SetLabel(wxString::Format("Mencoba Kemungkinan: %d", kasus));
        vector<string> temp_board = output_str(pos, initboard);
        
        Mat m = renderToMat(temp_board, initboard);
        
        if (frame && frame->m_bitmapDisplay) {
            frame->m_bitmapDisplay->SetBitmap(wxBitmap(MatToWxImage(m)));
        }
        wxYield();
    }
}

void renderToImage(const vector<string>& vstr, const vector<string>& initboard, string fileName) {
    Mat res = renderToMat(vstr, initboard);
    if (!res.empty()) {
        imwrite(fileName, res);
    }
}