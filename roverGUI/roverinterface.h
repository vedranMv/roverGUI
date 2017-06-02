#ifndef ROVERINTERFACE_H
#define ROVERINTERFACE_H


#include <QString>

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
#define ESP_UID         0
/// Definitions of ServiceID for service offered by this module
//  Start/stop TCP server
//  Args: enable(1B)|port(2B)
#define ESP_T_TCPSERV   0
//  Open TCP connection to server
//  Args: KeepAlive(1B)|IPaddress(7B-15B)|port(2B)|socketID(1B)
#define ESP_T_CONNTCP   1
//  Send data through socket with specific ID
//  Args: socketID(1B)|message
#define ESP_T_SENDTCP   2
//  Receive data from specific socket ID
//  Args: socketID(1B)
#define ESP_T_RECVSOCK  3
//  Close socket with specific ID
//  Args: socketID(1B)
#define ESP_T_CLOSETCP  4

///-----------------------------------------------------------------------------
///         Radar task IDs
///-----------------------------------------------------------------------------
//  Unique identifier of this module as registered in task scheduler
#define RADAR_UID       1
/// Definitions of ServiceID for service offered by this module
//  Initiate radar scan
//  Args: scanType(1B)
#define RADAR_SCAN      0
//  Set horizontal angle for radar
//  Args: angle(4B)
#define RADAR_SETH      2
//  Set vertical angle of radar
//  Args: angle(4B)
#define RADAR_SETV      3

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

QString AssembleRequest(uint8_t libUID, uint8_t serviceID)
{
    QString retVal;

    retVal[0] = libUID;
    retVal[1] = serviceID;

    return retVal;
}

#endif // ROVERINTERFACE_H
