/* 
 * File:   menu.cpp
 * Author: SONY
 * 
 * Created on 02 April 2013, 00:20
 */

#include "menu.h"

using namespace gui;

menu::menu(bool popup) {
    
    memset(&m_info, 0, sizeof(MENUINFO));
    m_info.cbSize = sizeof(MENUINFO);
    m_info.fMask = MIM_BACKGROUND | MIM_HELPID | MIM_MAXHEIGHT | MIM_MENUDATA | MIM_STYLE;

    if(popup)
        handle = CreatePopupMenu();
    else
        handle = CreateMenu();

    GetMenuInfo(handle, &m_info);

    m_info.dwStyle = MNS_NOTIFYBYPOS;
    m_info.dwMenuData = (ULONG_PTR)this;

    SetMenuInfo(handle, &m_info);
}

menu *menu::getByHandle(HMENU hMenu) {
    
    MENUINFO info;
    info.cbSize = sizeof(MENUINFO);
    info.fMask = MIM_MENUDATA;
    GetMenuInfo(hMenu, &info);

    return (menu *)info.dwMenuData;
}

mitem *menu::getItemByIndex(int index)
{
    MENUITEMINFO mi_info;
    
    mi_info.cbSize = sizeof(MENUITEMINFO);
    mi_info.fMask = MIIM_DATA;
    GetMenuItemInfo(handle, index, true, &mi_info );

    return (mitem *)mi_info.dwItemData;
}

HMENU menu::getHandle() {
    return handle;
}

void menu::addItem(mitem *item) {
    item->setPosition(InsertMenuItem(handle, (UINT)item, false, &item->mi_info));
    item->setParent(this);
}

menu::~menu() {
    ::DestroyMenu(handle);
}

