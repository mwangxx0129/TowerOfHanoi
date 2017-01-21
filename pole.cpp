#include<QWidget>
#include <QPainter>
#include "disk.h"
#include "pole.h"
//---------------------------------------------------------|
extern int HEIGHT_DISK;
extern float scale;
//---------------------------------------------------------|
Pole::Pole(int inIndex, int inNumDisks, QWidget * inPar)
    :QWidget(inPar),index(inIndex),numDisks(inNumDisks)
{
    for(int i=0; i<numDisks; i++)
    {
        Disk* d = new Disk(inPar,numDisks - i,i,this);
        stack[i] = d;
    }

    setEnabled(true);
    show();
    raise();
}
//---------------------------------------------------------|
Pole::~Pole()
{
    //    setParent(NULL);
    for (int i=0; i<numDisks; i++)
    {
        delete stack[i];
    }
}
//---------------------------------------------------------|
void Pole::paintEvent(QPaintEvent *)
{
    QColor poleColor(127, 0, 0);
    QColor edgePoleColor(0, 0, 0);
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);
    resize(scale *120, scale *240);
    p.scale(scale, scale);
    p.setPen(edgePoleColor);
    p.setBrush(poleColor);
    QRectF rectangle(56,60,8,140-(numDisks * HEIGHT_DISK));
    p.drawRoundedRect(rectangle,5,5);

}
//---------------------------------------------------------|
//return the top disk on the pole, otherwise NULL
Disk* Pole::take()
{
    Disk *d = NULL;
    if(numDisks >0)
    {
        d = stack[--numDisks];
        stack[numDisks] = NULL;
        d->Lift();
    }
    return d;
}
//---------------------------------------------------------|
// false means size is wrong or pointer NULL.
// put the disk on the pole, true success.
bool Pole::put(Disk* d)
{

    if(numDisks == 0)
    {
        stack[0] = d;
        numDisks++;
        d->setPolePos(this,0);
        raise();
        return true;
    }
    else
    {
        if(stack[numDisks-1]->Size() < d->Size())
        {
            return false;
        }
        else
        {
            stack[numDisks] = d;
            numDisks++;
            d->setPolePos(this,numDisks-1);
            raise();
            return true;
        }
    }
}
//---------------------------------------------------------|

