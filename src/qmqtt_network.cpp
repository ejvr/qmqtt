/*
 * qmqtt_network.cpp - qmqtt network
 *
 * Copyright (c) 2013  Ery Lee <ery.lee at gmail dot com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *   * Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *   * Neither the name of mqttc nor the names of its contributors may be used
 *     to endorse or promote products derived from this software without
 *     specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */
#include <QDataStream>
#include "qmqtt_network.h"
#include "qmqtt_socket.h"
#include "qmqtt_ssl_socket.h"
#include "qmqtt_timer.h"

const QHostAddress DEFAULT_HOST = QHostAddress::LocalHost;
const QString DEFAULT_HOST_NAME = QStringLiteral("localhost");
const quint16 DEFAULT_PORT = 1883;
const bool DEFAULT_AUTORECONNECT = false;
const int DEFAULT_AUTORECONNECT_INTERVAL_MS = 5000;

QMQTT::Network::Network(QObject* parent)
    : NetworkInterface(parent)
    , _port(DEFAULT_PORT)
    , _host(DEFAULT_HOST)
    , _autoReconnect(DEFAULT_AUTORECONNECT)
    , _autoReconnectInterval(DEFAULT_AUTORECONNECT_INTERVAL_MS)
    , _socket(new QMQTT::Socket)
    , _autoReconnectTimer(new QMQTT::Timer)
    , _readState(Header)
{
    initialize();
}

#ifndef QT_NO_SSL

QMQTT::Network::Network(bool ssl, bool ignoreSelfSigned, QObject* parent)
    : NetworkInterface(parent)
    , _port(DEFAULT_PORT)
    , _hostName(DEFAULT_HOST_NAME)
    , _autoReconnect(DEFAULT_AUTORECONNECT)
    , _autoReconnectInterval(DEFAULT_AUTORECONNECT_INTERVAL_MS)
    , _socket(ssl ?
        static_cast<QMQTT::SocketInterface *>(new QMQTT::SslSocket(ignoreSelfSigned)) :
        new QMQTT::Socket)
    , _autoReconnectTimer(new QMQTT::Timer)
    , _readState(Header)
{
    initialize();
}

#endif // QT_NO_SSL

QMQTT::Network::Network(SocketInterface* socketInterface, TimerInterface* timerInterface,
                        QObject* parent)
    : NetworkInterface(parent)
    , _port(DEFAULT_PORT)
    , _host(DEFAULT_HOST)
    , _autoReconnect(DEFAULT_AUTORECONNECT)
    , _autoReconnectInterval(DEFAULT_AUTORECONNECT_INTERVAL_MS)
    , _socket(socketInterface)
    , _autoReconnectTimer(timerInterface)
    , _readState(Header)
{
    initialize();
}

void QMQTT::Network::initialize()
{
    _socket->setParent(this);
    _autoReconnectTimer->setParent(this);
    _autoReconnectTimer->setSingleShot(true);
    _autoReconnectTimer->setInterval(_autoReconnectInterval);

    QObject::connect(_socket, &SocketInterface::connected, this, &Network::connected);
    QObject::connect(_socket, &SocketInterface::disconnected, this, &Network::onDisconnected);
    QObject::connect(_socket->ioDevice(), &QIODevice::readyRead, this, &Network::onSocketReadReady);
    QObject::connect(
        _autoReconnectTimer, &TimerInterface::timeout,
        this, static_cast<void (Network::*)()>(&Network::connectToHost));
    QObject::connect(_socket,
        static_cast<void (SocketInterface::*)(QAbstractSocket::SocketError)>(&SocketInterface::error),
        this, &Network::onSocketError);
}

QMQTT::Network::~Network()
{
}

bool QMQTT::Network::isConnectedToHost() const
{
    return _socket->state() == QAbstractSocket::ConnectedState;
}

void QMQTT::Network::connectToHost(const QHostAddress& host, const quint16 port)
{
    _host = host;
    _hostName.clear();
    _port = port;
    connectToHost();
}

void QMQTT::Network::connectToHost(const QString& hostName, const quint16 port)
{
    _hostName = hostName;
    _port = port;
    connectToHost();
}

void QMQTT::Network::connectToHost()
{
    _readState = Header;
    if (_hostName.isEmpty())
    {
        _socket->connectToHost(_host, _port);
    }
    else
    {
        _socket->connectToHost(_hostName, _port);
    }
}

void QMQTT::Network::onSocketError(QAbstractSocket::SocketError socketError)
{
    emit error(socketError);
    if(_autoReconnect)
    {
        _autoReconnectTimer->start();
    }
}

void QMQTT::Network::sendFrame(Frame& frame)
{
    if(_socket->state() == QAbstractSocket::ConnectedState)
    {
        QDataStream out(_socket->ioDevice());
        frame.write(out);
    }
}

void QMQTT::Network::disconnectFromHost()
{
    _socket->disconnectFromHost();
}

QAbstractSocket::SocketState QMQTT::Network::state() const
{
    return _socket->state();
}

bool QMQTT::Network::autoReconnect() const
{
    return _autoReconnect;
}

void QMQTT::Network::setAutoReconnect(const bool autoReconnect)
{
    _autoReconnect = autoReconnect;
}

int QMQTT::Network::autoReconnectInterval() const
{
    return _autoReconnectInterval;
}

void QMQTT::Network::setAutoReconnectInterval(const int autoReconnectInterval)
{
    _autoReconnectInterval = autoReconnectInterval;
}

void QMQTT::Network::onSocketReadReady()
{
    QIODevice *ioDevice = _socket->ioDevice();
    QByteArray data = ioDevice->read(ioDevice->bytesAvailable());
    foreach(char byte, data) {
        switch (_readState) {
        case Header:
            _header = static_cast<quint8>(byte);
            _readState = Length;
            _length = 0;
            _shift = 0;
            break;
        case Length:
            _length |= (byte & 0x7F) << _shift;
            _shift += 7;
            if ((byte & 0x80) != 0)
                break;
            if (_length == 0) {
                Frame frame(_header, _data);
                emit received(frame);
                _readState = Header;
                break;
            }
            _readState = PayLoad;
            _data.clear();
            break;
        case PayLoad:
            _data.append(byte);
            --_length;
            if (_length > 0)
                break;
            Frame frame(_header, _data);
            emit received(frame);
            _readState = Header;
            break;
        }
    }
}

void QMQTT::Network::onDisconnected()
{
    emit disconnected();
    if(_autoReconnect)
    {
        _autoReconnectTimer->start();
    }
}
