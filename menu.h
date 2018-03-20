#ifndef MENU_H
#define MENU_H

#include <QDialog>

namespace Ui {
class Menu;
}

class Menu : public QDialog
{
    Q_OBJECT

public:
    explicit Menu(QWidget *parent = 0);
    ~Menu();

private slots:
    void on_pushButton_clicked();

    void on_boardSizeSelector_editingFinished();

    void on_inRowSelector_editingFinished();

    void on_boardSizeSelector_valueChanged();

    void on_inRowSelector_valueChanged();

signals:
    void gameSettings(int newInRow,int newSize);

private:
    int boardSize;
    int inRowSize;
    Ui::Menu *ui;
};

#endif // MENU_H
