#include <WiFi.h>
#include <FirebaseESP32.h>

#define WIFI_SSID "SPFL"
#define WIFI_PASSWORD "Mac@20$$_"

#define API_KEY "AIzaSyBUjcQoCBNHrBcjKfvXYLiNYPd_QydZnXE"
#define DATABASE_URL "https://lampada-bluweb-default-rtdb.firebaseio.com/"

#define PIN_RELE 5

FirebaseData fbdo;
FirebaseConfig config;

void conectaWiFi() {
  Serial.print("A conectar ao Wi-Fi...");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" Conectado!");
}

void setup() {
  Serial.begin(115200);
  pinMode(PIN_RELE, OUTPUT);
  digitalWrite(PIN_RELE, LOW);

  conectaWiFi();

  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;

  Firebase.begin(&config, nullptr);
  Firebase.reconnectWiFi(true);

  Serial.println("Sistema iniciado!");
}

void loop() {
  if (Firebase.getInt(fbdo, "/Quarto/estado")) {
    int valor = fbdo.intData();
    Serial.println("Valor recebido: " + String(valor));

    if (valor > 0) {
      digitalWrite(PIN_RELE, HIGH);
      Serial.println("Relé LIGADO");
    } else {
      digitalWrite(PIN_RELE, LOW);
      Serial.println("Relé DESLIGADO");
    }
  } else {
    Serial.println("Erro: " + fbdo.errorReason());
  }

  delay(500);
}
