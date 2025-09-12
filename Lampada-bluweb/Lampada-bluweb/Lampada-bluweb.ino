#include <WiFi.h>
#include <Firebase_ESP_Client.h>

#define WIFI_SSID "SPFL2"
#define WIFI_PASSWORD "Mac@20$$_"

#define API_KEY "AIzaSyBUjcQoCBNHrBcjKfvXYLiNYPd_QydZnXE"
#define DATABASE_URL "https://lampada-bluweb-default-rtdb.firebaseio.com/"

const int Quarto = 22;

FirebaseData fbdo;
FirebaseConfig config;

unsigned long lastSend = 0;

void conectaWiFi(){
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("A conectar ao Wi-Fi");
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".")
  }
  Serial.println();
  serial.print("Wi-Fi ligado. IP: ");
  serial.println(WiFi.localIP());
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(200);

  pinMode(Quarto, OUTPUT);
  digitalWrite(Quarto, LOW);

  conectaWiFi();

  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;

  Firebase.begin(&config, nullptr);
  Firebase.reconnectWiFi(true);

}

void loop() {
  // put your main code here, to run repeatedly:
 
  if(Firebase.RTDB.getString(&fbdo, "/Quarto/estado")){
    String estado = fbdo.stringData();
    Serial.println("Estado da Lampada: " + estado);
    if(estado=="LIGADA"){
      digitalWrite(Quarto, HIGH);
    }else if(estado=="DESLIGADA"){
      digitalWrite(Quarto, LOW);
    }
  }
}
