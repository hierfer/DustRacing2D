// This file is part of Dust Racing (DustRAC).
// Copyright (C) 2011 Jussi Lind <jussi.lind@iki.fi>
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

#include "track.hpp"
#include "trackdata.hpp"
#include "tracktile.hpp"
#include "map.hpp"

#include "MiniCore/Core/MCCamera"
#include "MiniCore/Core/MCSurface"

#include <cassert>

Track::Track(TrackData * pTrackData)
: m_pTrackData(pTrackData)
, m_rows(m_pTrackData->map().rows())
, m_cols(m_pTrackData->map().cols())
, m_width(m_cols * TrackTile::TILE_W)
, m_height(m_rows * TrackTile::TILE_H)
, m_scale(0.0)
{
    assert(pTrackData);
}

MCUint Track::width() const
{
    return m_width;
}

MCUint Track::height() const
{
    return m_height;
}

const TrackData & Track::trackData() const
{
    return *m_pTrackData;
}

TrackTile * Track::trackTileAtLocation(MCUint x, MCUint y) const
{
    // X index
    MCUint i = x * m_cols / m_width;
    i = i >= m_cols ? m_cols - 1 : i;

    // Y index
    MCUint j = y * m_rows / m_height;
    j = j >= m_rows ? m_rows - 1 : j;

    return static_cast<TrackTile *>(m_pTrackData->map().getTile(i, j));
}

void Track::calculateVisibleIndices(const MCBBox<int> & r,
    MCUint & i0, MCUint & i2, MCUint & j0, MCUint & j2)

{
    // Calculate which tiles are visible in the Camera window:
    // columns from i0 to i2 and rows from j0 to j2.

    // X low index
    i0 = r.x1() * m_cols / m_width;
    i0 = i0 >= m_cols ? 0 : i0;

    // X high index
    i2 = r.x2() * m_cols / m_width;
    i2 = i2  >= m_cols ? m_cols - 1 : i2;

    // Y low index
    j0 = r.y1() * m_rows / m_height;
    j0 = j0 >= m_rows ? 0 : j0;

    // Y high index
    j2 = r.y2() * m_rows / m_height;
    j2 = j2  >= m_rows ? m_rows - 1 : j2;
}

void Track::render(MCCamera * pCamera)
{
    const MapBase & rMap = m_pTrackData->map();

    // Get the Camera window
    MCBBox<MCFloat> cameraBox(pCamera->bbox());

    // Calculate which tiles are visible
    MCUint i2, j2, i0, j0;
    calculateVisibleIndices(cameraBox, i0, i2, j0, j2);

    static const int w  = TrackTile::TILE_W;
    static const int h  = TrackTile::TILE_H;

    // Loop through the visible tile matrix and draw the tiles
    int initX = i0 * w;
    int x     = initX;
    int y     = j0 * h;
    for (MCUint j = j0; j <= j2; j++)
    {
        x = initX;
        for (MCUint i = i0; i <= i2; i++)
        {
            if (TrackTile * pTile = static_cast<TrackTile *>(rMap.getTile(i, j)))
            {
                if (MCSurface * pSurface = pTile->surface())
                {
                    pSurface->renderScaled(
                        pCamera,
                        MCVector3dF(x + w / 2, y + h / 2, 0), m_scale * w / 2, m_scale * h / 2,
                        pTile->rotation());
                }
            }

            x += w;
        }

        y += h;
    }
}

bool Track::update()
{
    if (m_scale < 1.0)
    {
        m_scale += 0.05f;
        return true;
    }
    else
    {
        // This helps to remove some glitches in tile boundaries.
        m_scale = 1.001f;
        return false;
    }
}

void Track::reset()
{
    m_scale = 0.0;
}

Track::~Track()
{
    delete m_pTrackData;
}
