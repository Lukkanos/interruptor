#include <ESP8266WiFi.h>
#include <EEPROM.h>

const char* ssid = "SUA_REDE"; //Coloque a sua rede
const char* password = "SUA_SENHA"; //Coloque a sua senha

WiFiServer server(80);

bool ligado = false;
int brilho = 100;

void salvarEstado() {
  EEPROM.write(0, ligado ? 1 : 0);
  EEPROM.write(1, brilho);
  EEPROM.commit();
}

void carregarEstado() {
  ligado = EEPROM.read(0) == 1;
  brilho = EEPROM.read(1);
  if (brilho > 100) brilho = 100;
}

void setup() {
  EEPROM.begin(512);
  carregarEstado();
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  server.begin();

  if (ligado) {
    Serial.println("LIGAR");
  } else {
    Serial.println("DESLIGAR");
  }
  Serial.println("BRILHO:" + String(brilho));
}

void loop() {
  WiFiClient client = server.available();

  if (client) {
    String request = "";
    unsigned long timeout = millis() + 2000;

    while (client.connected() && millis() < timeout) {
      if (client.available()) {
        char c = client.read();
        request += c;
        if (request.indexOf("\r\n\r\n") != -1) {
          break;
        }
      }
    }

    if (request.indexOf("GET /L") != -1) {
      ligado = true;
      Serial.println("LIGAR");
      salvarEstado();
    }
    if (request.indexOf("GET /D") != -1) {
      ligado = false;
      Serial.println("DESLIGAR");
      salvarEstado();
    }
    if (request.indexOf("GET /B") != -1) {
      int idx = request.indexOf("/B") + 2;
      String brilhoStr = request.substring(idx, request.indexOf(" ", idx));
      brilho = brilhoStr.toInt();
      if (brilho > 100) brilho = 100;
      Serial.println("BRILHO:" + String(brilho));
      salvarEstado();
    }

    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("Connection: close");
    client.println();

//Começo da Pagina HTML
    client.println("<!DOCTYPE html><html lang='pt-BR'>");
    client.println("<head>");
    client.println("<meta charset='UTF-8'>");
    client.println("<meta name='viewport' content='width=device-width, initial-scale=1.0'>");
    client.println("<title>Quarto</title>");
    client.println("<style>");
    client.println("* { -webkit-tap-highlight-color: transparent; }");

    // Aqui a regra para html e body
    client.println("html, body {");
    client.println("  height: 100%;");
    client.println("  width: 100%;");
    client.println("  margin: 0;");
    client.println("  padding: 0;");
    client.println("  user-select: none;");
    client.println("  -webkit-user-select: none;");
    client.println("  -moz-user-select: none;");
    client.println("  -ms-user-select: none;");
    client.println("  overflow: hidden;");
    client.println("  position: relative;");
    client.println("}");

    client.println("body::before {");
    client.println("  content: '';");
    client.println("  position: absolute;");
    client.println("  top: 0; left: 0; right: 0; bottom: 0;");
    client.println("  background: linear-gradient(135deg, #000000, #434343);");
    client.println("  z-index: -1;");
    client.println("  transition: background 1s ease;");
    client.println("}");
    client.println("body.ligado::before {");
    client.println("  background: linear-gradient(135deg, #004e92, #000428);");
    client.println("}");
    client.println("h1 {");
    client.println("  color: white;");
    client.println("  font-size: 48px;");
    client.println("  margin: 0;");
    client.println("  padding: 20px;");
    client.println("  text-align: center;");
    client.println("}");
    client.println(".container {");
    client.println("  display: flex;");
    client.println("  justify-content: center;");
    client.println("  align-items: center;");
    client.println("  flex-direction: column;");
    client.println("  height: calc(100% - 160px);");
    client.println("  gap: 40px;");
    client.println("}");
    client.println(".switch {");
    client.println("  position: relative;");
    client.println("  display: inline-block;");
    client.println("  width: 140px;");
    client.println("  height: 70px;");
    client.println("}");
    client.println(".switch input {");
    client.println("  opacity: 0;");
    client.println("  width: 0;");
    client.println("  height: 0;");
    client.println("}");
    client.println(".slider {");
    client.println("  position: absolute;");
    client.println("  cursor: pointer;");
    client.println("  top: 0;");
    client.println("  left: 0;");
    client.println("  right: 0;");
    client.println("  bottom: 0;");
    client.println("  background-color: #e41212;");
    client.println("  transition: .4s;");
    client.println("  border-radius: 70px;");
    client.println("}");
    client.println(".slider:before {");
    client.println("  position: absolute;");
    client.println("  content: '';");
    client.println("  height: 62px;");
    client.println("  width: 62px;");
    client.println("  left: 4px;");
    client.println("  bottom: 4px;");
    client.println("  background-color: white;");
    client.println("  transition: .4s;");
    client.println("  border-radius: 50%;");
    client.println("}");
    client.println("input:checked + .slider {");
    client.println("  background-color: #4CAF50;");
    client.println("}");
    client.println("input:checked + .slider:before {");
    client.println("  transform: translateX(70px);");
    client.println("}");
    client.println(".slider-container {");
    client.println("  text-align: center;");
    client.println("  opacity: 0;");
    client.println("  transform: scale(0.8);");
    client.println("  transition: opacity 0.5s ease, transform 0.5s ease;");
    client.println("  pointer-events: none;");
    client.println("}");
    client.println(".slider-container.visible {");
    client.println("  opacity: 1;");
    client.println("  transform: scale(1);");
    client.println("  pointer-events: all;");
    client.println("}");
    client.println(".slider-container label {");
    client.println("  color: white;");
    client.println("  font-size: 20px;");
    client.println("}");
    client.println("input[type=range] {");
    client.println("  -webkit-appearance: none;");
    client.println("  width: 300px;");
    client.println("  height: 10px;");
    client.println("  border-radius: 5px;");
    client.println("  background: linear-gradient(to right, #4CAF50 var(--value, 100%), #ddd var(--value, 100%));");
    client.println("  outline: none;");
    client.println("  transition: background 0.3s ease;");
    client.println("}");
    client.println("input[type=range]::-webkit-slider-thumb {");
    client.println("  -webkit-appearance: none;");
    client.println("  width: 20px;");
    client.println("  height: 20px;");
    client.println("  background: #4CAF50;");
    client.println("  border-radius: 50%;");
    client.println("  cursor: pointer;");
    client.println("}");
    client.println("</style>");
    client.println("</head>");
    client.println("<body>");
    client.println("<h1>Quarto</h1>");
    client.println("<div class='container'>");
    client.print("<label class='switch'>");
    client.print("<input type='checkbox' id='led' onclick='toggleLED()' ");
    if (ligado) client.print("checked");
    client.println(">");
    client.println("<span class='slider'></span>");
    client.println("</label>");
    client.println("<div class='slider-container' id='brilhoContainer'>");
    client.println("<label for='brilho'>Brilho</label><br>");
    client.print("<input type='range' id='brilho' min='0' max='100' value='");
    client.print(brilho);
    client.println("' onchange='setBrilho(this.value)'>");
    client.println("</div>");
    client.println("</div>");
    client.println("<script>");
    client.println("function toggleLED() {");
    client.println("  var xhr = new XMLHttpRequest();");
    client.println("  var checkbox = document.getElementById('led');");
    client.println("  var body = document.body;");
    client.println("  var brilhoContainer = document.getElementById('brilhoContainer');");
    client.println("  if (checkbox.checked) {");
    client.println("    xhr.open('GET', '/L', true);");
    client.println("    body.classList.add('ligado');");
    client.println("    brilhoContainer.classList.add('visible');");
    client.println("  } else {");
    client.println("    xhr.open('GET', '/D', true);");
    client.println("    body.classList.remove('ligado');");
    client.println("    brilhoContainer.classList.remove('visible');");
    client.println("  }");
    client.println("  xhr.send();");
    client.println("}");
    client.println("function setBrilho(valor) {");
    client.println("  var xhr = new XMLHttpRequest();");
    client.println("  xhr.open('GET', '/B' + valor, true);");
    client.println("  xhr.send();");
    client.println("  setSliderColor(valor);");
    client.println("}");
    client.println("function setSliderColor(valor) {");
    client.println("  var slider = document.getElementById('brilho');");
    client.println("  slider.style.setProperty('--value', valor + '%');");
    client.println("}");
    client.println("window.onload = function() {");
    client.println("  setSliderColor(document.getElementById('brilho').value);");
    client.println("  var brilhoContainer = document.getElementById('brilhoContainer');");
    client.println("  if (" + String(ligado ? "true" : "false") + ") {");
    client.println("    document.body.classList.add('ligado');");
    client.println("    brilhoContainer.classList.add('visible');");
    client.println("  } else {");
    client.println("    brilhoContainer.classList.remove('visible');");
    client.println("  }");
    client.println("};");
    client.println("</script>");
    client.println("</body>");
    client.println("</html>");

    delay(1);
    client.stop();
  }
}
