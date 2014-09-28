#include <NewPing.h>
#include <Wire.h>
#include <UTFT.h>

// Declare which fonts we will be using
extern uint8_t SmallFont[];

// Set the pins to the correct ones for your development shield
// ------------------------------------------------------------
// Standard Arduino Mega/Due shield            : <display model>,38,39,40,41
// CTE TFT LCD/SD Shield for Arduino Due       : <display model>,25,26,27,28
// Teensy 3.x TFT Test Board                   : <display model>,23,22, 3, 4
// ElecHouse TFT LCD/SD Shield for Arduino Due : <display model>,22,23,31,33
//
// Remember to change the model parameter to suit your display module!
UTFT myGLCD(ITDB32S,38,39,40,41);


#define MAX_DISTANCE 500 // Maximum distance (in cm) to ping.
#define PING_INTERVAL 33 // Milliseconds between sensor pings (29ms is about the min to avoid cross-sensor echo).

#define RRT 46
#define RRE 47
#define RT  48
#define RE  49
#define RLT 50
#define RLE 51
#define FRT 42
#define FRE 43
#define FT  44
#define FE  45
#define FLT 52
#define FLE 53

NewPing sonar_forward(FT, FE, MAX_DISTANCE); 
NewPing sonar_forward_left(FLT, FLE, MAX_DISTANCE); 
NewPing sonar_forward_right(FRT, FRE, MAX_DISTANCE); 
NewPing sonar_reverse(RT, RE, MAX_DISTANCE); 
NewPing sonar_reverse_left(RLT, RLE, MAX_DISTANCE); 
NewPing sonar_reverse_right(RRT, RRE, MAX_DISTANCE); 

char cmd = ' ';
char prev_cmd = ' ';
unsigned int safe_distance = 10;
int loop_count = 0;
int reset_delay = 10;

void setup() {
    Serial.begin(9600);           // set up Serial library at 9600 bps
    Serial1.begin(9600);
    Wire.begin();
    
    pinMode(FLT, OUTPUT);
    pinMode(FLE, INPUT);
    pinMode(FT,  OUTPUT);
    pinMode(FE,  INPUT);
    pinMode(FRT, OUTPUT);
    pinMode(FRE, INPUT);
    pinMode(RLT, OUTPUT);
    pinMode(RLE, INPUT);
    pinMode(RT,  OUTPUT);
    pinMode(RE,  INPUT);
    pinMode(RRT, OUTPUT);
    pinMode(RRE, INPUT);

    myGLCD.InitLCD();
    myGLCD.setFont(SmallFont);
    myGLCD.clrScr();
}

void serial_print (char *direction, int secs, int cms)
{
    char output_string[256];
    sprintf(output_string, "%s - %d cms - %d us", direction, secs, cms);
    Serial.println(output_string);
    myGLCD.print(output_string, CENTER, 100);
    
}

boolean check_forward() {
    unsigned int uS = sonar_forward.ping(); // Send ping, get ping time in microseconds (uS).
    unsigned int distance = uS / US_ROUNDTRIP_CM;
    char *str;

    myGLCD.clrScr();
    serial_print("forward", distance, uS);

    if (distance < safe_distance) {  // This is where the LED On/Off happens
//    if ((distance !=0) && (distance < safe_distance)) {  // This is where the LED On/Off happens
        myGLCD.setColor(255, 0, 0);
        myGLCD.fillRect(290, 105, 319, 134);
        return false;
    }
    else {
        myGLCD.setColor(0, 255, 0);
        myGLCD.fillRect(290, 105, 319, 134);
        return true;
    }
}

boolean check_forward_left() {
    unsigned int uS = sonar_forward_left.ping(); // Send ping, get ping time in microseconds (uS).
    unsigned int distance = uS / US_ROUNDTRIP_CM;

    myGLCD.clrScr();
    serial_print("forward_left", distance, uS);

    if (distance < safe_distance) {  // This is where the LED On/Off happens
//    if ((distance !=0) && (distance < safe_distance)) {  // This is where the LED On/Off happens
        myGLCD.setColor(255, 0, 0);
        myGLCD.fillRect(290, 00, 319, 29);
        return false;
    }
    else {
        myGLCD.setColor(0, 255, 0);
        myGLCD.fillRect(290, 00, 319, 29);
        return true;
    }
}

boolean check_forward_right() {
    unsigned int uS = sonar_forward_right.ping(); // Send ping, get ping time in microseconds (uS).
    unsigned int distance = uS / US_ROUNDTRIP_CM;

    myGLCD.clrScr();
    serial_print("forward_right", distance, uS);

    if (distance < safe_distance) {  // This is where the LED On/Off happens
//    if ((distance !=0) && (distance < safe_distance)) {  // This is where the LED On/Off happens
        myGLCD.setColor(255, 0, 0);
        myGLCD.fillRect(290, 210, 319, 239);
        return false;
    }
    else {
        myGLCD.setColor(0, 255, 0);
        myGLCD.fillRect(290, 210, 319, 239);
        return true;
    }
}

boolean check_reverse() {
    unsigned int uS = sonar_reverse.ping(); // Send ping, get ping time in microseconds (uS).
    unsigned int distance = uS / US_ROUNDTRIP_CM;

    myGLCD.clrScr();
    serial_print("reverse", distance, uS);
 
    if (distance < safe_distance) {  // This is where the LED On/Off happens
//    if ((distance !=0) && (distance < safe_distance)) {  // This is where the LED On/Off happens
        myGLCD.setColor(255, 0, 0);
        myGLCD.fillRect(0, 105, 29, 134);
        return false;
    }
    else {
        myGLCD.setColor(0, 255, 0);
        myGLCD.fillRect(0, 105, 29, 134);
        return true;
    }
}

boolean check_reverse_left() {
    unsigned int uS = sonar_reverse_left.ping(); // Send ping, get ping time in microseconds (uS).
    unsigned int distance = uS / US_ROUNDTRIP_CM;

    myGLCD.clrScr();
    serial_print("reverse_left", distance, uS);

    if (distance < safe_distance) {  // This is where the LED On/Off happens
//    if ((distance !=0) && (distance < safe_distance)) {  // This is where the LED On/Off happens
        myGLCD.setColor(255, 0, 0);
        myGLCD.fillRect(0, 0, 29, 29);
        return false;
    }
    else {
        myGLCD.setColor(0, 255, 0);
        myGLCD.fillRect(0, 0, 29, 29);
        return true;
    }
}

boolean check_reverse_right() {
    unsigned int uS = sonar_reverse_right.ping(); // Send ping, get ping time in microseconds (uS).
    unsigned int distance = uS / US_ROUNDTRIP_CM;

    myGLCD.clrScr();
    serial_print("reverse_right", distance, uS);

    if (distance < safe_distance) {  // This is where the LED On/Off happens
//    if ((distance !=0) && (distance < safe_distance)) {  // This is where the LED On/Off happens
        myGLCD.setColor(255, 0, 0);
        myGLCD.fillRect(0, 210, 29, 239);
        return false;
    }
    else {
        myGLCD.setColor(0, 255, 0);
        myGLCD.fillRect(0, 210, 29, 239);
        return true;
    }
}

void wsend(char c)
{
Serial.println("wire before begin");  
    Wire.beginTransmission(9);
Serial.println("wire before write");  
    Wire.write(c);
Serial.println("wire after write");  
    Wire.endTransmission();
Serial.println("wire after end");  
}

void stop()
{
    wsend('S');
}

void forward()
{
    if (check_forward())
    {
        wsend('F');
    }
    else
    {
        stop();
    }
}

void reverse(){
    if (check_reverse())
    {
        wsend('B');
    }
    else
    {
        stop();
    }
}

void forward_left(){
    if (check_forward_left())
    {
        wsend('G');
    }
    else
    {
        stop();
    }
}

void forward_right(){
    if (check_forward_right())
    {
        wsend('I');
    }
    else
    {
        stop();
    }
}

void reverse_left(){
    if (check_reverse_left())
    {
        wsend('H');
    }
    else
    {
        stop();
    }
}

void reverse_right(){
    if (check_reverse_right())
    {
        wsend('J');
    }
    else
    {
        stop();
    }
}

void loop() { 

    delay(50);
        myGLCD.setColor(255, 0, 0);
        myGLCD.fillRect(290, 105, 319, 134);
 
        if (prev_cmd == 'F') {
            if (!check_forward())
            {
                stop();
            }
        } else if (prev_cmd == 'B') {
            if (!check_reverse())
            {
                stop();
            }
        } else if (prev_cmd == 'G') {
            if (!check_forward_left())
            {
                stop();
            }
        } else if (prev_cmd == 'I') {
            if (!check_forward_right())
            {
                stop();
            }
        } else if (prev_cmd == 'H') {
            if (!check_reverse_left())
            {
                stop();
            }
        } else if (prev_cmd == 'J') {
            if (!check_reverse_right())
            {
                stop();
            }
        }

    if (Serial1.available()) {
        cmd = Serial1.read();

        if (cmd == 'F') {
            forward();
            prev_cmd = cmd;
        } else if (cmd == 'B') {
            reverse();
            prev_cmd = cmd;
        } else if (cmd == 'G') {
            forward_left();
            prev_cmd = cmd;
        } else if (cmd == 'I') {
            forward_right();
            prev_cmd = cmd;
        } else if (cmd == 'H') {
            reverse_left();
            prev_cmd = cmd;
        } else if (cmd == 'J') {
            reverse_right();
            prev_cmd = cmd;
        } else if (cmd == 'S') {
            stop();
            prev_cmd = cmd;
/*        } else if (cmd == '1') {
            move_duration = 1;
            prev_cmd = cmd;
        } else if (cmd == '2') {
            move_duration = 2;
            prev_cmd = cmd;
        } else if (cmd == '3') {
            move_duration = 3;
            prev_cmd = cmd;
        } else if (cmd == '4') {
            move_duration = 4;
            prev_cmd = cmd;
        } else if (cmd == '5') {
            move_duration = 5;
            prev_cmd = cmd;
        } else if (cmd == '6') {
            move_duration = 6;
            prev_cmd = cmd;
        } else if (cmd == '7') {
            move_duration = 7;
            prev_cmd = cmd;
        } else if (cmd == '8') {
            move_duration = 8;
            prev_cmd = cmd;
        } else if (cmd == '9') {
            move_duration = 9;
            prev_cmd = cmd;
*/        }
    }
}
