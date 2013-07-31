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
            fPlottables(),
            fUseXRange(false), fXMin(0.), fXMax(0.),
            fUseYRange(false), fYMin(0.), fYMax(0.)
    {
        std::string canvasName = GetNextCanvasName(fCanvasBaseName);
        fPad = new TCanvas(canvasName.c_str(), canvasName.c_str());
        std::string histName = std::string("hPlotArea") + canvasName;
        fPlotArea = new TH1C(histName.c_str(), "Plot Area", 1, 0., 1.);
        fPlotArea->SetBit(kCanDelete);
        fPlotArea->SetBinContent(1, 1);
    }

    TMultiPlotter::TMultiPlotter(TPad* pad) :
            fPad(pad),
            fOwnPad(false),
            fCanvasBaseName("MPC"),
            fPlotArea(NULL),
            fPlottables(),
            fUseXRange(false), fXMin(0.), fXMax(0.),
            fUseYRange(false), fYMin(0.), fYMax(0.)
    {
        pad->cd();
        std::string histName = std::string("hPlotArea") + std::string(pad->GetName());
        fPlotArea = new TH1C(histName.c_str(), "Plot Area", 1, 0., 1.);
        fPlotArea->SetBit(kCanDelete);
        fPlotArea->SetBinContent(1, 1);
    }

    TMultiPlotter::~TMultiPlotter()
    {
        if (fOwnPad) delete fPad;
        //delete fPlotArea;
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
        if (! fUseXRange)
        {
            fXMin = fPad->GetUxmin();
            fXMax = fPad->GetUxmax();
        }
        if (! fUseYRange)
        {
            fYMin = fPad->GetUymin();
            fYMax = fPad->GetUymax();
        }
        //std::cout << "drawn first hist" << std::endl;
        //std::cout << fXMin << "  " << fXMax << "  " << fYMin << "  " << fYMax << std::endl;

        for (it++; it != fPlottables.end(); it++)
        {
            (*it)->Draw();
            fPad->Update();
            if (! fUseXRange)
            {
                fXMin = TMath::Min(fXMin, fPad->GetUxmin());
                fXMax = TMath::Max(fXMax, fPad->GetUxmax());
            }
            if (! fUseYRange)
            {
                fYMin = TMath::Min(fYMin, fPad->GetUymin());
                fYMax = TMath::Max(fYMax, fPad->GetUymax());
            }
            //std::cout << "drawn next hist" << std::endl;
            //std::cout << xMin << "  " << xMax << "  " << yMin << "  " << yMax << std::endl;
        }

        fPlotArea->GetXaxis()->SetLimits(fXMin, fXMax);
        fPlotArea->GetYaxis()->SetRangeUser(fYMin, fYMax);
        fPlotArea->Draw("axis");

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
        if (fOwnPad)
        {
            fPad->GetListOfPrimitives()->Remove(fPlotArea);
            delete fPad;
        }
        fPad = pad;
        fOwnPad = false;
        return;
    }



} // end namespace rootplotter
