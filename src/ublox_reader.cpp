#include "ublox_reader.h"
#include <cstdint>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// Decode NAV-POSLLH payload into gps struct
static int NAV_POSLLH(uint8_t *buffer, classId *gps) {
  memcpy(&gps->iTOW,   buffer + 0,  4);  // GPS time of week [ms]
  memcpy(&gps->lon,    buffer + 4,  4);  // Longitude [1e-7 deg]
  memcpy(&gps->lat,    buffer + 8,  4);  // Latitude [1e-7 deg]
  memcpy(&gps->height, buffer + 12, 4);  // Height above ellipsoid [mm]
  memcpy(&gps->hMSL,   buffer + 16, 4);  // Height above mean sea level [mm]
  memcpy(&gps->hAcc,   buffer + 20, 4);  // Horizontal accuracy estimate [mm]
  memcpy(&gps->vAcc,   buffer + 24, 4);  // Vertical accuracy estimate [mm]
  return 0;
}

// Convert hex string (like "B5 62 01 02 ...") to byte vector
static vector<uint8_t> hexToBytes(const string &rawHex) {
  vector<uint8_t> bytes;
  stringstr
