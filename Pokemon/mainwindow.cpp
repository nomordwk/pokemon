#include "mainwindow.h"
#include "./ui_mainwindow.h"

using namespace std;

int loadTextCase(string inputFile);
int loadPokemon(string inputFile);
int loadMoves(string inputFile);
int loadGameData(string inputFile);
string showFileName(int i);


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//menu選擇load
void MainWindow::on_button_load_clicked()
{
    //更改頁面
    ui->stackedWidget->setCurrentIndex(1);
}

//menu選擇play
void MainWindow::on_button_play_clicked()
{
    //更改頁面
     ui->stackedWidget->setCurrentIndex(2);
}

//返回menu
void MainWindow::on_button_goback_clicked()
{
    //更改頁面
    ui->stackedWidget->setCurrentIndex(0);
}

//讀取寶可夢txt
void MainWindow::on_button_load_file_2_clicked()
{
    //抓取訊息框內路徑
    string address = ui->lineEdit_2->text().toStdString();

    //跑在main裡面的函式 讀取後更改狀態
    if(loadPokemon(address) == 1){
        ui->txt_pokemon_check->setText("Load Success!");
        //如果資料都讀取過了 開放遊玩按鈕
        if(ui->txt_move_check->text() == "Load Success!" && ui->txt_pokemon_check->text() == "Load Success!"){
            ui->button_start->setEnabled(true);
        }
    }
    else{
        ui->txt_pokemon_check->setText("Load Error!");
    }
}

//讀取move.txt
void MainWindow::on_button_load_file_3_clicked()
{
    //抓取訊息框內路徑
    string address = ui->lineEdit_3->text().toStdString();

    //跑在main裡面的函式 讀取後更改狀態
    if(loadMoves(address) == 1){
        ui->txt_move_check->setText("Load Success!");
        //如果資料都讀取過了 開放遊玩按鈕
        if(ui->txt_move_check->text() == "Load Success!" && ui->txt_pokemon_check->text() == "Load Success!"){
            ui->button_start->setEnabled(true);
        }
    }
    else{
        ui->txt_move_check->setText("Load Error!");
    }
}

//讀取gamedata.exe
void MainWindow::on_button_load_file_4_clicked()
{
    //抓取訊息框內路徑
    string address = ui->lineEdit_4->text().toStdString();

    //跑在main裡面的函式 讀取後更改狀態
    if(loadGameData(address) == 1){
        ui->txt_game_check->setText("Load Success!");
        //如果資料都讀取過了 開放遊玩按鈕
        if(ui->txt_move_check->text() == "Load Success!" && ui->txt_pokemon_check->text() == "Load Success!"){
            ui->button_start->setEnabled(true);
        }
    }
    else{
        ui->txt_game_check->setText("Load Error!");
    }
}

//讀取case
void MainWindow::on_button_load_file_clicked()
{
    //抓取訊息框內路徑
    string address = ui->lineEdit->text().toStdString();
    int checkNumber = loadTextCase(address);

    //確認是哪個文件讀取錯誤
    if(checkNumber == 0){ //case
        ui->txt_text_case_check->setText("Load Error!");
    }
    else if(checkNumber == 1){ //pokemon
        ui->txt_text_case_check->setText("Load Error!");
        ui->txt_pokemon_check->setText("Load Error!");
    }
    else if(checkNumber == 2){ //move
        ui->txt_text_case_check->setText("Load Error!");
        ui->txt_pokemon_check->setText("Load Success!");
        ui->txt_move_check->setText("Load Error!");
        ui->lineEdit_2->setText(QString::fromStdString(showFileName(0))); //訊息框更改路徑
    }
    else if(checkNumber == 3){ //gamedata
        ui->txt_text_case_check->setText("Load Error!");
        ui->txt_pokemon_check->setText("Load Success!");
        ui->txt_move_check->setText("Load Success!");
        ui->txt_game_check->setText("Load Error!");
        ui->lineEdit_2->setText(QString::fromStdString(showFileName(0))); //訊息框更改路徑
        ui->lineEdit_3->setText(QString::fromStdString(showFileName(1)));
    }
    else if(checkNumber == 4){ //沒出錯 開放start鈕
        ui->txt_text_case_check->setText("Load Success!");
        ui->txt_pokemon_check->setText("Load Success!");
        ui->txt_move_check->setText("Load Success!");
        ui->txt_game_check->setText("Load Success!");
        ui->lineEdit_2->setText(QString::fromStdString(showFileName(0))); //訊息框更改路徑
        ui->lineEdit_3->setText(QString::fromStdString(showFileName(1)));
        ui->lineEdit_4->setText(QString::fromStdString(showFileName(2)));
        ui->button_start->setEnabled(true); //開放start按鈕
    }
}

