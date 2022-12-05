/* 
 * File:   label.cpp
 * Author: SONY
 * 
 * Created on 31 March 2013, 19:29
 */

#include "lable.h"

using namespace gui;

lable::lable(){
    
}

lable::lable(LPCSTR szText, base *parent) {
    Create(szText, parent);
}

void lable::Create(LPCSTR szText, base* parent) {
    
    HINSTANCE hInstance = GetModuleHandle(NULL);
    
    this->handle = CreateWindowEx(0, "STATIC", "", 0, 
            CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 
            0, 0, hInstance, 0);
    
    this->defaultProcess = SetWindowLongPtr(this->handle, GWLP_WNDPROC, (LONG)(WNDPROC)WindowProcedure);
    
    setParent(parent);
    setText(szText);
    setSize(100, 14);
    InitializeBase();
    Show();
}

lable::~lable() {
}

