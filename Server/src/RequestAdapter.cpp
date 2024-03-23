#include "../include/RequestAdapter.h"
#include <stdexcept>

av_uplink_t createUplinkPacketFromRequest(GUI_FIELD field, uint8_t order_value) {
    av_uplink_t p;

    p.order_id = getOrderIdFromGui(field);
    p.order_value = order_value;
    return p;
}

uint8_t getOrderIdFromGui(GUI_FIELD f) {
    switch (f)
    {
    case GUI_FIELD::GUI_CMD_CALIBRATE:
        return CMD_ID::AV_CMD_CALIBRATE;
        break;
    case GUI_FIELD::GUI_CMD_RECOVER:
        return CMD_ID::AV_CMD_RECOVER;
        break;
    case GUI_FIELD::GUI_CMD_ARM:
        return CMD_ID::AV_CMD_ARM;
        break;

    case GUI_FIELD::GUI_CMD_IGNITION:
        return CMD_ID::AV_CMD_IGNITION;
        break;

    case GUI_FIELD::GUI_CMD_ABORT:
        return CMD_ID::AV_CMD_ABORT;
        break;

    case GUI_FIELD::GUI_CMD_MANUAL_DEPLOY:
        return CMD_ID::AV_CMD_MANUAL_DEPLOY;
        break;

    case GUI_FIELD::IGNITER_LOX:
        return CMD_ID::AV_CMD_IGNITER_LOX;
        break;
    
    case GUI_FIELD::IGNITER_FUEL:
        return CMD_ID::AV_CMD_IGNITER_FUEL;
        break;

    
    case GUI_FIELD::MAIN_LOX:
        return CMD_ID::AV_CMD_MAIN_LOX;
        break;

    case GUI_FIELD::MAIN_FUEL:
        return CMD_ID::AV_CMD_MAIN_FUEL;
        break;
    
    case GUI_FIELD::VENT_LOX:
        return CMD_ID::AV_CMD_VENT_LOX;
        break;

    case GUI_FIELD::VENT_FUEL:
        return CMD_ID::AV_CMD_VENT_FUEL;
        break;

    case GUI_FIELD::GUI_CMD_PRESSURIZE:
        return CMD_ID::AV_CMD_PRESSURIZE;
        break;  

    case GUI_FIELD::GUI_CMD_FILLING_LOX:
        return CMD_ID::GSE_CMD_FILLING_LOX;
        break;  

    case GUI_FIELD::GUI_CMD_VENT:
        return CMD_ID::GSE_CMD_VENT;
        break;

    case GUI_FIELD::GUI_CMD_DISCONNECT:
        return CMD_ID::GSE_CMD_DISCONNECT;
        break;

    default:
    
        throw std::invalid_argument("Invalid CMD");
        break;
    }
}