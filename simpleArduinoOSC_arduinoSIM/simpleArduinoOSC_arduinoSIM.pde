/**
 * (./) udp.pde - how to use UDP library as unicast connection
 * (cc) 2006, Cousot stephane for The Atelier Hypermedia
 * (->) http://hypermedia.loeil.org/processing/
 *
 Simulation of arduino sending ultrasonic sensor data to server (processing Android)
 */

// import UDP library
import hypermedia.net.*;


UDP udp;  // define the UDP object

/**
 * init
 */
void setup() {
frameRate(0.25);
smooth();
  // create a new datagram connection on port 12000
  // and wait for incomming message
  udp = new UDP( this, 12100 );
  //udp.log( true );     // <-- printout the connection activity
  udp.listen( true );
}

//process events
void draw() {
 byte[] message  = {76,49,50,48,82,50,50,48,13,10};  // the message to send
    String ip       = "localhost";  // the remote IP address
    int port        = 12000;    // the destination port
    // send the message
  udp.send( message, ip, port );
    delay(1000);
    byte[] message2  = {76,50,48,82,50,13,10};  
    udp.send( message2, ip, port );
    delay(1000);
    byte[] message3  = {76,53,82,50,51,49,13,10};  
    udp.send( message3, ip, port );
    delay(1000);
    byte[] message4  = {76,48,82,51,13,10};  
    udp.send( message4, ip, port );
}
