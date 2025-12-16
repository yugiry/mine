#pragma once
#include "function.h"

class Tile
{
private:
	enum TILES
	{
		EMPTY,
		ONE,
		TWE,
		THREE,
		FOUR,
		FIVE,
		SIX,
		SEVEN,
		FLAG,
		MINE,
		TILES_END
	};
	int turf_img{ -1 };
	int tile_img[TILES_END]{ -1 };
	Map map[TILE_WIDTH * TILE_HEIGHT];
public:
	Tile();
	~Tile();
	void DrawTile();
};