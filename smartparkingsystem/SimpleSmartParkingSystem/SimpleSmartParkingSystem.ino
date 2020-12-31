
/*
 * Created by Alinda Arnold (Mobizt)
 * 
 * Email: alindaarnold0001b@gmail.com
 * 
 * 
 * 
 * Copyright (c) 2019 schanter
 * 
 * This example is for the beginner
 *
*/


#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>

//1. Change the following info
#define FIREBASE_HOST "https://smartparking256.firebaseio.com/"
#define FIREBASE_AUTH "OLN45U7C6fRmdJgOx5BbP5BUES11UcEq5svvDX4Z"
#define WIFI_SSID "schanter"
#define WIFI_PASSWORD "schanter"


//2. Define FirebaseESP8266 data object for data sending and receiving
FirebaseData firebaseData;

int slot_1 = D1;
int slot_2 = D3;


void setup()
{
  pinMode(slot_1,INPUT);
//  pinMode(slot_2,INPUT);
  delay(200);
  Serial.begin(115200);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();


  //3. Set your Firebase info

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  //4. Enable auto reconnect the WiFi when connection lost
  Firebase.reconnectWiFi(true);

  //5. Try to set int data to Firebase
  //The set function returns bool for the status of operation
  //firebaseData requires for sending the data
  if(Firebase.getJSON(firebaseData, "/parkingslots"))
  {
    //Success
    Firebase.deleteNode(firebaseData, "/parkingslots");
     Serial.println("node deleted successfully");
     delay(1000);

  }else{
    //Failed?, get the error reason from firebaseData

    Serial.print("Error in setInt, ");
    Serial.println(firebaseData.errorReason());
  }
  
}

void loop()
{


int slot_1_val = digitalRead(slot_1);
int slot_2_val = digitalRead(slot_2);

delay(1000);

  if(slot_1_val == 1){
    
      Firebase.setString(firebaseData, "/parkingslots/Slot_1", "Not Car Parked");

      delay(500);
    }else if(slot_1_val == 0){

      Firebase.setString(firebaseData, "/parkingslots/Slot_1", "Car Parked");
      delay(500);

      
      }


    if(slot_2_val == 1){
    
      Firebase.setString(firebaseData, "/parkingslots/Slot_2", "NO Car Parked");

      delay(500);
    }else if(slot_2_val == 0){

      Firebase.setString(firebaseData, "/parkingslots/Slot_2", "Car Is Parked");
      delay(500);

      
      }

}
