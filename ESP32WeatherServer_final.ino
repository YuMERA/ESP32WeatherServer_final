    
  //#define ESP8266 define define
  #if defined(ESP8266)
    #include <ESP8266WiFi.h>
    #include <ESP8266WebServer.h>
    #include <ESP8266HTTPClient.h>
  #else
    #include <WiFi.h>
    #include <WebServer.h>
    #include <HTTPClient.h>
  #endif
  
// Ako ne zelis da ti se bilo sta ispisuje u Serijskom terminalu onda stavis pod komentar #define DEBUG
//------------------------------------------------------------------------------------------------------
  #define DEBUG
  #ifdef DEBUG
    #define spln(x) Serial.println(x)
    #define sp(x) Serial.print(x)
    #define spf(x,y) Serial.printf(x,y)
  #else
    #define spln(x)
    #define sp(x)
    #define spf(x,y)
  #endif

  #include <ArduinoJson.h>
  #include <TimeLib.h>
  #include <WiFiClient.h>
  #include <MySQL_Connection.h>
  #include <MySQL_Cursor.h>
  #include <time.h>

// Moji #include fajlovi
//--------------------------------
  #include "style_css.h"
  #include "index_html.h"

// Izbor web servera za ESP8266 ili ESP32
//-----------------------------------------   
  #if defined(ESP8266)
    ESP8266WebServer server(3003);
  #else
    WebServer server(3003);
  #endif

// Open Weather Map, API, server name ....
//--------------------------------------------------------------------------------------------------    
  #define unit_type "metric"    // or "imperial"
  #define lat 45.130914         // latitude for Sid,RS
  #define lon 19.242530         // longitude for Sid,RS
  String url_ow = "";           // URL for HTTP get weather data
  String url_uv = "";           // URL for HTTP get uv index data
  const char *server_ow = "api.openweathermap.org";
  unsigned long id_city = 3190922; //Id za Sid   
  const char *api_key = "d8b774acf13f2ea889a3950c2c2a89c1"; //REPLACE_WITH_YOUR_API_KEY;

// ThingSpeak information
//--------------------------------------------------------------------------------------------------
  const char *thingSpeakAddress = "http://api.thingspeak.com";
  unsigned long channelID = 1365442;
  const char *readAPIKey  = "OC8ZG5H8MA0A28HG";
  const char *writeAPIKey = "4DQ2VAVQSEYQJ8KS";
  //const unsigned long postingInterval = 120L * 1000L;

// Soft Ap variables 
//--------------------------------------------------------------------------------------------------
  const char *APssid = "MeteoStanica-MERA";
  const char *APpassword = "NeveNa91";  // "" No password for the AP
  IPAddress APlocal_IP(192, 168, 4, 1);
  IPAddress APgateway(192, 168, 4, 1);
  IPAddress APsubnet(255, 255, 255, 0);

// Client
//--------------------------------------------------------------------------------------------------    
    WiFiClient client;

// MySQL Connection
//--------------------------------------------------------------------------------------------------
  MySQL_Connection conn(&client);
  MySQL_Cursor *cursor;
  IPAddress server_addr(37,59,55,185);  // remotemysql.com IP of the MySQL *server* here 
  char *user = "nUm8euijbj";            // MySQL user login username
  char *password = "85LoYraODw";        // MySQL user login password/
    
// Station variables 
//--------------------------------------------------------------------------------------------------
  const char *ssid = "YuMERA1";         // Network to be joined as a station SSID
  const char *passphrase = "NeveNa91";  // Network to be joined as a station password
  const char *host = "192.168.1.5";     // Connection to my Visual APP over TCP 3001
  const int MyAppPort = 3001;
  IPAddress mystaticip(192, 168, 1, 50);
  IPAddress mygateway(192, 168, 1, 1);
  IPAddress mysubnet(255, 255, 255, 0);
  IPAddress myDNS(8, 8, 8, 8);    

// General Variables
//--------------------------------------------------------------------------------------------------
  #define Alt "132"                     // Altitude
  unsigned long previousMillis = 0;     // will store last temp was read
  const long interval = 50000;          // interval at which to read sensor
  String content;                       // html kod servera
  String cIp="(null)";                  // string IP adresa za svakog klijenta koji preko veba pristupi weatherstanici
  String Tem="(null)";                  // izmerena temperatura
  String Hum="(null)";                  // vlaznost
  String Pre="(null)";                  // pritisak
  String Win="(null)";                  // brzina vetra (jos nije implementirano na mojoj meteo stanici)
  String Slp="(null)";                  // nadmorska visina na osnovu izmereneog pritiska i pritiska na nivou mora
  String Win1="(null)";                 // privremeno za brzinu vetra dok ne zavrsim moj anemometar
  String symbolWindDir="";              // oznaka za smer vetra
  String Vcc="(null)";                  // napon ba bateriji
  String Rsi="(null)";                  // jacina WiFi signala izmedju ESP meteo stanice i ESP web servera
  String Tmb="(null)";                  // temperatura na BME280 koji se nalazi u kucistu meteo stanice
  char lastTime[25] = "--:--";          // vreme poslednjeg merenja
  String uv_index_description = "";     // Vrednost UV indexa

// Klimerko variable
//--------------------------------------------------------------------------------------------------
  String pm1_kli  = "0";                // PM1 cestice izmerene na klimerku
  String pm25_kli = "0";                // PM2.5 cestice
  String pm10_kli = "0";                // PM10 cestice
  String tem_kli  = "0";                // temperatura na klimerku
  String hum_kli  = "0";                // vlaznost
  String pre_kli  = "0";                // pritisak
  char   lastTimeKli[25] = "--:--";     // vreme zadnjeg azuriranja podataka sa klimerka
  String airQuality = "n/a";            // kvalitet vazduha engleski
  String _airQuality = "Nema ažuriranja";// kvalitet vazduha srpski
  String _color = "Black";              // kolor teksta za kvaliret vazduha

// Time variable
//--------------------------------------------------------------------------------------------------
  #define UTC (1)                       // time zone "+01:00"
  byte tz = 2;                          // Time zone +1 default. Letnje racunjanje vremena +2
  int timezone = 1 * 3600;              // 3600 za +1 i 7200 za +2 (letnje racunjanje vremena)
  int dst = 1;                          // 1 - aktivno, 0 - neaktivno letnje racunjanje vremena
    
// Variable from Json data
//--------------------------------------------------------------------------------------------------
  int nowID;                            // Brojcana oznaka trenutnog stanja [weather][id]
  String dan_noc;
  String weather_main = "";             // Sadasnje stanje vremena
  String wind_deg="";                   // Smer vetra na osnovi degress
  String txtIconWeather = "";           // Naziv ikone u zavisnosti od stanja trenutnog meteo stanja
  String txtWindDir= "";                // smer vetra
  char sunrise[32],sunset[32];          // Izlazak i zalazak sunca(UTC unix time)
  byte clouds;                          // Oblacnost u %
  String uv_index;                      // UV index zracenja
  int humidity;                         // Vlaznost sa bazne stanice 

// Promenljiva za memorisanje trenutnog vremena pri izracuno koliko je proteklo vremena
//--------------------------------------------------------------------------------------------------    
  unsigned long prevMillis;

// Variable Json data from ip-api
//--------------------------------------------------------------------------------------------------
  String ip_query = "";                 // root["query"]
  String ip_status = "";                // root["status"] 
  String ip_country = "";               // root["country"]
  String ip_countryCode = "";           // root["countryCode"]
  String ip_region = "";                // root["region"]
  String ip_regionName = "";            // root["regionName"]
  String ip_city = "";                  // root["city"]
  String ip_timezone = "";              // root["timezone"]
  String ip_isp = "";                   // root["isp"]
  String ip_message = "";               // root["message"]


void setup() {
  Serial.begin(115200);
  for(uint8_t t = 4; t > 0; t--) {
    spf("   [SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }
    
  spln("\n\tESP AP & Station & UDP/TCP System");

// Start wifi konekcije sa mojim ruterom
//------------------------------------------------------------------
  WiFi.config(mystaticip, mygateway, mysubnet, mygateway);
  WiFi.mode(WIFI_AP_STA);//WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, passphrase);
  
  spf("\tStation connecting to %s WiFi\n\n", ssid);

  if (testWifi()){
    spln(" success!");
    spln(" -------------------------------------------------------");
    sp("  Station connected, IP address: ");
    spln(WiFi.localIP());
    spf("  Signal Strength: %d dBm\n", WiFi.RSSI());
    sp("  ESP Board MAC Address:  ");
    spln(WiFi.macAddress());
  }else{
    spln(" ESP goes to restart");
    ESP.restart();
  }

// Configure the Soft Access Point.
//---------------------------------------------------------------------------------------------------------------------
  sp("  Soft-AP configuration ... ");
  spln(WiFi.softAPConfig(APlocal_IP, APgateway, APsubnet) ? "OK" : "Failed!"); // configure network
  sp("  Setting soft-AP ... ");
  spln(WiFi.softAP(APssid, APpassword , 1, 1, 1) ? "OK" : "Failed!"); // Setup the Access Point chanel 1 and SSID hide
  sp("  Soft-AP IP address = ");
  spln(WiFi.softAPIP()); // Confirm AP IP address
  spln(" -------------------------------------------------------");

// Kreiram url na weather server sa kojeg preuzimam podatatke u JSON formatu
//------------------------------------------------------------------------------------------------------------------------------------------------------
  url_ow += "http://" + String(server_ow) + "/data/2.5/weather?lat=" +String(lat,6)+ "&lon=" +String(lon,6)+ "&units=" + unit_type+ "&appid="+ api_key;
  url_uv += "http://" + String(server_ow) + "/data/2.5/uvi?appid="+ api_key+ "&lat=" +String(lat,2)+ "&lon=" +String(lon,2);

// Odgovar web servera u zavisnosti od pristupa nekoj od strana
//---------------------------------------------------------------------------------------
  server.on("/", handleRoot);           // root
  server.on("/input", handleInput);     // pristigli izmereni podaci sa meteo stanice
  server.on("/map.html", handleMap);    // prikaz google map pozicije moje meteo stanice
  server.on("/about.html", handleAbout);// nesto o samoj meteo stanici
  server.on("/json.html", handleJson);  // kreiram JSON podatke sa prosledjivanje drugima
  server.on("/min.html", handleMin);    // minimizovani prikaz izmerenih podataka
  server.on("/gra.html",handleGra);     // Graficki prikaz podataka
  server.on("/kli", handleKli);         // podaci koje saljem na klimerka.org
  server.on("/style.css",handleCss);    // 
  server.onNotFound(handleNotFound);// Not Found
  server.begin();
  
  spln(" HTTP web server started\n");

  configTime(timezone, dst, "pool.ntp.org","time.nist.gov");  // uzimam vreme sa interneta na osvovu moje vremenske zone
  spln(" Waiting for Internet time");                         // i da li se koristi letnje racunjanje vremena

  while(!time(nullptr)){
    sp("*");
    delay(100);
  }
  spln(" Time response....OK!\n");   
  delay(100);
  
  getWeatherCondition();
  delay(1000);
}

// Funkcija za testiranje izabranog ili snimljenog WiFi-a 
//----------------------------------------------------------------
bool testWifi(void){
  int c = 0;
  sp(" Waiting for WiFi to connect ");
  while ( c < 20 ) {
    if (WiFi.status() == WL_CONNECTED)
    {
      return true;
    }
    delay(500);
    sp(".");
    c++;
  }
  spln("");
  sp(" Connection timed out.");
  return false;
}

void loop(){
  server.handleClient();
}

void getIpCondition(){
  ip_query = ""; ip_status = ""; ip_country = ""; ip_countryCode = ""; ip_region = ""; 
  ip_regionName = ""; ip_city = ""; ip_timezone = ""; ip_isp = ""; ip_message = "";
  // JSon data za IP client-a
  //------------------------------------------------------------------------
  if (WiFi.status() == WL_CONNECTED) {
    //http://ip-api.com/docs/api:json#test
    String  url_ip_api = "http://ip-api.com/json/";
            url_ip_api += String(cIp)+ "?fields=country,countryCode,region,regionName,city,timezone,isp,query,status,message";
    spln (" Json URL for ip-api: " + url_ip_api);
    HTTPClient http;  // Deklarisanje objekta na class HTTPClient
    #if defined(ESP8266)
      WiFiClient client;
      http.begin(client,url_ip_api);
    #else
      http.begin(url_ip_api);
    #endif
    
    int httpCode = http.GET();
    spln(" Response ; " + String(httpCode));

    if (httpCode > 0) {
      String payload = http.getString();
      const size_t bufferSize = JSON_OBJECT_SIZE(9) + 308;
      DynamicJsonDocument doc(bufferSize);
      const char* json = payload.c_str();
      spln( " Json data : " + String(json));
      deserializeJson(doc, json);
      
      // Root object
      ip_query         = doc["query"].as<String>();       // "109.245.39.10"
      ip_status        = doc["status"].as<String>();      // "success"
      if(ip_status == "success") {
        ip_country     = doc["country"].as<String>();     // "Serbia"
        ip_countryCode = doc["countryCode"].as<String>(); // "RS"
        ip_region      = doc["region"].as<String>();      // "00"
        ip_regionName  = doc["regionName"].as<String>();  // "Vojvodina"
        ip_city        = doc["city"].as<String>();        // "Šid"
        ip_timezone    = doc["timezone"].as<String>();    // "Europe/Belgrade"
        ip_isp         = doc["isp"].as<String>();         // "CETIN Ltd. Belgrade"
      }else{
        ip_message     = doc["message"].as<String>();
      }
      spln(" JSon data from IP client");
      spln(" -------------------------------------------------------");
      spln(" Query       : " + ip_query);
      spln(" Status      : " + ip_status);
      spln(" Country     : " + ip_country);
      spln(" Country code: " + ip_countryCode);
      spln(" Region      : " + ip_region);
      spln(" Region name : " + ip_regionName);
      spln(" City        : " + ip_city);
      spln(" Time zone   : " + ip_timezone);
      spln(" ISP         : " + ip_isp);
      spln(" Message     : " + ip_message);
      spln(" -------------------------------------------------------");
    }
    http.end();   // Close connection
  }

  char buf[400];
  sprintf(buf,"INSERT INTO nUm8euijbj.ip_client (ip_query,ip_status,ip_country,ip_countryCode,ip_region,ip_regionName,ip_city,ip_timezone,ip_isp,ip_message) "
              "VALUES ('%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s')" , 
              ip_query.c_str(), ip_status, ip_country, ip_countryCode, ip_region, ip_regionName, ip_city, ip_timezone.c_str(), ip_isp.c_str(), ip_message.c_str()); 
  
  spln("\n Send client data to MySQL database.");
  
  MySQL_connect(); // Connecting to SQL... 
  
  if (conn.connected()){
    cursor->execute("SET character_set_client = 'UTF8MB4';");
    cursor->execute("SET character_set_connection='UTF8MB4';");
    cursor->execute("SET character_set_results='UTF8MB4';");
    cursor->execute(buf);
    delay(50);
    delete cursor;
    spln(" SQL Query : " + String(buf));
    spln(" Success stored IP Condition data to MySQL database.\n");
  }else{
    spln(" Connection failed.\n");
    conn.close();          
  }
}

void getWeatherCondition(){// Json podaci koje preuzimam sa drugih meteo servera. Jos uvek nisam zavrsio kompletna merenja kod mene na stanici
  if (WiFi.status() == WL_CONNECTED) {
    spln(" Weather data processing");
    spln(" Connected to json data with API " + url_ow);

    HTTPClient http;  // Declare an object of class HTTPClient

    #if defined(ESP8266)
      WiFiClient client;
      http.begin(client,url_ow);
    #else
      http.begin(url_ow);
    #endif

    int httpCode = http.GET();
    
    spln(" Response : " + String(httpCode));
    
    if (httpCode > 0) {
      
      String payload = http.getString();// Get payload
      
      const size_t bufferSize = JSON_ARRAY_SIZE(1) + JSON_OBJECT_SIZE(1) + 2*JSON_OBJECT_SIZE(2) + // JSON buffer 
      JSON_OBJECT_SIZE(4) + JSON_OBJECT_SIZE(5) + JSON_OBJECT_SIZE(6) + JSON_OBJECT_SIZE(12) + 355;
      DynamicJsonDocument doc(bufferSize); 
      
      // Parse JSON data
      //------------------------------------------------------------------------------------------------------------------------------
      const char* json = payload.c_str();
      spln(" Json data : " + String(json));
      deserializeJson(doc, json);
      // Root object
      //------------------------------------------------------------------------------------------------------------------------------
      nowID            = doc["weather"][0]["id"];                 // Opis trenutnog meteo (ne)vremena
      txtIconWeather   = getMeteoconIcon(nowID);                  // Opis trenutnog meteo (ne)vremena prevedeno na srpski
      dan_noc          = doc["weather"][0]["icon"].as<String>();  // Na osnovu icone znamo dali je dan ili noc
      Win1             = doc["wind"]["speed"].as<String>();       // Brzina vetra u m/s
      weather_main     = doc["weather"][0]["main"].as<String>();  // Trenutno stanje vremena
      clouds           = doc["clouds"]["all"];                    // Oblacnost u %
      int deg          = doc["wind"]["deg"];                      // Smer vetra
      wind_deg         = WindDir(deg);                            // Smer vetra prevod srpski
      unsigned long sr = doc["sys"]["sunrise"];                   // Izlazak sunca
      unsigned long ss = doc["sys"]["sunset"];                    // Zalazak sunca
      sr = sr + tz * 3600;                                        // Dodajem time zone +2 (7200 a za +1 3600) u secundama
      ss = ss + tz * 3600;

      sprintf(sunrise, "%02d:%02d:%02d",hour(sr),minute(sr),second(sr));// kreiram lokal time HH:MM:SS od UTC time za izlazak sunca
      sprintf(sunset, "%02d:%02d:%02d",hour(ss),minute(ss),second(ss)); // za zalazak sunca
      
      String city = doc["name"];                                  // Ime mesta za koje prikupljamo podatke
      float tempNow = doc["main"]["temp"];                        // Temperatura (pruzeti podataka)
      humidity = doc["main"]["humidity"];                         // Vlaznost (preuzet podataka)
      String iconcode = doc["weather"][0]["icon"];                // ID ikone koju prikazujem
      String TodayIcon = "http://openweathermap.org/img/w/" + iconcode + ".png";// Link sa kojeg pruzima sliku za ID
      spln(" -------------------------------------------------------");
      spln("   City    : " + city);
      spln("   Temp    : " + String(tempNow,2));    
      spln("   Hum     : " + String(humidity));           
      spln("   Icona   : " + txtIconWeather);
      spln("   Slika   : " + TodayIcon);
      spln("   Sunrise : " + (String)sunrise);
      spln("   Sunset  : " + (String)sunset);
      spln(" -------------------------------------------------------\n");
    
    }else{
      spln(" No response from the Weather server.\n");
    }
    http.end();   // Close connection
  }
    
  // UV index
  //---------------------------------------------------------------
  spln(" UV Index data processing");
  spln(" Connected to json data with API " + url_uv);
  HTTPClient http;  // Deklaracija objekta na class HTTPClient

  #if defined(ESP8266)
    WiFiClient client;
    http.begin(client,url_uv);
  #else
    http.begin(url_uv);
  #endif

  int httpCode = http.GET();
  spln(" Response ; " + String(httpCode));
  if (httpCode > 0) {
    
    String payload = http.getString();// Get payload
    
    const size_t bufferSize = JSON_OBJECT_SIZE(5) + 172;// JSON buffer
    DynamicJsonDocument doc(bufferSize);
    
    // Parse JSON data
    //--------------------------------------------------------------------
    const char* json = payload.c_str();
    spln( " Json data : " + String(json));
    deserializeJson(doc, json);

    // Root object
    // Get main report
    //----------------------------------
    uv_index = doc["value"].as<String>();// Pruzeti uv index kao string
    spln(" -------------------------------------------------------");
    spln("   UV Index  : " + uv_index);
    spln(" -------------------------------------------------------\n");

    // Vrednost UV indexa http://www.hidmet.gov.rs/ciril/prognoza/uv1.php
    if (uv_index.toInt() >= 11)
      uv_index_description = "Ekstremno visoka"; 
    else if(uv_index.toInt() >= 8 || uv_index.toInt() <= 10)
      uv_index_description = "Vrlo visoka";
    else if(uv_index.toInt() >= 6 || uv_index.toInt() <= 7)
      uv_index_description = "Visoka"; 
    else if(uv_index.toInt() >= 3 || uv_index.toInt() <= 5)
      uv_index_description = "Umerena"; 
    else if(uv_index.toInt() >= 0 || uv_index.toInt() <= 2)
      uv_index_description = "Niska";  
     
  }
  http.end();
}

void handleJson(){// Kreiram stranu na kojoj je sano text po Json standardu. Ovo za preuzimanje izmerenih vrednosti za potrebe trece strane
  server.send(200, "text/html", json_html);
}

void handleKli() { // Kad stignu podaci sa klimerka
  time_t now = time(nullptr);
  struct tm* p_tm = localtime(&now);
  sprintf(lastTimeKli,"%2d:%02d - %02d.%02d.%04d.", (p_tm->tm_hour+UTC)%24, p_tm->tm_min, ((p_tm->tm_hour+UTC)%24 == 0) ? p_tm->tm_mday +1 : p_tm->tm_mday,
          p_tm->tm_mon+1,(p_tm->tm_year + 1900));

  
  String message = " Number of args received from klimerko : ";
  message += server.args();                     // Ukupan broj svih parametara koji se potrazuju
  message += "\n";                            
  message += " -------------------------------------------------------------------\n";
  for (int i = 0; i < server.args(); i++) {
    message += "  Arg nº" + (String)i + " -> "; // Redni broj parametra
    message += server.argName(i) + ": ";        // Naziv za parametar
    message += server.arg(i) + "\n";            // Vrednost parametra
    delay(10);
  }
  message += " -------------------------------------------------------------------"; 
  spln(message);
  spln(" Vreme zadnjeg merenja klimerka : " + String(lastTimeKli) + "\n");
  pm1_kli  = server.arg("PM1");                 // server.arg(0);
  pm25_kli = server.arg("PM25");                // server.arg(1);
  pm10_kli = server.arg("PM10");                // server.arg(2);
  tem_kli  = server.arg("Temperature");         // server.arg(3);
  hum_kli  = server.arg("Humidity");            // server.arg(4);
  pre_kli  = server.arg("Pressure");            // server.arg(5);

  int pm10 = pm10_kli.toInt();
  // Assign a text value of how good the air is based on average value
  // http://www.amskv.sepa.gov.rs/kriterijumi.php
  if (pm10 <= 20) {
    airQuality = "Excellent";       // Kvalitet vazduha
    _airQuality = "Odličan";        // Kvalitet srpski prevod
    _color = "MediumSeaGreen";      // Boja prikaza kvaliteta
  } else if (pm10 >= 21 && pm10 <= 40) {
    airQuality = "Good";
    _airQuality = "Dobar";
    _color = "Coral";
  } else if (pm10 >= 41 && pm10 <= 50) {
    airQuality = "Acceptable";
    _airQuality = "Prihvatljiv";
    _color = "Tomato";
  } else if (pm10 >= 51 && pm10 <= 100) {
    airQuality = "Polluted";
    _airQuality = "Zagađen";
    _color = "OrangeRed";
  } else if (pm10 > 100) {
    airQuality = "Very Polluted";
    _airQuality = "Jako Zagađen";
    _color = "Red";
  }
      
  server.send(200, "text/plain", "OK!"); // Send HTTP status 200 (Ok) and send some text to the browser/client
}

void handleInput() {// Ovde se hendluje strana kada dolaze izmerene vrednosti
  time_t now = time(nullptr);
  struct tm* p_tm = localtime(&now);
  sprintf(lastTime,"%2d:%02d - %02d.%02d.%04d.", (p_tm->tm_hour+UTC)%24, p_tm->tm_min, ((p_tm->tm_hour+UTC)%24 == 0) ? p_tm->tm_mday +1 : p_tm->tm_mday,
          p_tm->tm_mon+1,(p_tm->tm_year + 1900));


  String message = " Number of args received : ";
  message += server.args();                     // Ukupan broj svih parametara koji se potrazuju
  message += "\n";                        
  message += " -------------------------------------------------------------------\n";
  for (int i = 0; i < server.args(); i++) {
    message += "  Arg nº" + (String)i + " -> "; // Redni broj parametra
    message += server.argName(i) + ": ";        // Naziv za parametar
    message += server.arg(i) + "\n";            // Vrednost parametra
    delay(10);
  }
  message += " -------------------------------------------------------------------"; 
  spln(message);
  spln(" Vreme zadnjeg merenja : " + String(lastTime) + "\n");
  Tem = server.arg("Temperature");      // Temperatura DS18B20
  //Hum = server.arg("Humidity");       // Vlaznost (moj BME)
  Hum = String(humidity);               // Vlaznost preuzet podataka (ovako sam morao jer BME280 brljavi sa vlaznosti)
  Pre = server.arg("Pressure");         // Pritisak
  Win = server.arg("WinSpeed");         // Brzina vetra (preuzet podatak)
  Vcc = server.arg("Voltage");          // Napon na bateriji
  Rsi = server.arg("RSSI");             // Jacina wifi signala
  Tmb = server.arg("TempInCase");       // Temperatura u kucistu sa BME280 
  Slp = server.arg("SeaLevelPressure"); // Nadmoraka visina na osnovu pritiska
  
  server.send(200, "text/plain", "OK!");// Send HTTP status 200 (Ok) and send some text to the browser/client

  // Slanje podataka na moj kanal na ThingSpeak
  //-----------------------------------------------------------
  String thingSpeak = String(thingSpeakAddress); 
          thingSpeak += "/update?api_key=" + String(writeAPIKey);
          thingSpeak += "&field1=" +  Tem;
          thingSpeak += "&field2=" +  Hum;
          thingSpeak += "&field3=" +  Pre;
          thingSpeak += "&field4=" +  Win1;
          thingSpeak += "&field5=" +  uv_index;
          thingSpeak += "&field6=" +  Vcc;
          thingSpeak += "&field7=" +  Rsi;

  spln (" Send data to ThingSpeak my channel");
  spln (" Link : " + thingSpeak); 
      
  HTTPClient http;
      
  #if defined(ESP8266)
    WiFiClient client;
    http.begin(client,thingSpeak);
  #else
    http.begin(thingSpeak);
  #endif

  int httpCode = http.GET();
  
  spln(" Response ; " + String(httpCode));
  if (httpCode > 0) {
    spln(" Data sent successfully\n");
  }else{
    spln(" Failure! Data not sent successfully.\n");
  }
  http.end();
      
  // Insert MySQL      
  //------------------------------------------------------------
  char buf[512];
  sprintf(buf, "INSERT INTO nUm8euijbj.meteo_data (Temperature,Humidity,Pressure,WinSpeed,UVindex,Voltage,RSSI,TempInCase,wMain,wIcon,PM10,PM1,PM25,K_Tem,K_Hum,K_Pre) "
                "VALUES ('%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', %s, %s, %s, %s, %s, %s)" ,
                Tem, Hum, Pre, Win1, uv_index, Vcc, Rsi, Tmb, weather_main, txtIconWeather.c_str(), pm10_kli, pm1_kli, pm25_kli, tem_kli, hum_kli, pre_kli);
  
  // Connecting to SQL 
  //---------------------------------------------------------------
  spln(" Send measured meteo data to MySQl database.");
  MySQL_connect();
      
  if (conn.connected()){
    //cursor->execute("SET time_zone = '+02:00';");//("SET @@session.time_zone = '+02:00'");//Setovanje time zone za citanje podataka zbog vremenske razlike sa serverom
    cursor->execute("SET character_set_client = 'UTF8MB4';");
    cursor->execute("SET character_set_connection = 'UTF8MB4';");
    cursor->execute("SET character_set_results = 'UTF8MB4';");
    cursor->execute(buf);
    delay(50);
    delete cursor;
    spln(" SQL Query : " + String(buf));
    spln(" Recording data.\n");
  }else{
    spln("Connection failed.\n");
    conn.close();          
  }
}

void handleRoot() {// Osnovna starnica web sajta
      
  cIp = server.client().remoteIP().toString();
  spln(" Remote client IP : " + String(cIp));
  getIpCondition();
  getWeatherCondition();
  
  String ow_f; 
  if (nowID == 800 || nowID == 801 || nowID == 802){// Za ova tri ID-a mogu da biram ikonu dan-noc
    ow_f = "-" + dan_noc.substring(dan_noc.length()-1);
  }else{
    ow_f = ""; 
  } 

  String s = index_html;
  // Tabela
  //---------------------------------------------------------------------------
  s.replace("@@h_tem@@",Tem);           // Temperatura
  s.replace("@@h_hum@@",Hum);           // Vlaznost vazduha
  s.replace("@@h_pre@@",Pre);           // Atmosferski pritisak
  s.replace("@@h_winsm@@",Win1);        // Brzina vetra
  s.replace("@@h_wins@@",wind_deg);     // Smer vetra
  s.replace("@@h_wind@@",symbolWindDir);// Smer vetra oznaka
  s.replace("@@h_obl@@",String(clouds));// Intezitet oblacnosti
  s.replace("@@h_izl@@",sunrise);       // Izlazak sunca
  s.replace("@@h_zal@@",sunset);        // Zalazak sunca
  s.replace("@@h_uv@@",String(uv_index.toFloat(),1));// UV index
  s.replace("@@h_uvd@@",uv_index_description);// Descriptionm uv index-a
  s.replace("@@h_alt@@",Alt);           // Altitude
  s.replace("@@h_vcc@@",Vcc);           // Vcc Battery
  s.replace("@@h_rsi@@",Rsi);           // RSI
  s.replace("@@h_mes@@",lastTime);      // Poslednje merenje
  s.replace("@@h_pm0@@",pm1_kli);       // PM1 suspend
  s.replace("@@h_pm1@@",pm25_kli);      // PM2.5 suspend
  s.replace("@@h_pm2@@",pm10_kli);      // PM10 suspend 
  
  // Widgets
  //---------------------------------------------------------------------------
  s.replace("@@w_sta@@",weather_main);  // Trenutno stanje vremena
  s.replace("@@w_stas@@",txtIconWeather);// Trenutno stanje vremena na srpskom
  s.replace("@@w_icon@@",String(nowID) + ow_f);
  s.replace("@@w_temhead@@",String(round(Tem.toFloat()),0));// Zaokruzena vrednost temperature bez decimala
  s.replace("@@w_tem@@",Tem);
  s.replace("@@w_pre@@",Pre);
  s.replace("@@w_hum@@",Hum);
  s.replace("@@w_uvi@@",String(uv_index.toFloat(),1));// uv_index);
  s.replace("@@w_alt@@",Alt);           // Altitude
  s.replace("@@w_air@@",airQuality);    // Kvalitet vazduha
  
  // Pozicija na mapi i izlazak-zalazak sunca
  //---------------------------------------------------------------------------
  s.replace("@@n_lat@@",String(lat,2)); // Latitude
  s.replace("@@n_lon@@",String(lon,2)); // Longitude
  s.replace("@@n_izl@@",sunrise);       // Izlazak sunca
  s.replace("@@n_zal@@",sunset);        // Zalazak sunca
  
  // Klimerko
  //---------------------------------------------------------------------------
  s.replace("@@k_color@@",_color);      // Boja teksta za prikaz zagadjenosti
  s.replace("@@k_air@@",airQuality);    // Kvalitet vazduha EN
  s.replace("@@k_airs@@",_airQuality);  // Kvaltet vazduha SR
  s.replace("@@k_pm1@@",pm10_kli);      // PM10
  s.replace("@@k_pm2@@",pm25_kli);      // PM2.5
  s.replace("@@k_pm0@@",pm1_kli);       // PM1
  s.replace("@@k_last@@",lastTimeKli);  // Zadnje merenje kvaliteta vazduha
  
  // Your IP adress
  //---------------------------------------------------------------------------
  s.replace("@@ip@@",cIp);              // Your ip adress

  server.send(200, "text/html", s);
}

void handleAbout(){// About web page    
  server.send(200, "text/html", about_html);
  }
void handleGra(){// Page za gradicki prikaz izmerenih vrednosti  
  server.send(200, "text/html", gra_html);
  }
void handleNotFound(){// Page not found
  String message = " Bad request!\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\n Method: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\n Arguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}
void handleMap() { // Google maps location za moju meteo stanicu
  server.send(200, "text/html", map_html);
}

void handleMin() {// Minimalni prikaz osnpvnih merenja
  
  String s1 = min_html;
  s1.replace("@@min-tem@@", Tem);
  s1.replace("@@min-hum@@", Hum);
  s1.replace("@@min-pre@@", Pre);
  s1.replace("@@min-alt@@", Alt);
  
  server.send(200, "text/html", s1);
}

void handleCss() {// Ovde koristim standarni style.css file
  server.send(200,"text/css",style_css);    
}
/*void handleFavIcon() {// Koristim icon za web brovser kao x-image
  server.send(200,"text/ico", fav_icon2);  
}*/

void MySQL_connect(){
  sp(" Server : ");
  spln(server_addr);
  spf(" User   : %s\n",user);
  spf(" Pass   : %s\n",password);
  sp(" Connecting...");
  if (conn.connect(server_addr, 3306, user, password)){
    //spln(" OK!\n");
  }else
    spln(" MySQL connection FAILED.\n");
  
  // create MySQL cursor object
  cursor = new MySQL_Cursor(&conn);
}

String getMeteoconIcon(int ID) { 
  // Group 800: Clear
  if (ID == 800) return "Vedro nebo";
  // Group 80x: Clouds
  if (ID == 801) return "Malo oblaka";                // few clouds
  if (ID == 802) return "Raštrkani oblaci";           // scattered clouds
  if (ID == 803) return "Razbijeni oblaci";           // broken clouds
  if (ID == 804) return "Oblačno";                    // overcast clouds
  // Group 7xx: Atmosphere
  if (ID == 701) return "Izmaglica";                  // mist
  if (ID == 711) return "Dim";                        // smoke
  if (ID == 721) return "Izmaglica";                  // haze
  if (ID == 731) return "Pesak,prašina-vrtlog";       // sand, dust whirls
  if (ID == 741) return "Magla";                      // fog
  if (ID == 751) return "Pesak";                      // sand
  if (ID == 761) return "Prašina";                    // dust
  if (ID == 762) return "Vulkanski pepeo";            // volcanic ash
  if (ID == 771) return "Udar vetra";                 // squalls
  if (ID == 781) return "Tornado";                    // tornado
  // Group 6xx: Snow
  if (ID == 600) return "Lagani sneg";                // light snow
  if (ID == 601) return "Sneg";                       // snow
  if (ID == 602) return "Mečava";                     // heavy snow
  if (ID == 611) return "Susnežica";                  // sleet
  if (ID == 612) return "Tuš susnežice";              // shower sleet
  if (ID == 615) return "Lagana kiša i sneg";         // light rain and snow
  if (ID == 616) return "Kiša i sneg";                // rain and snow
  if (ID == 620) return "Lagani padavine snega";      // light shower snow
  if (ID == 621) return "Tuš snega";                  // shower snow
  if (ID == 622) return "Jake padavine snega";        // heavy shower snow
  // Group 5xx: Rain
  if (ID == 500) return "Slaba kiša";                 // light rain     
  if (ID == 501) return "Umerena kiša";               // moderate rain 
  if (ID == 502) return "Kiša s jakim intenzitetom";  // heavy intensity rain 
  if (ID == 503) return "Jaka kiša";                  // very heavy rain 
  if (ID == 504) return "Ekstremna kiša";             // extreme rain 
  if (ID == 511) return "Ledena kiša";                // freezing rain
  if (ID == 520) return "Lagan intezitet kiše";       // light intensity shower rain
  if (ID == 521) return "Pljusak";                    // shower rain
  if (ID == 522) return "Pljusak jakog inteziteta";   // heavy intensity shower rain 
  if (ID == 531) return "Mestimičan pljusak";         // ragged shower rain 
  // Group 3xx: Drizzle
  if (ID == 300) return "Slab intezitet rominjanja";  // light intensity drizzle
  if (ID == 301) return "Rominjanje";                 // drizzle
  if (ID == 302) return "Jak intezitet rominjanja";   // heavy intensity drizzle
  if (ID == 310) return "Slab intezitet rominjanja kiše";// light intensity drizzle rain
  if (ID == 311) return "Rominjanje kiše";            // drizzle rain
  if (ID == 312) return "Jak intezitet rominjanja kiše"; // heavy intensity drizzle rain
  if (ID == 313) return "Pljusak i rominjanja";       // shower rain and drizzle
  if (ID == 314) return "Jak pljusak i rominjanje";   // heavy shower rain and drizzle
  if (ID == 321) return "Rominjanje";                 // shower drizzle
  // Group 2xx: Thunderstorm
  if (ID == 200) return "Oluja sa slabom kišom";      // thunderstorm with light rain 
  if (ID == 201) return "Oluja sa kišom";             // thunderstorm with rain  
  if (ID == 202) return "Oluja sa jakom kišom";       // thunderstorm with heavy rain  
  if (ID == 210) return "Slaba oluja";                // light thunderstorm 
  if (ID == 211) return "Oluja";                      // thunderstorm
  if (ID == 212) return "Jaka oluja";                 // heavy thunderstorm
  if (ID == 221) return "Oluja sa grmljavinom";       // ragged thunderstorm 
  if (ID == 230) return "Oluja sa slabim rominjanjem";// thunderstorm with light drizzle 
  if (ID == 231) return "Oluja sa rominjanjem";       // thunderstorm with drizzle 
  if (ID == 232) return "Oluja sa jakim rominjanjem"; // thunderstorm with heavy drizzle
        
  return "N/A";
}

String WindDir (int code){// Wind Direction and Degrees
  if (code >= 349 && code <  11) {symbolWindDir = "N"  ; return "Sever";}              // N    348.75 -  11.25
  if (code >=  11 && code <  34) {symbolWindDir = "NNE"; return "Sever-Severistok";}   // NNE   11.25 -  33.75
  if (code >=  34 && code <  56) {symbolWindDir = "NE" ; return "Severoistok";}        // NE    33.75 -  56.25
  if (code >=  56 && code <  79) {symbolWindDir = "ENE"; return "Istok-Severoistok";}  // ENE   56.25 -  78.75
  if (code >=  79 && code < 101) {symbolWindDir = "E"  ; return "Istok";}              // E     78.75 - 101.25
  if (code >= 101 && code < 124) {symbolWindDir = "ESE"; return "Istok-Jugoistok";}    // ESE  101.25 - 123.75
  if (code >= 124 && code < 146) {symbolWindDir = "SE" ; return "Jugoistok";}          // SE   123.75 - 146.25
  if (code >= 146 && code < 169) {symbolWindDir = "SSE"; return "Jug-Jugoistok";}      // SSE  146.25 - 168.75
  if (code >= 169 && code < 191) {symbolWindDir = "S"  ; return "Jug";}                // S    168.75 - 191.25
  if (code >= 191 && code < 214) {symbolWindDir = "SSW"; return "Jug-Jugozapad";}      // SSW  191.25 - 213.75
  if (code >= 214 && code < 236) {symbolWindDir = "SW" ; return "Jugozapad";}          // SW   213.75 - 236.25
  if (code >= 236 && code < 259) {symbolWindDir = "WSW"; return "Zapad-Jugozapad";}    // WSW  236.25 - 258.75
  if (code >= 259 && code < 281) {symbolWindDir = "W"  ; return "Zapad";}              // W    258.75 - 281.25
  if (code >= 281 && code < 304) {symbolWindDir = "WNW"; return "Zapad-Severozapad";}  // WNW  281.25 - 303.75
  if (code >= 304 && code < 326) {symbolWindDir = "NW" ; return "Severozapad";}        // NW   303.75 - 326.25
  if (code >= 326 && code < 349) {symbolWindDir = "NNW"; return "Sever-Severozapad";}  // NNW  326.25 - 348.75
  symbolWindDir = "N/A";
  return "N/A";
}
