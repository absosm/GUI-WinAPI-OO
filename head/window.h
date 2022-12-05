/* 
 * File:   window.h
 * Author: SONY
 *
 * Created on 29 March 2013, 09:18
 */

#ifndef WINDOW_H
#define	WINDOW_H

#include "base.h"
#include "menu.h"

namespace gui {
    class window : public base {
    public:
        window();
        void Create(LPCSTR szTitle);
        void setTitle(LPCSTR szTitle);
        LPCSTR getTitle();
        void Maximize();
        void Minimize();
        void Restore();
        void ShowMessage(LPCSTR sMsg);
        void setMenu(menu *Menu);
        void setIcon(DWORD ID);
        void setBackgroundColor(BYTE r, BYTE g, BYTE b);
        virtual void InitializeComponent();
        virtual ~window();
    private:
        static void RegisterWindowClass();
        HMENU *hMenu;
    };
}



#endif	/* WINDOW_H */

