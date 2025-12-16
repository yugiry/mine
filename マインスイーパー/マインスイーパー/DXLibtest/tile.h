#pragma once
#include "function.h"

class Tile
{
private:
	enum TILES
	{
		EMPTY,
		ONE,
		TWO,
		THREE,
		FOUR,
		FIVE,
		SIX,
		SEVEN,
		MINE,
		FRAG,
		TILES_END
	};
	enum CLICKFLAG
	{
		LEFT,
		RIGHT,
		CLICKFLAG_END
	};
	int turf_img{ -1 };
	int tile_img[TILES_END]{ -1 };
	int click_time{ -1 };
	bool clickflag_left{ false };
	bool clickflag[CLICKFLAG_END]{ false };
	Point mouse;
	Map map[TILE_WIDTH * TILE_HEIGHT];
public:
	Tile();
	~Tile();
	void Action();
	void CheckClick(int);
	void SetMine(int);
	int GetRandNum(int, int);
	void DrawTile();
};