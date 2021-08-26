#include <SPI.h>
#include "cactus_io_BME280_SPI.h"
#include "Air_Quality_Sensor.h"

#define BME_SCK 13 // Serial Clock
#define BME_MISO 12 // Serial Data Out
#define BME_MOSI 11 // Serial Data In
#define BME_CS 10 // Chip Select
AirQualitySensor sensor(A0);

BME280_SPI bme(BME_CS,BME_MOSI,BME_MISO,BME_SCK);

void setup() {

  Serial.begin(9600);
    while (!Serial);
     Serial.println("Waiting sensor to init...");
    delay(20000);
    
     if (sensor.init()) {
        Serial.println("Sensor ready.");
    } else {
        Serial.println("Sensor ERROR!");
    }
    if (!bme.begin()) {
Serial.println("Could not find a valid BME280 sensor, check wiring!");
while (1);
}

bme.setTempCal(-1);// Sensor was reading high so offset by 1 degree C  
}
void loop() {

bme.readSensor();
int quality = sensor.slope();

Serial.print("Sensor value: ");
    Serial.println(sensor.getValue());

    if (quality == AirQualitySensor::FORCE_SIGNAL) {
        Serial.println("High pollution! Force signal active.");
    } else if (quality == AirQualitySensor::HIGH_POLLUTION) {
        Serial.println("High pollution!");
    } else if (quality == AirQualitySensor::LOW_POLLUTION) {
        Serial.println("Low pollution!");
    } else if (quality == AirQualitySensor::FRESH_AIR) {
        Serial.println("Fresh air.");
    }
    
Serial.print(bme.getPressure_MB()); Serial.print(" mb\t"); // Pressure in millibars
Serial.print(bme.getHumidity()); Serial.print(" %\t\t");
Serial.print(bme.getTemperature_C()); Serial.print(" *C\t");
Serial.print(bme.getTemperature_F()); Serial.println(" *F");

// Add a 2 second delay.
delay(2000); //just here to slow down the output.
}
