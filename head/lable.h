/* 
 * File:   label.h
 * Author: SONY
 *
 * Created on 31 March 2013, 19:29
 */

#ifndef LABEL_H
#define	LABEL_H

#include "base.h"

namespace gui {
    class lable : public base{
    public:
        lable();
        lable(LPCSTR szText, base *parent);
        void Create(LPCSTR szText, base *parent);
        virtual ~lable();
    private:

    };
}



#endif	/* LABEL_H */

