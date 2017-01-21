#ifndef DISK_H
#define DISK_H
//---------------------------------------------------------|
class Pole;

//---------------------------------------------------------|
class Disk: public QWidget
{
private:

    int size; // size of disk
    int pos; // index on pole
    Pole *on;

    void setPolePos(Pole *d, int p);
    void Lift();
    int Size()
    {
        return size;
    }

public:
    Disk(QWidget *,int, int, Pole *);
    void paintEvent(QPaintEvent *);
    Pole *On()
    {
        return on;
    }
    friend class Pole;
};

#endif // DISK_H
