/*
 * TPlottable.h
 *
 *  Created on: Apr 2, 2013
 *      Author: nsoblath
 */

#ifndef TPLOTTABLE_H_
#define TPLOTTABLE_H_

#include "Rtypes.h"

#include <string>

namespace rootplotter
{

    class TPlottable
    {
        public:
            TPlottable();
            virtual ~TPlottable();

        public:
            const std::string& GetDrawOpts() const;
            void SetDrawOpts(const std::string& opts);

        private:
            std::string fDrawOpts;

        public:
            void Draw();
            void DrawSame();

        private:
            virtual void DoDraw(const std::string& opts) = 0;

            ClassDef(rootplotter::TPlottable, 1);
    };

    inline const std::string& TPlottable::GetDrawOpts() const
    {
        return fDrawOpts;
    }

    inline void TPlottable::SetDrawOpts(const std::string& opts)
    {
        fDrawOpts = opts;
        return;
    }

    inline void TPlottable::Draw()
    {
        DoDraw(fDrawOpts);
        return;
    }

    inline void TPlottable::DrawSame()
    {
        DoDraw(fDrawOpts + std::string("same"));
        return;
    }

}

class TH1;

namespace rootplotter
{

    class TPlottableTH1 : public TPlottable
    {
        public:
            TPlottableTH1();
            virtual ~TPlottableTH1();

            TH1* GetHistogram() const;
            void SetHistogram(TH1* hist);

        private:
            TH1* fHist;

        private:
            virtual void DoDraw(const std::string& opts);

            ClassDef(rootplotter::TPlottableTH1, 1);
    };

    inline TH1* TPlottableTH1::GetHistogram() const
    {
        return fHist;
    }

    inline void TPlottableTH1::SetHistogram(TH1* hist)
    {
        fHist = hist;
        return;
    }

}

#endif /* TPLOTTABLE_H_ */
