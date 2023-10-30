#include "camadaHtml.h"
#include "globalVars.h"
#include "camadaSystem.h"
#include <WebServer.h>


WebServer server(80);
String msg = "";

void setup() {
  Serial.begin(9600);
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

  server.on("/send-flag", HTTP_GET, []() {
    Serial.println("Aviso atendido");
    server.send(200, "text/plain", "Aviso atendido");
  });
  
  server.onNotFound(handle_NotFound);
  server.begin();
  Serial.println("HTTP servidor está funcionando");
  
  config_fallDetect();
  config_emergencyButton();
}

void loop() {
  server.handleClient();
  
  if(fall_detected){
    msg = "Queda detectada";
    fall_detected = false;
  }

  if(emergency_detected){
    msg = "Emergencia acionada";
    emergency_detected = false;
  }

  if(flag_ready_to_read){
    read_accelerometer();
    flag_ready_to_read = false; 
  }
  
}

void teste(){
    char dado = Serial.read();
  
  if(dado=='c'){
    fall_detected = true;
    msg = "Queda detectada";
  }

   if(dado=='d'){
    fall_detected = true;
    msg = "Emergencia acionada";
  }
}

void handle_OnConnect() {
  server.send(200, "text/html", SendHTML(msg));
}

void handle_NotFound() {
  server.send(404, "text/plain", "Pagina não existente");
}
