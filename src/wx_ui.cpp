#include <wx/wx.h>
#include <iostream>  
#include <chrono>
#include "outputarr.hpp"
#include "allqueendirec.hpp"

class QueenFrame : public wxFrame {
public:
    QueenFrame();
};

class QueenApp : public wxApp {
public:
    bool OnInit() override {
        QueenFrame* frame = new QueenFrame();
        frame->Show(true);
        return true;
    }
};

wxIMPLEMENT_APP(QueenApp);

QueenFrame::QueenFrame() : wxFrame(nullptr, wxID_ANY, "Queen LinkedIn Solver", wxDefaultPosition, wxSize(600, 500)) {
    wxPanel* panel = new wxPanel(this);
    wxStaticText* output = new wxStaticText(panel, wxID_ANY, "Ready", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
    output->SetFont(wxFont(10, wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

    wxButton* btn = new wxButton(panel, wxID_ANY, "Cari Solusi");

    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(btn, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 10);
    sizer->Add(output, 1, wxEXPAND | wxALL, 10);
    panel->SetSizer(sizer);

    btn->Bind(wxEVT_BUTTON, [this, output](wxCommandEvent&) {
        using clock = std::chrono::high_resolution_clock;
        
        std::string path = "test/input.txt";
        Shape_Arr shapes = import_shapes_from_file(path);
        std::vector<std::string> initboard = create_str_map_from_file(path);
        
        std::vector<int> allpos(9, 0);
        std::vector<std::vector<int>> allpermute;
        std::vector<int> valid_array;
        int jumlah_kasus = 0;

        auto t1 = clock::now();
        
        bool ketemu = find_solution(shapes, allpos, allpermute, jumlah_kasus, valid_array, output, initboard);

        auto t2 = clock::now();
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();

        if (ketemu) {
            std::vector<std::string> board = output_str(valid_array, initboard);
            wxString final_text;
            for (const auto& line : board) final_text << line << "\n";
            final_text << wxString::Format("\nSUCCESS!\nWaktu pencarian: %lld ms\nBanyak kasus yang ditinjau: %d kasus", ms, jumlah_kasus);
            output->SetLabel(final_text);
        } else {
            output->SetLabel(wxString::Format("Tidak ada solusi Solution\nWaktu pencarian: %lld ms\nBanyak kasus yang ditinjau: %d kasus", ms, jumlah_kasus));
        }
        
        this->Layout();
    });
}