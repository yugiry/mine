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
	enum CHECKTILE
	{
		UPLEFT = -(MAP_WIDTH + 1),
		UPMIDDLE = -MAP_WIDTH,
		UPRIGHT = -(MAP_WIDTH - 1),
		MIDDLELEFT = -1,
		MIDDLERIGHT = 1,
		DOWNLEFT = MAP_WIDTH - 1,
		DOWNMIDDLE = MAP_WIDTH,
		DOWNRIGHT = MAP_WIDTH + 1
	};
	int turf_img{ -1 };
	int tile_img[TILES_END]{ -1 };
	int click_time{ -1 };
	bool clickflag_left{ false };
	bool clickflag[CLICKFLAG_END]{ false };
	bool setmineflag{ false };
	bool resetflag{ false };
	Point mouse;
	Map map[TILE_WIDTH * TILE_HEIGHT];
public:
	Tile();
	~Tile();
	void Action();
	void ResetTile();
	void CheckClick(int);
	void SetMine(int);
	int GetRandNum(int, int);
	void AddTileNum(int, int);
	void OpenChainTiles(int);
	void OpenTile(int, int);
	bool CheckClickBox(int, int);
	void DrawTile();
};