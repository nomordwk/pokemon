#ifndef POKEMON_H
#define POKEMON_H

#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<sstream>

using namespace std;

struct Moves {
    string movesName; //名字
    string movesType; //屬性
    char pS;          //PS
    int power;        //傷害
    int accuracy;     //準確性
    int pp;           //使用次數
    string con;       //附加效果
};

class GameState{
protected:
    int gameTurn; //遊戲回合
    //遊戲行動
    vector<string> gameCase;
public:
    GameState(){};
    ~GameState(){};

    void setGameCase(string gCase){this->gameCase.push_back(gCase);}
    void cleanCase(){this->gameCase.clear();}
    vector<string> showCase(){return this->gameCase;}
};

class Pokemon {
protected:
    //寶可夢名字
    string name;
    //寶可夢屬性
    vector<string> type;
    //寶可夢技能
    vector<Moves> moves;
    int hp;	 //最大生命
    int lastHp; //剩餘生命
    int atk; //攻擊
    int def; //防禦
    int spAtk; //特攻
    int spDef; //特防
    int speed; //速度

public:
    //啥都沒有等設置
    Pokemon(){};

    //讀取直接輸入
    Pokemon(string name, vector<string> type, int hp, int atk, int def, int spAtk, int spDef, int speed) {
        this->name = name;
        for (int i = 0; i < type.size(); i++) {
            this->type.push_back(type[i]);
        }
        this->hp = hp;
        this->atk = atk;
        this->def = def;
        this->spAtk = spAtk;
        this->spDef = spDef;
        this->speed = speed;
    }

    ~Pokemon(){};

    //各種基礎設置
    void setName(string name){this->name = name;}
    void setType(vector<string> type){
        for (int i = 0; i < type.size(); i++) {
            this->type.push_back(type[i]);
        }
    }
    void setHp(int hp){this->hp = hp;}
    void setAtk(int atk){this->atk = atk;}
    void setDef(int def){this->def = def;}
    void setSpAtk(int spAtk){this->spAtk = spAtk;}
    void setSpDef(int spDef){this->spDef = spDef;}
    void setSpeed(int speed){this->speed = speed;}

    //新增一個技能
    void setOneMoves(Moves move){this->moves.push_back(move);}
    //一次性新增技能
    void setMoves(vector<Moves> moves){
        for (int i = 0; i < moves.size(); i++) {
            this->moves.push_back(moves[i]);
        }
    }

    //顯示名字
    string showName(){return this->name;}

    //清空屬性
    void cleanType(){this->type.clear();}
};

class GameTeam {
protected:
    //寶可夢隊員
    vector<Pokemon> teamer;
public:
    GameTeam(){};
    ~GameTeam(){};

    //新增寶可夢隊員
    void setOneTeamer(Pokemon pokemon){this->teamer.push_back(pokemon);}

    //回傳寶可夢總隊員
    vector<Pokemon> showTeamer(){return this->teamer;}

    //清空寶可夢隊伍
    void cleaner(){this->teamer.clear();}
};

#endif // POKEMON_H
