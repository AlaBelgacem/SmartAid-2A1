#ifndef PIECHART_H
#define PIECHART_H
#include <QWidget>
#include "crises.h"

class piechart : public QWidget
{
    Q_OBJECT
public:
    explicit piechart(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *);
signals:

public slots:
private:
   Crises Cr;
};

#endif // PIECHART_H
