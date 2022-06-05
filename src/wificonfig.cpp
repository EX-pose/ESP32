#include "wificonfig.h"

WebServer server(8080);

void handleRoot() {
	server.send(200, "text/html", HTTP_ROOT_INTERFACE);
}

void handleNotFound() {
	String message = "File Not Found\n\n";
	message += "URI: ";
	message += server.uri();
	message += "\nMethod:";
	message += (server.method() == HTTP_GET) ? "GET" : "POST";
	message += "\nsArguments:";
	message += server.args();
	message += "\n";
	for (uint8_t i = 0; i < server.args(); i++) {
		message += " " + server.argName(i) + ":" + server.arg(i) + "\n";
	}
	server.send(404, "text/plain", message);
}

void handleConfigWiFi() {
    String ssid;
    String pass;
    if (server.hasArg("ssid") && server.hasArg("password")) {
        ssid = server.arg("ssid");
        pass  = server.arg("password");

        Serial.println("SSID: " + ssid);
        Serial.println("PASSWORD: " + pass);
    } else {
        server.send(200, "text/plain", "ssid or password not found");
        return;
    }

    server.send(200, "text/html", "config wifi success<br/>ssid:" + ssid + "<br/>password:" + pass);
    delay(1000);

    server.close(); //关闭web服务器
    WiFi.softAPdisconnect(); //关闭AP模式

    WiFi.mode(WIFI_MODE_STA);
    Serial.println("begin to connect wifi " + ssid);
    WiFi.begin(ssid.c_str(), pass.c_str());
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
		Serial.print(".");
    }
    Serial.println("\nconnect network" + ssid + " sucess");
}

void network_init() {
    WiFi.mode(WIFI_MODE_AP); //设置为AP模式
    WiFi.softAPConfig(IPAddress(192, 168, 4, 1), IPAddress(192, 168, 4, 1), IPAddress(255, 255, 255, 0)); //配置AP网络

    if (WiFi.softAP("ESP32_network")) {  //启动AP
        Serial.println("AP started");
		Serial.print("AP ip : ");
        Serial.println(WiFi.softAPIP().toString() + "\n");
	}

    if (MDNS.begin("esp32")) { //给设备设置域名
		Serial.println("MDNS responder started");
	}

    server.on("/", handleRoot);
    server.on("/configwifi", handleConfigWiFi);
    server.onNotFound(handleNotFound);

    server.begin(); //开启web服务
	Serial.println("HTTP server started");
}

void network_work() {
    server.handleClient();
}