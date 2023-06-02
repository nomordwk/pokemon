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


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}


//讀取case
int loadTextCase(string inputFile){
    ifstream input;
    input.open(inputFile);

    //開啟失敗回傳0
    if(!input.is_open()){
        return 0;
    }

    if(fileName.size()!=0){
        fileName.clear();
        ourPokemon.cleanCase();
    }

    string inputLine; //每行
    int count = 0;    //計算行數
    int countOpen = 1;//檢查開啟狀態

    //迴圈獲取每一行
    while(getline(input,inputLine)){
        //如果在三行內
        if(count < 3){
            //檢查行數 依據行數跑不同函式
            switch(count){
            case 0:
                if(loadPokemon(inputLine) == 1){ //非1代表錯誤
                    countOpen += 1;
                    fileName.push_back(inputLine);
                }else{
                    return 1; //用數字判斷錯誤在哪
                }
                break;
            case 1:
                if(loadMoves(inputLine) == 1){  //非1代表錯誤
                    countOpen += 1;
                    fileName.push_back(inputLine);
                }else{
                    return 2; //用數字判斷錯誤在哪
                }
                break;
            case 2:
                if(loadGameData(inputLine) == 1){ //非1代表錯誤
                    countOpen += 1;
                    fileName.push_back(inputLine);
                }else{
                    return 3; //用數字判斷錯誤在哪
                }
                break;
            }
            count += 1; //行數增加
        }
        else{
            //剩下的都是遊戲指令 放入遊戲狀態case陣列等待呼叫
            ourPokemon.setGameCase(inputLine);
        }
    }
    //回傳總值(通常都是4)
    return countOpen;
}

//讀取寶可夢文件
int loadPokemon(string inputFile){
    ifstream input;
    input.open(inputFile);

    //開啟失敗回傳0
    if(!input.is_open()){
        return 0;
    }

    //檢查有無讀取過 有就歸零重新讀取
    if(allPokemon.size() != 0){
        allPokemon.clear();
    }

    string inputLine;       //每行
    vector<int> inputValue; //儲存數值
    vector<string> inputType; //儲存屬性
    int counts = 0; //計算行數
    Pokemon pokemon; //暫存用

    //迴圈獲取每一行 名字 屬性 數值
    while(getline(input, inputLine)){
        //如果在三行內
        if(counts < 3){
            switch(counts){
                case 0:{
                    pokemon.setName(inputLine); //第一行名字
                    break;
                }
                case 1:{
                    //開始空格切割
                    stringstream stringstream(" ");
                    string temp;

                    stringstream << inputLine;
                    stringstream >> temp; //TN Type數量 要忽略所以先跑一次

                    while (stringstream >> temp)
                    {
                        inputType.push_back(temp);//放入Type陣列
                    }

                    pokemon.setType(inputType);//放入暫存寶可夢
                    break;
                }
                case 2:{
                    //開始空格切割
                    stringstream stringstream1(" ");
                    string temp1;

                    stringstream1 << inputLine;

                    while (stringstream1 >> temp1)
                    {
                        inputValue.push_back(stoi(temp1));//放入數值陣列
                    }

                    //土法煉鋼 一個個丟進去
                    pokemon.setHp(inputValue[0]);
                    pokemon.setAtk(inputValue[1]);
                    pokemon.setDef(inputValue[2]);
                    pokemon.setSpAtk(inputValue[3]);
                    pokemon.setSpDef(inputValue[4]);
                    pokemon.setSpeed(inputValue[5]);

                    break;
                }
                default:{
                    break;
                }
            }

            counts++;
        }
        else{
            //暫存寶可夢資料 存到所有寶可夢內
            allPokemon.push_back(pokemon);
            //初始化
            counts = 0;
            inputValue.clear();
            inputType.clear();
            pokemon.cleanType();
        }
    }
    return 1;
}

//讀取Move文件
int loadMoves(string inputFile){
    ifstream input;
    input.open(inputFile);

    //開啟失敗回傳0
    if(!input.is_open()){
        return 0;
    }

    //檢查有無讀取過 有就歸零重新讀取
    if(movesOfAll.size() != 0){
        movesOfAll.clear();
    }

    string inputLine;          //每行
    vector<string> inputVaule; //數值

    while(getline(input, inputLine)){
        Moves move; //暫存技能資料

        //開始空格切割
        stringstream stringstream(" ");
        string temp;

        stringstream << inputLine;

        while (stringstream >> temp)
        {
            inputVaule.push_back(temp); //全部資訊存陣列
        }

        //土法煉鋼 一個個設置進去
        move.movesName = inputVaule[0];
        move.movesType = inputVaule[1];
        if(inputVaule[2] == "Physical"){
            move.pS = 'p';
        }
        else{
            move.pS = 's';
        }
        move.power = stoi(inputVaule[3]);
        move.accuracy = stoi(inputVaule[4]);
        move.pp = stoi(inputVaule[5]);
        if(inputVaule.size() > 6){
            move.con = inputVaule[6];
        }
        else{
            move.con = "Non"; //如果最後沒東西就設Non
        }

        //存進所有技能裡
        movesOfAll.push_back(move);
    }
    return 1;
}

//讀取gameData文件
int loadGameData(string inputFile){
    ifstream input;
    input.open(inputFile);

    //暫存寶可夢隊伍陣列
    vector<Pokemon> teamPokemon;

    //開啟失敗回傳0
    if(!input.is_open()){
        return 0;
    }

    //檢查有無讀取過 有就歸零重新讀取
    if(team1.showTeamer().size() != 0 || team2.showTeamer().size() != 0){
        team1.cleaner();
        team2.cleaner();
    }

    //分我方敵方 我方先
    for(int h=0;h<2;h++){
        vector<string> inputName;  //寶可夢名字
        vector<string> inputSkill; //寶可夢技能
        string inputLine;          //每行
        int inputNumber;           //隊伍寶可夢數量

        //獲取隊伍寶可夢數量
        getline(input,inputLine);

        //轉為數字存進去
        inputNumber = stoi(inputLine);

        //依照數量迴圈
        for(int i=0; i < inputNumber; i++){
            //先獲取名字 和技能數量
            getline(input,inputLine);

            //空格分割
            stringstream stringstream(" ");
            string temp;

            stringstream << inputLine;

            stringstream >> temp;

            //放進Name迴圈 (先不放技能數量)
            inputName.push_back(temp);

            //下一行 各個招式
            getline(input,inputLine);

            stringstream << inputLine;

            //放入技能陣列內
            while (stringstream >> temp)
            {
                inputSkill.push_back(temp);
            }

            //檢查所有寶可夢
            for(int j=0;j<allPokemon.size();j++){
                //找到和暫存陣列內同名的
                if(allPokemon[j].showName() == inputName[0]){
                    //檢查所有技能
                    for(int d=0;d<stoi(inputName[1]);d++){
                        for(int k=0;k<movesOfAll.size(); k++){
                            //找到和暫存陣列內同名的
                            if(movesOfAll[k].movesName == inputSkill[d]){
                                //放進那個寶可夢的技能欄位裡
                                allPokemon[j].setOneMoves(movesOfAll[k]);
                                break;
                            }
                        }
                    }

                    //將此寶可夢放進隊伍裡 team1我方 team2敵方
                    if(h==0){
                        team1.setOneTeamer(allPokemon[j]);
                    }
                    else{
                        team2.setOneTeamer(allPokemon[j]);
                    }
                }
            }
        }

    }

    return 1;
}

//因為找不到cpp共通全域函數的方法所以先寫一個函數回傳檔案名給ui介面
string showFileName(int i){return fileName[i];}
