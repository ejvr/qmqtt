/*
 * example.cpp - qmqtt example
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
#include <QCoreApplication>
#include <QDebug>
#include <qmqtt.h>
#include <QSslConfiguration>
#include <QSslError>
#include <QTimer>

const QHostAddress EXAMPLE_HOST = QHostAddress::LocalHost;
const quint16 EXAMPLE_PORT = 1883;
const QString EXAMPLE_TOPIC = "qmqtt/exampletopic";

int main(int argc, char** argv)
{
    QCoreApplication app(argc, argv);

    QMQTT::Client publisher(QHostAddress::LocalHost, 1883);
    // QSslConfiguration sslConfig = QSslConfiguration::defaultConfiguration();
    // QMQTT::Client publisher("localhost", 8883, sslConfig);
    // QMQTT::Client publisher("ws://localhost:9001", "origin", QWebSocketProtocol::VersionLatest);
    QTimer timer;
    int number = 0;
    QObject::connect(&publisher, &QMQTT::Client::connected, [&] {
        timer.start(1000);
    });
    QObject::connect(&timer, &QTimer::timeout, [&] {
        QMQTT::Message message(number, EXAMPLE_TOPIC,
                               QString("Number is %1").arg(number).toUtf8());
        qDebug() << "Published:" << message.payload();
        publisher.publish(message);
        number++;
        if(number >= 10)
        {
            timer.stop();
            publisher.disconnectFromHost();
        }
    });
    QObject::connect(&publisher, &QMQTT::Client::disconnected, [&] {
        app.quit();
    });
    // QObject::connect(&publisher, &QMQTT::Client::sslErrors, [&](const QList<QSslError> &errors) {
    //     for (QSslError e : errors)
    //     {
    //         auto err = e.error();
    //         qDebug() << e;
    //     }
    //     publisher.ignoreSslErrors();
    // });
    publisher.connectToHost();

    QMQTT::Client subscriber(QHostAddress::LocalHost, 1883);
    QObject::connect(&subscriber, &QMQTT::Client::connected, [&] {
        subscriber.subscribe(EXAMPLE_TOPIC, 0);
    });
    QObject::connect(&subscriber, &QMQTT::Client::received, [&](const QMQTT::Message &message) {
        qDebug() << "Received:" << message.payload();
    });
    subscriber.connectToHost();

    return app.exec();
}
