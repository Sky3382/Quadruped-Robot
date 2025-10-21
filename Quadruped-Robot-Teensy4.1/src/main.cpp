#include "config.h"
#include "body.h"

Adafruit_PWMServoDriver pwmController = Adafruit_PWMServoDriver();
MPU6050 mpu(Wire1);

Body robot;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); // USB Serial
  Serial.println("Serial initialized!");

  Serial1.begin(115200);  // RX1 = pin 0, TX1 = pin 1 Communiction with esp

  //initialyse MPU6050
  Wire1.begin();
  mpu.begin();

  // Initialize PCA9685
  pwmController.begin();
  pwmController.setPWMFreq(50);  // 50 Hz for analog servos

  robot.moveToPose(0, 0, 0, 0, 0, 0);

  //MoveToStartPosition();

  delay(3000); //wait for stabilization

  Serial.println(F("Calculating gyro offset, do not move MPU6050..."));

  mpu.calcOffsets(true,true); //calibrate MPU6050
  delay(1000);
  Serial.println(F("Calibration done."));

  delay(100);
}
