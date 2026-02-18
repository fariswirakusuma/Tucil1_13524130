

#ifndef QUEENFRAME_HPP
#define QUEENFRAME_HPP

#include <wx/wx.h>
#include <vector>
#include <string>

class QueenFrame : public wxFrame {
public:
    QueenFrame();
    wxStaticBitmap* m_bitmapDisplay; 
    std::vector<std::string> m_finalBoard;
    std::vector<std::string> m_initialBoard;
private:
};

#endif