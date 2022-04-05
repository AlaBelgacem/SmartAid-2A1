#include "chatsocket.h"

ChatSocket::ChatSocket(qintptr handle,QObject *parent ):QTcpSocket(parent)
{
setSocketDescriptor(handle);
connect(this,&ChatSocket::readyRead,[&](){
    emit DuReadyRead(this);
});
connect (this,&ChatSocket::stateChanged,[&](int S )
{
   emit DuStateChanged(this,S);
});
}
