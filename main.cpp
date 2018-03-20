#include "mainwindow.h"
#include "menu.h"
#include "endgame.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow mainGameWindow;
    Menu menuWindow;
    EndGame endGameDialog;
    QObject::connect(&menuWindow, SIGNAL(gameSettings(int,int)), &mainGameWindow, SLOT(setGameSettings(int,int)));
    QObject::connect(&mainGameWindow, SIGNAL(setQuote(QString)), &endGameDialog, SLOT(setQuote(QString)));
    QObject::connect(&mainGameWindow, SIGNAL(reselectValues()), &menuWindow, SLOT(exec()));
    QObject::connect(&endGameDialog, SIGNAL(endGameSig()), &mainGameWindow, SLOT(endGame()));
    QObject::connect(&endGameDialog, SIGNAL(resetGameSig()), &mainGameWindow, SLOT(resetGame()));
    mainGameWindow.show();
    menuWindow.exec();
    a.quit();
    return a.exec();
}
