// This file is part of Dust Racing 2D.
// Copyright (C) 2017 Jussi Lind <jussi.lind@iki.fi>
//
// Dust Racing 2D is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// Dust Racing 2D is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Dust Racing 2D. If not, see <http://www.gnu.org/licenses/>.

#include "minimap.hpp"

#include "renderer.hpp"
#include "tracktile.hpp"

#include <MCSurface>

#include "../common/mapbase.hpp"

MiniMap::MiniMap()
{
}

MiniMap::MiniMap(const MapBase & trackMap, int x, int y, int size)
{
    initialize(trackMap, x, y, size);
}

void MiniMap::initialize(const MapBase & trackMap, int x, int y, int size)
{
    // Set m_tileW and m_tileH so that they are squares
    m_tileW = size / trackMap.cols();
    m_tileH = size / trackMap.rows();

    if (m_tileW > m_tileH)
    {
        m_tileW = m_tileH;
    }
    else
    {
        m_tileH = m_tileW;
    }

    float initX, initY;

    // Center the map
    if (trackMap.cols() % 2 == 0)
    {
        initX = x - trackMap.cols() * m_tileW / 2 + m_tileW / 4;
    }
    else
    {
        initX = x - trackMap.cols() * m_tileW / 2;
    }

    initY = y - trackMap.rows() * m_tileH / 2;

    m_map.clear();

    // Loop through the visible tile matrix and store relevant tiles
    float tileX, tileY;
    tileY = initY;
    for (auto j = 0; j < trackMap.rows(); j++)
    {
        tileX = initX;
        for (auto i = 0; i < trackMap.cols(); i++)
        {
            TrackTile * tile = static_cast<TrackTile *>(trackMap.getTile(i, j).get());
            if (MCSurface * surface = tile->previewSurface())
            {
                surface->setShaderProgram(Renderer::instance().program("menu"));
                surface->setColor(MCGLColor(1.0, 1.0, 1.0));
                surface->setSize(m_tileH, m_tileW);

                MinimapTile minimapTile;
                minimapTile.pos = MCVector3dF(tileX + m_tileW / 2, tileY + m_tileH / 2);
                minimapTile.rotation = tile->rotation();

                m_map[surface].push_back(minimapTile);
            }

            tileX += m_tileW;
        }

        tileY += m_tileH;
    }
}

void MiniMap::render()
{
    for (auto && i : m_map)
    {
        MCSurface * surface = i.first;
        surface->setShaderProgram(Renderer::instance().program("menu"));
        surface->bindMaterial();
        surface->setColor(MCGLColor(1.0, 1.0, 1.0));
        surface->setSize(m_tileH, m_tileW);

        for (auto && j : i.second)
        {
            const MinimapTile minimapTile = j;
            surface->render(nullptr, minimapTile.pos, minimapTile.rotation);
        }
    }
}
