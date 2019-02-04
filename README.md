# Thing_centered_design
Some code examples on how to use Arduino as dataloggers


# Instructions

## Step 1 - install the libraries
Copy all the files and folder you find in the Arduino_Libraries folder of this repository to your Arduino Libraryes folder, usyally that is inside Documents->Arduino->Libraries

## Connect your hardware
Please find inside the example folder more information on the specific wiring needed for each code example

## Step 2 - update RTC
The kit makes use of the RTC module to keep track of time. To reset time and date follow the guide [here](http://wiki.seeedstudio.com/Grove-RTC/)

## Check out the code examples
Here is a list of the code examples you will find in this repository:

	**TASK CAM EXAMPLES**
	- How to program the "task cam" to take a picture at regular intervals
	- How to program the "task cam" to trigger the shutter based on a sensors

	**SD DATA LOGGING EXAMPLES**
	- How to save some sensor data (temperature, humidity, light) to SD card at regular time intervals
	- How to save datapoints to SD card only when a specific sensor is triggered (eg. movement sensor)

## HINTS
	- use a power bank to power your project
	- try to hide the sensors as much as possible

**NB:** in case you produce code that you think might be used by other students contribute to this repository and comment by opening issues.
