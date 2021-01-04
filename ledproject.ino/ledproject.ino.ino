#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <Adafruit_NeoPixel.h>
#include <SPI.h>
#define PIN 27
#define NUMPIXELS 150
#define BLYNK_PRINT Serial
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// Function to test if wifi connection works
#define WIFI_NETWORK "tcwhhome"
#define WIFI_PASSWORD "twch1019"
#define WIFI_TIMEOUT_MS 20000
void connectToWifi(){
  Serial.print("Connecting to Wifi");
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_NETWORK, WIFI_PASSWORD);

  unsigned long startAttemptTime = millis();

  while(WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < WIFI_TIMEOUT_MS){
    Serial.print(".");
    delay(100);
  }

  if(WiFi.status() != WL_CONNECTED){
    Serial.println("Not connected to Wifi");
  }else{
    Serial.print("Connected!");
    Serial.println(WiFi.localIP());
  }
}



// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "uOlz7fi1IpqMfFdIB-SipVfuRrBfbZSp";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "tcwhhome";
char pass[] = "twch1019";


BLYNK_WRITE(V2)
{
  int R = param[0].asInt();
  int G = param[1].asInt();
  int B = param[2].asInt();
  Serial.println(R);
  Serial.println(G);
  Serial.println(B);
  for (int i = 0; i < NUMPIXELS; i++) {

    pixels.setPixelColor(i, pixels.Color(R, G, B));

    pixels.show();
  }
}

void setup()
{
  // Debug console
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
    pixels.begin();                                                         
}

void loop()
{
  Blynk.run();
}
