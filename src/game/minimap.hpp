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

#ifndef MINIMAP_HPP
#define MINIMAP_HPP

#include <map>
#include <vector>

#include <MCVector3d>

class MapBase;
class MCSurface;
class TrackTile;

class MiniMap
{
public:

    MiniMap();

    explicit MiniMap(const MapBase & trackMap, int x, int y, int size);

    void initialize(const MapBase & trackMap, int x, int y, int size);

    void render();

private:

    struct MinimapTile
    {
        MCVector3dF pos;

        int rotation;
    };

    std::map<MCSurface *, std::vector<MinimapTile> > m_map;

    float m_tileW = 0;

    float m_tileH = 0;
};

#endif // MINIMAP_HPP
