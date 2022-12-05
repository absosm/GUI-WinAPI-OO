/* 
 * File:   base.cpp
 * Author: SONY
 * 
 * Created on 29 March 2013, 09:07
 */

#include "base.h"
#include "menu.h"

using namespace gui;

base::base(){
	handle=0;
	parent=0;
	defaultProcess=0;
	background=0;
	color=0;
}

void base::InitializeBase(){
    SetWindowLongPtr(handle, GWLP_USERDATA, (LONG_PTR)this);
    Font = font::getDefault();
    setFont(Font);
}

void base::Show() {
    ShowWindow(handle, SW_SHOW);
}

void base::Hide() {
    ShowWindow(handle, SW_HIDE);
}

void base::Close() {
    DestroyWindow(handle);
}

void base::setPosition(POSITION pos) {
    position = pos;
    SetWindowPos(handle, 0, pos.x, pos.y, 0, 0, SWP_NOSIZE);
}

void base::setPosition(LONG x, LONG y) {
    position.x = x;
    position.y = y;
    SetWindowPos(handle, 0, x, y, 0, 0, SWP_NOSIZE);
}

void base::setParent(base *parent) {
    
    if (parent == this->parent) return;
    
    if(this->parent != 0) {
        this->parent->RemoveChild(this);
        this->parent = 0;
    }
    
    if(parent == 0) {
        SetParent(this->handle, 0);
        RemoveStyle(WS_CHILD);
    } else {
        addStyle(WS_CHILD);
        RemoveStyle(WS_CAPTION);
        this->parent = parent;
        parent->addChild(this);
        SetParent(this->handle, parent->getHandle());
    }

    if(this->parent != 0){
        this->parent->Redraw();
    }
    
}

void base::setFont(font *Font) {
    SendMessage(handle, WM_SETFONT, (WPARAM)Font->getHandle(), true);
    this->Font = Font;
}

void base::setStyle(DWORD style) {
    SetWindowLong(handle, GWL_STYLE, style);
    Redraw();
}

DWORD base::getStyle() {
    return GetWindowLong(handle, GWL_STYLE);
}

void base::addStyle(DWORD style) {
    setStyle(getStyle() | style);
}

void base::RemoveStyle(DWORD style) {
    setStyle(getStyle() & (~style));
}

void base::setExtendedStyle(DWORD style) {
    SetWindowLong(handle, GWL_EXSTYLE, style);
    Redraw();
}

DWORD base::getExtendedStyle() {
    return GetWindowLong(handle, GWL_EXSTYLE);
}

void base::addChild(base* child) {
    if(child->getParent() != this) {
        child->setParent(this);
    } else {
        children.push_back(child);
    }
}

void base::RemoveChild(base *child) {
    for(unsigned int i = 0; i < children.size(); i++) {
        if(children[i] == child) {
            children.erase(children.begin() + i);
            if(child->getParent() == this) {
                child->setParent(0);
            }
            break;
        }
    }
}

base *base::getParent() {
    return parent;
}

POSITION base::getPosition() {
    
    RECT rect;
    
    GetWindowRect(handle, &rect);
    
    position.x = rect.left;
    position.y = rect.top;
    
    return position;
}

void base::setSize(LONG width, LONG height) {
    
    size.width = width;
    size.height = height;
    SetWindowPos(handle, 0, 0, 0, width, height, SWP_NOMOVE);
}

Size base::getSize() {
    
    RECT rect;
    
    GetWindowRect(handle, &rect);
    
    size.width = rect.right - rect.left;
    size.height = rect.bottom - rect.top;
    
    return size;   
}

HWND base::getHandle() {
    return (handle);
}

void base::Destroy() {
    if(handle != 0) {
        DestroyWindow(handle);
        handle = 0;
    }
}

void base::Redraw() {
    InvalidateRect(handle, 0, true);
}

void base::setText(LPCSTR szText){
    SetWindowText(handle, szText);
}

LPCSTR base::getText() {
    
    LPSTR str;
    
    int length = GetWindowTextLength(handle);
    
    str = (LPSTR)malloc(sizeof(char) * (length + 1));
    
    GetWindowText(handle, str, length + 1);
            
    return str;
}

void base::setEnabled(bool enabled) {
    EnableWindow(handle, enabled);
}

bool base::getEnabled() {
    return (bool)(IsWindowEnabled(handle) == TRUE);
}

void base::setBackgroundColor(BYTE r, BYTE g, BYTE b) {
    if(background != 0)
        DeleteObject(background);

    background = CreateSolidBrush(RGB(r, g, b));
}

void base::setColor(BYTE r, BYTE g, BYTE b) {
    color = RGB(r, g, b);
}

int base::Loop() {
    MSG messages;
   
    while (GetMessage(&messages, NULL, 0, 0)) {
        TranslateMessage(&messages);
        DispatchMessage(&messages);
    }
    
    return messages.wParam;
}

bool base::onCreate(){
    return false;
}

bool base::onClose(){
    return false;
}

bool base::onMouseMove(POINTS point) {
    return false;
}

bool base::onMouseDoubleClick(POINTS point) {
    return false;
}

bool base::onMouseClick(POINTS point, MouseButton button) {
    return false;
}

bool base::onMouseDown(POINTS point, MouseButton button) {
    return false;
}

bool base::onMouseUp(POINTS point, MouseButton button) {
    return false;
}

bool base::onKeyDown(WCHAR key) {
    return false;
}

bool base::onKeyUp(WCHAR key) {
    return false;
}

bool base::onActivate() {
    return false;
}

bool base::onTextChanged(LPCSTR szText) {
    return false;
}

LRESULT base::WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){
    
    base *element = (base*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
    
    if(element != 0) {
        switch (message) {
            case WM_ACTIVATE: if (element->onActivate()) { return 0;} break;
            case WM_SETTEXT: if (element->onTextChanged((LPCSTR)lParam)){ return 0;} break;
            case WM_CLOSE: if (element->onClose()) { return 0;} break;
            case WM_CREATE: if (element->onCreate()) { return 0;} break;
            case WM_LBUTTONDBLCLK: {POINTS pos = MAKEPOINTS(lParam); if (element->onMouseDoubleClick(pos)) return 0;} break;
            case WM_MOUSEMOVE: {POINTS pos = MAKEPOINTS(lParam); if (element->onMouseMove(pos)) return 0;} break;
            case WM_LBUTTONDOWN:
            case WM_RBUTTONDOWN:
            case WM_MBUTTONDOWN:{
                POINTS pos = MAKEPOINTS(lParam);
                MouseButton button = (message == WM_LBUTTONDOWN) ? Left : ((message == WM_RBUTTONDOWN) ? Right : Middle);
                if(element->onMouseDown(pos, button)) return 0;
                break;
            }
            case WM_LBUTTONUP:
            case WM_RBUTTONUP:
            case WM_MBUTTONUP: {
                POINTS pos = MAKEPOINTS(lParam);
                MouseButton button = (message == WM_LBUTTONDOWN) ? Left : ((message == WM_RBUTTONDOWN) ? Right : Middle);
                element->onMouseClick(pos, button);
                if(element->onMouseUp(pos, button)) return 0;
                break;
            }
            case WM_KEYDOWN: if(element->onKeyDown((WCHAR)wParam)) return 0; break;
            case WM_KEYUP: if(element->onKeyUp((WCHAR)wParam)) return 0; break;
            case WM_DESTROY: PostQuitMessage(WM_QUIT); break;
            case WM_MENUCOMMAND: {
                menu *Menu = menu::getByHandle((HMENU)lParam);
                mitem *item = Menu->getItemByIndex(wParam);
                item->onMouseClick();
            } break;
            case WM_CTLCOLORSTATIC:
            case WM_CTLCOLORBTN:
            case WM_CTLCOLOREDIT:
            case WM_CTLCOLORLISTBOX:
            case WM_CTLCOLORSCROLLBAR: {
                base *control = (base*)GetWindowLongPtr((HWND)lParam, GWLP_USERDATA);
                SetBkMode((HDC)wParam,TRANSPARENT);
                SetTextColor((HDC)wParam, control->color);
                if(control != 0 && control->background != 0)
                    return (INT_PTR)control->background;
                else
                    return (BOOL)CreateSolidBrush(GetSysColor(COLOR_MENU));
                break;
            }
            default: break;
        }
        
        if(element->defaultProcess != 0) {
            return CallWindowProc((WNDPROC)element->defaultProcess, hwnd, message, wParam, lParam);
        }
    }

    return DefWindowProc(hwnd, message, wParam, lParam);
    
}

base::~base() {
}
