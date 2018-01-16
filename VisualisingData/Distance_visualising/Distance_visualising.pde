import processing.serial.*;

Serial myPort;
String val;

boolean firstContact = false;

void setup() {

    size(500, 500);

    String portName = Serial.list()[0];
    myPort = new Serial(this, portName, 9600);

    // store incoming data in buffer until reading a carriage return
    myPort.bufferUntil('\n');

}

void draw() {
    //not needed
}

void serialEvent( Serial myPort) {

    val = myPort.readStringUntil('\n');

    if (val != null) {
        val = trim(val);
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
            println(val);


        }
    }
}