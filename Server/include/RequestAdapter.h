#include "../ERT_RF_Protocol_Interface/PacketDefinition.h"
#ifndef REQUESTADAPTER_H
#define REQUESTADAPTER_H

av_uplink_t createUplinkPacketFromRequest(GUI_FIELD field, uint8_t order_value);
uint8_t getOrderIdFromGui(GUI_FIELD f);

#endif // REQUESTADAPTER_H 