#include <WiFi.h>
#include <NTPClient.h>
#include <FirebaseESP32.h>

/* Update time 7:16 Pm - 07/06/2022 */

// Replace with your network credentials
//const char* ssid     = "BKer_1_5Ghz";
//const char* password = "huynhbs25251325";
//const char* ssid     = "BKer_1";
//const char* password = "huynhbs25251325";
//const char* ssid = "6BeVanDan_2.4G";
//const char* password = "99999999";
const char* ssid     = "Viva Star Wifi Free";
const char* password = "68686868";
//const char* ssid     = "HUNG_VNPT";
//const char* password = "huynhhan";

//const char* ssid     = "BKer_1";
//const char* password = "HuynhTop176C142129";


//Firebase
#define FIREBASE_HOST "https://wifi-controller-94a3b.firebaseio.com/"
#define FIREBASE_AUTH "ttVcbl0zUQn8Hsz4clnrf0C15kIfP3KUZG2M6rTm"
FirebaseData firebaseData1;
FirebaseData firebaseData2;
FirebaseData firebase_Calendar;
FirebaseData first;
String path = "/Nodes";
String path_Calendar = "/Calendar";
String path_Days = "Days";
String path_Times = "Times";
String note_Day = "Day";
String note_Month = "Month";
String note_Year = "Year";
String note_Hour = "Hour";
String note_Min = "Min";
String note_Second = "Second"; 
String nodeID = "Node2";
String otherNodeID = "Node1"; 
const int ledPin =  19; //GPIO19 for LED
const int swPin =  18; //GPIO18 for Switch
boolean swState = true;

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

// Variables to save date and time
String formattedDate;
String dayStamp;
String timeStamp;
//======================================
void streamCallback(StreamData data)
{

  if (data.dataType() == "boolean") {
    if (data.boolData())
      Serial.println("*streamCallback* Set " + nodeID + " to High");
    else
      Serial.println("*streamCallback* Set " + nodeID + " to Low");
    digitalWrite(ledPin, data.boolData());
  }
}
//=====================================
void streamTimeoutCallback(bool timeout)
{
  if (timeout)
  {
    Serial.println();
    Serial.println("Stream timeout, resume streaming...");
    Serial.println();
  }
}
//===================================
void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP()); //streamCallback

// Init Firebase
  Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH);
Firebase.reconnectWiFi(true);

  if ((!Firebase.beginStream(firebase_Calendar, path_Calendar + "/" + path_Days + "/" + note_Day))& (!Firebase.beginStream(firebase_Calendar, path_Calendar + "/" + path_Times + "/" + note_Hour)))
  {
    
    Serial.println("Could not begin stream");
    Serial.println("REASON: " + firebase_Calendar.errorReason());
    Serial.println();
  }
  else
  {
    Serial.println("start connect to firebase_Calendar");
    }
  Firebase.setStreamCallback(firebase_Calendar, streamCallback, streamTimeoutCallback);

// Initialize a NTPClient to get time
  timeClient.begin();
  timeClient.setTimeOffset(+7*60*60);
}
void loop() {
  while(!timeClient.update()) {
    timeClient.forceUpdate();
  }
  // The formattedDate comes with the following format:
  // 2018-05-28T16:00:13Z
  // We need to extract date and time
  formattedDate = timeClient.getFormattedDate();
 // Serial.println(formattedDate);

  // Extract date
  int splitT = formattedDate.indexOf("T");
  dayStamp = formattedDate.substring(0, splitT);
//  Serial.print("DATE: ");
//  Serial.println(dayStamp);
  // Extract time
  timeStamp = formattedDate.substring(splitT+1, formattedDate.length()-1);
//  Serial.print("HOUR: ");
//  Serial.println(timeStamp);
//===================================
/*
    if (Firebase.setBool(firebaseData1, path + "/" + otherNodeID, false)) {
      if (swState)
        Serial.println("Set " + otherNodeID + " to High");
      else
        Serial.println("Set " + otherNodeID + " to Low");
    } else {
      //swState = _swState;
      Serial.println("Could not set " + otherNodeID);
    }
    */
//===================================
if (Firebase.setString(firebase_Calendar, path_Calendar + "/" + path_Days + "/" + note_Day, dayStamp))
{
       Serial.print("DATE: ");
  Serial.println(dayStamp);
    }

if (Firebase.setString(firebase_Calendar, path_Calendar + "/" + path_Times + "/" + note_Hour, timeStamp))
{
       Serial.print("HOUR: ");
  Serial.println(timeStamp);
    }
  
 // delay(1000);
}
