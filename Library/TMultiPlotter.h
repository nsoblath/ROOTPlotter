/*
 * TMultiPlotter.h
 *
 *  Created on: Apr 1, 2013
 *      Author: nsoblath
 */

#ifndef TMULTIPLOTTER_H_
#define TMULTIPLOTTER_H_

//#include "TIFactory.h"

#include "TPlottable.h"

#include "TH1.h"

#include <list>
#include <string>

class TPad;

namespace rootplotter
{
    class TPlottable;

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

            TH1C fPlotArea;

        public:
            //template< class XToPlot >
            //Bool_t AddPlottable(XToPlot* toPlot);
            Bool_t AddPlottableTH1(TH1* toPlot);

            void Draw();

        private:
            std::list< TPlottable* > fPlottables;

            ClassDef(rootplotter::TMultiPlotter, 1);
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

    /*
    template< class XToPlot >
    Bool_t TMultiPlotter::AddPlottable(XToPlot* toPlot)
    {
        TIFactory< TPlottable >* plottableFactory = TIFactory< TPlottable >::GetInstance();



        //TPlottable* newPlottable = new TDerivedPlottable< XToPlot >(plottable);
        return true;
    }
    */

} // end namespace rootplotter

#endif /* TMULTIPLOTTER_H_ */
