#ifndef PROV_WIFI_H
#define PROV_WIFI_H

#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager
#include <ESPmDNS.h>

void connectToWiFi() {
    WiFi.config(INADDR_NONE, INADDR_NONE, INADDR_NONE, INADDR_NONE);
    WiFi.setHostname("mylamp");
    WiFi.mode(WIFI_STA); // explicitly set mode, esp defaults to STA+AP
    //WiFi.disconnect(true);
    

    //WiFiManager, Local intialization. Once its business is done, there is no need to keep it around
    WiFiManager wm;
    wm.setShowInfoErase(true);      //  show erase button on info page

    //set static ip
    //wm.setSTAStaticIPConfig(IPAddress(192,168,2,151), IPAddress(192,168,2,1), IPAddress(255,255,255,0)); // set static ip,gw,sn
    wm.setShowStaticFields(true); // force show static ip fields
    wm.setShowDnsFields(true);    // force show dns field always

    //reset settings - wipe credentials for testing
    //wm.resetSettings();

    // Automatically connect using saved credentials,
    // if connection fails, it starts an access point with the specified name ( "AutoConnectAP"),
    // if empty will auto generate SSID, if password is blank it will be anonymous AP (wm.autoConnect())
    // then goes into a blocking loop awaiting configuration and will return success result

    // bool res;
    // res = wm.autoConnect(); // auto generated AP name from chipid
    // res = wm.autoConnect("My_Lamp_WiFi_Prov"); // anonymous ap
   
    bool res = wm.autoConnect("Add_My_Lamp_to_WiFi","password"); // password protected ap

    if(!res) {
        Serial.println("Failed to connect");
        // ESP.restart();
    } 
    else {
        //if you get here you have connected to the WiFi    
        Serial.println("connected...yeey :)");
        Serial.println(WiFi.getHostname());
        if (!MDNS.begin("mylamp")) {
        Serial.println("Error setting up MDNS responder!");
        while(1) {
            delay(1000);
        }
      }
      Serial.println("mDNS responder started");
    }
}

#endif
