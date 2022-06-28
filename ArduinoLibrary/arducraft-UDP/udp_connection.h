
#include "tab/arduino_secrets.h"
#include <SPI.h>
#include <WiFiNINA.h>
#include <WiFiUdp.h>


char UDP_ssid[] = SECRET_SSID;
char UDP_pass[] = SECRET_PASS;

unsigned int UDP_localPort = 6000; // local port to listen on
char UDP_packetBuffer[256];        // buffer to hold incoming packet

WiFiUDP Udp;

class UDPClient {
private:
  void printWifiStatus() {
    Serial.print("SSID: ");
    Serial.println(WiFi.SSID());
    IPAddress ip = WiFi.localIP();
    Serial.print("IP Address: ");
    Serial.println(ip);
    long rssi = WiFi.RSSI();
    Serial.print("signal strength (RSSI):");
    Serial.print(rssi);
    Serial.println(" dBm");
  }

public:
  void begin() {

    if (WiFi.status() == WL_NO_MODULE) {
      Serial.println("Communication with WiFi module failed!");
      // don't continue
      while (true)
        ;
    }

    String fv = WiFi.firmwareVersion();
    if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
      Serial.println("Please upgrade the firmware");
    }

    // attempt to connect to WiFi network:
    while (WiFi.status() != WL_CONNECTED) {
      Serial.print("Attempting to connect to SSID: ");
      Serial.println(UDP_ssid);
      // Connect to WPA/WPA2 network. Change this line if using open or WEP
      // network:

      WiFi.begin(UDP_ssid, UDP_pass);

      // wait 2 seconds for connection:
      delay(2000);
    }
    Serial.println("Connected to WiFi");
    printWifiStatus();

    Serial.println("\nStarting connection to server...");
    // if you get a connection, report back via serial:
    Udp.begin(UDP_localPort);
  }

  auto getData() {
    // if there's data available, read a packet
    int packetSize = Udp.parsePacket();
    if (packetSize) {
      IPAddress remoteIp = Udp.remoteIP();
      // read the packet into packet Buffer
      int len = Udp.read(UDP_packetBuffer, 255);
      if (len > 0) {
        UDP_packetBuffer[len] = 0;
      }
      return UDP_packetBuffer;
    }
  }

  void sendString(auto data[]) {
    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    Udp.write(data);
    Udp.endPacket();
  }
};
