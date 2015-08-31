  #include <ESP8266WiFi.h>
  #include <WiFiClient.h>
  #include <ESP8266WebServer.h>
  #define LIGHTPIN 13
  #define LEDPIN 0
   
  const char* ssid     = "Robostorm";
  const char* password = "r0b0tic$";
  
  ESP8266WebServer server(80);
  
  unsigned long time = 0;
  unsigned long old = 0;
  boolean ledState = false;
   
  String rootPage = "<html><head><style>button{width: 100%;font-size: 10em;}</style></head><body><form action='/on'><button>ON</button></form><form action='/off'><button>OFF</button></form></body></html>";
   
  void setup(void) {
    // You can open the Arduino IDE Serial Monitor window to see what the code is doing
    Serial.begin(115200);  // Serial connection from ESP-01 via 3.3v console cable
    
    pinMode(LIGHTPIN, OUTPUT);
    pinMode(LEDPIN, OUTPUT);
   
    // Connect to WiFi network
    WiFi.begin(ssid, password);
    Serial.print("\n\r \n\rWorking to connect");
   
    // Wait for connection
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    Serial.println("");
    Serial.println("Light Switch Server");
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    
    server.on("/", [](){  // if you add this subdirectory to your webserver call, you get text below :)
      server.send(200, "text/html", rootPage);            // send to someones browser when asked
    });
    
    server.on("/on", [](){  // if you add this subdirectory to your webserver call, you get text below :)
      digitalWrite(LIGHTPIN, HIGH);
      server.send(200, "text/html", rootPage);            // send to someones browser when asked
    });
   
    server.on("/off", [](){  // if you add this subdirectory to your webserver call, you get text below :)
      digitalWrite(LIGHTPIN, LOW);
      server.send(200, "text/html", rootPage);               // send to someones browser when asked
    });
    
    server.begin();
    Serial.println("HTTP server started");
    time = millis();
    old = time;
  }
   
  void loop(void) {
    time = millis();
    server.handleClient();
    if(time - old >= 500) {
      if(ledState) {
        digitalWrite(LEDPIN, LOW);
        ledState = !ledState;
      } else {
        digitalWrite(LEDPIN, HIGH);
        ledState = !ledState;
      }
      old = time;
    }
  }
