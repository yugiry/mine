#pragma once
#include "tile.h"

Tile::Tile()
{
	//画像データをロードする
	turf_img = LoadGraph("image\\turf.png");
	tile_img[EMPTY] = LoadGraph("image\\empty.png");

	for (int i = 0; i < MAP_WIDTH * MAP_HEIGHT; i++)
	{
		map[i].num = 0;
		map[i].open = false;
		map[i].pos = { (i % MAP_WIDTH) * TILE_WIDTH,(i / MAP_WIDTH) * TILE_HEIGHT + TILE_HEIGHT * 3 / 2 };
	}
}

void Tile::DrawTile()
{
	for (int i = 0; i < MAP_WIDTH * MAP_HEIGHT; i++)
	{
		if (!map[i].open)
		{
			DrawGraph(map[i].pos.x, map[i].pos.y, turf_img, true);
		}
		else
		{

		}
	}
}

Tile::~Tile()
{

}