/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "d:/Labs/Final_Project/src/Final_Project.ino"
void setup();
void loop();
#line 1 "d:/Labs/Final_Project/src/Final_Project.ino"
SYSTEM_THREAD(ENABLED);

#include <MQTT.h>
#include "oled-wing-adafruit.h"
#include "blynk.h"
//#include "Wire.h"
//#include "SparkFun_VCNL4040_Arduino_Library.h" 
#include "LIS3DH.h"
//OledWingAdafruit display;

void callback(char* topic, byte* payload, unsigned int length);

MQTT client("lab.thewcl.com", 1883, callback);//which connection it should connect to


// recieve message
void callback(char* topic, byte* payload, unsigned int length) 
{
  char p[length + 1];
  memcpy(p, payload, length);
  p[length] = NULL;
  Serial.printlnf("%s",p);
  
  
}

//OledWingAdafruit display;
LIS3DHSPI accel(SPI, D3, WKP);


const unsigned long PRINT_SAMPLE_PERIOD = 100;
unsigned long lastPrintSample = 0;


//os_thread_t thread1; //defined the first thread
//os_thread_t thread2; //defined the second thread
//os_thread_t thread3; //defined the third thread

uint16_t tempPin = A5;
volatile double temperatureC = 0.0;
volatile double temperatureF = 0.0;
volatile double temperatureK = 0.0;

void setup()
{
  Serial.begin(9600);
  pinMode(A5, INPUT);
  Blynk.begin("DISy_9aRsQHnyt8mtvZXh09rT-tdy72R", IPAddress(167, 172, 234, 162), 9090);
  LIS3DHConfig config;
	config.setAccelMode(LIS3DH::RATE_100_HZ);
	bool setupSuccess = accel.setup(config);
	Serial.printlnf("setupSuccess=%d", setupSuccess);
  //os_thread_create(&thread1, "myThread1", OS_THREAD_PRIORITY_DEFAULT, myThread1, NULL, 1024); //creates the first thread
  //os_thread_create(&thread2, "myThread2", OS_THREAD_PRIORITY_DEFAULT, myThread2, NULL, 1024); //creates the second thread
  //os_thread_create(&thread3, "myThread3", OS_THREAD_PRIORITY_DEFAULT, myThread3, NULL, 1024); //creats the third thread
}



void loop()
{
  Blynk.run();
  

 if (millis() - lastPrintSample >= PRINT_SAMPLE_PERIOD) {
		lastPrintSample = millis();

		LIS3DHSample sample;
		if (accel.getSample(sample)) {
      Blynk.virtualWrite(V1, sample.x);
      Blynk.virtualWrite(V2, sample.y);
      Blynk.virtualWrite(V3, sample.z);
		}
		else {
			Serial.println("no sample");
		}
	}
  

 if (client.isConnected()) {
    
    client.subscribe("paris");//subscribes to the thread so it can recieve messages. 
    client.loop();
  } else {
    client.connect(System.deviceID());
  }
  
    uint64_t reading = analogRead(A5);
    double voltage = (reading * 3.3) / 4095.0;
    double temperatureC = (voltage - 0.5) * 100;
    double temperatureF = (temperatureC * 9.0 / 5.0) + 32.0;
    double temperatureK = (temperatureC + 273.15);
    String t = (String)temperatureK;
    client.publish("tjTemperature", t);
    delay(1000);
}

//void myThread1(void *args) //thread 1 controls the accelerometer data
//{
  //while (1)
  //{
    //if (millis() - lastPrintSample >= PRINT_SAMPLE_PERIOD) 
    //{
		  //lastPrintSample = millis();

      //LIS3DHSample sample;
      //if (accel.getSample(sample)) 
      //{
        //WITH_LOCK(Serial)
        //{
          //Serial.printlnf("%d,%d,%d", sample.x, sample.y, sample.z);//these are the values the accelerometer outputs, and it only does that if the accelerometer is able to get values. ie, is hooked up properly. 
          
        //}
        //String w = (String)sample.x + (String)sample.y + (String)sample.z;
        //client.publish("paris", sample);

        //Blynk.virtualWrite(V1, sample.x);//wrtites the data recieved under the variable "sample.x" to the blynk graph for easy viewing of the number 
        //Blynk.virtualWrite(V2, sample.y);//wrtites the data recieved under the variable "sample.y" to the blynk graph for easy viewing of the number 
        //Blynk.virtualWrite(V3, sample.z);//wrtites the data recieved under the variable "sample.z" to the blynk graph for easy viewing of the number 
      //}
      //else 
      //{
        //WITH_LOCK(Serial)
          //{
            //Serial.println("no sample");//if the accelerometer is not outputing data in anyway, it will print to the serial monitor that it was not able to gather a sample. 
          //} 
		  //}
    //}
    //delay(250);
	////}
//}//


//void myThread2(void *args) 
//{
  //while (1)
  //{
    //uint64_t reading = analogRead(A5);
    //double voltage = (reading * 3.3) / 4095.0;
    //double temperatureC = (voltage - 0.5) * 100;
    //double temperatureF = (temperatureC * 9.0 / 5.0) + 32.0;
    //double temperatureK = (temperatureC + 273.15);
    //String t = "BROADCAST Temp(K): " + (String)temperatureK;
    //client.publish("paris", t);
    //delay(1500);
    //WITH_LOCK(Serial)
    //{
      //Serial.println(t);
    //}
    //delay(1000);
  //}
//}