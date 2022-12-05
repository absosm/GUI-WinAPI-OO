/* 
 * File:   main.cpp
 * Author: SONY
 *
 * Created on 29 March 2013, 00:22
 */
#include "window.h"
#include "resource.h"

using namespace gui;

class TMainForm : public window {
public:
    TMainForm();
    void InitializeComponent();
};

TMainForm Form;
window *MainForm = &Form;

void TMainForm::InitializeComponent() {
    
}

int WINAPI WinMain (HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    
    MainForm->Create("Wa7sh Server");
    ////////////////////////////////////////////////////////////////////////////    
    
    MainForm->setSize(600, 400);
    
    MainForm->setIcon(IDI_ICON_LOGO);
    
    ////////////////////////////////////////////////////////////////////////////
    MainForm->Show();
        
    return MainForm->Loop();
}

TMainForm::TMainForm(){

}
