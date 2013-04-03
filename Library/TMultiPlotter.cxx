/*
 * TMultiPlotter.cxx
 *
 *  Created on: Apr 1, 2013
 *      Author: nsoblath
 */

#include "TMultiPlotter.h"

#include "HelperFunctions.h"

#include "TCanvas.h"
#include "TPad.h"
#include "TROOT.h"

#include <iostream>

ClassImp(rootplotter::TMultiPlotter);

namespace rootplotter
{
    TMultiPlotter::TMultiPlotter(const std::string& canvasBaseName) :
            fPad(NULL),
            fCanvasBaseName(canvasBaseName),
            fPlotArea("hPlotArea", "Plot Area", 1, 0., 1.),
            fPlottables()
    {
        std::string canvasName = GetNextCanvasName(fCanvasBaseName);
        fPad = new TCanvas(canvasName.c_str(), canvasName.c_str());
    }

    TMultiPlotter::TMultiPlotter(TPad* pad) :
            fPad(pad),
            fCanvasBaseName("MPC"),
            fPlotArea("hPlotArea", "Plot Area", 1, 0., 1.),
            fPlottables()
    {
    }

    TMultiPlotter::~TMultiPlotter()
    {
    }

    Bool_t TMultiPlotter::AddPlottableTH1(TH1* toPlot)
    {
        TPlottableTH1* newPlottable = new TPlottableTH1();
        newPlottable->SetHistogram(toPlot);
        fPlottables.push_back(newPlottable);
        return true;
    }

    void TMultiPlotter::Draw()
    {
        fPad->cd();

        std::list< TPlottable* >::iterator it = fPlottables.begin();
        (*it)->Draw();
        fPad->Update();
        Double_t xMin = fPad->GetUxmin();
        Double_t xMax = fPad->GetUxmax();
        Double_t yMin = fPad->GetUymin();
        Double_t yMax = fPad->GetUymax();
        std::cout << "drawn first hist" << std::endl;
        std::cout << xMin << "  " << xMax << "  " << yMin << "  " << yMax << std::endl;

        for (it++; it != fPlottables.end(); it++)
        {
            (*it)->Draw();
            fPad->Update();
            xMin = TMath::Min(xMin, fPad->GetUxmin());
            xMax = TMath::Max(xMax, fPad->GetUxmax());
            yMin = TMath::Min(yMin, fPad->GetUymin());
            yMax = TMath::Max(yMax, fPad->GetUymax());
            std::cout << "drawn next hist" << std::endl;
            std::cout << xMin << "  " << xMax << "  " << yMin << "  " << yMax << std::endl;
        }

        fPlotArea.GetXaxis()->SetLimits(xMin, xMax);
        fPlotArea.GetYaxis()->SetRangeUser(yMin, yMax);
        fPlotArea.Draw();

        for (it = fPlottables.begin(); it != fPlottables.end(); it++)
        {
            (*it)->DrawSame();
        }
        return;
    }

} // end namespace rootplotter
