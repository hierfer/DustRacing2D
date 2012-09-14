// This file is part of Dust Racing (DustRAC).
// Copyright (C) 2012 Jussi Lind <jussi.lind@iki.fi>
//
// DustRAC is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// DustRAC is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with DustRAC. If not, see <http://www.gnu.org/licenses/>.

#ifndef TIMINGOVERLAY_HPP
#define TIMINGOVERLAY_HPP

#include "overlaybase.hpp"
#include <vector>
#include <string>

#include <MCTextureText>

class Car;
class MCTextureFontManager;
class MCTextureFont;
class Race;
class Timing;

//! Renders timeing information on top of the game scene.
class TimingOverlay : public OverlayBase
{
public:

    //! Constructor.
    TimingOverlay();

    //! \reimp
    virtual void render();

    //! \reimp
    virtual bool update();

    //! Show timing for the given car.
    void setCarToFollow(const Car & car);

    //! Set the timing data.
    void setTiming(Timing & timing);

    //! Set current race.
    void setRace(Race & race);

private:

    MCTextureFontManager   & m_fontManager;
    MCTextureFont          & m_font;
    MCTextureText            m_text;
    const Car              * m_pCar;
    Timing                 * m_pTiming;
    Race                   * m_pRace;
    std::vector<std::string> m_posTexts;
    bool                     m_showRecordTime;
};

#endif // TIMINGOVERLAY_HPP
