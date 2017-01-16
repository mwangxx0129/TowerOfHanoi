#include <QPainter>
#include "disk.h"
#include "pole.h"

extern int HEIGHT_DISK;
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

    QColor poleColor(207, 162, 95);
    QColor edgePoleColor(0, 0, 0);
    p.setPen(edgePoleColor);
    p.setBrush(poleColor);
    //p.drawRoundedRect(60,90,20,240-(numDisks*23),10,8);
    //p.drawRoundedRect(60,90,20,100,10,8);
    p.drawRect(56,60,8,140-(numDisks * HEIGHT_DISK));

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

