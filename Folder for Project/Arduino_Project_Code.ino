#include <SD.h>

File moistureStatus;

const int motor = 2; //sets the peristaltic pump as motor and placed in digital pin 2
String statusreport = ""; //stores the contents of the txt file to be read
int counter = 0;

void setup() {
  
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) { // wait for serial port to connect. Needed for native USB port only
  }

  Serial.print("Initializing SD card..."); //prints out the status of the SD card to the console

  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");

  pinMode(motor, OUTPUT); //sets the motor of the peristaltic liquid pump as output

  // open the file for reading:
  moistureStatus = SD.open("output.txt");
  if (moistureStatus) {
    Serial.println("output.txt:");
    
    // read from the file until there's nothing else in it:
    while (moistureStatus.available()) {
     statusreport += (char)moistureStatus.read(); // stores the text from the txt file in statusreport
    }
  
    // closes the file:
    moistureStatus.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
}

void loop() {
  //compares the content of statusreport with predefined conditions (optimal, almost dry, or dry)
  //loops the condition until counter reaches limit (converts to approximately a minimum of 5 minutes of watering per update)
  while (counter <= 60){
    if (statusreport == "optimal") {
        //does nothing since the soil meets the moisture requirement
        counter += 1;   
        }
    if (statusreport == "almost dry") {
        digitalWrite(motor, HIGH); //turns the pump on
        delay(5000); //keeps pump on for 5 seconds
        digitalWrite(motor,LOW); //turns the pump off
        delay(30000); //keeps pump on for 30 seconds  
        counter += 1;     
        }
    if (statusreport == "dry") {
        digitalWrite(motor, HIGH); //turns the pump on
        delay(7500); //keeps pump on for 7.5 seconds
        digitalWrite(motor,LOW); //turns the pump off
        delay(30000); //keeps pump on for 30 seconds  
        counter += 1;           
        }
  }
  exit(0); //exits the loop
}
