/**
                          __  _               __  _  _       
                         / _|(_)             / _|(_)| |      
       ___  ___   _ __  | |_  _   __ _      | |_  _ | |  ___ 
      / __|/ _ \ | '_ \ |  _|| | / _` |     |  _|| || | / _ \
     | (__| (_) || | | || |  | || (_| |     | |  | || ||  __/
      \___|\___/ |_| |_||_|  |_| \__, |     |_|  |_||_| \___|
                                  __/ |                      
                                 |___/                                         
    @authors M.Rochat & E.Dutruy (Co-TL GS 23-24)
    @date 06-02-2024
    @brief config file to setup GUI
*/

#ifndef SETUP_H
#define SETUP_H

#include "DataView.h"
#include "TelemetryView.h"
#include "GSManagerView.h"

// ----------------------------- Setup Views -----------------------------------
using LeftView = DataView;
using MiddleView = TelemetryView;
using RightView = GSManagerView;


// ----------------------------- MainWindow setup ------------------------------
namespace mws {
    const QString title = "Firehorn Project Ground Control Station";
    const int x = 100;
    const int y = 100;
    const int width = 800;
    const int height = 600;
    const int middleSectionWidth = 40; // % left and right  will be (100-x)/2
} // namespace mws


// ----------------------------- Colour ----------------------------------------
namespace col {
    QString background = "background-color: #696a6e";
} // namespace col


#endif /* SETUP_H */
