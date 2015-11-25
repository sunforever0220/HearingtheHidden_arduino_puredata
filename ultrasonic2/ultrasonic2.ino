#include <NewPing.h>
unsigned int us_value1,us_value2;
#define MAX_DISTANCE 400

NewPing sonar1(3, 2, MAX_DISTANCE);//left
NewPing sonar2(9, 8, MAX_DISTANCE);//right

void setup()
{ Serial.begin(9600); 
}

void loop()
{ us_value1 = sonar1.ping()/US_ROUNDTRIP_CM;
  us_value2 = sonar2.ping()/US_ROUNDTRIP_CM;
  Serial.print(us_value1);
  delay(5);
  Serial.print(" ");
  delay(5);
  Serial.print(us_value2);
  Serial.println();
  delay(2000);  // update per 2s
}
