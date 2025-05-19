#include <OneWire.h>
#include <DallasTemperature.h>
//#include <SoftwareSerial.h>

#define SENSOR_PIN A0         // Conductivity Sensor pin
#define PH_SENSOR_PIN A3      // pH Sensor pin
#define ONE_WIRE_BUS 8        // DS18B20 temperature sensor pin

#define I 1.02                // Constant current in mA
#define cell_constant 1      // Cell constant for conductivity

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
//SoftwareSerial BTSerial(HC05_TX, HC05_RX); // Uncomment if using Bluetooth

float Celsius = 0;
float conductivity = 0;
float ph_value = 0;
String inputCommand = "";

void setup() {
    Serial.begin(9600);       // Serial Monitor
    //BTSerial.begin(9600);   // Bluetooth if used
    sensors.begin();          // Start temperature sensor
    pinMode(SENSOR_PIN, INPUT);
    pinMode(PH_SENSOR_PIN, INPUT);

    Serial.println("Bluetooth Ready! Send Command...");
}

void loop() {
    if (Serial.available()) {
        inputCommand = Serial.readString();
        inputCommand.trim();

        if (inputCommand == "1") {
            
            // --- Conductivity Measurement ---
            float cond_array[10];
            for (int i = 0; i < 10; i++) {
                int sensorValue = analogRead(SENSOR_PIN);
                float voltage = sensorValue * (5.0 / 1023.0);
                float resistance = (voltage / I) * 1000.0;
                float cond = (1.0 / resistance) * 1000.0 * cell_constant*6.5;
                cond_array[i] = cond;
                delay(50);
            }

            // --- Sort the readings ---
            for (int i = 0; i < 9; i++) {
                for (int j = i + 1; j < 10; j++) {
                    if (cond_array[i] > cond_array[j]) {
                        float temp = cond_array[i];
                        cond_array[i] = cond_array[j];
                        cond_array[j] = temp;
                    }
                }
            }

            // --- Average middle 6 values (index 2 to 7) ---
            float avgConductivity = 0.0;
            for (int i = 2; i < 8; i++) {
                avgConductivity += cond_array[i];
            }
            conductivity = avgConductivity / 6.0;

            


            // --- pH Measurement ---
            int buffer_arr[10];
            for (int i = 0; i < 10; i++) {
                buffer_arr[i] = analogRead(PH_SENSOR_PIN);
                delay(10);
            }

            // Sort readings to remove outliers
            for (int i = 0; i < 9; i++) {
                for (int j = i + 1; j < 10; j++) {
                    if (buffer_arr[i] > buffer_arr[j]) {
                        int temp = buffer_arr[i];
                        buffer_arr[i] = buffer_arr[j];
                        buffer_arr[j] = temp;
                    }
                }
            }

            unsigned long avgval = 0;
            for (int i = 2; i < 8; i++) avgval += buffer_arr[i];

            float ph_voltage = (float)avgval * 5.0 / 1024.0 / 6.0;
            ph_value = 3.5 * ph_voltage;

           

            // --- Temperature Measurement ---
            sensors.requestTemperatures();
            Celsius = sensors.getTempCByIndex(0);

            
            
            Serial.print("<");
            Serial.print("Conductivity (mS/cm): ");
            Serial.println(conductivity, 3);
            
             Serial.print("pH: ");
            Serial.println(ph_value, 2);
            
            Serial.print("Temperature (°C): ");
            Serial.println(Celsius, 2);

            // --- Health Status ---
            Serial.print("Health Status: ");
            if (conductivity >= 7.0 && conductivity <= 16.0 && ph_value >= 5.5 && ph_value <= 7.0 && Celsius >= 35 && Celsius < 37) {
                Serial.println("Normal Urine | Advice: Maintain hydration.");
            }
            else if (conductivity < 7.0 && ph_value > 7.0 && Celsius <= 35) {
                Serial.println("Over-hydration | Advice: Reduce excessive water intake.");
            }
            else if (conductivity > 16.0 && ph_value < 5.5 && Celsius > 37) {
                Serial.println("Dehydration | Advice: Drink ORS, coconut water.");
            }
            else if (conductivity >= 21.5 && conductivity <= 33.9 && ph_value < 5.5 && Celsius >= 35 && Celsius <= 38) {
                Serial.println("Uric Acid Stones | Advice: Reduce salt, red meat.");
            }
            else if (conductivity >= 21.5 && conductivity <= 32.2 && ph_value > 6.2 && Celsius >= 35 && Celsius <= 38) {
                Serial.println("Calcium Phosphate Stones | Advice: Increase citrate intake.");
            }
            else if (ph_value <= 5.5 && Celsius > 38) {
                Serial.println("UTI | Advice: Drink water, cranberry juice.");
            }
            else {
                Serial.println("Unknown Condition | Advice: Consult a doctor.");
            }
            Serial.print(">");
            delay(1000); // Avoid repeated reading
        }
    }
}
