/*
 * HelperFunctions.cxx
 *
 *  Created on: Apr 1, 2013
 *      Author: nsoblath
 */

#include "HelperFunctions.h"

#include "TROOT.h"
#include "TSeqCollection.h"

#include <sstream>




std::string GetNextCanvasName(const std::string& baseName)
{
    std::string name;

    TSeqCollection* listOfCanvases = gROOT->GetListOfCanvases();
    TObject* foundCanvas = NULL;
    UInt_t iCanvas = 1;
    while (foundCanvas == NULL)
    {
        std::stringstream conv;
        conv << iCanvas;
        name = baseName + conv.str();
        foundCanvas = listOfCanvases->FindObject(name.c_str());
    }

    return name;
}


