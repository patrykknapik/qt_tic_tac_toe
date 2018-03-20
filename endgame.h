#ifndef ENDGAME_H
#define ENDGAME_H

#include <QDialog>

namespace Ui {
class endGame;
}

class EndGame : public QDialog
{
    Q_OBJECT

public:
    explicit EndGame(QWidget *parent = 0);
    bool again(){return againFlag;}
    ~EndGame();
public slots:
    void setQuote(QString endQuote);

private slots:
    void on_yesButton_clicked();

    void on_noButton_clicked();

signals:
    void resetGameSig();
    void endGameSig();

private:
    bool againFlag = true;
    Ui::endGame *ui;
};

#endif // ENDGAME_H
