/* 
 * File:   font.cpp
 * Author: SONY
 * 
 * Created on 01 April 2013, 06:25
 */

#include "font.h"

using namespace gui;

font::font(LPCSTR typeface, USHORT size, FontStyle style) {
    
    if(typeface != 0)
        this->typeface = (LPSTR)typeface;
    
    LOGFONT lf;
    GetObject(GetStockObject(DEFAULT_GUI_FONT), sizeof(LOGFONT), &lf);
    hfont = CreateFont(size, lf.lfWidth, lf.lfEscapement, lf.lfOrientation,
            ((style & Bold) > 0) ? FW_BOLD : FW_NORMAL,
            ((style & Italic) > 0) ? true : false, 
            ((style & Underline) > 0) ? true : false, 
            ((style & Strikeout) > 0) ? true : false, 
            lf.lfCharSet,
            lf.lfOutPrecision, 
            lf.lfClipPrecision, 
            lf.lfQuality,
            lf.lfPitchAndFamily,
            (typeface != 0 ? typeface : lf.lfFaceName));
}

font *font::getDefault(){
    static font *dfont = new font();
    return dfont;
}

LPCSTR font::getTypeFace() {
    return typeface;
}

USHORT font::getSize() {
    return size;
}

HFONT font::getHandle() {
    return hfont;
}

font::~font() {
    free(typeface);
    DeleteObject(hfont);
}

