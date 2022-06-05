#ifndef WIFI_CONFIG_H
#define WIFI_CONFIG_H

#include <WiFi.h>
#include <WebServer.h>
#include <ESPmDNS.h>

#define HTTP_ROOT_INTERFACE \
"<!DOCTYPE html>" \
"<html lang=\"zh\">" \
"<head>" \
    "<meta charset=\"UTF-8\">" \
    "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">" \
    "<title>WiFi 配网</title>" \
"</head>" \
"<body>" \
    "<form method=\"get\" action=\"configwifi\">" \
        "<span>SSID:</span><input type=\"text\" name=\"ssid\"><br/>" \
        "<span>PASS:</span><input type=\"text\" name=\"password\"><br/>" \
        "<input type=\"submit\">" \
    "</form>" \
"</body>" \
"</html>" 


void network_init();

void network_work();

#endif