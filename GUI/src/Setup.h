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
namespace mws
{
    const QString title = "Firehorn Project Ground Control Station";
    const int x = 100;
    const int y = 100;
    const int width = 800;
    const int height = 600;
    const int middleSectionWidth = 50; // % left and right  will be (100-x)/2
    const int sideWidth = (100 - middleSectionWidth) / 2;
} // namespace mws

namespace network
{
    const QString serverIP = "127.0.0.1";
    const int serverPort = 12345;
}
// ----------------------------- Colour ----------------------------------------
namespace col
{
    inline QString backgroundColorCode = "#161A36";
    inline QString primary = "#B8C196";
    inline QString secondary = "#BDB979";
    inline QString accent = "#F5251A";
    inline QString complementary = "#457069";
    inline QString complementaryLighter = "#538078";

    inline QString background() { return "background-color: " + backgroundColorCode + ";"; }
    inline QString defaultCardStyle(QString id) { return QString(R"(
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
                                                      .arg(id); }
} // namespace col

#endif /* SETUP_H */

#ifndef ENUM_GUI_FIELD_UTIL
#define ENUM_GUI_FIELD_UTIL

// Field naming

namespace fieldUtil
{
    inline QString enumToFieldName(GUI_FIELD field)
    {
        QString name;
        switch (field)
        {
        case IGNITER_LOX:
            name = "IGNITER LOX";
            break;
        case IGNITER_FUEL:
            name = "IGNITER FUEL";
            break;
        case MAIN_LOX:
            name = "MAIN LOX";
            break;
        case MAIN_FUEL:
            name = "MAIN FUEL";
            break;
        case VENT_LOX:
            name = "VENT LOX";
            break;
        case VENT_FUEL:
            name = "VENT FUEL";
            break;
        case ORDER_ID:
            name = "ORDER ID";
            break;
        case ORDER_VALUE:
            name = "ORDER VALUE";
            break;
        case PACKET_NBR:
            name = "PACKET NBR";
            break;
        case TIMESTAMP:
            name = "TIMESTAMP";
            break;
        case GNSS_LON:
            name = "GNSS LON";
            break;
        case GNSS_LAT:
            name = "GNSS LAT";
            break;
        case GNSS_ALT:
            name = "GNSS ALT";
            break;
        case GNSS_LON_R:
            name = "GNSS LON R";
            break;
        case GNSS_LAT_R:
            name = "GNSS LAT R";
            break;
        case GNSS_ALT_R:
            name = "GNSS ALT R";
            break;
        case GNSS_VERTICAL_SPEED:
            name = "GNSS VERTICAL SPEED";
            break;
        case N2_PRESSURE:
            name = "N2 PRESSURE";
            break;
        case FUEL_PRESSURE:
            name = "FUEL PRESSURE";
            break;
        case LOX_PRESSURE:
            name = "LOX PRESSURE";
            break;
        case FUEL_LEVEL:
            name = "FUEL LEVEL";
            break;
        case LOX_LEVEL:
            name = "LOX LEVEL";
            break;
        case ENGINE_TEMP:
            name = "ENGINE TEMP";
            break;
        case IGNITER_PRESSURE:
            name = "IGNITER PRESSURE";
            break;
        case LOX_INJ_PRESSURE:
            name = "LOX INJ PRESSURE";
            break;
        case FUEL_INJ_PRESSURE:
            name = "FUEL INJ PRESSURE";
            break;
        case CHAMBER_PRESSURE:
            name = "CHAMBER PRESSURE";
            break;
        case AV_STATE:
            name = "AV STATE";
            break;
        case GNSS_CHOICE:
            name = "GNSS CHOICE";
            break;
        case FILLINGN2O:
            name = "FILLINGN2O";
            break;
        case VENT_GSE:
            name = "VENT GSE";
            break;
        case TANK_PRESSURE:
            name = "TANK PRESSURE";
            break;
        case TANK_TEMPERATURE:
            name = "TANK TEMPERATURE";
            break;
        case FILLING_PRESSURE:
            name = "FILLING PRESSURE";
            break;
        case DISCONNECT_ACTIVE:
            name = "DISCONNECT ACTIVE";
            break;
        case LOADCELL_RAW:
            name = "LOADCELL RAW";
            break;
        case ENGINE_STATE:
            name = "ENGINE STATE";
            break;
        case GSE_VENT:
            name = "GSE VENT";
            break;
        case GSE_CMD_STATUS:
            name = "GSE CMD STATUS";
            break;
        default:
            name = "UNKNOWN";
            break;
        }
        return name;
    }

    inline GUI_FIELD fieldNameToEnum(const QString& fieldName)
    {
        if (fieldName == "IGNITER LOX")
            return IGNITER_LOX;
        else if (fieldName == "IGNITER FUEL")
            return IGNITER_FUEL;
        else if (fieldName == "MAIN LOX")
            return MAIN_LOX;
        else if (fieldName == "MAIN FUEL")
            return MAIN_FUEL;
        else if (fieldName == "VENT LOX")
            return VENT_LOX;
        else if (fieldName == "VENT FUEL")
            return VENT_FUEL;
        else if (fieldName == "ORDER ID")
            return ORDER_ID;
        else if (fieldName == "ORDER VALUE")
            return ORDER_VALUE;
        else if (fieldName == "PACKET NBR")
            return PACKET_NBR;
        else if (fieldName == "TIMESTAMP")
            return TIMESTAMP;
        else if (fieldName == "GNSS LON")
            return GNSS_LON;
        else if (fieldName == "GNSS LAT")
            return GNSS_LAT;
        else if (fieldName == "GNSS ALT")
            return GNSS_ALT;
        else if (fieldName == "GNSS LON R")
            return GNSS_LON_R;
        else if (fieldName == "GNSS LAT R")
            return GNSS_LAT_R;
        else if (fieldName == "GNSS ALT R")
            return GNSS_ALT_R;
        else if (fieldName == "GNSS VERTICAL SPEED")
            return GNSS_VERTICAL_SPEED;
        else if (fieldName == "N2 PRESSURE")
            return N2_PRESSURE;
        else if (fieldName == "FUEL PRESSURE")
            return FUEL_PRESSURE;
        else if (fieldName == "LOX PRESSURE")
            return LOX_PRESSURE;
        else if (fieldName == "FUEL LEVEL")
            return FUEL_LEVEL;
        else if (fieldName == "LOX LEVEL")
            return LOX_LEVEL;
        else if (fieldName == "ENGINE TEMP")
            return ENGINE_TEMP;
        else if (fieldName == "IGNITER PRESSURE")
            return IGNITER_PRESSURE;
        else if (fieldName == "LOX INJ PRESSURE")
            return LOX_INJ_PRESSURE;
        else if (fieldName == "FUEL INJ PRESSURE")
            return FUEL_INJ_PRESSURE;
        else if (fieldName == "CHAMBER PRESSURE")
            return CHAMBER_PRESSURE;
        else if (fieldName == "AV STATE")
            return AV_STATE;
        else if (fieldName == "GNSS CHOICE")
            return GNSS_CHOICE;
        else if (fieldName == "FILLINGN2O")
            return FILLINGN2O;
        else if (fieldName == "VENT GSE")
            return VENT_GSE;
        else if (fieldName == "TANK PRESSURE")
            return TANK_PRESSURE;
        else if (fieldName == "TANK TEMPERATURE")
            return TANK_TEMPERATURE;
        else if (fieldName == "FILLING PRESSURE")
            return FILLING_PRESSURE;
        else if (fieldName == "DISCONNECT ACTIVE")
            return DISCONNECT_ACTIVE;
        else if (fieldName == "LOADCELL RAW")
            return LOADCELL_RAW;
        else if (fieldName == "ENGINE STATE")
            return ENGINE_STATE;
        else if (fieldName == "GSE VENT")
            return GSE_VENT;
        else if (fieldName == "GSE CMD STATUS")
            return GSE_CMD_STATUS;
        else
            return UNKNOWN;
    }

}



#endif /* ENUM_GUI_FIELD_UTIL */
