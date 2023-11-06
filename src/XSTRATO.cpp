/*!
 *
 * \file XSTRATO.cpp
 *
 * \brief XSTRATO Software GS
 *
 *  The goal of this program is to receive telemetry and Image from
 *  Xstrato up in stratosphere
 *
 *
 * \author      ISOZ Lionel - EPFL EL MA4
 * \date        12.04.2023
 */

#include <iostream>
#include <XstratoWindow.h>
#include <QApplication>
#include <thread>

//#include "../Capsule/src/capsule.h"
#include <capsule.h>

/*void myfunc(int* x) {
    while(true) {
        *x = *x + 1;
        std::cout << "thread running val: " << *x << std::endl;
        //std::this_thread::sleep_for(std::chrono::milliseconds (1));
    }
}

void handleRxPacketDevice1(uint8_t packetId, uint8_t *dataIn, uint32_t len) {

}*/

int main(int argc, char** argv) {

    //CapsuleStatic device1(handleRxPacketDevice1);
    //device1.getCodedLen(34);

    QApplication app(argc, argv); // QWidget: Must construct a QApplication before a QWidget

//    int x = 3;

    XstratoWindow xstratoWindow;

   // std::thread t1(&myfunc, &x);

    xstratoWindow.setWindowState(Qt::WindowMaximized);

    xstratoWindow.show();

    app.exec();

   // t1.join();

    std::cout << "program running" << std::endl;


    return 0;
}