#include <SoftwareSerial.h>
#include <SPI.h>
#include <Wire.h>

#define CAM_RX  12
#define CAM_TX  13
#define CAM_PWR 10


SoftwareSerial camSerial(CAM_RX, CAM_TX); // RX, TX

int photoIndex=0;

void setup() {
  camSerial.begin(38400);
  Serial.begin(9600);
  initialiseCamera();

  digitalWrite(CAM_PWR, 0);

}

void loop() {
  // put your main code here, to run repeatedly:
  capturePicture();
  delay(5000);
}

// Initialise camera module (blocking)
void initialiseCamera() {
  camSerial.write('~');
  camSerial.write('i');
  camSerial.write(0x0D);
  camSerial.write(0x0A);

  delay(100);

  while (camSerial.available() < 2) {
    // Wait for "INI"
  }

#ifdef DEBUG
  Serial.println(F("Cam init'd"));
#endif

  // Flush serial
  while (camSerial.available() > 0) {
    camSerial.read();
  }
}


// Capture picture
void capturePicture() {
  digitalWrite(CAM_PWR, 1);
  
  // Flush serial
  while (camSerial.available() > 0) {
    camSerial.read();
  }

  // Send "Take photo" command to camera module
  camSerial.write(0x21);
  camSerial.write((uint8_t)photoIndex++);
  camSerial.write(0x0D);
  camSerial.write(0x0A);
  delay(1400);

  // Wait for saving to complete
  Serial.print("saving");
  while (camSerial.available() <= 0) {
    Serial.print(".");
  }
  Serial.println();

  // Flush serial
  while (camSerial.available() > 0) {
    camSerial.read();
  }

  digitalWrite(CAM_PWR, 0);

}
