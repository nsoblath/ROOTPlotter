/*
 * TMultiPlotter.h
 *
 *  Created on: Apr 1, 2013
 *      Author: nsoblath
 */

#ifndef TMULTIPLOTTER_H_
#define TMULTIPLOTTER_H_

#ifndef ROOT_Rtypes
#include "Rtypes.h"
#endif

#include <string>

class TPad;

class TMultiPlotter
{
    public:
        TMultiPlotter(const std::string& canvasBaseName = "MPC");
        TMultiPlotter(TPad* pad);
        virtual ~TMultiPlotter();

    public:
        TPad* GetPad() const;
        void SetPad(TPad* canvas);

        const std::string& GetCanvasBaseName() const;
        void SetCanvasBaseName(const std::string& name);

    private:
        TPad* fPad;

        std::string fCanvasBaseName;
};

inline TPad* TMultiPlotter::GetPad() const
{
    return fPad;
}

inline void TMultiPlotter::SetPad(TPad* pad)
{
    fPad = pad;
    return;
}

inline const std::string& TMultiPlotter::GetCanvasBaseName() const
{
    return fCanvasBaseName;
}

inline void TMultiPlotter::SetCanvasBaseName(const std::string& name)
{
    fCanvasBaseName = name;
    return;
}

#endif /* TMULTIPLOTTER_H_ */
