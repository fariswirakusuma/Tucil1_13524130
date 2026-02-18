#include <wx/wx.h>
#include <wx/filedlg.h>
#include <iostream>  
#include <chrono>
#include "queenframe.hpp"
#include "outputarr.hpp"
#include "allqueendirec.hpp"
#include "inputfile.hpp"

class QueenApp : public wxApp {
public:
    bool OnInit() override {
        wxInitAllImageHandlers();
        QueenFrame* frame = new QueenFrame();
        frame->Centre();
        frame->Show(true);
        return true;
    }
};

wxIMPLEMENT_APP(QueenApp);

QueenFrame::QueenFrame() : wxFrame(nullptr, wxID_ANY, "Queen LinkedIn Solver", wxDefaultPosition, wxSize(650, 850)) {
    wxPanel* panel = new wxPanel(this);
    
    m_bitmapDisplay = new wxStaticBitmap(panel, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxSize(450, 450));
    
    wxStaticText* output = new wxStaticText(panel, wxID_ANY, "Ready", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
    output->SetFont(wxFont(10, wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

    wxButton* btnCari = new wxButton(panel, wxID_ANY, "Pilih File Dan Cari Solusi");
    wxButton* btnSimpan = new wxButton(panel, wxID_ANY, "Simpan Hasil (.png)");
    btnSimpan->Enable(false); 

    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(m_bitmapDisplay, 0, wxALIGN_CENTER | wxALL, 15);
    sizer->Add(btnCari, 0, wxALIGN_CENTER | wxTOP, 5);
    sizer->Add(btnSimpan, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 5);
    sizer->Add(output, 1, wxEXPAND | wxALL, 15);
    panel->SetSizer(sizer);
    btnCari->Bind(wxEVT_BUTTON, [this, output, btnSimpan](wxCommandEvent&) {
        wxFileDialog openDlg(this, "Buka Board", "test/", "", "Board Files (*.png;*.txt)|*.png;*.txt", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
        if (openDlg.ShowModal() == wxID_CANCEL) return;

        std::string path = std::string(openDlg.GetPath().mb_str());
        
        Shape_Arr shapes;
        std::vector<std::string> initboard;

        if (path.substr(path.find_last_of(".") + 1) == "png") {
            auto res = load_from_png(path);
            shapes = res.first; 
            initboard = res.second;
        } else {
            shapes = import_shapes_from_file(path);
            initboard = create_str_map_from_file(path);
        }

        if (shapes.empty()) {
            output->SetLabel("Error: File tidak valid!");
            return;
        }
        this->m_initialBoard = initboard;

        std::vector<int> allpos(shapes.size(), 0);
        std::vector<std::vector<int>> allpermute;
        std::vector<int> valid_array;
        int jumlah_kasus = 0;

        auto t1 = std::chrono::high_resolution_clock::now();
        bool ketemu = find_solution(shapes, allpos, allpermute, jumlah_kasus, valid_array, output, this->m_initialBoard, this);
        auto t2 = std::chrono::high_resolution_clock::now();
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();

        if (ketemu) {
            this->m_finalBoard = output_str(valid_array, this->m_initialBoard);
            
            wxString final_text;
            for (const auto& line : this->m_finalBoard) final_text << line << "\n";
            final_text << wxString::Format("\nSUCCESS!\nWaktu pencarian: %lld ms\nBanyak kasus yang ditinjau: %d kasus", ms, jumlah_kasus);
            output->SetLabel(final_text);
            cv::Mat finalMat = renderToMat(this->m_finalBoard, this->m_initialBoard); 
            if (!finalMat.empty()) {
                m_bitmapDisplay->SetBitmap(wxBitmap(MatToWxImage(finalMat)));
            }
            
            btnSimpan->Enable(true);
        } else {
            output->SetLabel(wxString::Format("Tidak ada solusi\nWaktu pencarian: %lld ms\nBanyak kasus yang ditinjau: %d kasus", ms, jumlah_kasus));
            btnSimpan->Enable(false);
        }
        
        this->Layout();
    });
    btnSimpan->Bind(wxEVT_BUTTON, [this](wxCommandEvent&) {
        if (this->m_finalBoard.empty() || this->m_initialBoard.empty()) {
            wxMessageBox("Gagal menyimpan: Data papan tidak lengkap.", "Error", wxOK | wxICON_ERROR);
            return;
        }

        wxFileDialog saveDlg(this, "Simpan Gambar", "", "solusi.png", "PNG files (*.png)|*.png", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
        if (saveDlg.ShowModal() == wxID_CANCEL) return;
        std::string path = std::string(saveDlg.GetPath().mb_str());
        if (!path.empty()) {
            renderToImage(this->m_finalBoard, this->m_initialBoard, path);
            wxMessageBox("Gambar berhasil disimpan!", "Info", wxOK | wxICON_INFORMATION);
        }
    });
}