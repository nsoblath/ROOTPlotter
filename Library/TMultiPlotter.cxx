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
#include "TStyle.h"

#include <iostream>

ClassImp(rootplotter::TMultiPlotter);

namespace rootplotter
{
    TMultiPlotter::TMultiPlotter(const std::string& canvasBaseName) :
            fPad(NULL),
            fOwnPad(true),
            fCanvasBaseName(canvasBaseName),
            fPlotArea(NULL),
            fPlottables()
    {
        std::string canvasName = GetNextCanvasName(fCanvasBaseName);
        fPad = new TCanvas(canvasName.c_str(), canvasName.c_str());
        std::string histName = std::string("hPlotArea") + canvasName;
        fPlotArea = new TH1C(histName.c_str(), "Plot Area", 1, 0., 1.);
    }

    TMultiPlotter::TMultiPlotter(TPad* pad) :
            fPad(pad),
            fOwnPad(false),
            fCanvasBaseName("MPC"),
            fPlotArea(NULL),
            fPlottables()
    {
        pad->cd();
        std::string histName = std::string("hPlotArea") + std::string(pad->GetName());
        fPlotArea = new TH1C(histName.c_str(), "Plot Area", 1, 0., 1.);
    }

    TMultiPlotter::~TMultiPlotter()
    {
        delete fPlotArea;
        if (fOwnPad) delete fPad;
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
        gStyle->SetOptStat(0);

        std::list< TPlottable* >::iterator it = fPlottables.begin();
        (*it)->Draw();
        fPad->Update();
        Double_t xMin = fPad->GetUxmin();
        Double_t xMax = fPad->GetUxmax();
        Double_t yMin = fPad->GetUymin();
        Double_t yMax = fPad->GetUymax();
        //std::cout << "drawn first hist" << std::endl;
        //std::cout << xMin << "  " << xMax << "  " << yMin << "  " << yMax << std::endl;

        for (it++; it != fPlottables.end(); it++)
        {
            (*it)->Draw();
            fPad->Update();
            xMin = TMath::Min(xMin, fPad->GetUxmin());
            xMax = TMath::Max(xMax, fPad->GetUxmax());
            yMin = TMath::Min(yMin, fPad->GetUymin());
            yMax = TMath::Max(yMax, fPad->GetUymax());
            //std::cout << "drawn next hist" << std::endl;
            //std::cout << xMin << "  " << xMax << "  " << yMin << "  " << yMax << std::endl;
        }

        fPlotArea->GetXaxis()->SetLimits(xMin, xMax);
        fPlotArea->GetYaxis()->SetRangeUser(yMin, yMax);
        fPlotArea->Draw();

        DrawSame();
        return;
    }

    void TMultiPlotter::DrawSame()
    {
        for (std::list< TPlottable* >::iterator it = fPlottables.begin(); it != fPlottables.end(); it++)
        {
            (*it)->DrawSame();
        }
        return;
    }

    void TMultiPlotter::SetPad(TPad* pad)
    {
        if (fOwnPad) delete pad;
        fPad = pad;
        fOwnPad = false;
        return;
    }



} // end namespace rootplotter
