#include "mainwindow.h"
#include "ui_mainwindow.h"
#define BUTTON_SIZE 50
#define BORDER_SIZE 25

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    boardSize = 3;
    inRowSize = 3;
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setGameSettings(int newInRow, int newSize){
    boardSize = newSize;
    inRowSize = newInRow;
    game.set_sizes(newSize,newInRow);
    this->setFixedSize(boardSize*BUTTON_SIZE + BORDER_SIZE*2,boardSize*BUTTON_SIZE + BORDER_SIZE*2);

    qDebug() <<"size: "<< boardSize << " in row: "<< inRowSize << '\n';

    ui->gridLayoutWidget->setGeometry(BORDER_SIZE,BORDER_SIZE,0,0);
    ui->gridLayoutWidget->setFixedSize(boardSize*BUTTON_SIZE,boardSize*BUTTON_SIZE);


    for(int i=0; i<boardSize; ++i){
        for(int j=0; j<boardSize; ++j)
        {
            QPushButton *tmpButton = new QPushButton(this);
            tmpButton->setFixedSize(BUTTON_SIZE,BUTTON_SIZE);
            ui->gridLayout->addWidget(tmpButton,i,j);
            fields << tmpButton;
        }
    }
    for(int k = 0; k < boardSize*boardSize; ++k){
        QObject::connect(fields.at(k),SIGNAL(clicked()),this,SLOT(fieldClicked()));
    }
    updateIcons();
}

void MainWindow::runGame(){

    emit setQuote("TESTOWY QUOTE");
    for(int k = 0; k < boardSize*boardSize; ++k){
        ui->gridLayout->removeWidget(fields.at(k));
        delete fields.at(k);
    }
    fields.clear();
    status = false;

}

void MainWindow::fieldClicked(){
    QObject * sender = QObject::sender();
    int x, y, index;
    bool fieldEmpty = true;

    for(int k=0;k<fields.size();++k){
        if(fields.at(k)==sender)
            index = k;
    }
    x = index%boardSize;
    y = index/boardSize;
    qDebug()<<"Wcisnieto przycisk: x = "<<x<<" y = "<<y<<'\n';
    try{
    gameStatus = game.move(x,y);
    }catch(std::logic_error & msg){
        qDebug()<<"Błąd: "<< msg.what() << '\n';
        fieldEmpty = false;
    }
    updateIcons();
    qDebug()<<"Status: "<< gameStatus << '\n';
    switch(gameStatus){
    case player:
        emit setQuote("Wgrałeś! :D");
        break;
     case computer:
        emit setQuote("Pregrałeś :/");
        break;
    case draw:
       emit setQuote("Remis :)");
       break;
    default:
        break;
    }
}

void MainWindow::updateIcons(){
    int index = 0;
    field ** board;
    board = game.get_board();

    for(int i=0;i<boardSize;++i){
        for(int j = 0; j<boardSize; ++j){
            switch (board[j][i]) {
            case X:
                fields.at(index++)->setText(QString("X"));
                break;
             case O:
                fields.at(index++)->setText(QString("O"));
                break;
            default:
                fields.at(index++)->setText(QString(""));
                break;
            }

        }
    }
}

void MainWindow::endGame(){
    this->close();
}
void MainWindow::resetGame(){
    field ** board;
    board = game.get_board();
    for(int i=0;i<boardSize;++i){
       delete[] board[i];
    }
    delete[] board;
    for(int j = 0; j < boardSize*boardSize; ++j){
        ui->gridLayout->removeWidget(fields.at(j));
        delete fields.at(j);
    }
    fields.clear();
    emit reselectValues();
}
