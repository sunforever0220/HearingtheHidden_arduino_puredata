#include <NewPing.h>
unsigned int us_value1,us_value2;
#define MAX_DISTANCE 400
#define DEBUG true
#define wifi_pin 13

String Wifi_SSID="Ambientwalk";//replace with your Wifi SSID name
String Wifi_PWD="ambientwalkosc";       //replace with your Wifi password

//String apikey="0P31Q41VMNV3KVJO";  // YOUR THINGSPEAK.COM ACCOUNT API KEY
NewPing sonar1(3, 2, MAX_DISTANCE);//left
NewPing sonar2(9, 8, MAX_DISTANCE);//right


void setup()
{
  pinMode(13, OUTPUT); 
  digitalWrite (13, HIGH);   
  Serial.begin(9600); 
  Serial1.begin(9600);

  //sendData("AT+RST\r\n",2000,DEBUG); // reset module
  sendData("AT+CWMODE=1\r\n",500,DEBUG); // configure as client
  sendData("AT+CWJAP=\"" + Wifi_SSID + "\",\"" + Wifi_PWD + "\"\r\n",3000,DEBUG); // connect to router
  delay(10000);
  sendData("AT+CIFSR\r\n",500,DEBUG); // get ip address
  sendData("AT+CIPMUX=1\r\n",500,DEBUG); // configure for multiple connections
  
  Serial.println("Server ready");
  Serial.println();
}

void loop()
{ us_value1 = sonar1.ping()/US_ROUNDTRIP_CM;
  Serial.print("Distance1: ");
  Serial.print(us_value1);
  Serial.print("cm; ");
  us_value2 = sonar2.ping()/US_ROUNDTRIP_CM;
   Serial.print("Distance2: ");
  Serial.print(us_value2);
  Serial.println("cm ");
  
  String ultrasonic1=String(us_value1);// turn integer to string
  String ultrasonic2=String(us_value2);
  
  // TCP CONNECTION
  /*
  String connectServer = "AT+CIPSTART=4,\"UDP\",\"";
  connectServer += "184.106.153.149"; // api.thingspeak.com
  connectServer += "\",80";
*/
//UDP connection to OSC receiver
  String connectServer = "AT+CIPSTART=4,\"TCP\",\"";
  connectServer += "172.20.10.2"; // api.thingspeak.com
  connectServer += "\",12000";

    
  //Serial.print("TCP Connection = ");
  Serial.print("UDP Connection = ");
  Serial.println(connectServer);
  Serial1.println(connectServer);
  delay(2000);  // wait 2 second to establish connection between thingSpeak and ESP8266
   
  if(Serial1.find("Error"))
  {
    Serial.println("AT+CIPSTART error");
    return;
  }
  
  // UPDATE THINGSPEAK CHANNEL WITH DATA STRING
  /*
  String dataToPush = "GET /update?api_key=";
  dataToPush += apikey;
  dataToPush +="&field1=";
  dataToPush += ultrasonic1;
  dataToPush +="&field2=";
  dataToPush += ultrasonic2;
  dataToPush += "\r\n\r\n";
*/
//sample osc
String dataToPush = "L120R220\r\n";


  Serial.print("Data updated = ");
  Serial.print(dataToPush);

  // SEND DATA LENGTH
  String sendData = "AT+CIPSEND=4,";
  sendData += String(dataToPush.length());

  Serial.print("Data length = ");
  Serial.println(sendData);
  Serial1.println(sendData);
  delay(500);  // wait 2 second to establish connection between thingSpeak and ESP8266

  if(Serial1.find(">"))
  {
    Serial1.print(dataToPush);
    Serial.println("Data sent");
  }
  else
  {
    Serial1.println("AT+CIPCLOSE");
    Serial.println("AT+CIPCLOSE");  // alerting closing connection
  }
   
  delay(15000);  // thingSpeak needs minimum 15 sec delay between updates
}

String sendData(String command, const int timeout, boolean debug)
{
    String response = "";
    
    Serial1.print(command); // send the read character to the esp8266
    
    long int time = millis();
    
    while( (time+timeout) > millis())
    {
      while(Serial1.available())
      {
        char c = Serial1.read(); // read the next character.
        response+=c;
      }  
    }
    
    if(debug)
    {
      Serial.print(response);
    }
    
    return response;
}
