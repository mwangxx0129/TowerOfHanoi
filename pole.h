#ifndef POLE_H
#define POLE_H

//---------------------------------------------------------|
class QWidget;
class QPaintEvent;
class Disk;

const int MAX_DISKS = 8;

//---------------------------------------------------------|
class Pole: public QWidget
{
private:
    int index; // index of pole
    int numDisks; // currently on pole
    Disk * stack[MAX_DISKS]; //stack of disks on this pole
public:
    Pole(int , int , QWidget * );
    ~Pole();
    void paintEvent(QPaintEvent *);

    int getNumDisks(){return numDisks;}
    int getIndex(){return index;}

    Disk* take(); //return the top disk on the pole, otherwise NULL
    bool put(Disk* d);// false means size is wrong or pointer NULL. put the disk on the pole, true success.
};

#endif // POLE_H
