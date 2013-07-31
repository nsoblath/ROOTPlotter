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
            Bool_t fOwnPad;

            std::string fCanvasBaseName;

            TH1C* fPlotArea;

        public:
            //template< class XToPlot >
            //Bool_t AddPlottable(XToPlot* toPlot);
            Bool_t AddPlottableTH1(TH1* toPlot);

            void SetTitle(const std::string& title);
            void SetXTitle(const std::string& title);
            void SetYTitle(const std::string& title);
            void SetZTitle(const std::string& title);

            void SetXDrawRange(Double_t xMin, Double_t xMax);
            void UnsetXDrawRange();

            void SetYDrawRange(Double_t yMin, Double_t yMax);
            void UnsetYDrawRange();

            void Draw();
            void DrawSame();

        private:
            std::list< TPlottable* > fPlottables;

            Bool_t fUseXRange;
            Double_t fXMin, fXMax;

            Bool_t fUseYRange;
            Double_t fYMin, fYMax;

            ClassDef(rootplotter::TMultiPlotter, 1);
    };

    inline TPad* TMultiPlotter::GetPad() const
    {
        return fPad;
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

    inline void TMultiPlotter::SetTitle(const std::string& title)
    {
        fPlotArea->SetTitle(title.c_str());
        return;
    }

    inline void TMultiPlotter::SetXTitle(const std::string& title)
    {
        fPlotArea->SetXTitle(title.c_str());
        return;
    }

    inline void TMultiPlotter::SetYTitle(const std::string& title)
    {
        fPlotArea->SetYTitle(title.c_str());
        return;
    }

    inline void TMultiPlotter::SetZTitle(const std::string& title)
    {
        fPlotArea->SetZTitle(title.c_str());
        return;
    }

    inline void TMultiPlotter::SetXDrawRange(Double_t xMin, Double_t xMax)
    {
        fXMin = xMin;
        fXMax = xMax;
        fUseXRange = true;
        return;
    }

    inline void TMultiPlotter::UnsetXDrawRange()
    {
        fUseXRange = false;
        return;
    }

    inline void TMultiPlotter::SetYDrawRange(Double_t yMin, Double_t yMax)
    {
        fYMin = yMin;
        fYMax = yMax;
        fUseYRange = true;
        return;
    }

    inline void TMultiPlotter::UnsetYDrawRange()
    {
        fUseYRange = false;
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
