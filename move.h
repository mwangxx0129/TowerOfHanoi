#ifndef MOVE_H
#define MOVE_H

class Move
{
    qint16 from;
    qint16 to;

public:
    Move(qint16, qint16);
    Move();

    int getFrom() const {return from;}
    int getTo() const {return to;}
};

#endif // MOVE_H
