/*!
 *      ______ _____ _______      _____  _____     ___   ___ ___   ___
 *     |  ____|  __ \__   __|    / ____|/ ____|   |__ \ / _ \__ \ / _ \
 *     | |__  | |__) | | |      | |  __| (___        ) | | | | ) | | | |
 *     |  __| |  _  /  | |      | | |_ |\___ \      / /| | | |/ /| | | |
 *     | |____| | \ \  | |      | |__| |____) |    / /_| |_| / /_| |_| |
 *     |______|_|  \_\ |_|       \_____|_____/    |____|\___/____|\___/
 *
 * \file FancyGUI.cpp
 *
 * \brief Ground Support Equipment Transceiver
 *
 * \author      ISOZ Lionel, KESKE Cem - EPFL EL BA3
 * \date        02.04.2020
 *   <img src="bellalui.png" width=600>
 */

#include <memory>
#include <thread>
#include <chrono>
#include <QApplication>
#include <connector.h>
#include <Worker.h>
#include <propgsgui.h>
#include <QDebug>



int main(int argc, char **argv) {

    //set up everything
    // Test Test Ok it is a test1
    //std::shared_ptr<Connector> connector(std::make_shared<Connector>());

    QApplication app(argc, argv);

    qDebug()<<"here?";
    PropGSGUI propGsgui;

    //run all threads
    //std::thread t1(&Worker::mainRoutine, Worker(connector));

    //std::this_thread::sleep_for(std::chrono::milliseconds(300));
    qDebug()<<"here?";
    propGsgui.show();

    //std::this_thread::sleep_for(std::chrono::milliseconds(300));

    app.exec();

    std::cout<<"hello"<<std::endl;

    //std::this_thread::sleep_for(std::chrono::milliseconds(300));

    //t1.join();

    //std::this_thread::sleep_for(std::chrono::milliseconds(300));
    
    return 0;
}
