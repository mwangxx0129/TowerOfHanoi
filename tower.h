#ifndef TOWER_H
#define TOWER_H

#include <QMainWindow>
#include <QQueue>
#include <QStack>
#include "move.h"
//---------------------------------------------------------|
class Pole;
class Move;
class Disk;
//---------------------------------------------------------|
namespace Ui
{
class tower;
}

class tower : public QMainWindow
{
    Q_OBJECT

public:
    explicit tower(QWidget *parent = 0);
    ~tower();
    void resizeEvent(QResizeEvent *); // resize the window


private slots:
    void on_pushButton_0_clicked();

    void on_pushButton_1_clicked();

    void on_pushButton_2_clicked();

    void on_actionNew_triggered();

    void on_actionSet_Disks_triggered();

    void on_actionExit_triggered();

    void on_actionUndo_triggered();

    void on_actionUndo_All_triggered();

    void on_actionAuto_Play_triggered();

    void on_spinBox_valueChanged(int arg1);

    void delayedAction();

    void on_horizontalSlider_actionTriggered();

private:
    Ui::tower *ui;
    Pole* poles[3];
    Disk *moving = NULL;
    QQueue<Move> schedule;
    QStack<Move> undoStack;

    QTimer *timer;
    int interval;
    bool autoplay;
    int value;
    void EnableAllButton(bool );
    void on_pushButton_clicked(Pole * p);
    void CalculateSchedule(int count, int from, int to, int spare);
    //... 1. argu 2. to do autopaly 3. slowly to visible

};

#endif // TOWER_H
