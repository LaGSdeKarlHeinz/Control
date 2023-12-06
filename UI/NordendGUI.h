/*!
 * \file Nordend_GUI.h
 *
 * \brief Nordend_GUI module interface
 *
 * \author      ISOZ Lionel - EPFL EL MA4
 * \date        11.07.2023	
 */

#ifndef Nordend_GUI_H
#define Nordend_GUI_H

#include <QMainWindow>
#include <QSerialPort>
#include "../Capsule/src/capsule.h"
#include "../ERT_RF_Protocol_Interface/PacketDefinition.h"
#include <fstream>
#include <QPushButton> // valve function
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui { class nordend; } // named of object "QMainWindow" in ui file
QT_END_NAMESPACE

class NordendGUI: public QMainWindow {
    Q_OBJECT
public:
    NordendGUI();

    virtual ~NordendGUI();

public slots:
    void readSerialData();
    void on_open_serial_pressed();
    void on_close_serial_pressed();
    void on_abort_cmd_pressed();
    void on_recover_cmd_pressed();
    void on_arm_cmd_pressed();
    void on_disarm_cmd_pressed();
    void on_ignition_cmd_pressed();
    void on_disconnect_cmd_pressed();
    void on_pressurization_cmd_pressed();
    void on_reset_valves_pressed();
    void on_debug_button_pressed();
    void on_tare_button_pressed();
    void on_reset_traj_button_pressed();

    // full manual cmd
    void on_cmd_active_pressurization_pressed();
    void on_cmd_inactive_pressurization_pressed();
    void on_cmd_active_N2O_servo_pressed();
    void on_cmd_inactive_N2O_servo_pressed();
    void on_cmd_active_fuel_servo_pressed();
    void on_cmd_inactive_fuel_servo_pressed();
    void on_cmd_active_N2O_vent_pressed();
    void on_cmd_inactive_N2O_vent_pressed();
    void on_cmd_active_fuel_vent_pressed();
    void on_cmd_inactive_fuel_vent_pressed();

    void on_cmd_active_N2O_fill_pressed();
    void on_cmd_inactive_N2O_fill_pressed();
    void on_cmd_active_GSE_vent_pressed();
    void on_cmd_inactive_GSE_vent_pressed();

    void on_GSE_fill_pressed();
    void on_GSE_vent_pressed();
    void on_AV_servo_N2O_pressed();
    void on_AV_servo_fuel_pressed();
    void on_AV_vent_N2O_pressed();
    void on_AV_vent_fuel_pressed();
    void on_AV_pressurization_pressed();


    void on_cmd_new_valve2_active_pressed();
    void on_cmd_new_valve2_active_inactive();
    void on_cmd_new_valve1_active_pressed();
    void on_cmd_new_valve1_active_inactive();


    void serialError();

    void qtimer_callback();

public:
    void handleSerialRxPacket(uint8_t packetId, uint8_t *dataIn, uint32_t len);
private:
    void sendSerialPacket(uint8_t packetId, uint8_t *packet, uint32_t size);
    void set_valve_img(QPushButton * valve, int i, bool normally_open = false, bool horizontal_bar = false);
    void set_valve_light(QLabel * light, bool condition);
    void update_AV_states(FLIGHTMODE state);
    void set_AV_state(QLabel* st_label);//, control_state_copy_t state);

    void send_cmd(uint8_t order_id, uint8_t order_value, QPushButton* button);

    double compute_downrange(double rocket_lat, double rocket_lon);

    void logAVTelemetryPacket(const av_downlink_t* packet);
    void logGSETelemetryPacket(const PacketGSE_downlink *packet);

    void showInfoMessage(QString message);

private:
    Ui::nordend *ui;

    QSerialPort *serial;

    Capsule<NordendGUI> capsule;

    PacketGSE_downlink packetGSE_downlink;

    av_downlink_t packetAV_downlink;

    QTimer * qtimer; // for time since last rx packet
    time_t lastRxTime_AV;
    time_t lastRxTime_GSE;
    time_t start_filling_time;
    time_t disconnect_time;

    QLabel* last_state; // for state table color setting

    // for load cell
    float tare_val;
    float gain_val;
};


#endif //Nordend_GUI_H
