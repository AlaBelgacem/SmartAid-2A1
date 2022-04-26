#include "PieChart.h"
#include <QPainter>

piechart::piechart(QWidget *parent) : QWidget(parent)
{

}

void piechart::paintEvent(QPaintEvent *)
{
    QString x1,x2,x3;

    QPainter painter(this);
    QRectF size = QRectF(10,10,this->width()-100,this->width()-100);
    painter.setBrush(QColor(85, 0, 0));
    Cr.stat(&x1,&x2,&x3);
    int y1 = (x1.toInt() * 360)/100;
    int y2 = (x2.toInt() * 360)/100;
    painter.drawPie(size, 0, y1 * 16);
    painter.setBrush(QColor(171, 58, 58));
    painter.drawPie(size, y1 * 16, (360 - y1)*16);
    painter.setBrush(QColor(128, 20, 20));
    painter.drawPie(size, (y2+y1 )* 16, (360 - (y2+y1))*16);
}
