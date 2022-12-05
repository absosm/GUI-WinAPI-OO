/* 
 * File:   menu.h
 * Author: SONY
 *
 * Created on 02 April 2013, 00:20
 */

#ifndef MENU_H
#define	MENU_H

#include "base.h"
#include <windows.h>

namespace gui {
    
    class mitem;

    class menu {
    friend mitem;
    public:
        menu(bool popup);
        static menu *getByHandle(HMENU hMenu);
        mitem *getItemByIndex(int index);
        HMENU getHandle();
        void addItem(mitem *item);
        virtual ~menu();
    private:
        HMENU handle;
        MENUINFO m_info;

    };
    
    class mitem {
    friend menu;
    public:
        mitem();
        mitem(LPCSTR text);
        void InitializeInfo();
        void setPosition(int Pos);
        int getPosition();
        void setParent(menu *parent);
        menu *getParent();
        void setMenu(menu *menu);
        void setText(LPCSTR text);
        void setIcon(DWORD ID);
        void UpdateInfo();
        virtual void onMouseClick();
        virtual ~mitem();
    private:
        int position;
    protected:
        menu *parent;
        MENUITEMINFO mi_info;
    };
}

#endif	/* MENU_H */

