
#include "globalVars.h"
#include "camadaSystem.h"
#include <WebServer.h>
//++++++++++++++++++++++++++++++++++++
// Definições WIFI
//++++++++++++++++++++++++++++++++++++
const char* WIFISSID = "Yuri";
const char* senha = "ym338link";
String per = "";
//++++++++++++++++++++++++++++++++++++
// Definições de rede
//++++++++++++++++++++++++++++++++++++
IPAddress local_IP(192, 168, 1, 50); //Defina o IP de acesso
IPAddress gateway(192, 168, 1, 1);   //Defina o IP do roteador de internet
IPAddress subnet(255, 255, 255, 0);  //Defina a máscara de sub-rede
IPAddress primaryDNS(192, 168, 1, 1);//opcional - DNS primário
IPAddress secondaryDNS(8, 8, 8, 8);  //opcional - DNS secundário
WebServer server(80);

void setup() {
  Serial.begin(9600);
  delay(400);

  // ip fixo
  if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
    Serial.println("STA Failed to configure");
  }// fim ip fixo
  Serial.println("Conectando a rede:  ");
  Serial.println(WIFISSID);
  WiFi.begin(WIFISSID , senha);
  while (WiFi.status() != WL_CONNECTED)   {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Sucesso ao conectar-se a rede WiFi");
  Serial.print("endereço de IP para o web server: ");
  Serial.println(WiFi.localIP());
  server.on("/", handle_OnConnect);
  server.onNotFound(handle_NotFound);
  server.begin();
  Serial.println("HTTP servidor está funcionando");
  
  config_fallDetect();
  config_emergencyButton();
}

void loop() {
  char dado = Serial.read();
  
  if(dado=='c'){
    fall_detected = true;
  }
  
  if(fall_detected){
    per = "Queda detectada";
    send_fall_notification(per);
    fall_detected = false;
  }

  if(emergency_detected){
    send_emergency_notification();
    emergency_detected = false;
  }

  if(flag_ready_to_read){
    read_accelerometer();
    flag_ready_to_read = false; 
  }
  
}

String send_fall_notification(String per) {
  server.handleClient();
}

String send_emergency_notification() {
  Serial.print("emergencia detectada");
}

void handle_OnConnect() {
  server.send(200, "text/html", SendHTML(per));
}

void handle_NotFound() {
  server.send(404, "text/plain", "Pagina não existente");
}
