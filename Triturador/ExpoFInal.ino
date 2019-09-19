#include <NewPing.h>

#define TRIGGER_PIN  12  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     11  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
int Distancia;
int Motor = 5;
int Boton = 8;
int i;
int Conteo = 0;
int Botellas;
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

void setup() {

  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
  pinMode(Boton, INPUT);
  pinMode(Motor, OUTPUT);
}

void loop() {
  digitalWrite(Motor, LOW);
  if (digitalRead(Boton) == 0)
  {
    Conteo++;
    delay(1000);
    if (Conteo > 1) {
      Conteo = 0;
    }
  }

  while (Conteo == 1)
  {
    Distancia = sonar.ping_cm();
    delay(50);                     // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
    Serial.print("Ping: ");
    Serial.print(Distancia); // Send ping, get distance in cm and print result (0 = outside set distance range)
    Serial.println("cm");

    if (Distancia < 5)
    {
      Botellas++;
      delay(200);
      Serial.println(Botellas);
    }
    if (digitalRead(Boton) == 0)
    {
      Conteo = 0;
      delay(1000);
    }
  }

  if (Botellas!=0) {
    while(i <Botellas){
    digitalWrite(Motor, HIGH);
    delay(4000);
    Serial.print("Botella: ");
    Serial.println(Botellas);
    i++;
    }
  }
  Botellas = 0;
}
