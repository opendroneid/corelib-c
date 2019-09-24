/*
Copyright (C) 2019 Intel Corporation

SPDX-License-Identifier: Apache-2.0

Open Drone ID C Library

Maintainer:
Gabriel Cox
gabriel.c.cox@intel.com
*/

#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <unistd.h>
#include <opendroneid.h>
#define SLEEPMS 1000000 //ns

odid_encoded_basic_id_t basicID_enc;
odid_encoded_location_t location_enc;
odid_encoded_auth_t auth_enc;
odid_encoded_self_id_t selfID_enc;
odid_encoded_system_t system_enc;

odid_data_basic_id_t basicID_data;
odid_data_location_t location_data;
odid_data_auth_t auth_data;
odid_data_self_id_t selfID_data;
odid_data_system_t system_data;

const int SIM_STEPS = 20;
const float SIM_STEP_SIZE = 0.0001;
const float DISTANCE_PER_LAT = 111699.0;


double simLat = 45.5393092;
double simLon = -122.9663894;
double simGndLat = 45.5393082;
double simGndLon = -122.9663884;
float simDirection = 0;
float simSpeedHorizontal;

enum compdirs {E,S,W,N};
enum compdirs direction = E;
int stepCount = 0;

void updateLocation(void)
{
    simSpeedHorizontal = DISTANCE_PER_LAT * SIM_STEP_SIZE;
    stepCount++;
    switch(direction) {
        case E:
            simLon+= SIM_STEP_SIZE;
            simDirection = 90;
            if (stepCount >= SIM_STEPS) {
                direction = S;
                stepCount = 0;
            }
            break;
        case S:
            simLat-= SIM_STEP_SIZE;
            simDirection = 180;
            if (stepCount >= SIM_STEPS) {
                direction = W;
                stepCount = 0;
            }
            break;
        case W:
            simLon-= SIM_STEP_SIZE;
            simDirection = 270;
            if (stepCount >= SIM_STEPS) {
                direction = N;
                stepCount = 0;
            }
            break;
        case N:
            simLat+= SIM_STEP_SIZE;
            simDirection = 0;
            if (stepCount >= SIM_STEPS) {
                direction = E;
                stepCount = 0;
            }
            break;
    }
}

void ODID_getSimData(uint8_t *message, uint8_t msgType)
{
    switch (msgType) {
        case 0:
            basicID_data.id_type = ODID_ID_TYPE_SERIAL_NUMBER;
            basicID_data.ua_type = ODID_UA_TYPE_ROTORCRAFT;
            // 4 chr mfg code, 1chr Len, 15chr serial
            odid_safe_copy_fill(basicID_data.uas_id, "INTCE123456789012345", sizeof(basicID_data.uas_id));

            odid_encode_message_basic_id(&basicID_enc, &basicID_data);
            memcpy(message, &basicID_enc, ODID_MESSAGE_SIZE);
            break;

        case 1:
            updateLocation();
            location_data.Status = ODID_STATUS_AIRBORNE;
            location_data.Direction = simDirection;
            location_data.SpeedHorizontal = simSpeedHorizontal;
            location_data.SpeedVertical = 2;
            location_data.Latitude = simLat;
            location_data.Longitude = simLon;
            location_data.AltitudeBaro = 100;
            location_data.AltitudeGeo = 100;
            location_data.HeightType = ODID_HEIGHT_REF_OVER_GROUND;
            location_data.Height = 50;
            location_data.HorizAccuracy = odid_create_enum_horizontal_accuracy(2.5f);
            location_data.VertAccuracy = odid_create_enum_vertical_accuracy(2.5f);
            location_data.BaroAccuracy = odid_create_enum_vertical_accuracy(3.5f);
            location_data.SpeedAccuracy = odid_create_enum_speed_accuracy(0.2f);
            location_data.TSAccuracy = odid_create_enum_timestamp_accuracy(0.5f);
            location_data.TimeStamp = 60;

            odid_encode_message_location(&location_enc, &location_data);
            memcpy(message, &location_enc, ODID_MESSAGE_SIZE);
            break;

        case 2:
            auth_data.AuthType = ODID_AUTH_TYPE_MPUID;
            auth_data.DataPage = 0;
            odid_safe_copy_fill(auth_data.AuthData, "030a0cd033a3", sizeof(auth_data.AuthData));

            odid_encode_message_auth(&auth_enc, &auth_data);
            memcpy(message, &auth_enc, ODID_MESSAGE_SIZE);
            break;

        case 3:
            selfID_data.DescType = ODID_DESC_TYPE_TEXT;
            odid_safe_copy_fill(selfID_data.Desc, "Real Estate Photos", sizeof(selfID_data.Desc));
            odid_encode_message_self_id(&selfID_enc, &selfID_data);
            memcpy(message, &selfID_enc, ODID_MESSAGE_SIZE);
            break;

        case 4:
            system_data.LocationSource = ODID_LOCATION_SRC_TAKEOFF;
            system_data.remotePilotLatitude = simGndLat;
            system_data.remotePilotLongitude = simGndLon;
            system_data.GroupCount = 35;
            system_data.GroupRadius = 75;
            system_data.GroupCeiling = 176.9;
            system_data.GroupFloor = 41.7;
            odid_encode_message_system(&system_enc, &system_data);
            memcpy(message, &system_enc, ODID_MESSAGE_SIZE);
            break;
    }
}

void test_sim()
{
    uint8_t testBytes[ODID_MESSAGE_SIZE];
    int x;
    while (1)
    {
        for (x=0; x<=4; x++) {
            memset(testBytes,0,ODID_MESSAGE_SIZE);
            ODID_getSimData(testBytes,x);
            odid_print_byte_array(testBytes, ODID_MESSAGE_SIZE, 1);
            usleep(SLEEPMS);
        }
    }

}
