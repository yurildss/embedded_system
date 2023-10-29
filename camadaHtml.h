
String SendHTML(String per) {
    String ptr = "<!DOCTYPE html>\n<html>\n<head>\n";
    ptr += "<meta http-equiv=\"refresh\" content=\"1\">\n";
    ptr += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n";
    ptr += "<link href=\"https://fonts.googleapis.com/css?family=Open+Sans:300,400,600\" rel=\"stylesheet\">\n";
    ptr += "<title>OBSERVADOR DE QUEDA E EMERGENCIA</title>\n";
    ptr += "<style>\n";
    ptr += "html { font-family: 'Open Sans', sans-serif; display: block; margin: 0px auto; text-align: center; color: #333333; }\n";
    ptr += "body { margin-top: 50px; }\n";
    ptr += "h1 { margin: 50px auto 30px; }\n";
    ptr += ".side-by-side { display: inline-block; vertical-align: middle; position: relative; }\n";
    ptr += ".humidity-icon { background-color: #3498db; width: 30px; height: 30px; border-radius: 50%; line-height: 36px; }\n";
    ptr += ".humidity-text { font-weight: 600; padding-left: 15px; font-size: 19px; width: 160px; text-align: left; }\n";
    ptr += ".superscript { font-size: 17px; font-weight: 600; position: absolute; right: -20px; top: 15px; }\n";
    ptr += ".data { padding: 10px; }\n";
    ptr += "</style>\n";
    ptr += "</head>\n<body>\n";
    ptr += "<div id=\"webpage\">\n";
    ptr += "<h1>OBSERVADOR DE QUEDA/EMERGENCIA</h1>\n";
    ptr += "</div>\n";
    ptr += "<div class=\"data\">\n";
    ptr += "<div class=\"side-by-side humidity-icon\">\n";
    ptr += "</div>\n";
    ptr += "<div class=\"side-by-side humidity-text\">\n";
    ptr += (String)per;
        // Adiciona um botão na página
    ptr += "<button onclick=\"sendFlag()\">Visto</button>\n";
    ptr += "<script>\n";
      
    ptr += "function sendFlag() {\n";
    ptr += "  var xhr = new XMLHttpRequest();\n";
    ptr += "  xhr.open('GET', '/send-flag', true);\n";
    ptr += "  xhr.send();\n";
    ptr += "}\n";
    ptr += "</script>\n";

    ptr += "</div>\n";
    ptr += "</div>\n</body>\n</html>\n";
    return ptr;
}
