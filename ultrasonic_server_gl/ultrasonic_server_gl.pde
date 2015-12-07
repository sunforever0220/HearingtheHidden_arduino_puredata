/**
 * (./) udp.pde - how to use UDP library as unicast connection
 * (cc) 2006, Cousot stephane for The Atelier Hypermedia
 * (->) http://hypermedia.loeil.org/processing/
 * This is the server (android) code that receives messages from the arduino/arduino simulator
 * Create a communication between Processing (Android) <-> LibPD 
**/

import hypermedia.net.*;
//String res_message="";
String left="", right=""; 
int distance_L=0,distance_R=0;
boolean isLeft=false,isRight=false;
UDP udp;  // define the UDP object

void setup() {
size(500,250);background(0);
stroke(255);
  // create a new datagram connection on port 6000
  // and wait for incomming message
  udp = new UDP( this, 12000 );
  //udp.log( true );     // <-- printout the connection activity
  udp.listen( true );
  smooth();
}

//process events
void draw() {
clear();
//text("Left: "+distance_L,30,50);text("Right: "+distance_R,230,50);
double ratio=0.625;
println(ratio);
stroke(255);
text("Left: "+distance_L+"cm", 10,50);
text("Right: "+distance_R+"cm", 400,50);
//draw left object
if(distance_L!=0){
  float x_left=width/2-distance_L*(float)ratio-6;float y=height/2-50;
rect(x_left,0,2,500);
println("rect position: "+ x_left +", "+y);
}
//draw right object
if(distance_R!=0){
float x_right=width/2+distance_R*(float)ratio+4;float y=height/2-50;
rect(x_right,0,2,500);
println("rect position: "+ x_right +", "+y);
}
//draw user
ellipse(width/2-3,height/2-3,10,10);
//distance_L=0;
//left="";right="";
}

/**
 * To perform any action on datagram reception, you need to implement this 
 * handler in your code. This method will be automatically called by the UDP 
 * object each time he receive a nonnull message.
 * By default, this method have just one argument (the received message as 
 * byte[] array), but in addition, two arguments (representing in order the 
 * sender IP address and his port) can be set like below.
 */
// void receive( byte[] data ) {       // <-- default handler
void receive( byte[] data ) {  // <-- extended handler
 for(int i=0; i < data.length; i++){
//res_message+=i+":"+data[i]+",";
if(data[i]!=13&&data[i]!=10){
if(data[i]==76){isLeft=true;isRight=false;}
else if(data[i]==82){isLeft=false;isRight=true;}
else if(data[i]>=48&&data[i]<=57){
if(isLeft){left+=data[i]-48;}else if(isRight){right+=data[i]-48;}
}
}//end ignoring /r/n
else if(data[i]==10){//convert String into int
distance_L=int(left);
distance_R=int(right);
left="";right="";
}
 }
}
