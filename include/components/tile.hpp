#pragma once

enum class TileLayer : int {
    Background = 0,
    Floor = 1,
    HalfFull = 2
};

struct Tile {
    TileLayer layer;
};
