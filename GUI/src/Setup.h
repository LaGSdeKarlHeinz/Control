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
#include "ValveControlView.h"

// ----------------------------- Setup Views -----------------------------------
using LeftView = TelemetryView;
using MiddleView = ValveControlView;
using RightView = GSManagerView;


// ----------------------------- MainWindow setup ------------------------------
namespace mws {
    const QString title = "Firehorn Project Ground Control Station";
    const int x = 100;
    const int y = 100;
    const int width = 800;
    const int height = 600;
    const int middleSectionWidth = 50; // % left and right  will be (100-x)/2
    const int sideWidth = (100-middleSectionWidth)/2;
} // namespace mws


// ----------------------------- Colour ----------------------------------------
namespace col {
    inline QString backgroundColorCode = "#161A36"; 
    inline QString primary = "#B8C196";
    inline QString secondary = "#BDB979"; 
    inline QString accent = "#F5251A"; 
    inline QString complementary = "#457069";
    inline QString complementaryLighter = "#538078";

    inline QString background() {return "background-color: " + backgroundColorCode + ";";}
    inline  QString defaultCardStyle(QString id) {return QString(R"(
        #%3 {
        background: qradialgradient(cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 %1, stop:0.95 %2);
        border-radius: 10%;
        border-width: 2px;
        border-color: #B8C196;
        }
        #child {
            color: #B8C196;
            background: transparent;
        }
        )")          
        .arg(col::backgroundColorCode)
        .arg("rgba(30, 35, 69, 225)")
        .arg(id) ;}
} // namespace col


#endif /* SETUP_H */
