
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_button_load_clicked();

    void on_button_play_clicked();

    void on_button_goback_clicked();

    void on_button_load_file_2_clicked();

    void on_button_load_file_3_clicked();

    void on_button_load_file_4_clicked();

    void on_button_load_file_clicked();
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
