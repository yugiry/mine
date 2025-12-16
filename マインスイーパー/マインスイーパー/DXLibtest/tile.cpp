#pragma once
#include "tile.h"
#include <random>

Tile::Tile()
{
	//画像データをロードする
	turf_img = LoadGraph("image\\turf.png");
	tile_img[EMPTY] = LoadGraph("image\\empty.png");
	tile_img[ONE] = LoadGraph("image\\one.png");
	tile_img[TWO] = LoadGraph("image\\two.png");
	tile_img[THREE] = LoadGraph("image\\three.png");
	tile_img[FOUR] = LoadGraph("image\\four.png");
	tile_img[FIVE] = LoadGraph("image\\five.png");
	tile_img[SIX] = LoadGraph("image\\six.png");
	tile_img[SEVEN] = LoadGraph("image\\seven.png");
	tile_img[FRAG] = LoadGraph("image\\frag.png");
	tile_img[MINE] = LoadGraph("image\\mine.png");

	//タイルの初期化
	for (int i = 0; i < MAP_WIDTH * MAP_HEIGHT; i++)
	{
		map[i].num = 0;
		map[i].open = false;
		map[i].flag = false;
		map[i].pos = { (i % MAP_WIDTH) * TILE_WIDTH,(i / MAP_WIDTH) * TILE_HEIGHT + TILE_HEIGHT * 3 / 2 };
	}

	click_time = 0;
}

void Tile::Action()
{
	//マウスカーソルの位置を取得
	GetMousePoint(&mouse.x, &mouse.y);

	if ((GetMouseInput() & MOUSE_INPUT_LEFT) && !clickflag[LEFT])
	{
		CheckClick(LEFT);
	}
	clickflag[LEFT] = (GetMouseInput() & MOUSE_INPUT_LEFT);

	if ((GetMouseInput() & MOUSE_INPUT_RIGHT) && !clickflag[RIGHT])
	{
		CheckClick(RIGHT);
	}
	clickflag[RIGHT] = (GetMouseInput() & MOUSE_INPUT_RIGHT);
}

void Tile::CheckClick(int _LR)
{
	//どのタイルがクリックされたか調べる
	for (int i = 0; i < MAP_WIDTH * MAP_HEIGHT; i++)
	{
		Point checker{ (i % MAP_WIDTH) * TILE_WIDTH ,(i / MAP_WIDTH) * TILE_HEIGHT + TILE_HEIGHT * 3 / 2 };
		if (checker.x < mouse.x && mouse.x < checker.x + TILE_WIDTH && checker.y < mouse.y && mouse.y < checker.y + TILE_HEIGHT)
		{
			if (!map[i].open && !map[i].flag)
			{
				if (_LR == LEFT)
				{
					map[i].open = true;
				}
				else if (_LR == RIGHT)
				{
					map[i].flag = true;
				}
			}
		}
	}
}

void Tile::SetMine(int _tilenum)
{
	for (int i = 0; i < BOMB_NUM; i++)
	{
		
	}
}

int Tile::GetRandNum(int min, int max)
{
	int num;
	do {
		num = GetRand(max + SUB_NUM);
	} while (num < min);
}

//タイルを表示する関数
void Tile::DrawTile()
{
	for (int i = 0; i < MAP_WIDTH * MAP_HEIGHT; i++)
	{
		if (!map[i].open)
		{
			DrawGraph(map[i].pos.x, map[i].pos.y, turf_img, true);
			if (map[i].flag)
			{
				DrawGraph(map[i].pos.x, map[i].pos.y, tile_img[FRAG], true);
			}
		}
		else
		{
			DrawGraph(map[i].pos.x, map[i].pos.y, tile_img[map[i].num], true);
		}

	}
}

Tile::~Tile()
{

}