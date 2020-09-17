/*
Copyright (C) 2019 Intel Corporation

SPDX-License-Identifier: Apache-2.0

Open Drone ID C Library

Maintainer:
Gabriel Cox
gabriel.c.cox@intel.com
*/

#ifndef _OPENDRONEID_H_
#define _OPENDRONEID_H_

#include <stdint.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#define ODID_MESSAGE_SIZE 25
#define ODID_ID_SIZE 20
#define ODID_STR_SIZE 23
#define ODID_PROTOCOL_VERSION 0
#define ODID_SPEC_VERSION 0.8
#define ODID_AUTH_MAX_PAGES 5
#define ODID_AUTH_PAGE_ZERO_DATA_SIZE 6
#define ODID_PACK_MAX_MESSAGES 10

#define ODID_SUCCESS    0
#define ODID_FAIL       1

#define MIN_DIR         0       // Minimum direction
#define MAX_DIR         360     // Maximum direction
#define INV_DIR         361     // Invalid direction
#define MIN_SPEED_H     0       // Minimum speed horizontal
#define MAX_SPEED_H     254.25f // Maximum speed horizontal
#define INV_SPEED_H     255     // Invalid speed horizontal
#define MIN_SPEED_V     -62     // Minimum speed vertical
#define MAX_SPEED_V     62      // Maximum speed vertical
#define INV_SPEED_V     63      // Invalid speed vertical
#define MIN_LAT         -90     // Minimum latitude
#define MAX_LAT         90      // Maximum latitude
#define MIN_LON         -180    // Minimum longitude
#define MAX_LON         180     // Maximum longitude
#define MIN_ALT         -1000   // Minimum altitude
#define MAX_ALT         31767.5f// Maximum altitude
#define INV_ALT         MIN_ALT // Invalid altitude
#define MAX_TIMESTAMP   (60 * 60 * 10)
#define MAX_AUTH_LENGTH ((ODID_STR_SIZE - ODID_AUTH_PAGE_ZERO_DATA_SIZE) + \
                         ODID_STR_SIZE * (ODID_AUTH_MAX_PAGES - 1))
#define MAX_AREA_RADIUS 2550

typedef enum ODID_messagetype {
    ODID_MESSAGETYPE_BASIC_ID = 0,
    ODID_MESSAGETYPE_LOCATION = 1,
    ODID_MESSAGETYPE_AUTH = 2,
    ODID_MESSAGETYPE_SELF_ID = 3,
    ODID_MESSAGETYPE_SYSTEM = 4,
    ODID_MESSAGETYPE_OPERATOR_ID = 5,
    ODID_MESSAGETYPE_PACKED = 0xF,
    ODID_MESSAGETYPE_INVALID = 0xFF,
} ODID_messagetype_t;

typedef enum ODID_idtype {
    ODID_IDTYPE_NONE = 0,
    ODID_IDTYPE_SERIAL_NUMBER = 1,
    ODID_IDTYPE_CAA_REGISTRATION_ID = 2, // Civil Aviation Authority
    ODID_IDTYPE_UTM_ASSIGNED_UUID = 3, // UAS (Unmanned Aircraft System) Traffic Management
    // 4 to 15 reserved
} ODID_idtype_t;

typedef enum ODID_uatype {
    ODID_UATYPE_NONE = 0,
    ODID_UATYPE_AEROPLANE = 1, // Fixed wing
    ODID_UATYPE_HELICOPTER_OR_MULTIROTOR = 2,
    ODID_UATYPE_GYROPLANE = 3,
    ODID_UATYPE_HYBRID_LIFT = 4, // Fixed wing aircraft that can take off vertically
    ODID_UATYPE_ORNITHOPTER = 5,
    ODID_UATYPE_GLIDER = 6,
    ODID_UATYPE_KITE = 7,
    ODID_UATYPE_FREE_BALLOON = 8,
    ODID_UATYPE_CAPTIVE_BALLOON = 9,
    ODID_UATYPE_AIRSHIP = 10, // Such as a blimp
    ODID_UATYPE_FREE_FALL_PARACHUTE = 11, // Unpowered
    ODID_UATYPE_ROCKET = 12,
    ODID_UATYPE_TETHERED_POWERED_AIRCRAFT = 13,
    ODID_UATYPE_GROUND_OBSTACLE = 14,
    ODID_UATYPE_OTHER = 15,
} ODID_uatype_t;

typedef enum ODID_status {
    ODID_STATUS_UNDECLARED = 0,
    ODID_STATUS_GROUND = 1,
    ODID_STATUS_AIRBORNE = 2,
    ODID_STATUS_EMERGENCY = 3,
    // 3 to 15 reserved
} ODID_status_t;

typedef enum ODID_Height_reference {
    ODID_HEIGHT_REF_OVER_TAKEOFF = 0,
    ODID_HEIGHT_REF_OVER_GROUND = 1,
} ODID_Height_reference_t;

typedef enum ODID_Horizontal_accuracy {
    ODID_HOR_ACC_UNKNOWN = 0,
    ODID_HOR_ACC_10NM = 1,      // Nautical Miles. 18.52 km
    ODID_HOR_ACC_4NM = 2,       // 7.408 km
    ODID_HOR_ACC_2NM = 3,       // 3.704 km
    ODID_HOR_ACC_1NM = 4,       // 1.852 km
    ODID_HOR_ACC_0_5NM = 5,     // 926 m
    ODID_HOR_ACC_0_3NM = 6,     // 555.6 m
    ODID_HOR_ACC_0_1NM = 7,     // 185.2 m
    ODID_HOR_ACC_0_05NM = 8,    // 92.6 m
    ODID_HOR_ACC_30_METER = 9,
    ODID_HOR_ACC_10_METER = 10,
    ODID_HOR_ACC_3_METER = 11,
    ODID_HOR_ACC_1_METER = 12,
    // 13 to 15 reserved
} ODID_Horizontal_accuracy_t;

typedef enum ODID_Vertical_accuracy {
    ODID_VER_ACC_UNKNOWN = 0,
    ODID_VER_ACC_150_METER = 1,
    ODID_VER_ACC_45_METER = 2,
    ODID_VER_ACC_25_METER = 3,
    ODID_VER_ACC_10_METER = 4,
    ODID_VER_ACC_3_METER = 5,
    ODID_VER_ACC_1_METER = 6,
    // 7 to 15 reserved
} ODID_Vertical_accuracy_t;

typedef enum ODID_Speed_accuracy {
    ODID_SPEED_ACC_UNKNOWN = 0,
    ODID_SPEED_ACC_10_METERS_PER_SECOND = 1,
    ODID_SPEED_ACC_3_METERS_PER_SECOND = 2,
    ODID_SPEED_ACC_1_METERS_PER_SECOND = 3,
    ODID_SPEED_ACC_0_3_METERS_PER_SECOND = 4,
    // 5 to 15 reserved
} ODID_Speed_accuracy_t;

typedef enum ODID_Timestamp_accuracy {
    ODID_TIME_ACC_UNKNOWN = 0,
    ODID_TIME_ACC_0_1_SECOND = 1,
    ODID_TIME_ACC_0_2_SECOND = 2,
    ODID_TIME_ACC_0_3_SECOND = 3,
    ODID_TIME_ACC_0_4_SECOND = 4,
    ODID_TIME_ACC_0_5_SECOND = 5,
    ODID_TIME_ACC_0_6_SECOND = 6,
    ODID_TIME_ACC_0_7_SECOND = 7,
    ODID_TIME_ACC_0_8_SECOND = 8,
    ODID_TIME_ACC_0_9_SECOND = 9,
    ODID_TIME_ACC_1_0_SECOND = 10,
    ODID_TIME_ACC_1_1_SECOND = 11,
    ODID_TIME_ACC_1_2_SECOND = 12,
    ODID_TIME_ACC_1_3_SECOND = 13,
    ODID_TIME_ACC_1_4_SECOND = 14,
    ODID_TIME_ACC_1_5_SECOND = 15,
} ODID_Timestamp_accuracy_t;

typedef enum ODID_authtype {
    ODID_AUTH_NONE = 0,
    ODID_AUTH_UAS_ID_SIGNATURE = 1, // Unmanned Aircraft System
    ODID_AUTH_OPERATOR_ID_SIGNATURE = 2,
    ODID_AUTH_MESSAGE_SET_SIGNATURE = 3,
    ODID_AUTH_NETWORK_REMOTE_ID = 4, // Authentication provided by Network Remote ID
    // 5 to 9 reserved for the specification. 0xA to 0xF reserved for private use
} ODID_authtype_t;

typedef enum ODID_desctype {
    ODID_DESC_TYPE_TEXT = 0,
    // 1 to 200 reserved
    // 201 to 255 available for private use
} ODID_desctype_t;

typedef enum ODID_operatorIdType {
    ODID_OPERATOR_ID = 0,
    // 1 to 200 reserved
    // 201 to 255 available for private use
} ODID_operatorIdType_t;

typedef enum ODID_operator_location_type {
    ODID_OPERATOR_LOCATION_TYPE_TAKEOFF = 0,
    ODID_OPERATOR_LOCATION_TYPE_LIVE_GNSS = 1,
    ODID_OPERATOR_LOCATION_TYPE_FIXED = 2,
    // 3 to 255 reserved
} ODID_operator_location_type_t;

typedef enum ODID_classification_type {
    ODID_CLASSIFICATION_TYPE_UNDECLARED = 0,
    ODID_CLASSIFICATION_TYPE_EU = 1, // European Union
    // 2 to 7 reserved
} ODID_classification_type_t;

typedef enum ODID_category_EU {
    ODID_CATEGORY_EU_UNDECLARED = 0,
    ODID_CATEGORY_EU_OPEN = 1,
    ODID_CATEGORY_EU_SPECIFIC = 2,
    ODID_CATEGORY_EU_CERTIFIED = 3,
    // 4 to 15 reserved
} ODID_category_EU_t;

typedef enum ODID_class_EU {
    ODID_CLASS_EU_UNDECLARED = 0,
    ODID_CLASS_EU_CLASS_0 = 1,
    ODID_CLASS_EU_CLASS_1 = 2,
    ODID_CLASS_EU_CLASS_2 = 3,
    ODID_CLASS_EU_CLASS_3 = 4,
    ODID_CLASS_EU_CLASS_4 = 5,
    ODID_CLASS_EU_CLASS_5 = 6,
    ODID_CLASS_EU_CLASS_6 = 7,
    // 8 to 15 reserved
} ODID_class_EU_t;

 /*
 * @name ODID_DataStructs
 * ODID Data Structures in their normative (non-packed) form.
 * This is the structure that any input adapters should form to
 * let the encoders put the data into encoded form.
 */
typedef struct ODID_BasicID_data {
    ODID_uatype_t UAType;
    ODID_idtype_t IDType;
    char UASID[ODID_ID_SIZE+1]; // Additional byte to allow for null term in normative form
} ODID_BasicID_data;

typedef struct ODID_Location_data {
    ODID_status_t Status;
    float Direction;          // Degrees. 0 <= x < 360. Route course based on true North. Invalid, No Value, or Unknown: 361deg
    float SpeedHorizontal;    // m/s. Positive only. Invalid, No Value, or Unknown: 255m/s. If speed is >= 254.25 m/s: 254.25m/s
    float SpeedVertical;      // m/s. Invalid, No Value, or Unknown: 63m/s. If speed is >= 62m/s: 62m/s
    double Latitude;          // Invalid, No Value, or Unknown: 0 deg (both Lat/Lon)
    double Longitude;         // Invalid, No Value, or Unknown: 0 deg (both Lat/Lon)
    float AltitudeBaro;       // meter (Ref 29.92 inHg, 1013.24 mb). Invalid, No Value, or Unknown: -1000m
    float AltitudeGeo;        // meter (WGS84-HAE). Invalid, No Value, or Unknown: -1000m
    ODID_Height_reference_t HeightType;
    float Height;             // meter. Invalid, No Value, or Unknown: -1000m
    ODID_Horizontal_accuracy_t HorizAccuracy;
    ODID_Vertical_accuracy_t VertAccuracy;
    ODID_Vertical_accuracy_t BaroAccuracy;
    ODID_Speed_accuracy_t SpeedAccuracy;
    ODID_Timestamp_accuracy_t TSAccuracy;
    float TimeStamp;          // seconds after the full hour
} ODID_Location_data;

/*
 * The Authentication message can have two different formats.
 * Five data pages are supported.
 * For data page 0, the fields PageCount, Length and TimeStamp are present and
 * AuthData is only 17 bytes.
 * For data page 1 through 4, PageCount,Length and TimeStamp are not present and
 * the size of AuthData is 23 bytes.
 */
typedef struct ODID_Auth_data {
    uint8_t DataPage;   // 0 - 4
    ODID_authtype_t AuthType;
    uint8_t PageCount;  // Page 0 only. Maximum ODID_AUTH_MAX_PAGES
    uint8_t Length;     // Page 0 only. Bytes. Total of AuthData from all data pages
    uint32_t Timestamp; // Page 0 only. Relative to 00:00:00 01/01/2019
    char AuthData[ODID_STR_SIZE+1]; // Additional byte to allow for null term in normative form
} ODID_Auth_data;

typedef struct ODID_SelfID_data {
    ODID_desctype_t DescType;
    char Desc[ODID_STR_SIZE+1]; // Additional byte to allow for null term in normative form
} ODID_SelfID_data;

typedef struct ODID_System_data {
    ODID_operator_location_type_t OperatorLocationType;
    ODID_classification_type_t ClassificationType;
    double OperatorLatitude;  // Invalid, No Value, or Unknown: 0 deg (both Lat/Lon)
    double OperatorLongitude; // Invalid, No Value, or Unknown: 0 deg (both Lat/Lon)
    uint16_t AreaCount;       // Default 1
    uint16_t AreaRadius;      // meter. Default 0
    float AreaCeiling;        // meter. Invalid, No Value, or Unknown: -1000m
    float AreaFloor;          // meter. Invalid, No Value, or Unknown: -1000m
    ODID_category_EU_t CategoryEU; // Only filled if ClassificationType = ODID_CLASSIFICATION_TYPE_EU
    ODID_class_EU_t ClassEU;       // Only filled if ClassificationType = ODID_CLASSIFICATION_TYPE_EU
} ODID_System_data;

typedef struct ODID_OperatorID_data {
    ODID_operatorIdType_t OperatorIdType;
    char OperatorId[ODID_ID_SIZE+1]; // Additional byte to allow for null term in normative form
} ODID_OperatorID_data;

typedef struct ODID_UAS_Data {
    ODID_BasicID_data BasicID;
    ODID_Location_data Location;
    ODID_Auth_data Auth[ODID_AUTH_MAX_PAGES];
    ODID_SelfID_data SelfID;
    ODID_System_data System;
    ODID_OperatorID_data OperatorID;

    uint8_t BasicIDValid;
    uint8_t LocationValid;
    uint8_t AuthValid[ODID_AUTH_MAX_PAGES];
    uint8_t SelfIDValid;
    uint8_t SystemValid;
    uint8_t OperatorIDValid;
} ODID_UAS_Data;

/**
* @Name ODID_PackedStructs
* Packed Data Structures prepared for broadcast
* It's best not directly access these.  Use the encoders/decoders.
*/

typedef struct __attribute__((__packed__)) ODID_BasicID_encoded {
    // Byte 0 [MessageType][ProtoVersion]  -- must define LSb first
    uint8_t ProtoVersion: 4;
    uint8_t MessageType : 4;

    // Byte 1 [IDType][UAType]  -- must define LSb first
    uint8_t UAType: 4;
    uint8_t IDType: 4;

    // Bytes 2-21
    char UASID[ODID_ID_SIZE];

    // 22-24
    char Reserved[3];
} ODID_BasicID_encoded;

typedef struct __attribute__((__packed__)) ODID_Location_encoded {
    // Byte 0 [MessageType][ProtoVersion]  -- must define LSb first
    uint8_t ProtoVersion: 4;
    uint8_t MessageType : 4;

    // Byte 1 [Status][Reserved][NSMult][EWMult] -- must define LSb first
    uint8_t SpeedMult: 1;
    uint8_t EWDirection: 1;
    uint8_t HeightType: 1;
    uint8_t Reserved: 1;
    uint8_t Status: 4;

    // Bytes 2-18
    uint8_t Direction;
    uint8_t SpeedHorizontal;
    int8_t SpeedVertical;
    int32_t Latitude;
    int32_t Longitude;
    uint16_t AltitudeBaro;
    uint16_t AltitudeGeo;
    uint16_t Height;

    // Byte 19 [VertAccuracy][HorizAccuracy]  -- must define LSb first
    uint8_t HorizAccuracy:4;
    uint8_t VertAccuracy:4;

    // Byte 20 [BaroAccuracy][SpeedAccuracy]  -- must define LSb first
    uint8_t SpeedAccuracy:4;
    uint8_t BaroAccuracy:4;

    // Byte 21-22
    uint16_t TimeStamp;

    // Byte 23 [Reserved2][TSAccuracy]  -- must define LSb first
    uint8_t TSAccuracy:4;
    uint8_t Reserved2:4;

    // Byte 24
    char Reserved3;
} ODID_Location_encoded;

typedef struct __attribute__((__packed__)) ODID_Auth_encoded_page_zero {
    // Byte 0 [MessageType][ProtoVersion]  -- must define LSb first
    uint8_t ProtoVersion: 4;
    uint8_t MessageType : 4;

    // Byte 1 [AuthType][DataPage]
    uint8_t DataPage: 4;
    uint8_t AuthType: 4;

    // Bytes 2-7
    uint8_t PageCount;
    uint8_t Length;
    uint32_t Timestamp;

    // Byte 8-24
    char AuthData[ODID_STR_SIZE - ODID_AUTH_PAGE_ZERO_DATA_SIZE];
} ODID_Auth_encoded_page_zero;

typedef struct __attribute__((__packed__)) ODID_Auth_encoded_page_non_zero {
    // Byte 0 [MessageType][ProtoVersion]  -- must define LSb first
    uint8_t ProtoVersion: 4;
    uint8_t MessageType : 4;

    // Byte 1 [AuthType][DataPage]
    uint8_t DataPage: 4;
    uint8_t AuthType: 4;

    // Byte 2-24
    char AuthData[ODID_STR_SIZE];
} ODID_Auth_encoded_page_non_zero;

typedef union ODID_Auth_encoded{
    ODID_Auth_encoded_page_zero page_zero;
    ODID_Auth_encoded_page_non_zero page_non_zero;
} ODID_Auth_encoded;

typedef struct __attribute__((__packed__)) ODID_SelfID_encoded {
    // Byte 0 [MessageType][ProtoVersion]  -- must define LSb first
    uint8_t ProtoVersion: 4;
    uint8_t MessageType : 4;

    // Byte 1
    uint8_t DescType;

    // Byte 2-24
    char Desc[ODID_STR_SIZE];
} ODID_SelfID_encoded;

typedef struct __attribute__((__packed__)) ODID_System_encoded {
    // Byte 0 [MessageType][ProtoVersion]  -- must define LSb first
    uint8_t ProtoVersion: 4;
    uint8_t MessageType : 4;

    // Byte 1 [Reserved][ClassificationType][OperatorLocationType]  -- must define LSb first
    uint8_t OperatorLocationType: 2;
    uint8_t ClassificationType: 3;
    uint8_t Reserved: 3;

    // Byte 2-9
    int32_t OperatorLatitude;
    int32_t OperatorLongitude;

    // Byte 10-16
    uint16_t AreaCount;
    uint8_t  AreaRadius;
    uint16_t AreaCeiling;
    uint16_t AreaFloor;

    // Byte 17 [CategoryEU][ClassEU]  -- must define LSb first
    uint8_t ClassEU: 4;
    uint8_t CategoryEU: 4;

    // Byte 18-24
    char Reserved2[7];
} ODID_System_encoded;

typedef struct __attribute__((__packed__)) ODID_OperatorID_encoded {
    // Byte 0 [MessageType][ProtoVersion]  -- must define LSb first
    uint8_t ProtoVersion: 4;
    uint8_t MessageType : 4;

    // Byte 1
    uint8_t OperatorIdType;

    // Bytes 2-21
    char OperatorId[ODID_ID_SIZE];

    // 22-24
    char Reserved[3];
} ODID_OperatorID_encoded;

typedef union ODID_Messages_encoded {
    uint8_t rawData[ODID_MESSAGE_SIZE];
    ODID_BasicID_encoded basicId;
    ODID_Location_encoded location;
    ODID_Auth_encoded auth;
    ODID_SelfID_encoded selfId;
    ODID_System_encoded system;
    ODID_OperatorID_encoded operatorId;
} ODID_Messages_encoded;

typedef struct __attribute__((__packed__)) ODID_MessagePack_encoded {
    // Byte 0 [MessageType][ProtoVersion]  -- must define LSb first
    uint8_t ProtoVersion: 4;
    uint8_t MessageType : 4;

    // Byte 1 - 2
    uint8_t SingleMessageSize;
    uint8_t MsgPackSize;

    // Byte 3 - 252
    ODID_Messages_encoded Messages[ODID_PACK_MAX_MESSAGES];
} ODID_MessagePack_encoded;

typedef struct ODID_MessagePack_data {
    uint8_t SingleMessageSize; // Must always be ODID_MESSAGE_SIZE
    uint8_t MsgPackSize; // Number of messages in pack (NOT number of bytes)

    ODID_Messages_encoded Messages[ODID_PACK_MAX_MESSAGES];
} ODID_MessagePack_data;

// API Calls
void odid_initBasicIDData(ODID_BasicID_data *data);
void odid_initLocationData(ODID_Location_data *data);
void odid_initAuthData(ODID_Auth_data *data);
void odid_initSelfIDData(ODID_SelfID_data *data);
void odid_initSystemData(ODID_System_data *data);
void odid_initOperatorIDData(ODID_OperatorID_data *data);
void odid_initMessagePackData(ODID_MessagePack_data *data);
void odid_initUasData(ODID_UAS_Data *data);

int encodeBasicIDMessage(ODID_BasicID_encoded *outEncoded, ODID_BasicID_data *inData);
int encodeLocationMessage(ODID_Location_encoded *outEncoded, ODID_Location_data *inData);
int encodeAuthMessage(ODID_Auth_encoded *outEncoded, ODID_Auth_data *inData);
int encodeSelfIDMessage(ODID_SelfID_encoded *outEncoded, ODID_SelfID_data *inData);
int encodeSystemMessage(ODID_System_encoded *outEncoded, ODID_System_data *inData);
int encodeOperatorIDMessage(ODID_OperatorID_encoded *outEncoded, ODID_OperatorID_data *inData);
int encodeMessagePack(ODID_MessagePack_encoded *outEncoded, ODID_MessagePack_data *inData);

int decodeBasicIDMessage(ODID_BasicID_data *outData, ODID_BasicID_encoded *inEncoded);
int decodeLocationMessage(ODID_Location_data *outData, ODID_Location_encoded *inEncoded);
int decodeAuthMessage(ODID_Auth_data *outData, ODID_Auth_encoded *inEncoded);
int decodeSelfIDMessage(ODID_SelfID_data *outData, ODID_SelfID_encoded *inEncoded);
int decodeSystemMessage(ODID_System_data *outData, ODID_System_encoded *inEncoded);
int decodeOperatorIDMessage(ODID_OperatorID_data *outData, ODID_OperatorID_encoded *inEncoded);
int decodeMessagePack(ODID_UAS_Data *uasData, ODID_MessagePack_encoded *pack);

int getAuthPageNum(ODID_Auth_encoded *inEncoded, int *pageNum);
ODID_messagetype_t decodeMessageType(uint8_t byte);
ODID_messagetype_t decodeOpenDroneID(ODID_UAS_Data *uas_data, uint8_t *msg_data);

// Helper Functions
ODID_Horizontal_accuracy_t createEnumHorizontalAccuracy(float Accuracy);
ODID_Vertical_accuracy_t createEnumVerticalAccuracy(float Accuracy);
ODID_Speed_accuracy_t createEnumSpeedAccuracy(float Accuracy);
ODID_Timestamp_accuracy_t createEnumTimestampAccuracy(float Accuracy);

float decodeHorizontalAccuracy(ODID_Horizontal_accuracy_t Accuracy);
float decodeVerticalAccuracy(ODID_Vertical_accuracy_t Accuracy);
float decodeSpeedAccuracy(ODID_Speed_accuracy_t Accuracy);
float decodeTimestampAccuracy(ODID_Timestamp_accuracy_t Accuracy);

// OpenDroneID WiFi functions

/**
 * drone_export_gps_data - prints drone information to json style string,
 * according to odid message specification
 * @UAS_Data: general drone status information
 * @buf: buffer for the json style string
 * @buf_size: size of the string buffer
 *
 * Returns pointer to gps_data string on success, otherwise returns NULL
 */
void drone_export_gps_data(ODID_UAS_Data *UAS_Data, char *buf, size_t buf_size);

/**
 * odid_message_build_pack - combines the messages and encodes the odid pack
 * @UAS_Data: general drone status information
 * @pack: buffer space to write to
 * @buflen: maximum length of buffer space
 *
 * Returns length on success, < 0 on failure. @buf only contains a valid message
 * if the return code is >0
 */
int odid_message_build_pack(ODID_UAS_Data *UAS_Data, void *pack, size_t buflen);

/* odid_wifi_build_nan_sync_beacon_frame - creates a NAN sync beacon frame
 * that shall be send just before the NAN action frame.
 * @mac: mac address of the wifi adapter where the NAN frame will be sent
 * @buf: pointer to buffer space where the NAN will be written to
 * @buf_size: maximum size of the buffer
 *
 * Returns the packet length on success, or < 0 on error.
 */
int odid_wifi_build_nan_sync_beacon_frame(char *mac, uint8_t *buf, size_t buf_size);

/* odid_wifi_build_message_pack_nan_action_frame - creates a message pack
 * with each type of message from the drone information into an NAN action fram
 * @UAS_Data: general drone status information
 * @mac: mac address of the wifi adapter where the NAN frame will be sent
 * @send_counter: sequence number, to be increase for each call of this function
 * @buf: pointer to buffer space where the NAN will be written to
 * @buf_size: maximum size of the buffer
 *
 * Returns the packet length on success, or < 0 on error.
 */
int odid_wifi_build_message_pack_nan_action_frame(ODID_UAS_Data *UAS_Data, char *mac,
						  uint8_t send_counter,
						  uint8_t *buf, size_t buf_size);

/* odid_message_process_pack - decodes the messages from the odid message pack
 * @UAS_Data: general drone status information
 * @pack: buffer space to read from
 * @buflen: length of buffer space
 *
 * Returns 0 on success
 */
int odid_message_process_pack(ODID_UAS_Data *UAS_Data, uint8_t *pack, size_t buflen);

/* odid_wifi_receive_message_pack_nan_action_frame - processes a received message pack
 * with each type of message from the drone information into an NAN action frame
 * @UAS_Data: general drone status information
 * @mac: mac address of the wifi adapter where the NAN frame will be sent
 * @buf: pointer to buffer space where the NAN is stored
 * @buf_size: maximum size of the buffer
 *
 * Returns 0 on success, or < 0 on error. Will fill 6 bytes into @mac.
 */
int odid_wifi_receive_message_pack_nan_action_frame(ODID_UAS_Data *UAS_Data,
						    char *mac, uint8_t *buf, size_t buf_size);


#ifndef ODID_DISABLE_PRINTF
void printByteArray(uint8_t *byteArray, uint16_t asize, int spaced);
void printBasicID_data(ODID_BasicID_data *BasicID);
void printLocation_data(ODID_Location_data *Location);
void printAuth_data(ODID_Auth_data *Auth);
void printSelfID_data(ODID_SelfID_data *SelfID);
void printOperatorID_data(ODID_OperatorID_data *OperatorID);
void printSystem_data(ODID_System_data *System_data);
#endif // ODID_DISABLE_PRINTF

#ifdef __cplusplus
}
#endif

#endif // _OPENDRONEID_H_
