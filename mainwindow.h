#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QIcon>
#include <QPixmap>
#include <QPushButton>
#include <stdexcept>
#include "tic_tac_toe.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    bool playing(){return status;}
    void runGame();
    ~MainWindow();
private slots:
    void fieldClicked();

public slots:
    void setGameSettings(int newInRow, int newSize);
    void endGame();
    void resetGame();

signals:
    void setQuote(QString);
    void reselectValues();

private:
    Ui::MainWindow *ui;
    tic_tac_toe game;
    bool status = true;
    QVector<QPushButton*> fields;
    int boardSize;
    int inRowSize;
    result gameStatus;
    void updateIcons();
};

#endif // MAINWINDOW_H
