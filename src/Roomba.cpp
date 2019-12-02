// #include <Arduino.h>
// #include <MPU9250.h>
// #include <Wire.h>

// #define baudRate 115200

// #define pursuit 0x0;
// #define evade 0x1;

// class Roomba {
// private:
//     // Pin assignments
//     const uint8_t photodiode = A0;
//     const uint8_t leftChannel = 9;
//     const uint8_t rightChannel = 10;

//     // Default bot configurations
//     uint8_t m_speed = 100;
//     MPU9250* IMU;

// protected:
//     void updateIMU() {
//         IMU->readSensor();
//     }

//     void forwardConfig() {
//         digitalWrite(4, HIGH);
//         digitalWrite(5, LOW);
//         digitalWrite(6, LOW);
//         digitalWrite(7, HIGH);
//     }

//     void backwardConfig() {
//         digitalWrite(4, LOW);
//         digitalWrite(5, HIGH);
//         digitalWrite(6, HIGH);
//         digitalWrite(7, LOW);
//     }

// public:
//     /* Constructor */
//     Roomba(MPU9250* imu) {
//         IMU = imu;
//     }

//     /* setup() Function */
//     void begin() {
//         // Initialize the serial port
//         Serial.begin(baudRate);
        
//         // Initialize and configure IMU
//         Serial.println("initializing IMU...");
//         int imu_status = IMU->begin();
//         if (imu_status < 0) {
//             Serial.print("unable to initialize IMU! Status code: ");
//             Serial.println(imu_status);
//             while(1);
//         } else {
//             Serial.print("IMU initialized with status code: ");
//             Serial.println(imu_status);
//         }
//         IMU->setGyroRange(MPU9250::GYRO_RANGE_250DPS);
//     }

//     /* Motor Controls */
//     void forward() {
//         forwardConfig();
//         analogWrite(rightChannel, m_speed);
//         analogWrite(leftChannel, m_speed+4);
//     }

//     void backward() {
//         backwardConfig();
//         analogWrite(rightChannel, m_speed);
//         analogWrite(leftChannel, m_speed-4);
//     }

//     void stopTurn() {
//         analogWrite(rightChannel, 0);
//         analogWrite(leftChannel, 0);
        
//         // TODO: implement turning
//     }

//     // setSpeed sets the target straight-line motor speed between 0-255.
//     void setSpeed(uint8_t speed) {
//         if (speed < 35) {
//             m_speed = 0;
//         } else {
//             m_speed = speed;
//         }
//     }

//     // getSpeed returns the current straight-line motor speed
//     unsigned getSpeed() {
//         return (unsigned)m_speed;
//     }

//     // Print with `Serial.print(Roomba.getAccelX(), 6)`
//     float getAccelX() {
//         updateIMU();
//         return IMU->getAccelX_mss();
//     }

//     // Print with `Serial.print(Roomba.getAccelY(), 6)`
//     float getAccelY() {
//         updateIMU();
//         return IMU->getAccelY_mss();
//     }

//     // Print with `Serial.print(Roomba.getAccelZ(), 6)`
//     float getAccelZ() {
//         updateIMU();
//         return IMU->getAccelZ_mss();
//     }
// };
