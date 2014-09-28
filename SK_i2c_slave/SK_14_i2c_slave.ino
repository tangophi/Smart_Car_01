#include <AFMotor.h>
#include <Wire.h>




AF_DCMotor RBmotor(1, MOTOR12_64KHZ);   // right back wheel
AF_DCMotor RFmotor(2, MOTOR12_64KHZ);   // right front wheel
AF_DCMotor LBmotor(4, MOTOR34_64KHZ);   // left back wheel
AF_DCMotor LFmotor(3, MOTOR34_64KHZ);   // left front wheel

int min_speed = 0;
int max_speed = 255;
int move_duration = 1;
char cmd = ' ';
char prev_cmd = ' ';
unsigned int safe_distance = 30;
int iteration_delay = 0;
int loop_count = 0;
int reset_delay = 10;

void setup() {
    Serial.begin(9600);           // set up Serial library at 9600 bps

    Wire.begin(9);
    Wire.onReceive(receiveEvent);
    
    // turn on motor
    RBmotor.setSpeed(200);
    RFmotor.setSpeed(200);
    LBmotor.setSpeed(200);
    LFmotor.setSpeed(200);

    RBmotor.run(RELEASE);
    RFmotor.run(RELEASE);
    LBmotor.run(RELEASE);
    LFmotor.run(RELEASE);
}

void receiveEvent(int howMany)
{
    cmd = Wire.read();
}

void serial_print (char *direction, int secs, int cms)
{
    char output_string[256];
    sprintf(output_string, "%-13s - %3d cms - %5d microseconds", direction, secs, cms);
    Serial.println(output_string);
}

void stop()
{
    RBmotor.setSpeed(0);  
    RFmotor.setSpeed(0);  
    LBmotor.setSpeed(0);  
    LFmotor.setSpeed(0);  
    
    RBmotor.run(RELEASE);
    RFmotor.run(RELEASE);
    LBmotor.run(RELEASE);
    LFmotor.run(RELEASE);
}

void forward(){
    int i = 0;
    RBmotor.run(FORWARD);
    RFmotor.run(FORWARD);
    LBmotor.run(FORWARD);
    LFmotor.run(FORWARD);

    for (i=0; i<move_duration; i++) {
        RBmotor.setSpeed(max_speed);  
        RFmotor.setSpeed(max_speed);  
        LBmotor.setSpeed(max_speed);  
        LFmotor.setSpeed(max_speed);  
        delay(iteration_delay);
    }
}

void reverse(){
    int i = 0;
    RBmotor.run(BACKWARD);
    RFmotor.run(BACKWARD);
    LBmotor.run(BACKWARD);
    LFmotor.run(BACKWARD);

    for (i=0; i<move_duration; i++) {
        RBmotor.setSpeed(max_speed);  
        RFmotor.setSpeed(max_speed);  
        LBmotor.setSpeed(max_speed);  
        LFmotor.setSpeed(max_speed);  
        delay(iteration_delay);
    }
}

void forward_left(){
    int i = 0;
    RBmotor.run(FORWARD);
    RFmotor.run(FORWARD);
    LBmotor.run(FORWARD);
    LFmotor.run(FORWARD);

    for (i=0; i<move_duration; i++) {
        RBmotor.setSpeed(max_speed);  
        RFmotor.setSpeed(max_speed);  
        LBmotor.setSpeed(min_speed);  
        LFmotor.setSpeed(min_speed);  
        delay(iteration_delay);
    }
}

void forward_right(){
    int i = 0;
    RBmotor.run(FORWARD);
    RFmotor.run(FORWARD);
    LBmotor.run(FORWARD);
    LFmotor.run(FORWARD);

    for (i=0; i<move_duration; i++) {
        RBmotor.setSpeed(min_speed);  
        RFmotor.setSpeed(min_speed);  
        LBmotor.setSpeed(max_speed);  
        LFmotor.setSpeed(max_speed);  
        delay(iteration_delay);
    }
}

void reverse_left(){
    int i = 0;
    RBmotor.run(BACKWARD);
    RFmotor.run(BACKWARD);
    LBmotor.run(BACKWARD);
    LFmotor.run(BACKWARD);

    for (i=0; i<move_duration; i++) {
        RBmotor.setSpeed(max_speed);  
        RFmotor.setSpeed(max_speed);  
        LBmotor.setSpeed(min_speed);  
        LFmotor.setSpeed(min_speed);  
        delay(iteration_delay);
    }
}

void reverse_right(){
    int i = 0;
    RBmotor.run(BACKWARD);
    RFmotor.run(BACKWARD);
    LBmotor.run(BACKWARD);
    LFmotor.run(BACKWARD);

    for (i=0; i<move_duration; i++) {
        RBmotor.setSpeed(min_speed);  
        RFmotor.setSpeed(min_speed);  
        LBmotor.setSpeed(max_speed);  
        LFmotor.setSpeed(max_speed);  
        delay(iteration_delay);
    }
}

void loop() { 
    delay(10);
    
    if (cmd == 'F') {
        forward();
    } else if (cmd == 'B') {
        reverse();
    } else if (cmd == 'G') {
        forward_left();
    } else if (cmd == 'I') {
        forward_right();
    } else if (cmd == 'H') {
        reverse_left();
    } else if (cmd == 'J') {
        reverse_right();
    } else if (cmd == 'S') {
        stop();
    }
}
