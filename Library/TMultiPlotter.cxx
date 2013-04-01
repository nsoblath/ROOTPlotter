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

TMultiPlotter::TMultiPlotter(const std::string& canvasBaseName) :
        fPad(NULL),
        fCanvasBaseName(canvasBaseName)
{
    std::string canvasName = GetNextCanvasName(fCanvasBaseName);
    fPad = new TCanvas(fCanvasBaseName.c_str(), fCanvasBaseName.c_str());
}

TMultiPlotter::TMultiPlotter(TPad* pad) :
        fPad(pad),
        fCanvasBaseName("MPC")
{
}

TMultiPlotter::~TMultiPlotter()
{
}

