#ifndef ARDUINO_H
#define ARDUINO_H
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

class Arduino
{
public:
    Arduino();
    int connect_arduino();
    int close_arduino();
    int write_to_arduino(QByteArray);
    QByteArray read_from_arduino();
    QSerialPort* getserial();
    QString get_port_name();

private:
    QSerialPort* serial;
    static const quint16 arduino_vendor_id=1;
    static const quint16 arduino_prod_id=1;
    QString arduino_port;
    bool availibility;
    QByteArray data;

};

#endif // ARDUINO_H
