#include <QQueue>
#include <QStack>
#include <QTimer>

#include "tower.h"
#include "ui_tower.h"
#include "disk.h"
#include "pole.h"
#include "move.h"


float scale = 1.0;
Disk *moving = NULL;
//--

tower::tower(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::tower)
{
    ui->setupUi(this);

    value = ui->spinBox->value();
    poles[0] = new Pole(0, value,ui->pushButton_0);
    poles[1] = new Pole(1, 0,ui->pushButton_1);
    poles[2] = new Pole(2, 0,ui->pushButton_2);
    ui->spinBox->hide();

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(delayedAction()));

    autoplay = false;
}

tower::~tower()
{
    delete ui;
    for (int i=0;i<3;i++){

        delete poles[i];
    }
    moving = NULL;
    undoStack.clear();
    schedule.clear();
}

void tower::resizeEvent(QResizeEvent *){

    scale = qMin(width()/(360.0), height()/(300.0));
    ui->pushButton_0->resize(scale * 120, scale * 300); // number should be const
    ui->pushButton_1->resize(scale * 120, scale * 300);
    ui->pushButton_2->resize(scale * 120, scale * 300);

    ui->pushButton_1->move(scale * 120, 0);
    ui->pushButton_2->move(scale * 240,0);
}

void tower::CalculateSchedule(int count, int from, int to, int spare)
{
    if(count < 1) return;
    CalculateSchedule(count-1, from, spare, to);
    schedule.enqueue(Move(from, to));
    CalculateSchedule(count-1, spare, to, from);
}

void tower::on_pushButton_0_clicked()
{
    on_pushButton_clicked(poles[0]);
}

void tower::on_pushButton_1_clicked()
{
    on_pushButton_clicked(poles[1]);
}

void tower::on_pushButton_2_clicked()
{
    on_pushButton_clicked(poles[2]);
}

void tower::on_actionNew_triggered()
{
    for (int i=0;i<3;i++){

        delete poles[i];
    }
    if(moving){
        delete moving;
    }
    moving = NULL;
    undoStack.clear();
    schedule.clear();

    poles[0] = new Pole(0, value,ui->pushButton_0);
    poles[1] = new Pole(1, 0,ui->pushButton_1);
    poles[2] = new Pole(2, 0,ui->pushButton_2);
    ui->spinBox->hide();
}

void tower::on_actionSet_Disks_triggered()
{
    ui->spinBox->show();
}

void tower::on_actionExit_triggered()
{
    close();
}

void tower::on_actionUndo_triggered()
{
    if(!undoStack.empty()){
        Move mUndo = undoStack.pop();
        Pole* to = NULL;
        Pole* from = NULL;
        to = poles[mUndo.getTo()];
        from = poles[mUndo.getFrom()];
        if(moving){
            moving->On()->put(moving);
            moving = NULL;
        }
        moving = to->take();
        from->put(moving);
        moving = NULL;
    }
}

void tower::on_actionUndo_All_triggered()
{
    autoplay = false;
    timer->start(33);

}

void tower::on_actionAuto_Play_triggered()
{
    on_actionNew_triggered();
    CalculateSchedule(poles[0]->getNumDisks(),0,2,1);
    timer->start(500); // 0.5 second
    autoplay = true;
    ui->pushButton_0->setDisabled(true);
    ui->pushButton_1->setDisabled(true);
    ui->pushButton_2->setDisabled(true);
}

void tower::on_spinBox_valueChanged(int arg1)
{
    value = arg1;
}

void tower::delayedAction()
{
    if(autoplay){
        if(!schedule.empty()){
            Move autom = schedule.dequeue();
            moving = poles[autom.getFrom()]->take();
            poles[autom.getTo()]->put(moving);
            moving = NULL;
            undoStack.push(autom);
        }else{
            autoplay = false;
            ui->pushButton_0->setEnabled(true);
            ui->pushButton_1->setEnabled(true);
            ui->pushButton_2->setEnabled(true);
            timer->stop();
        }

    }else{
        if(undoStack.empty()){
            ui->pushButton_0->setEnabled(true);
            ui->pushButton_1->setEnabled(true);
            ui->pushButton_2->setEnabled(true);
            timer->stop();
        }else{
            on_actionUndo_triggered();
        }
    }
}

void tower::on_pushButton_clicked(Pole *p)
{
    if(!moving){
        moving = p->take();
    }else{
        int from = moving->On()->getIndex();
        if(p->put(moving)){
            Move mov(from,p->getIndex());
            undoStack.push(mov);
            moving = NULL;
        }else{
            moving->On()->put(moving);
            moving = NULL;
        }
    }
}
