/*
  HS300x - Read Sensors

  This example reads data from the on-board HS300x sensor of the
  Nano 33 BLE Sense Rev2 and prints the temperature and humidity sensor
  values to the Serial Monitor once a second.

  The circuit:
  - Arduino Nano 33 BLE Sense Rev2

  This example code is in the public domain.
*/

#ifdef NANO33BLE_SENSE_REV2
  #include <Arduino_HS300x.h>
#elif defined(NANO33BLE_SENSE)
  #include <Arduino_HTS221.h>
#endif
float old_temp = 0;
float old_hum = 0;

#ifdef NANO33BLE_SENSE_REV2
  HS300xClass& sensor = HS300x;
#else
  HTS221Class& sensor = HTS;
#endif

void setup() {
  Serial.begin(9600);
  while (!Serial);

  if (!sensor.begin()) {
    Serial.println("Failed to initialize humidity temperature sensor!");
    while (1);
  }
}

void loop() {
  // read all the sensor values
  float temperature = sensor.readTemperature();
  float humidity    = sensor.readHumidity();
  if (abs(old_temp - temperature) >= 0.5 || abs(old_hum - humidity) >= 1 ){
    // print each of the sensor values
    Serial.print("Temperature = ");
    Serial.print(temperature);
    Serial.println(" °C");

    Serial.print("Humidity    = ");
    Serial.print(humidity);
    Serial.println(" %");

    // print an empty line
    Serial.println();

    // wait 1 second to print again
    delay(1000);
  }
}