#include "MainFrame.h"

MainFrame::MainFrame(const std::string& title,const wxSize& size)
       : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, size)
{

    auto panel = new wxScrolled<wxPanel>(this, wxID_ANY);
    panel->SetScrollRate(0, FromDIP(10));
    wxBoxSizer* topsizer = new wxBoxSizer( wxVERTICAL );

    topsizer->Add(
        new ParamContainer(panel, 1, std::string("SomeParam")),
        0,            // make vertically stretchable
        wxEXPAND |    // make horizontally stretchable
        wxALL,        //   and make border all around
        1 );
    topsizer->AddSpacer(4);
    topsizer->Add(
        new ParamContainer(panel, 1, std::string("SomeParam")),
        0,            // make vertically stretchable
        wxEXPAND |    // make horizontally stretchable
        wxALL,        //   and make border all around
        1 );
            topsizer->AddSpacer(4);
    topsizer->Add(
        new ParamContainer(panel, 1, std::string("SomeParam")),
        0,            // make vertically stretchable
        wxEXPAND |    // make horizontally stretchable
        wxALL,        //   and make border all around
        1 );
            topsizer->AddSpacer(4);
    topsizer->Add(
        new ParamContainer(panel, 1, std::string("SomeParam")),
        0,            // make vertically stretchable
        wxEXPAND |    // make horizontally stretchable
        wxALL,        //   and make border all around
        1 );
            topsizer->AddSpacer(4);
    topsizer->Add(
        new ParamContainer(panel, 1, std::string("SomeParam")),
        0,            // make vertically stretchable
        wxEXPAND |    // make horizontally stretchable
        wxALL,        //   and make border all around
        1 );
            topsizer->AddSpacer(4);
    topsizer->Add(
        new ParamContainer(panel, 1, std::string("SomeParam")),
        0,            // make vertically stretchable
        wxEXPAND |    // make horizontally stretchable
        wxALL,        //   and make border all around
        1 );
            topsizer->AddSpacer(4);
    topsizer->Add(
        new ParamContainer(panel, 1, std::string("SomeParam")),
        0,            // make vertically stretchable
        wxEXPAND |    // make horizontally stretchable
        wxALL,        //   and make border all around
        1 );
            topsizer->AddSpacer(4);
    topsizer->Add(
        new ParamContainer(panel, 1, std::string("SomeParam")),
        0,            // make vertically stretchable
        wxEXPAND |    // make horizontally stretchable
        wxALL,        //   and make border all around
        1 );
            topsizer->AddSpacer(4);
    topsizer->Add(
        new ParamContainer(panel, 1, std::string("SomeParam")),
        0,            // make vertically stretchable
        wxEXPAND |    // make horizontally stretchable
        wxALL,        //   and make border all around
        1 );
            topsizer->AddSpacer(4);
    topsizer->Add(
        new ParamContainer(panel, 1, std::string("SomeParam")),
        0,            // make vertically stretchable
        wxEXPAND |    // make horizontally stretchable
        wxALL,        //   and make border all around
        1 );
            topsizer->AddSpacer(4);
    topsizer->Add(
        new ParamContainer(panel, 1, std::string("SomeParam")),
        0,            // make vertically stretchable
        wxEXPAND |    // make horizontally stretchable
        wxALL,        //   and make border all around
        1 );
            topsizer->AddSpacer(4);
    topsizer->Add(
        new ParamContainer(panel, 1, std::string("SomeParam")),
        0,            // make vertically stretchable
        wxEXPAND |    // make horizontally stretchable
        wxALL,        //   and make border all around
        1 );
            topsizer->AddSpacer(4);
    topsizer->Add(
        new ParamContainer(panel, 1, std::string("SomeParam")),
        0,            // make vertically stretchable
        wxEXPAND |    // make horizontally stretchable
        wxALL,        //   and make border all around
        1 );

    panel->SetSizerAndFit(topsizer);
}