#ifndef MESSENGER_H
#define MESSENGER_H

#include <QDialog>

namespace Ui {
class messenger;
}
namespace  duartecorporation
{
class messenger : public QDialog
{
    Q_OBJECT

public:
    explicit messenger(QWidget *parent = nullptr);
    ~messenger();
    QString hostname()const;
    quint16 port()const;
private slots:
    void on_pb_accepter_clicked();

    void on_pb_cancel_clicked();

private:
    Ui::messenger *ui;
    QString mHostname;
    quint16 mPort;
};

inline  QString messenger:: hostname()const
{
    return mHostname;
}
inline quint16 messenger::port()const
{
    return mPort;
}
}
#endif // MESSENGER_H
