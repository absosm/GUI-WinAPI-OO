/* 
 * File:   base.h
 * Author: SONY
 *
 * Created on 29 March 2013, 09:07
 */

#ifndef BASE_H
#define	BASE_H

#include <windows.h>
#include <vector>
#include "constant.h"
#include "font.h"

typedef struct tagPos {
    LONG x;
    LONG y;
}POSITION;

typedef struct tagSize{
    LONG width;
    LONG height;
}Size;

namespace gui {
    
    class base {
    public:
        base();
        virtual void Show();
        virtual void Hide();
        virtual void Close();
        virtual void setEnabled(bool enabled);
        virtual bool getEnabled();
        virtual void setPosition(LONG x, LONG y);
        virtual void setPosition(POSITION pos);
        virtual void setSize(LONG width, LONG height);
        virtual Size getSize();
        virtual HWND getHandle();
        virtual void Destroy();
        virtual void Redraw();
        virtual void setParent(base *parent);
        virtual base *getParent();
        virtual void addChild(base *child);
        virtual void RemoveChild(base *child);
        virtual POSITION getPosition();
        virtual void setStyle(DWORD style);
        virtual DWORD getStyle();
        virtual void addStyle(DWORD style);
        virtual void setExtendedStyle(DWORD style);
        virtual DWORD getExtendedStyle();
        virtual void RemoveStyle(DWORD style);
        virtual void setText(LPCSTR szText);
        virtual LPCSTR getText();
        virtual void setFont(font *Font);
        virtual void setColor(BYTE r, BYTE g, BYTE b);
        virtual void setBackgroundColor(BYTE r, BYTE g, BYTE b);
        virtual int Loop();
        virtual ~base();

        virtual bool onClose();
        virtual bool onCreate();
        virtual bool onMouseMove(POINTS point);
        virtual bool onMouseDown(POINTS point, MouseButton button);
        virtual bool onMouseUp(POINTS point, MouseButton button);
        virtual bool onMouseClick(POINTS point, MouseButton button);
        virtual bool onMouseDoubleClick(POINTS point);
        virtual bool onKeyDown(WCHAR key);
        virtual bool onKeyUp(WCHAR key);
        virtual bool onActivate();
        virtual bool onTextChanged(LPCSTR szText);
    protected:
        void InitializeBase();
        static LRESULT WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
        
        base *parent;
        std::vector<base*> children;
        HWND handle;
        LONG_PTR defaultProcess;
        font *Font;
        COLORREF color;
        HBRUSH background;
    private:
        POSITION position;
        Size size;
    };
}

#endif	/* BASE_H */

