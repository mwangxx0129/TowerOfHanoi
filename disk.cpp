#include <QWidget>
#include <QPainter>
#include "disk.h"
#include "pole.h"

//---------------------------------------------------------|
extern float scale;
QColor diskColor(200,200,0);
QColor diskEdgeColor(100,100,0);

int HEIGHT_DISK = 5; // height of disk
int MIN_SIZE_DISK = 10; // min size of disk
int DIF_SIZE_DISK = 6; // diff between two disks

int TOP_X = 6;
int TOP_Y = 3;

//---------------------------------------------------------|
Disk::Disk(int _size, int _pos, Pole *_on, QWidget *_parent)
    :size(_size), pos(_pos), on(_on)
{
    this->setParent(_parent);
    show();
    raise();
}

//---------------------------------------------------------|
void Disk::paintEvent(QPaintEvent *){
    int maxY = 200;
    // (x,y) is the center of bottom circle
    int x = 60;
    int y = maxY - pos * HEIGHT_DISK;
    int rX = MIN_SIZE_DISK + size * DIF_SIZE_DISK;
    int rY = rX/2;

    QPainter p(this);

    resize(120 * scale, 240 * scale);
    p.scale(scale, scale);
    p.setRenderHint(QPainter::Antialiasing);
    p.setBrush(diskColor);
    p.setPen(diskEdgeColor);
    p.save();

    p.drawEllipse(QPoint(x,y), rX, rY); // bottom ellipse
    p.setPen(Qt::NoPen);
    p.drawRect(x-rX,y-HEIGHT_DISK, 2*rX, HEIGHT_DISK); // rectangle
    p.setPen(diskEdgeColor);
    p.drawLine(x-rX,y, x-rX, y-HEIGHT_DISK);
    p.drawLine(x+rX,y, x+rX, y-HEIGHT_DISK);
    p.drawEllipse(QPoint(x,y-HEIGHT_DISK), rX, rY); // upper ellipse
    p.setBrush(diskEdgeColor);
    p.drawEllipse(QPoint(x,y-HEIGHT_DISK), TOP_X, TOP_Y); // top hole ellipse
    p.restore();
}

//---------------------------------------------------------|
void Disk::Lift(){
    pos = 35;
    repaint();
}

//---------------------------------------------------------|
void Disk::setPolePos(Pole *d, int p)
{
    if(on !=d){
        on = d;
        this->setParent(d->parentWidget());
        show();
    }
    pos = p;
    repaint();
}
