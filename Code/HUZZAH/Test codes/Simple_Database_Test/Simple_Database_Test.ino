/*
    Simple test to post some data to database
*/

#include <ESP8266WiFi.h>

const char* ssid     = "Router";
const char* password = "kungarike";
const char* host = "188.166.72.14";

void setup() {
  Serial.begin(115200);
  delay(100);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

int value = 0;

void loop() {
  delay(5000);
  ++value;

  Serial.print("connecting to ");
  Serial.println(host);

  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }

  // We now create a URI for the request
  //  String url = "/database";
  //  Serial.print("Requesting URL: ");
  //  Serial.println(url);


  const String cam_id = "1";
  const String location = "55.610823,12.9928";
  const String video_link = "http://videolink.mp4";

  const String data = "&cam_id=" + cam_id + "&location=" + location + "&video_link=" + video_link;

  // This will send the request to the server
  client.println(F("POST /database/add.php HTTP/1.1"));
  client.println(F("Host: 188.166.72.14")); // SERVER ADDRESS HERE TOO
  client.println(F("Content-Type: application/x-www-form-urlencoded"));
  client.print(F("Content-Length: "));
  client.println(data.length());
  client.println();
  client.print(data);
  delay(500);

  // Read all the lines of the reply from server and print them to Serial
  while (client.available()) {
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }

  Serial.println();
  Serial.println("closing connection");


  Serial.println("Stopping program");
  while (1) {
    delay(5000);
  }
}
