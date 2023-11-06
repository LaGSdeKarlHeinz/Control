///////////////////////////////////////////////////////////////////////////////////////
//
//                                                                                                                                                            
//	RRRRRRRRRRRRRRRRR   FFFFFFFFFFFFFFFFFFFFFFBBBBBBBBBBBBBBBBB           GGGGGGGGGGGGG
//	R::::::::::::::::R  F::::::::::::::::::::FB::::::::::::::::B       GGG::::::::::::G
//	R::::::RRRRRR:::::R F::::::::::::::::::::FB::::::BBBBBB:::::B    GG:::::::::::::::G
//	RR:::::R     R:::::RFF::::::FFFFFFFFF::::FBB:::::B     B:::::B  G:::::GGGGGGGG::::G
//	  R::::R     R:::::R  F:::::F       FFFFFF  B::::B     B:::::B G:::::G       GGGGGG
//	  R::::R     R:::::R  F:::::F               B::::B     B:::::BG:::::G              
//	  R::::RRRRRR:::::R   F::::::FFFFFFFFFF     B::::BBBBBB:::::B G:u:::G              
//	  R::::o::::::::RR    F:::::::::::::::F     B:::::::::::::BB  G:::::G    GGGGGGGGGG
//	  R::::RRRRRR:::::R   F::::::a::::::::F     B::::BBBBBB:::::B G:::::G    G::::::::G
//	  R::::R     R:::::R  F::::::FFFFFFFFFF     B::::B     B:::::BG:::::G    GGGGG::::G
//	  R::::R     R:::::R  F:::::F               B::::B     B:::::BG:::::G        G::::G
//	  R::::R     R:::::R  F:::::F               B::::B     B:::::B G:::::G       G::::G
//	RR:::::R     R:::::RFF:::::::FF           BB:::::BBBBBB::::::B  G:::::GGGGGGGG::::G
//	R::::::R     R:::::RF::::::::FF           B::::::s::::::::::B    GG:::::::::::::::G
//	R::::::R     R:::::RF::::::::FF           B::::::::::::::::B       GGG::::::GGG:::G
//	RRRRRRRR     RRRRRRRFFFFFFFFFFF           BBBBBBBBBBBBBBBBB           GGGGGG   GGGG
//                                                                                                                                                                   
//  Interface header file for communication protocol 
//
//  EPFL Rocket Team - Nordend Project 2023
//
//  Charlotte Heibig & Lionel Isoz & Yohan Hadji & Iacopo Sprenger
//  26.07.2023 
///////////////////////////////////////////////////////////////////////////////////////
#ifndef PACKET_H
#define PACKET_H

#include <stdint.h> // for uint8_t
#include <stddef.h> // for size_t
#include <stdbool.h>


#define ERT_PREFIX 				((uint32_t) ('R' << 24 | 'F' << 16 | 'B' << 8 | 'G'))

#define ACTIVE 					0xAC // 0xAC for ACtive 
#define INACTIVE 				0xDE // 0xDE for DEsactive

#define IGNITION_CODE 	0x42  // "66"  // in order_value


///////////////////////////////////////////////////////////////////////////////////////

// /!\ Flash again the MCU Mainboard
enum CAPSULE_ID {
	//////////////////////////////////
    // Rocket & GSE
    AV_TELEMETRY = 8,
    GSE_TELEMETRY,
	GS_CMD, // uplink from GS
	//////////////////////////////////
	// Tracker
	BINOC_ATTITUDE,
	BINOC_POSITION,
	BINOC_STATUS,
	BINOC_GLOBAL_STATUS,
	//////////////////////////////////
	TRACKER_CMD,
	//////////////////////////////////
	CALIBRATE_TELEMETRY
};

enum CMD_ID {
	AV_CMD_SERVO_N2O = 3,
    AV_CMD_SERVO_FUEL,
	AV_CMD_VENT_N2O,
	AV_CMD_VENT_FUEL,
	GSE_CMD_FILLING_N2O,
    GSE_CMD_VENT,
	GSE_CMD_DISCONNECT,
	AV_CMD_ARM,
	AV_CMD_PRESSURIZE,
	AV_CMD_ABORT,
	AV_CMD_RECOVER,
	AV_CMD_IGNITION,
	AV_CMD_MAN_PRESSURE
};


/////////////////////////////////////////////////////////////////
// Here is a template for writing new packet structures 
typedef struct __attribute__((__packed__)) {
	uint8_t data1;
	uint8_t data2;
	uint16_t data3;
} PacketTemplate;
#ifdef __cplusplus
const uint32_t packetTemplateSize = sizeof(PacketTemplate);
#endif

/////////////////////////////////////////////////////////////////
// ---------------------- AV PACKETS ------------------------  // 
/////////////////////////////////////////////////////////////////


typedef struct __attribute__((__packed__)) {
	uint8_t servo_N2O;
	uint8_t servo_fuel;
	uint8_t vent_N2O;
	uint8_t vent_fuel;
	uint8_t pressurize;
	uint8_t purge;
	uint8_t reserve;
} engine_state_t;
#ifdef __cplusplus
const uint32_t engine_state_size = sizeof(engine_state_t);
#endif

// AV UPLINK PACKET


typedef struct __attribute__((__packed__)) {
	uint32_t prefix;
	uint8_t order_id; // from CMD_ID
	uint8_t order_value;  // only ACTIVE or INACTIVE  	254 other possibilities unconsidered
} av_uplink_t;
#ifdef __cplusplus
const size_t av_uplink_size = sizeof(av_uplink_t);
#endif

// AV DOWNLINK PACKET

typedef struct __attribute__((__packed__)) {
	uint32_t prefix;
    uint32_t packet_nbr;
	uint32_t timestamp;
	// float    acc_z; // g
	// float    acc_hg_z; // g (high g)
	// float    baro_press; //hPa
	// float    baro_temp; //C
	// float    baro_press_r; //hPa
	float	 gnss_lon; //dd.dddddd
	float	 gnss_lat; //dd.dddddd
	float	 gnss_alt; //m
	float	 gnss_lon_r; //dd.dddddd
	float	 gnss_lat_r; //dd.dddddd
	float	 gnss_alt_r; //m
	float 	 gnss_vertical_speed; //m/s
	float    N2O_pressure;
    float    tank_temp;
    float    fuel_pressure;
    float    chamber_pressure;
	uint8_t  av_state; //enum
	engine_state_t engine_state; //binaries states of the valves
    //AV_cmd_status engine_state;
	uint8_t  gnss_choice;
} av_downlink_t;
#ifdef __cplusplus
const uint32_t av_downlink_size = sizeof(av_downlink_t);
#endif

typedef enum {
	MIAOU_RF = 0x65,
	MIAOU_GNSS = 0x69
}miaou_transfer_type;

typedef struct __attribute__((__packed__)) {
	float	longitude;
	float	latitude;
	float	altitude;
	float   speed;
	float 	hdop;
	uint32_t time;
} av_miaou_gnss_t;
#ifdef __cplusplus
const size_t av_miaou_gnss_size = sizeof(av_miaou_gnss_t);
#endif


//CAUTION COPIED FROM od/data_types.h
typedef enum control_state_copy
{
	/** Wait for arming or calibration */
	AV_CONTROL_IDLE,
	/** Calibrate sensors and actuators */
	AV_CONTROL_CALIBRATION,
	/** Manual Servo movement */
	AV_CONTROL_MANUAL_OPERATION,
	/** System is armed and ready to pressure*/
	AV_CONTROL_ARMED,
	/** system is pressured */
	AV_CONTROL_PRESSURED,
	/** fire igniter */
	AV_CONTROL_IGNITER,
	/** partially open valves*/
	AV_CONTROL_IGNITION,
	/** fully open valves */
	AV_CONTROL_THRUST,
	/** close ethanol valve */
	AV_CONTROL_SHUTDOWN,
	/** glide */
	AV_CONTROL_GLIDE,
	/** Descent */
	AV_CONTROL_DESCENT,
	/** Safe state */
	AV_CONTROL_SAFE,
	/** system error*/
	AV_CONTROL_ERROR,
	/** User triggered abort */
	AV_CONTROL_ABORT
} control_state_copy_t;

enum FLIGHTMODE {
  INITIALIZE_MODE = 0, 
  READYSTEADY_MODE,
  CALIBRATION_MODE,
  MANUAL_MODE,
  ARMED_MODE,
  PRESSURED_MODE,
  IGNITER_MODE,
  IGNITION_MODE,
  THRUST_MODE,
  SHUTDOWN_MODE, 
  ASCENT_MODE, 
  DESCENT_MODE, 
  GLIDING_MODE,
  ABORT_MODE
};

/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
////////// FROM HERE, GS stuff, please don't touch //////////////
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////
// ---------------------- GSE PACKETS ---------------------- // 

typedef struct __attribute__((__packed__)) {
	uint8_t fillingN2O;
	uint8_t vent;
} GSE_cmd_status;
#ifdef __cplusplus
const uint32_t GSE_cmd_status_size = sizeof(GSE_cmd_status);
#endif

typedef struct __attribute__((__packed__)) {
	float tankPressure;
	float tankTemperature;
	float fillingPressure;
    GSE_cmd_status status;
	bool disconnectActive;
	int32_t loadcellRaw;
} PacketGSE_downlink;
#ifdef __cplusplus
const uint32_t packetGSE_downlink_size = sizeof(PacketGSE_downlink);
#endif

/////////////////////////////////////////////////////////////////
// ---------------------- BINOC PACKETS ---------------------- // 

typedef struct __attribute__((__packed__)) {
	float azm;
	float elv;
} PacketBinocAttitude;
#ifdef __cplusplus
const uint32_t packetBinocAttitudeSize = sizeof(PacketBinocAttitude);
#endif

typedef struct __attribute__((__packed__)) {
	float lon;
	float lat;
	float alt;
} PacketBinocPosition;
#ifdef __cplusplus
const uint32_t packetBinocPositionSize = sizeof(PacketBinocPosition);
#endif

typedef struct __attribute__((__packed__)) {
	bool isInView;
	bool isCalibrated;
} PacketBinocStatus;
#ifdef __cplusplus
const uint32_t packetBinocStatusSize = sizeof(PacketBinocStatus);
#endif

typedef struct __attribute__((__packed__)) {
	PacketBinocAttitude attitude;
    PacketBinocPosition position;
    PacketBinocStatus status;
} PacketBinocGlobalStatus;
#ifdef __cplusplus
const uint32_t packetBinocGlobalStatusSize = sizeof(PacketBinocGlobalStatus);
#endif

/////////////////////////////////////////////////////////////////
// ---------------------- TRACKER PACKETS ---------------------- // 

typedef struct __attribute__((__packed__)) {
	float azm;
	float elv;
	int mode;
	float cutoffFreq;
	unsigned maxTimeWindow;
	unsigned timeStamp;
} PacketTrackerCmd;
#ifdef __cplusplus
const uint32_t packetTrackerCmdSize = sizeof(PacketTrackerCmd);
#endif

#endif /* PACKET_H */
