#include <Wire.h>
#include "DS1307.h"
#include "DHT.h"
#include <SPI.h>
#include <SD.h>


//define a object of DS1307 class
DS1307 clock;
String dateTimeString="";

// Initializethe DHT22 component
#define DHTPIN 6
#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE);


const int lightSensorPin=A0;

float temperature;
float humidity;
int light;

//pin configuration for the SDCard
const int chipSelect = 4;

int ledPin=13;

//Use pin 7 to receive the signal from the module
#define PIR_MOTION_SENSOR 7


void setup(){
  Serial.begin(9600);
  clock.begin();
	dht.begin();
	pinMode(chipSelect,OUTPUT);
	pinMode(13,OUTPUT);
	pinMode(PIR_MOTION_SENSOR, INPUT);


	Serial.print("Initializing SD card...");

	// see if the card is present and can be initialized:
	while (!SD.begin(chipSelect)) {
		Serial.println("Card failed, or not present");
		// don't do anything more:
		delay(1000);
	}
	Serial.println("card initialized.");
}

void loop(){
	if(digitalRead(PIR_MOTION_SENSOR)){//if it detects the moving people?
		updateTime();
		readtemperatureHumidity();
		readLightSensor();
		saveData();
		delay(2000);
	}else{
		//non si muove una foglia
	}
	 delay(200);
}

void saveData(){
	//turn on the pin 13 every time you write to SD card
	digitalWrite(13,HIGH);

	// make a string for assembling the data to log:
  String dataString = "";

	dataString+=dateTimeString;
	dataString+=',';
	dataString+=temperature;
	dataString+=',';
	dataString+=humidity;
	dataString+=',';
	dataString+=light;

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  File dataFile = SD.open("datalog.csv", FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
    // print to the serial port too:
		Serial.println("Writing to file");
    Serial.println(dataString);
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  }
	digitalWrite(13,LOW);
}

void readLightSensor(){
	light=analogRead(lightSensorPin);
}

//get temperature and humidity data from the sensor
void readtemperatureHumidity(){
	// Reading temperature or humidity takes about 250 milliseconds!
	// Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
	float h = dht.readHumidity();
	float t = dht.readTemperature();

	// check if returns are valid, if they are NaN (not a number) then something went wrong!
	if (isnan(t) || isnan(h)){
			Serial.println("Failed to read from DHT");
	}else{
		temperature=t;
		humidity=h;
	}
}

//get the time from the RTC clock
void updateTime(){
  clock.getTime();
	dateTimeString="";
	dateTimeString+=String(clock.dayOfMonth, DEC);
	dateTimeString+="/";
	dateTimeString+=String(clock.month, DEC);
	dateTimeString+="/";
	dateTimeString+=String(clock.year+2000, DEC);
	dateTimeString+=",";
	dateTimeString+=String(clock.hour, DEC);
	dateTimeString+=":";
	dateTimeString+=String(clock.minute, DEC);
	dateTimeString+=":";
	dateTimeString+=String(clock.second, DEC);
}
