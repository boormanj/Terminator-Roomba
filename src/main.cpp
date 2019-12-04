#include <Arduino.h>
#include <PID_v1.h>
// #include <MPU9250.h>

#define baudRate 115200
#define diode0 A0
#define diode1 A1
#define diode2 A2
#define diode3 A3
#define leftChannel 9
#define rightChannel 10

int offset0, offset1, offset2, offset3;
int rightSpeed = 100;
int leftSpeed = 100;
double setpoint, input, output;
double Kp = 1, Ki = 0, Kd = 0;

// MPU9250 IMU(Wire, 0x68);
PID pid(&input, &output, &setpoint, Kp, Ki, Kd, REVERSE);

#pragma region Movement
void forwardRight()  { digitalWrite(6, LOW);  digitalWrite(7, HIGH); }
void forwardLeft()   { digitalWrite(4, HIGH); digitalWrite(5, LOW); }
void backwardRight() { digitalWrite(6, HIGH); digitalWrite(7, LOW); }
void backwardLeft()  { digitalWrite(4, LOW);  digitalWrite(5, HIGH); }

void forwardConfig() {
    forwardRight();
    forwardLeft();
}

void backwardConfig() {
    backwardRight();
    backwardLeft();
}

void moveForward(int rightSpeed, int leftSpeed) {
    forwardConfig();
    analogWrite(rightChannel, rightSpeed);
    analogWrite(leftChannel, leftSpeed);
}

void stop() {
    forwardConfig();
    analogWrite(rightChannel, 0);
    analogWrite(leftChannel, 0);
}
#pragma endregion

#pragma region Calibrated Reading
int readLeftIR() {
    return analogRead(diode3) - offset3;
}

int readCenterLeftIR() {
    return analogRead(diode2) - offset2;
}

int readCenterRightIR() {
    return analogRead(diode1) - offset1;
}

int readRightIR() {
    return analogRead(diode0) - offset0;
}

int leftSideAvg() {
    return (readCenterLeftIR() + readLeftIR()) / 2;
}

int rightSideAvg() {
    return (readCenterRightIR() + readRightIR()) / 2;
}

int deviation() {
    return rightSideAvg() - leftSideAvg();
}
#pragma endregion

#pragma region Beacon Finding
bool beaconFound() {
    int left        = readLeftIR();
    int centerLeft  = readCenterLeftIR();
    int centerRight = readCenterRightIR();
    int right       = readRightIR();

    int threshold = 20;

    if (abs(left) > threshold || abs(centerLeft) > threshold || abs(centerRight) > threshold || abs(right) > threshold) {
        return true;
    }
    return false;
}

bool beaconRight() {
    return deviation() > 0;
}

bool beaconLeft() {
    return deviation() < 0;
}
#pragma endregion

void setup() {
    delay(2000);
    Serial.begin(baudRate);
    
    // IR Calibration
    offset0 = analogRead(diode0);
    offset1 = analogRead(diode1);
    offset2 = analogRead(diode2);
    offset3 = analogRead(diode3);
    Serial.println("IR Photodiodes Calibrated.");
    
    // PID setup
    input = deviation();
    setpoint = 0;
    pid.SetOutputLimits(-25, 25);
    pid.SetMode(AUTOMATIC);
    Serial.println("PID Controller Initialized.");

    // Move to Center
    moveForward(100, 104);
    Serial.println("Bot Moving");
    delay(2000);
    stop();
    Serial.println("Bot Stopping");
    delay(750);
}

void loop() {
    input = deviation();
    pid.Compute();
    moveForward(rightSpeed - output, leftSpeed + output);

    #pragma region Beacon Testing
    Serial.print("L:  "); Serial.print(readLeftIR()); Serial.print("\t");
    Serial.print("CL: "); Serial.print(readCenterLeftIR()); Serial.print("\t");
    Serial.print("CR: "); Serial.print(readCenterRightIR()); Serial.print("\t");
    Serial.print("R:  "); Serial.print(readRightIR()); Serial.print("\t");
    Serial.print("D:  "); Serial.print(deviation()); Serial.print("\t");
    Serial.print("O:  "); Serial.print(output); Serial.print("\t");

    if (beaconFound()) {
        Serial.print("BEACON");
        if (beaconRight()) {
            Serial.println(" RIGHT --> ");
        } else if (beaconLeft()) {
            Serial.println(" <-- LEFT ");
        } else {
            Serial.println(" -- CENTER -- ");
        }
    } else {  
        Serial.println();
    }

    delay(100);
    #pragma endregion
    
}


