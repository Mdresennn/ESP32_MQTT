d#include <WiFi.h>

// --- Configuração da rede que você quer conectar ---
const char* targetSSID = "POCO F3";
const char* targetPassword = "mateusSs";

// --- Configurações de tempo ---
const unsigned long scanInterval = 10000;     // 10 segundos entre scans
const unsigned long reconnectDelay = 5000;    // Tempo entre tentativas de reconexão

unsigned long lastScanTime = 0;
bool connectedToTarget = false;

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("Iniciando escaneamento e tentativa de conexão Wi-Fi...");

  WiFi.mode(WIFI_STA);
  WiFi.disconnect(true); // Garante que começa limpo
  delay(100);
}

void loop() {
  // Verifica se está conectado
  if (WiFi.status() == WL_CONNECTED) {
    if (!connectedToTarget) {
      Serial.println("✅ Conectado com sucesso!");
      Serial.printf("SSID: %s\n", WiFi.SSID().c_str());
      Serial.printf("IP: %s\n", WiFi.localIP().toString().c_str());
      connectedToTarget = true;
    }

    // Aqui você pode executar tarefas que dependem da internet
  } else {
    connectedToTarget = false;

    // Faz escaneamento periódico
    if (millis() - lastScanTime > scanInterval) {
      lastScanTime = millis();
      Serial.println("\n🔍 Escaneando redes Wi-Fi...");

      int number = WiFi.scanNetworks();
      if (number <= 0) {
        Serial.println("❌ Nenhuma rede encontrada ou erro.");
        return;
      }

      Serial.printf("🔎 %d redes encontradas:\n", number);
      bool foundTarget = false;

      for (int i = 0; i < number; i++) {
        String ssid = WiFi.SSID(i);
        int rssi = WiFi.RSSI(i);
        String tipo = (WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? "Aberta" : "Protegida";

        Serial.printf("%d: %s (%d dBm) [%s]\n", i + 1, ssid.c_str(), rssi, tipo.c_str());

        // Verifica se a rede desejada está na lista
        if (ssid == targetSSID) {
          foundTarget = true;
        }
      }

      if (foundTarget) {
        Serial.printf("📶 Rede '%s' encontrada. Tentando conectar...\n", targetSSID);
        WiFi.begin(targetSSID, targetPassword);
        delay(reconnectDelay); // Dá tempo para tentar conectar
      } else {
        Serial.printf("⚠️ Rede '%s' não encontrada. Tentará novamente em breve.\n", targetSSID);
      }
    }
  }

  delay(100); // Evita sobrecarregar o loop
}