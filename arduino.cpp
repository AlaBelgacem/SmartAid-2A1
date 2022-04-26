#include "arduino.h"
#include <qdebug.h>
Arduino::Arduino()
{
    data="";
    arduino_port="";
    availibility=false;
    serial = new QSerialPort;
}

QString Arduino::get_port_name(){
    return this->arduino_port;
}

QSerialPort* Arduino::getserial(){
    return serial;
}

int Arduino::close_arduino(){
    if(serial->isOpen()){
        serial->close();
        return 0;
    }
    return 1;
}



QByteArray Arduino::read_from_arduino()
{
    if(serial->isReadable()){
        data=serial->readAll();
        return data;
    }
    return 0;
}


int Arduino::write_to_arduino(QByteArray d){
    if(serial->isWritable()){
        serial->write(d);
        return 1;
    }
    else {
        qDebug()<<"couldn't write to serial";
    }
    return 0;
}
int Arduino::connect_arduino()
{
   foreach(const QSerialPortInfo &serial_port_info, QSerialPortInfo::availablePorts())
    {
        if(serial_port_info.hasVendorIdentifier() && serial_port_info.hasProductIdentifier())
        {
            if(serial_port_info.hasVendorIdentifier() == arduino_vendor_id && serial_port_info.hasProductIdentifier() == arduino_prod_id)
            {
                availibility=true;
                arduino_port=serial_port_info.portName();
            }
        }
    }
    if(availibility)
    {
        serial->setPortName(arduino_port);
        if(serial->open(QSerialPort::ReadWrite))
        {
            serial->setBaudRate(QSerialPort::Baud115200);
            serial->setDataBits(QSerialPort::Data8);
            serial->setParity(QSerialPort::NoParity);
            serial->setStopBits(QSerialPort::OneStop);
            serial->setFlowControl(QSerialPort::NoFlowControl);
            return  0;
        }
        return 1;
    }
    return  -1;

}
