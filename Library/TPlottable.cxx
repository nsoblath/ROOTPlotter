/*
 * TPlottable.cxx
 *
 *  Created on: Apr 2, 2013
 *      Author: nsoblath
 */

#include "TPlottable.h"

//#include "TIFactory.h"

#include "TH1.h"

ClassImp(rootplotter::TPlottable);

namespace rootplotter
{

    TPlottable::TPlottable()
    {
    }

    TPlottable::~TPlottable()
    {
    }

}

ClassImp(rootplotter::TPlottableTH1);

namespace rootplotter
{
    //static DerivedTIRegistrar< TPlottable, TPlottableTH1 > sPlottableTH1Registrar;

    TPlottableTH1::TPlottableTH1() :
            TPlottable(),
            fHist(NULL)
    {
    }

    TPlottableTH1::~TPlottableTH1()
    {
    }

    void TPlottableTH1::DoDraw(const std::string& opts)
    {
        fHist->Draw(opts.c_str());
    }

}
