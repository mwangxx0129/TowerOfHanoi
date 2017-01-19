#include<QWidget>
#include <QPainter>
#include "disk.h"
#include "pole.h"

QColor poleColor(127, 0, 0);
QColor edgePoleColor(0, 0, 0);
extern int HEIGHT_DISK;
extern float scale;

Pole::Pole(int _index, int _numDisks, QWidget * _parent)
{
    this->index = _index;
    this->numDisks = _numDisks;
    this->setParent(_parent);

    for(int i=0;i<_numDisks;i++){
        Disk* d = new Disk(_numDisks - i,i,this, _parent);
        stack[i] = d;
    }

    setEnabled(true);
    show();
    raise();
}
Pole::~Pole(){
    //    setParent(NULL);
    for (int i=0;i<numDisks;i++){
        delete stack[i];
    }
}
void Pole::paintEvent(QPaintEvent *){
    QPainter p(this);

    p.setRenderHint(QPainter::Antialiasing);
    resize(scale *120, scale *240);
    p.scale(scale, scale);

    p.setPen(edgePoleColor);
    p.setBrush(poleColor);
    p.drawRect(56,60,8,140-(numDisks * HEIGHT_DISK));
    //p.drawRoundedRect(56,80,6,85- numDisks *HEIGHT_DISK, 3,2);

}

Disk* Pole::take() //return the top disk on the pole, otherwise NULL
{

    Disk *d = NULL;
    if(numDisks >0){
        d = stack[--numDisks];
        stack[numDisks] = NULL;
        d->Lift();
    }
    return d;
}

bool Pole::put(Disk* d)// false means size is wrong or pointer NULL. put the disk on the pole, true success.
{

    if(numDisks == 0){
        stack[0] = d;
        numDisks++;
        d->setPolePos(this,0);
        raise();
        return true;
    }else{
        if(stack[numDisks-1]->Size() < d->Size()){
            return false;
        }else{
            stack[numDisks] = d;
            numDisks++;
            d->setPolePos(this,numDisks-1);
            raise();
            return true;
        }
    }
}

