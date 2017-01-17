/*
  ---------------------------------------------------------------
  HTTP GET Webclient class declaration
  Makes HTTP GET requests

  Notes:
  WiFi.status()-function does not properly work with scheduler. So we had to make up another way to setup WiFi
  ---------------------------------------------------------------
*/
class HTTPGETTask : public Task {
  protected:
    void setup() {
      Serial.print("Starting HTTP GET Request client");
      delay(500);

      // Connecting to the WiFi network
      Serial.println();
      Serial.println();
      Serial.print("Connecting to ");
      Serial.println(ssid);
      WiFi.begin(ssid, password);
      while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
      }
    }

    void loop()  {
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
      String url = "/testwifi/index.html";
      Serial.print("Requesting URL: ");
      Serial.println(url);

      // This will send the request to the server
      client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                   "Host: " + host + "\r\n" +
                   "Connection: close\r\n\r\n");
      delay(500);

      // Read all the lines of the reply from server and print them to Serial
      while (client.available()) {
        String line = client.readStringUntil('\r');
        Serial.print(line);
      }

      Serial.println();
      Serial.println("closing connection");
    }

  private:

    int value = 0;
} gethttp_task;

