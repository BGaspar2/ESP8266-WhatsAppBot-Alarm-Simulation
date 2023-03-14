#include <ESP8266WiFi.h>
#include <ThingESP.h>

ThingESP8266 thing("USER", "PROYECT-NAME", "USER");

int LED = 5;              //D1(gpio5)
const int buttonPin = 4;  //D2(gpio4)
int buttonState = 0;
int ledstate = LOW;  //initial value

// the pin our push button is on
// Define your WIFI settings.
const char *ssid = "YOUR-SSID-NETWORK";
const char *password = "YOUR-PASSWORD";


unsigned long previousMillis = 0;
const long INTERVAL = 6000;

void setup() {
  Serial.begin(115200);

  pinMode(LED, OUTPUT);
  pinMode(buttonPin, INPUT);  // Set the Tilt Switch as an input
  // It is just for assuring connection is alive.
  WiFi.mode(WIFI_OFF);
  delay(1000);
  // This mode allows NodeMCU to connect any WiFi directly.
  WiFi.mode(WIFI_STA);
  // Connect NodeMCU to your WiFi.
  WiFi.begin(ssid, password);

  Serial.print("\n\n");
  Serial.print("Try to connect to WiFi. Please wait! ");
  Serial.print("\n\n");


  thing.SetWiFi(ssid, password);

  thing.initDevice();
}

String HandleResponse(String query) {


  if (query == "alarma off" || query == "2" || query == "apagar") {
    ledstate = LOW;
    digitalWrite(LED, ledstate);
    return "Done: ALARMA OFF";
  }

  else if (query == "led status" || query == "estado") return digitalRead(LED) ? "ALARM is ON" : "ALARM is OFF";

  else return "Your query was invalid..";
}

void loop() {
  buttonState = digitalRead(buttonPin);
  
  String msg = "ALARMA ENCENDIDA 🚨, ESCRIBE APAGAR O TECLEA EL NUMERO 2 PARA DESACTIVARLA";
  if (buttonState == 1) {
    //reverse the current state of the ledstate variable
    ledstate = !ledstate;
    digitalWrite(LED, ledstate);
    delay(200);

    thing.sendMsg("+NUMBERS-TO-SEND-MESSAGES", msg);
    delay(5000);
    thing.sendMsg("+NUMBERS-TO-SEND-MESSAGES", msg);
     delay(5000);
    thing.sendMsg("+NUMBERS-TO-SEND-MESSAGES", msg);
    

  }



  thing.Handle();
}