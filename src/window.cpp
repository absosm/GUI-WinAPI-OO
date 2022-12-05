/* 
 * File:   window.cpp
 * Author: SONY
 * 
 * Created on 29 March 2013, 09:18
 */

#include "window.h"
#include "resource.h"

using namespace gui;

window::window(){

}

void window::Create(LPCSTR szTitle) {
    
    HINSTANCE hThisInstance = GetModuleHandle(NULL);
    
    RegisterWindowClass();
    
    handle = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW,
            "gui",
            szTitle,
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            NULL,
            NULL,
            hThisInstance,
            NULL
            );
    
    InitializeBase();
    
    InitializeComponent();
    
    onCreate();
}

void window::RegisterWindowClass() {
    
    static bool registered = false;
    if(registered) return;
    
    WNDCLASSEX wincl;
    HINSTANCE hThisInstance = GetModuleHandle(NULL);
    
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = "gui";
    wincl.lpfnWndProc = (WNDPROC)base::WindowProcedure;
    wincl.style = CS_DBLCLKS;
    wincl.cbSize = sizeof(WNDCLASSEX);
    
    wincl.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor(NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;
    wincl.cbClsExtra = 0;
    wincl.cbWndExtra = 0;
    
    wincl.hbrBackground = (HBRUSH) COLOR_WINDOW;
    
    RegisterClassEx(&wincl);
    
    registered = true;
}

void window::ShowMessage(LPCSTR sMsg) {
    MessageBox(NULL, sMsg, getText(), MB_OK);
}

void window::setTitle(LPCSTR szTitle) {
    setText(szTitle);
}

LPCSTR window::getTitle() {
    return getText();
}

void window::Maximize() {
    ShowWindow(handle, SW_MAXIMIZE);
}

void window::Minimize() {
    ShowWindow(handle, SW_MINIMIZE);
}

void window::Restore() {
    ShowWindow(handle, SW_RESTORE);
}

void window::setMenu(menu *Menu){
    SetMenu(handle, Menu->getHandle());
}

void window::setIcon(DWORD ID) {
    HICON Icon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(ID));
    SendMessage(handle, WM_SETICON, (WPARAM)ICON_SMALL, (LPARAM)Icon);
    SendMessage(handle, WM_SETICON, (WPARAM)ICON_BIG, (LPARAM)Icon);
}

void window::setBackgroundColor(BYTE r, BYTE g, BYTE b) {
    HBRUSH brush = CreateSolidBrush(RGB(r, g, b));
    SetClassLongPtr(handle, GCLP_HBRBACKGROUND, (LONG)brush);
}

void window::InitializeComponent() {
    
}

window::~window() {
    
}

