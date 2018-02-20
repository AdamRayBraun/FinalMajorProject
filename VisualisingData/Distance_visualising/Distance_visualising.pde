/*
Sketch to visualise current strength of each vibration motor being run by
the Arduino

NEEDS TO BE CONNECTED TO ARDUINO TO WORK
    - if not will not find a serial connection and throw a right wobbly
*/


import processing.serial.*;

// communication with arduino
Serial myPort;
String val;
boolean firstContact = false;

// variables from arduino
int[] ArduinoData;
int[] MotorData = {0,0,0,0,0};

void setup() {

    size(1000, 700);
    background(255, 204, 0);

    // comms set up
    String portName = Serial.list()[0];
    myPort = new Serial(this, portName, 9600);

    // store incoming data in buffer until reading a carriage return
    myPort.bufferUntil('\n');
}

void draw() {
    background(255, 204, 0);

    if (firstContact == true) {
        // draw circles to visualise strength
        for (int x = 0; x < 5; x++) {
            // map circle size and colour to motor strength
            float CircleColour = map(MotorData[x], 0, 153, 0, 255);
            float CircleSize = map(MotorData[x], 0, 153, 150, 250);

            fill(CircleColour, 10, 10);
            ellipse((((width/7) * x) + (width/7)), (height / 2), 150, CircleSize);
        }
    }
}

void serialEvent( Serial myPort) {

    val = myPort.readStringUntil('\n');

    if (val != null) {
        val = trim(val);
        // print raw data recieved
        println(val);

        // listen for first contact from arduino
        if (firstContact == false) {
            if (val.equals("A")) {
                myPort.clear();
                firstContact = true;
                myPort.write("A");
                println("CONTACT MADE");
            }
        }
        // if already made first contact
        else {

            //Parse sent ints after each comma
            ArduinoData = int(split(val, ","));

            for (int x = 0; x < MotorData.length; x++) {
                MotorData[x] = ArduinoData[x];
            }
        }
    }
}
