#define BLYNK_PRINT Serial
#define Jingwei_Home V1 //Blynk virtual pin 1 that stores the status of Jingwei
#define Chuyi_Home V2 //Blynk virtual pin 2 that stores the status of Chuyi
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "YOUR_BLYNK_AUTH_TOKEN";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "SSID";
char pass[] = "PASS";

// Home member status
int whether_jingwei_ishome = 0;
int whether_chuyi_ishome = 0;

// To read data from Blynk app widgets
BLYNK_WRITE(Jingwei_Home)
{
  whether_jingwei_ishome = param.asInt(); // param.asInt()  is the value from V1.

  if (whether_jingwei_ishome == 1) {
        //HIGH - ON
       Serial.println(F("Jingwei is home!")); // to serial monitor
       digitalWrite(13, HIGH); // Turn on the appliance when Jingwei is home.
      
    }else {
       //LOW - OFF
      Serial.println(F("Jingwei left home!"));  // to serial monitor
      if (whether_chuyi_ishome == 0) // Check if Chuyi is home
      {digitalWrite(13,LOW); // If both are out, turn off the appliance
      }
    }
}

BLYNK_WRITE(Chuyi_Home)
{
  whether_chuyi_ishome = param.asInt();

  if (whether_chuyi_ishome == 1) {
        //HIGH - ON
       Serial.println(F("Chuyi is home!")); // to seral monitor
       digitalWrite(13, HIGH);
      
    }else {
       //LOW - OFF
      Serial.println(F("Chuyi left home!"));  // to seral monitor
      if (whether_jingwei_ishome == 0)
      {digitalWrite(13,LOW);
      }
    }
}


void setup()
{
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 8442);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8442);
}

void loop()
{
  Blynk.run();


  // You can inject your own code or combine it with other sketches.
  // Check other examples on how to communicate with Blynk. Remember
  // to avoid delay() function!
}

