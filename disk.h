#ifndef DISK_H
#define DISK_H

#include <QWidget>
//---forward declaration

class QPaintEvent;
class Pole;

class Disk: public QWidget
{
private:
    Pole *on;
    int size; // size of disk
    int pos; // index on pole

    void setPolePos(Pole *d, int p);
    void Lift();
    int Size(){return size;}

public:
    Disk(int _size, int _pos, Pole *_on, QWidget *_parent);
    void paintEvent(QPaintEvent *);
    Pole *On(){return on;}
    friend class Pole;
};

#endif // DISK_H
