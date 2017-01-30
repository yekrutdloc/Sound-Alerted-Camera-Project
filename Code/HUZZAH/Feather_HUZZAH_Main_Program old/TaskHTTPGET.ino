/*
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
      while (!taskADCStarted) delay(100); //Wait for ADC task to start
      Serial.print(F("Starting HTTP GET Request client"));
      delay(500);

      // Connecting to the WiFi network
      Serial.println(F(""));
      Serial.println(F(""));
      Serial.print(F("Connecting to "));
      Serial.println(ssid);
      WiFi.begin(ssid, password);
      uint8_t wifiCounter = 0;
      while (WiFi.status() != WL_CONNECTED && wifiCounter < wifiConnectTimeout) {
        delay(1000);
        Serial.print(F("."));
        wifiCounter++;
      }
      if (wifiCounter == wifiConnectTimeout) { // Wi-Fi could not connect
        Serial.println(F("Wi-Fi connection timeout. Could not connect to Wi-Fi"));
        doWifiNotFoundChime = 1; // Do the wi-fi not found buzzer chime, showing that Wi-Fi connection has failed!
      } else { // do normal startup operation
        while (!taskBuzzerStarted) delay(100); //Wait for buzzer task to start
        doStartupChime = 1; // Do the startup buzzer chime, showing that Wi-Fi is connected
        while (doStartupChime) delay(100); // Wait for startup chime to finish
        taskHTTPGETStarted = 1; // Set startup flag
      }
    }

    void loop()  {
      if (sendGETRequestPing)
      {
        Serial.println(F("Doing a random GET request..."));

        //Serial.print(F("connecting to "));
        //Serial.println(host);

        // Use WiFiClient class to create TCP connections
        const int httpPort = 80;
        if (!client.connect(host, httpPort)) {
          Serial.println(F("connection failed"));
          return;
        }

        // We now create a URI for the request
        String url = F("/testwifi/index.html");
        //Serial.print(F("Requesting URL: "));
        //Serial.println(url);

        // This will send the request to the server
        client.print(String(F("GET ")) + url + F(" HTTP/1.1\r\n") +
                     F("Host: ") + host + F("\r\n") +
                     F("Connection: close\r\n\r\n"));

        sendGETRequestPing = 0; // Tell ADC task to continue
        Serial.println(F("Done with doing GET-request"));
      }
      delay(10);
      yield(); // Allow other essential backgrund tasks to run

      // Read all the lines of the reply from server and print them to Serial
      // This readStringUntil function takes a long time and is badly compatible with scheduler.
      // When this function is ran it freezes all other tasks.
      // Make another while loop to print out all characters in realtime with delay to support scheduler in the future
      //      while (client.available()) {
      //        String line = client.readStringUntil('\r');
      //        Serial.print(line);
      //        delay(10);
      //      }

      //      Serial.println(F(""));
      //      Serial.println(F("closing connection"));
    }

  private:
    WiFiClient client;

} gethttp_task;

