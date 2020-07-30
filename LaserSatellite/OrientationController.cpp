#include "OrientationController.h"
#include "LaserSatellite.h"

#define BETA 0.22

const double compassCalibrationBias[3] = {-1917.00, 2401.00, 3197.00};
const double compassCalibrationMatrix[3][3] = {{0.47, 0, 0}, {0, 0.47, 0}, {0, 0, 0.50}};

Madgwick filter;

Accelerometer accel(ACCEL_ADDRESS_V1);
Gyroscope gyro(GYRO_ADDRESS_V1);
Compass compass(COMPASS_ADDRESS_V1);

float gx, gy, gz, ax, ay, az, mx, my, mz;

float cx = 0, cy = 0, cz = 0;

void calibrateGyro(){
  float x = 0,y = 0,z = 0;
  for(int i = 0;i<200;i++){
     float vx, vy, vz;
     gyro.readRadPerSecXYZ(&vx, &vy, &vz);
     x+=vx;
     y+=vy;
     z+=vz;
     delay(5);
  }
  cx = -x/200;
  cy = -y/200;
  cz = -z/200;
}

void startIMU(){
  accel.begin();
  gyro.begin();
  gyro.setRange(RANGE_2000DPS);
  calibrateGyro();
  compass.begin();
  compass.calibrateMatrix(compassCalibrationMatrix, compassCalibrationBias);
  Wire.setClock(400000);
}

void updateOrientation(float fps){
  accel.readGXYZ(&ax, &ay, &az);
  gyro.readRadPerSecXYZ(&gx, &gy, &gz);
  gx+=cx;
  gy+=cy;
  gz+=cz;
  compass.readCalibrateGaussXYZ(&mx, &my, &mz);
  
  filter.setKoeff(fps, BETA);
  filter.update(gx, gy, gz, ax, ay, az, mx, my, mz);
  
  rot.x = filter.getPitchDeg();
  rot.y = filter.getRollDeg();
  rot.z = filter.getYawDeg();
}
