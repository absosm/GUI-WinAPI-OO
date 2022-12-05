/* 
 * File:   mitem.cpp
 * Author: SONY
 * 
 * Created on 02 April 2013, 00:43
 */

#include "menu.h"

using namespace gui;

mitem::mitem() {
	parent=0;
	position=0;
    InitializeInfo();
}

mitem::mitem(LPCSTR text){

	parent=0;
	position=0;
    
    InitializeInfo();

    if(text != 0) {
        mi_info.dwTypeData = (LPSTR)text;
        mi_info.cch = strlen(text);
    }
}

void mitem::setPosition(int position) {
    this->position = position;
}

int mitem::getPosition() {
    return this->position;
}

void mitem::setParent(menu* parent) {
    this->parent = parent;
}

menu *mitem::getParent() {
    return this->parent;
}

void mitem::InitializeInfo() {

    memset(&mi_info, 0, sizeof(MENUITEMINFO));
    mi_info.cbSize = sizeof(MENUITEMINFO);
    mi_info.fMask = MIIM_SUBMENU|MIIM_DATA|MIIM_STRING|MIIM_FTYPE|MIIM_STRING|MIIM_BITMAP|MIIM_CHECKMARKS|MIIM_ID|MIIM_STATE;
    mi_info.dwItemData = (ULONG_PTR)this;
    mi_info.dwTypeData = 0;
    mi_info.cch = 0;
    mi_info.wID = (ULONG_PTR)this;
    mi_info.hSubMenu = 0;
    mi_info.hbmpChecked = 0;
    mi_info.hbmpUnchecked = 0;
    mi_info.hbmpItem = 0;
    mi_info.fType = 0;
    mi_info.fState = MFS_ENABLED | MFS_UNCHECKED;
}

void mitem::setMenu(menu *menu) {

    if(mi_info.hSubMenu != 0) {
        RemoveMenu(parent->getHandle(), (UINT)this, MF_BYCOMMAND);
        mi_info.hSubMenu = (menu != 0 ? menu->getHandle() : 0);
        InsertMenuItem(parent->handle, position, true, &mi_info);
    } else {
        mi_info.hSubMenu = (menu != 0 ? menu->getHandle() : 0);
        UpdateInfo();
    }
}

void mitem::setText(LPCSTR text) {
    if(mi_info.dwTypeData != 0)
        free(mi_info.dwTypeData);

    mi_info.dwTypeData = (LPSTR)text;
    mi_info.cch = strlen(text)+1;

    UpdateInfo();
}

void mitem::setIcon(DWORD ID) {
    HBITMAP hBitmap = LoadBitmap(GetModuleHandle(NULL),MAKEINTRESOURCE(ID));
    mi_info.hbmpItem = (HBITMAP)hBitmap;
    UpdateInfo();
}

void mitem::onMouseClick(){
    return;
}

void mitem::UpdateInfo() {
    
    if(parent != 0) {
        mi_info.fMask = MIIM_SUBMENU|MIIM_DATA|MIIM_STRING|MIIM_FTYPE|MIIM_STRING|MIIM_BITMAP|MIIM_CHECKMARKS|MIIM_ID|MIIM_STATE;
        SetMenuItemInfo(parent->getHandle(), (UINT)this, false, &mi_info);
    }
}

mitem::~mitem() {
}