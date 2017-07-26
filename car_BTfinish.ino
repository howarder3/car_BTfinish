#include <Servo.h>
#include <SoftwareSerial.h>

#define FRONT_MOTOR_PIN 11
#define BACK_MOTOR_PWM 3
#define BACK_MOTOR_FORWARD 5
#define BACK_MOTOR_BACKWARD 6
#define STANDBY 4
#define BT_TX 8 
#define BT_RX 9 

#define FORWARD 0
#define BACKWARD 1
#define RIGHT 2
#define LEFT 3
#define SLOW 4
#define STOP 5

#define SPEED 255

int current_speed;
Servo servo;
SoftwareSerial BT(BT_TX, BT_RX);

void setup()
{
    Serial.begin(9600);
    Serial.println(" ");
    pinMode(FRONT_MOTOR_PIN, OUTPUT);
    pinMode(BACK_MOTOR_PWM, OUTPUT);
    pinMode(BACK_MOTOR_FORWARD, OUTPUT);
    pinMode(BACK_MOTOR_BACKWARD, OUTPUT);
    pinMode(STANDBY, OUTPUT);
    analogWrite(FRONT_MOTOR_PIN, 90);
    analogWrite(BACK_MOTOR_PWM, 0);
    digitalWrite(BACK_MOTOR_FORWARD, LOW);
    digitalWrite(BACK_MOTOR_BACKWARD, LOW);
    digitalWrite(STANDBY, HIGH);
    current_speed = SPEED;

    servo.attach(FRONT_MOTOR_PIN);
    Serial.println("CAR is ready!");

    // 設定藍牙模組的連線速率
    // 如果是HC-05，請改成38400
    BT.begin(9600);
    Serial.println("Bluetooth is ready!");
}


void loop()
{
    if (Serial.available() || BT.available()) 
    {
        char val;
        if(Serial.available())
        {
          val = Serial.read();
          BT.print(val);
        }
        else 
        {
          val = BT.read();
          Serial.print(val);
        }
        switch(val){
          case '0':
            digitalWrite(STANDBY, HIGH);
            servo.write(90);
            digitalWrite(BACK_MOTOR_FORWARD, HIGH);
            digitalWrite(BACK_MOTOR_BACKWARD, LOW);
            analogWrite(BACK_MOTOR_PWM, current_speed);
            Serial.print("Forward");
            break;
          case '1':
            digitalWrite(STANDBY, HIGH);
            servo.write(90);
            digitalWrite(BACK_MOTOR_FORWARD, LOW);
            digitalWrite(BACK_MOTOR_BACKWARD, HIGH);
            analogWrite(BACK_MOTOR_PWM, current_speed);
            Serial.print("Backward");
            break;
          case '2':
            digitalWrite(STANDBY, HIGH);
            servo.write(120);
            analogWrite(BACK_MOTOR_PWM, current_speed);
            Serial.print("Right");
            break;
          case '3':
            digitalWrite(STANDBY, HIGH);
            servo.write(60);
            analogWrite(BACK_MOTOR_PWM, current_speed);
            Serial.print("Left");
            break;
          case '4':
            digitalWrite(STANDBY, HIGH);
            current_speed /= 2;
            if(current_speed <= 65 )
                 current_speed = 64;
            analogWrite(BACK_MOTOR_PWM, current_speed);
            Serial.print("Slow");
            break;
          case '5':
            digitalWrite(STANDBY, LOW);
            current_speed = SPEED;
            Serial.print("Stop");
            break;
          case '6':
            digitalWrite(STANDBY, HIGH);
            current_speed *= 2;
            if(current_speed >= 255)
                 current_speed = 255;
            analogWrite(BACK_MOTOR_PWM, current_speed);
            Serial.print("fast");
            break;
            
        }
    }
}
