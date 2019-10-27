
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "AppServer.h"

String header;
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0;
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;


WiFiServer wifiServer(80);


AppServer::AppServer() {
  setupWifiServer();
}

void AppServer::checkClient() {
  WiFiClient client = wifiServer.available();
  if (client)
  {
    handleClient(client);
  }
}

void AppServer::setupWifiServer()
{
  Serial.begin(115200); // Start the Serial communication to send messages to the computer
  delay(10);
  Serial.println('\n');

  Serial.print("Connecting to ");
  Serial.print(ssid);
  Serial.println(" ...");

  WiFi.begin(ssid, password); // Connect to the network

  int i = 0;
  while (WiFi.status() != WL_CONNECTED)
  { // Wait for the Wi-Fi to connect
    delay(1000);
    Serial.print(++i);
    Serial.print(' ');
  }

  Serial.println('\n');
  Serial.println("Connection established!");
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP()); // Send the IP address of the ESP8266 to the computer

  Serial.print("Starting server on port 80");
  wifiServer.begin();
}



void AppServer::handleClient(WiFiClient client)
{                                // If a new client connects,
  Serial.println("New Client."); // print a message out in the serial port
  String currentLine = "";       // make a String to hold incoming data from the client
  String strColors;
  String strMode;
  currentTime = millis();
  previousTime = currentTime;
  while (client.connected() && currentTime - previousTime <= timeoutTime)
  { // loop while the client's connected
    currentTime = millis();
    if (client.available())
    {                         // if there's bytes to read from the client,
      char c = client.read(); // read a byte, then
      Serial.write(c);        // print it out the serial monitor
      header += c;
      if (c == '\n')
      { // if the byte is a newline character
        // if the current line is blank, you got two newline characters in a row.
        // that's the end of the client HTTP request, so send a response:
        if (currentLine.length() == 0)
        {
          // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
          // and a content-type so the client knows what's coming, then a blank line:
          client.println("HTTP/1.1 200 OK");
          client.println("Content-type:text/html");
          client.println("Connection: close");
          client.println();

          // turns the GPIOs on and off
          int pathMatch = header.indexOf("GET /setcolors/");
          if (pathMatch >= 0)
          {
            Serial.println("setcolor");
            Serial.println("header: " + header);
            strColors = header.substring(pathMatch + 15, header.indexOf(' ', pathMatch + 15));
            Serial.println("Colors:" + strColors);

            // parse each color, check for hash/hex, or dictionary color
            //parseSetColors(strColors);
          }
          
          // turns the GPIOs on and off
          pathMatch = header.indexOf("GET /setmode/");
          if (pathMatch >= 0)
          {
            Serial.println("setmode");
            Serial.println("header: " + header);
            strMode = header.substring(pathMatch + 13, header.indexOf(' ', pathMatch + 13));

            // parse each color, check for hash/hex, or dictionary color
            //parseMode(strMode);
          }

          // Display the HTML web page
          client.println("<!DOCTYPE html><html>");
          client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
          client.println("<link rel=\"icon\" href=\"data:,\">");
          // CSS to style the on/off buttons
          // Feel free to change the background-color and font-size attributes to fit your preferences
          client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
          client.println(".button { background-color: #195B6A; border: none; color: white; padding: 16px 40px;");
          client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
          client.println(".button2 {background-color: #77878A;}</style></head>");

          // Web Page Heading
          client.println("<body><h1>RGB Hood Light</h1>");

          client.println("<p><a href=\"/setmode/specific\"><button class=\"button\">Set Mode - Specific</button></a></p>");
          client.println("<p><a href=\"/setmode/rainbow\"><button class=\"button\">Set Mode - Fade Rainbow</button></a></p>");

          client.println("<p>Current mode: " + strMode + "</p");
          client.println("<p><a href=\"/set/red,green,blue\"><button class=\"button\">Set Colors</button></a></p>");
          client.println("<p>Current colors: " + strColors + "</p");

          // The HTTP response ends with another blank line
          client.println();
          // Break out of the while loop
          break;
        }
        else
        { // if you got a newline, then clear currentLine
          currentLine = "";
        }
      }
      else if (c != '\r')
      {                   // if you got anything else but a carriage return character,
        currentLine += c; // add it to the end of the currentLine
      }
    }
  }
  // Clear the header variable
  header = "";
  // Close the connection
  client.stop();
  Serial.println("Client disconnected.");
  Serial.println("");
}
