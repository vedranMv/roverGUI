#include "roverinterface.h"
#include <cstring>

void MakeRequest(uint8_t *req, uint16_t uid, uint16_t task, int32_t time, int32_t repeats)
{
    std::stringstream ss;
    ss<<DEVICE_ID<<":"<<uid<<":"<<task<<":"<<time<<":"<<repeats;

    memcpy(req, ss.str().c_str(), ss.str().length());
}

void AppendArgs(uint8_t *req, uint16_t *reqLen, void *args, uint16_t argLen)
{
    std::stringstream ss;
    ss<<req<<":"<<argLen<<"::";
    memcpy(req, ss.str().c_str(), ss.str().length());
    *reqLen = ss.str().length()+argLen+2;
    memcpy(req+ss.str().length(), args, argLen);
    memcpy(req+ss.str().length()+argLen, "\r\n", 2);
}
