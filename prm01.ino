#include <Wire.h>

struct STREAM_DATA {
  uint16_t battVoltage = (uint16_t)7525;
  float altitude = 10;
  float climb = 0;
  float roll = 0;
  float pitch = 0;
  float yaw = 0;
  uint8_t gps_sats = 0;
  float gps_lon = 0;
  float gps_lat = 0;
  float home_lon = 0;
  float home_lat = 0;
  uint16_t gps_speed = 0;
  boolean gps_fix = false;
  uint32_t home_distance = 0;
};

STREAM_DATA streamData;

boolean set = false;


void setup() {
  Wire.begin(4);
  Wire.onRequest(onRequest);
}

void loop() {
}

void set1() {

  int  alt = streamData.altitude * 10;
  byte  altHi = highByte(alt )  ;
  byte  altLo =  lowByte(alt ) ;

  int  yaw = streamData.yaw * 100;
  byte yawHi = highByte(yaw );
  byte yawLo = lowByte(yaw );


  int  speed2 = streamData.gps_speed * 10;
  byte speedHi = highByte(speed2);
  byte speedLo = lowByte(speed2);


  int  roll = streamData.roll * 10;
  byte rollHi = highByte(roll);
  byte rollLo = lowByte(roll);


  int  pitch = streamData.pitch * 10;
  byte pitchHi = highByte(pitch);
  byte pitchLo = lowByte(pitch);

//  int distance = calc_dist(streamData.gps_lat, streamData.gps_lon, streamData.home_lat, streamData.home_lon) * 100;
  byte distanceHi = highByte(streamData.home_distance);
  byte distanceLo = lowByte(streamData.home_distance);

  byte buffer[16] = {0x89, 0xAB, streamData.gps_sats, altHi, altLo, yawHi, yawLo, speedHi, speedLo, rollHi , rollLo, pitchHi, pitchLo, distanceHi, distanceLo, 0x00};
  Wire.write(buffer, 16);
}
void set2() {

  int  rise = streamData.climb * 10;
  byte  riseHi = highByte(rise);
  byte  riseLo =  lowByte(rise);

  byte voltesHi = highByte(streamData.battVoltage);
  byte voltesLo = lowByte(streamData.battVoltage);

  float lat = 40.689060;
  float log = -74.044636;

  byte buffer[16] = {0x89, 0xCD, streamData.gps_sats, riseHi, riseLo, voltesHi, voltesLo,/**/ 0x0, 0x0, 0x0 , 0x0, /**/0x0, 0x0, 0x0, 0x0,/**/ 0x00};
  Wire.write(buffer, 16);
}


void onRequest() {
  if (set) {
    set = false;
    set1();
  } else {
    set = true;
    set2();
  }
}
