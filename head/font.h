/* 
 * File:   font.h
 * Author: SONY
 *
 * Created on 01 April 2013, 06:25
 */

#ifndef FONT_H
#define	FONT_H

#include <windows.h>

namespace gui {
    
    typedef enum{
        None = 0,
        Bold = 1,
        Underline = 2,
        Italic = 4,
        Strikeout = 8
    } FontStyle;
    
    class font {
    public:
        font(LPCSTR typeface = 0, USHORT size = 14, FontStyle style = None);
        static font *getDefault();
        USHORT getSize();
        LPCSTR getTypeFace();
        HFONT getHandle();
        virtual ~font();
    private:
        HFONT hfont;
        LPSTR typeface;
        USHORT size;
    };
}

#endif	/* FONT_H */

