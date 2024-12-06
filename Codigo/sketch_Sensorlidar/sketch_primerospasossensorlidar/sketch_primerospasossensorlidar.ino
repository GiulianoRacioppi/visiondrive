#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // Dirección I2C del LCD y tamaño (16 columnas x 2 filas)

int dist; // Medición actual de distancia del LiDAR
int strength; // Fuerza de la señal del LiDAR
float temperature;

void setup() {
    Serial.begin(115200);
    Serial2.begin(115200, SERIAL_8N1, 16, 17); // Inicializar el HardwareSerial para TFMini (GPIO 16 = RX, GPIO 17 = TX)
    lcd.init(); // Inicializar el LCD
    lcd.backlight(); // Encender la retroiluminación del LCD
    lcd.clear(); // Limpiar el LCD
}

void loop() {
    // Leer y mostrar la tercera lectura del sensor LiDAR
    if (Serial2.available()) {
        int count = 0;
        while (Serial2.available()) {
            int data = Serial2.read();
            if (count == 2) {
                dist = data;
            } else if (count == 3) {
                dist += (data << 8);
            } else if (count == 4) {
                strength = data;
            } else if (count == 5) {
                strength += (data << 8);
            } else if (count == 6) {
                temperature = data;
            } else if (count == 7) {
                temperature += (data << 8);
            }
            count++;
        }

        // Mostrar la tercera lectura en el LCD
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Distance: ");
        lcd.print(dist);
        lcd.print(" cm");

        lcd.setCursor(0, 1);
        lcd.print("Strength: ");
        lcd.print(strength);

        delay(100); // Esperar antes de la siguiente lectura
    }
}