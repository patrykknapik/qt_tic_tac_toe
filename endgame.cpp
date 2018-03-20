#include "endgame.h"
#include "ui_endgame.h"

EndGame::EndGame(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::endGame)
{
    ui->setupUi(this);
}

EndGame::~EndGame()
{
    delete ui;
}

void EndGame::setQuote(QString endQuote){
    ui->endGameQuote->setText(endQuote);
    this->exec();
}

void EndGame::on_yesButton_clicked()
{
   this->close();
    emit resetGameSig();
}

void EndGame::on_noButton_clicked()
{
    this->close();
    emit endGameSig();
}
