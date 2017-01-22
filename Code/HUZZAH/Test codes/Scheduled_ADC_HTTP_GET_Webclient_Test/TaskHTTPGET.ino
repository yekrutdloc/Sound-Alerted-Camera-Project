/*16
  ---------------------------------------------------------------
  HTTP GET Webclient class declaration
  Makes HTTP GET requests

  Notes:
  WiFi.status()-function does not properly work with scheduler. So we had to make up another way to setup WiFi
  Most of the Serial.println in loop() is commented out because its so slow it holds the other tasks waiting
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
      if (sendGETRequestPing)
      {
        Serial.println("Doing a random GET request...");

        //Serial.print("connecting to ");
        //Serial.println(host);

        // Use WiFiClient class to create TCP connections
        const int httpPort = 80;
        if (!client.connect(host, httpPort)) {
          Serial.println("connection failed");
          return;
        }

        // We now create a URI for the request
        String url = "/testwifi/index.html";
        //Serial.print("Requesting URL: ");
        //Serial.println(url);

        // This will send the request to the server
        client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                     "Host: " + host + "\r\n" +
                     "Connection: close\r\n\r\n");

        sendGETRequestPing = 0; // Tell ADC task to continue
        Serial.println("Done with doing GET-request");
      }
      delay(10);
      yield(); // Allow other backgrund tasks to run

      // Read all the lines of the reply from server and print them to Serial
      // This readStringUntil function takes a long time and is badly compatible with scheduler.
      // When this function is ran it freezes all other tasks.
      // Make another while loop to print out all characters in realtime with delay to support scheduler in the future
      //      while (client.available()) {
      //        String line = client.readStringUntil('\r');
      //        Serial.print(line);
      //        delay(10);
      //      }

      //      Serial.println();
      //      Serial.println("closing connection");
    }

  private:
    WiFiClient client;

} gethttp_task;

