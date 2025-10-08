#include <WiFi.h>

void sacanNetworks

void setup() {
Serial.begin(115200);
Serial.println("iniciando Scan de redes WIFI");
}

void loop() {
}
void scanlNetworks(){
int number = WiFi.scanNetworks();
delay(500);
if(number == -1){
  Serial.println("ERRO!. não deu bom");
}
else{
   Serial.printf("Numero de redes encontradas: %d\n", number);
  for(int net =0; net < number; net++){
    Serial.printf("%d - %s | %d db\n", net, WiFi.SSID(net), WiFi.RSSI(net));
    }
  
}

}