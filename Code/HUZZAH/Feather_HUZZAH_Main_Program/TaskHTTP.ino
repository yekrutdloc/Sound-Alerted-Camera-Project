/*
  ---------------------------------------------------------------
  HTTP GET Webclient class declaration
  Makes HTTP GET requests

  Notes:
  WiFi.status()-function does not properly work with scheduler. So we had to make up another way to setup WiFi
  Most of the Serial.println in loop() is commented out because its so slow it holds the other tasks waiting
  ---------------------------------------------------------------
*/
class HTTPTask : public Task {
  protected:
    void setup() {
      while (!taskSoundSensorsStarted) delay(100); //Wait for Sound sensor task to start
      Serial.println(F("Starting HTTP Task..."));

      // Connecting to the WiFi network
      Serial.print(F("Connecting to "));
      Serial.print(ssid);
      WiFi.begin(ssid, password);
      uint8_t wifiCounter = 0;
      while (WiFi.status() != WL_CONNECTED && wifiCounter < wifiConnectTimeout) {
        delay(1000);
        Serial.print(F("."));
        wifiCounter++;
      }
      if (wifiCounter == wifiConnectTimeout) { // Wi-Fi could not connect
        Serial.println(F("Wi-Fi connection timeout. Could not connect to Wi-Fi..."));
        Serial.println(F("Try plugging out and back in the USB-cable"));
        Serial.println(F("STOPPING PROGRAM"));
        doWifiNotFoundChime = 1; // Do the wi-fi not found buzzer chime, showing that Wi-Fi connection has failed!
        digitalWrite(ledRedPin, HIGH); // Turn off status LED(LED is inverted, so HIGH is off)
        // Stop program
        while (1) {
          delay(1);
        }
      } else { // do normal startup operation
        Serial.println(F("Connected to Wi-Fi!"));
        Serial.print("IP address: ");
        Serial.println(WiFi.localIP());
        while (!taskBuzzerStarted) delay(100); //Wait for buzzer task to start
        doStartupChime = 1; // Do the startup buzzer chime, showing that Wi-Fi is connected
        while (doStartupChime) delay(100); // Wait for startup chime to finish
        delay(100);
        taskHTTPStarted = 1; // Set startup flag
      }
    }

    void loop()  {
      if (sendDatabaseInfo) {
        //TO-DO: Make video clip on camera and get link
        //TO-DO: Take photo/pano on camera and get link

        Serial.print(F("Connecting to database..."));
        WiFiClient client;
        if (!client.connect(databaseIP, 80)) {
          Serial.println(F("Failed to connect to database host!"));
          return;
        } else {
          Serial.println(F("Connected!"));
        }

        // DELETE THIS LATER
        const String video_link = F("http://videolink.mp4");

        // Create the data to send as one String
        const String data = "&cam_id=" + cam_id + "&location=" + location + "&video_link=" + video_link;

        Serial.print(F("Sending information to database..."));
        // Start sending the POST request to the server
        client.println(F("POST /database/add.php HTTP/1.1"));
        client.print(F("Host: "));
        client.println(databaseIP);
        client.println(F("Content-Type: application/x-www-form-urlencoded"));
        client.print(F("Content-Length: "));
        client.println(data.length());
        client.println();
        client.print(data);
        Serial.println(F("Sent!"));

        // Read all the lines of the reply from server and print them to Serial
        Serial.print(F("Waiting for response from server..."));
        while (!client.available()) delay(1);// Wait for server to respond
        Serial.println(F("Response received:"));
        Serial.println(F(""));
        delay(100);// Allow network buffer to fill
        while (client.available()) {
          String line = client.readStringUntil('\r');
          Serial.print(line);
        }
        Serial.println(F("Response ended."));
        Serial.println(F("HTTP task done."));

        sendDatabaseInfo = 0; // Clear
      }

      if (sendGETRequestPing) {
        Serial.println(F("Running a random GET request test..."));

        Serial.print(F("Connecting to "));
        Serial.println(testingHost);

        WiFiClient client;
        // Use WiFiClient class to create TCP connections
        if (!client.connect(testingHost, 80)) {
          Serial.println(F("Failed to connect to testing host!"));
          return;
        }

        // We now create a URI for the request
        String url = F("/testwifi/index.html");
        //Serial.print(F("Requesting URL: "));
        //Serial.println(url);

        // This will send the request to the server
        client.print(String(F("GET ")) + url + F(" HTTP/1.1\r\n") +
                     F("Host: ") + testingHost + F("\r\n") +
                     F("Connection: close\r\n\r\n"));

        sendGETRequestPing = 0; // Clear
        Serial.println(F("Done with doing GET-request"));
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
      delayMicroseconds(httpExeutionFrequency); // Frequency to check if HTTP request should run
      //yield(); // Allow other essential backgrund tasks to run
    }

  private:

} http_task;

