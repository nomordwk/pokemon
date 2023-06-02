#pragma once
#ifndef ALLHEADER_H
#define ALLHEADER_H
#include"Pokemon.h"
#include "mainwindow.h"
#include "./ui_mainwindow.h"

vector<Pokemon> allPokemon; //儲存所有輸入的寶可夢
vector<Moves> movesOfAll; //儲存所有輸入的招式
//分成兩個隊伍
GameTeam team1;
GameTeam team2;
//儲存遊戲回合 case
GameState ourPokemon;
//儲存檔案名稱
vector<string> fileName;

int loadTextCase(string inputFile);
int loadPokemon(string inputFile);
int loadMoves(string inputFile);
int loadGameData(string inputFile);

using namespace std;

#endif // ALLHEADER_H
