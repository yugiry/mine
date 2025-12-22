#pragma once
#include "DxLib.h"
#include <vector>

#pragma region 定数
//画面サイズ
constexpr auto WINDOW_WIDTH = 480;
constexpr auto WINDOW_HEIGHT = 434;
//マップ
constexpr auto MAP_WIDTH = 15;
constexpr auto MAP_HEIGHT = 12;
//タイル
constexpr auto TILE_WIDTH = 32;
constexpr auto TILE_HEIGHT = 32;
//爆弾の数
constexpr auto MINE_NUM = 30;
//計算用の定数
constexpr auto SUB_RANDMAXNUM = -1;

#pragma endregion

#pragma region 構造体
typedef struct Point
{
	int x;
	int y;
};
typedef struct Map
{
	Point pos;
	int num;
	bool open;
	bool flag;
};

#pragma endregion