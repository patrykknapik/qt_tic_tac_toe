#include "menu.h"
#include "ui_menu.h"

Menu::Menu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Menu)
{
    boardSize = 3;
    inRowSize = 3;
    ui->setupUi(this);
    ui->inRowSelector->setMaximum(boardSize);

}

Menu::~Menu()
{
    delete ui;
}

void Menu::on_pushButton_clicked()
{
    this->close();
    gameSettings(inRowSize, boardSize);

}


void Menu::on_boardSizeSelector_editingFinished(){
    boardSize = ui->boardSizeSelector->value();
    ui->inRowSelector->setMaximum(boardSize);
    ui->inRowSelector->setValue(boardSize);
}
void Menu::on_boardSizeSelector_valueChanged()
{
    boardSize = ui->boardSizeSelector->value();
    ui->inRowSelector->setMaximum(boardSize);
     ui->inRowSelector->setValue(boardSize);
}

void Menu::on_inRowSelector_editingFinished()
{
    inRowSize = ui->inRowSelector->value();
}

void Menu::on_inRowSelector_valueChanged()
{
    inRowSize = ui->inRowSelector->value();
}
