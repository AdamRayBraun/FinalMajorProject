import processing.serial.*;

Serial myPort;
String val;
boolean firstContact = false;
int[] ArduinoData;

int cm;
int[] MotorData = {0,0,0,0,0};

void setup() {

    size(1000, 700);
    background(255, 204, 0);

    String portName = Serial.list()[0];
    myPort = new Serial(this, portName, 9600);

    // store incoming data in buffer until reading a carriage return
    myPort.bufferUntil('\n');
}

void draw() {
    background(255, 204, 0);
    if (firstContact == true) {
        for (int x = 0; x < 5; x = x + 1) {

            float CircleColour = map(MotorData[x], 0, 153, 0, 255);
            float CircleSize = map(MotorData[x], 0, 153, 150, 250);

            // CircleColour = MotorData[x];
            // CircleSize = MotorData[x];

            fill(CircleColour, 0, 0);
            ellipse((((width/7) * x) + (width/7)), (height / 2), CircleSize, CircleSize);
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
                println("contact");
            }
        }
        // if already made first contact
        else {

            //Parse sent ints after each comma
            ArduinoData = int(split(val, ","));

            // cm value is always first int - # of motors might change
            cm = ArduinoData[0];

            for (int x = 1; x < MotorData.length; x = x+1) {
                MotorData[x - 1] = ArduinoData[x];
            }
        }
    }
}
