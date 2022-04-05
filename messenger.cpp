#include "messenger.h"
#include "ui_messenger.h"

namespace duartecorporation {


messenger::messenger(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::messenger)
{
    ui->setupUi(this);
}

messenger::~messenger()
{
    delete ui;
}

void messenger::on_pb_accepter_clicked()
{
    mHostname=ui->hostname->text();
    mPort=ui->port->value();
    accept();
}

void messenger::on_pb_cancel_clicked()
{
    reject();
}
}
