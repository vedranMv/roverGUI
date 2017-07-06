#ifndef ROVERINTERFACE_H
#define ROVERINTERFACE_H

#include <sstream>
#include <iostream>

const char libName[][20] =
{
    {"ESP8266"},
    {"Radar"},
    {"Engines"},
    {"MPU9250"},
    {"DataStream"},
    {"Platform"},
    {"EventLog"},
    {"Task scheduler"}
};

//  ID of this device when exchanging messages
const char DEVICE_ID[] = {"V125"};

//  Code expected by the client to initiate reboot of any module
#define REBOOT_CODE 0x17

/**     TCP port definitions for standard data streams   */
/*
 * Telemetry data stream
 * Telemetry includes bidirectional stream starting from rover to server containing
 * sensor data, time reference, health report etc. On received frame from rover
 * server replies with "ACK\r\n"
 * Server expects telemetry stream on TCP port 2700
 */
#define P_TELEMETRY     2700
/*
 * Commands data stream
 * This stream brings commands from server to rover. On received frame from
 * server rover replies "ACK\r\n"
 * Server expects commands stream on TCP port 2701
 */
#define P_COMMANDS      2701

///-----------------------------------------------------------------------------
///         ESP8266 task IDs
///-----------------------------------------------------------------------------
#define ESP_UID             0
/// Definitions of ServiceID for service offered by this module
//  Start/stop TCP server
//  Args: enable(1B)|port(2B)
#define ESP_T_TCPSERV       0
//  Open TCP connection to server
//  Args: KeepAlive(1B)|IPaddress(7B-15B)|port(2B)|socketID(1B)
#define ESP_T_CONNTCP       1
//  Send data through socket with specific ID
//  Args: socketID(1B)|message
#define ESP_T_SENDTCP       2
//  Receive data from specific socket ID
//  Args: socketID(1B)
#define ESP_T_RECVSOCK      3
//  Close socket with specific ID
//  Args: socketID(1B)
#define ESP_T_CLOSETCP      4

///-----------------------------------------------------------------------------
///         Radar task IDs
///-----------------------------------------------------------------------------
//  Unique identifier of this module as registered in task scheduler
#define RADAR_UID           1
/// Definitions of ServiceID for service offered by this module
//  Initiate radar scan
//  Args: scanType(1B)
#define RADAR_SCAN          0
//  Set horizontal angle for radar
//  Args: angle(4B)
#define RADAR_SETH          2
//  Set vertical angle of radar
//  Args: angle(4B)
#define RADAR_SETV          3

///-----------------------------------------------------------------------------
///         Engine task IDs
///-----------------------------------------------------------------------------
//  Unique identifier of this module as registered in task scheduler
#define ENGINES_UID         2
/// Definitions of ServiceID for service offered by this module
//  Move rover in a basic direction for a given distance or angle
//  Args: direction(uint8_t)|length-or-angle(4B float)|blocking(1B)
#define ENG_MOVE_ENG        0
//  Move rover along a circular path given by
//  Args: distance(4B float)|angle(4B float)|small-radius(4B float)
#define ENG_MOVE_ARC        1
//  Args: direction(uint8_t)|leftPercent(4B float)|rightPercent(4B float)
#define ENG_MOVE_PERC       2

///-----------------------------------------------------------------------------
///         Inertial unit(MPU9250) task IDs
///-----------------------------------------------------------------------------
#define MPU_UID             3

#define MPU_LISTEN          0   //  Enable interrupt to receive new sensor data
#define MPU_GET_DATA        1   //  Pass sensor data to user-defined hook
#define MPU_REBOOT          2   //  Reboot sensor moudle

///-----------------------------------------------------------------------------
///         Data stream task IDs
///-----------------------------------------------------------------------------
#define DATAS_UID       4
//  Definitions of ServiceID for service offered by this module
#define DATAS_T_KA      0   //  Keep alive socket

///-----------------------------------------------------------------------------
///         Platform task IDs
///-----------------------------------------------------------------------------
#define PLAT_UID            5
//  Definitions of ServiceID for service offered by this module
#define PLAT_TEL            0   //  Send telemetry data frame
#define PLAT_REBOOT         1   //  Reboot the system

///-----------------------------------------------------------------------------
///         EventLog task IDs
///-----------------------------------------------------------------------------
#define EVLOG_UID           6
//  Definitions of ServiceID for service offered by this module
#define EVLOG_DROP          0   //  Drop all data in the event log

///-----------------------------------------------------------------------------
///         Task scheduler task IDs
///-----------------------------------------------------------------------------
#define TASKSCHED_UID       7


/**
 * Events that modules can transmit
 * Priority inversion event can only be set by EventLogger and it occurs when
 * a module has emitted a higher priority event (such as EVENT_ERROR) followed by
 * a lower priority event (such as EVENT_OK) without going through process of
 * reinitialization.
 */
enum Events {EVENT_UNINITIALIZED,   //Module is not yet initialized
             EVENT_STARTUP,         //Module is in startup sequence
             EVENT_INITIALIZED,     //Module is fully initialized
             EVENT_OK,              //Module performed request
             EVENT_HANG,            //Module is hanging in communication with HW
             EVENT_ERROR,           //Module experienced error
             EVENT_PRIOINV };       //Priority inversion event

//  Event string description for GUI
/*const char events[][30] =
{
    {"EVENT_UNINITIALIZED"},   //Module is not yet initialized
    {"EVENT_STARTUP"},         //Module is in startup sequence
    {"EVENT_INITIALIZED"},     //Module is fully initialized
    {"EVENT_OK"},              //Module performed request
    {"EVENT_HANG"},            //Module is hanging in communication with HW
    {"EVENT_ERROR"},           //Module experienced error
    {"EVENT_PRIOINV"}          //Priority inversion in module
};*/
const char events[][30] =
{
    {"UNINITIALIZED"},   //Module is not yet initialized
    {"STARTUP"},         //Module is in startup sequence
    {"INITIALIZED"},     //Module is fully initialized
    {"OK"},              //Module performed request
    {"HANG"},            //Module is hanging in communication with HW
    {"ERROR"},           //Module experienced error
    {"PRIOINV"}          //Priority inversion in module
};


/**
 * @brief Construct new request from given parameters in a format MCU can parse
 * @param req
 * @param uid
 * @param task
 * @param time
 * @param repeats
 */
void MakeRequest(uint8_t *req, uint16_t uid, uint16_t task, int32_t time, int32_t repeats);
/**
 * @brief Append arguments to the previously constructed request
 * @note Has to be called even if there are no arguments (argLen=0)
 * @param req
 * @param reqLen
 * @param args
 * @param argLen
 */
void AppendArgs(uint8_t *req, uint16_t *reqLen, void *args, uint16_t argLen);

#endif // ROVERINTERFACE_H
