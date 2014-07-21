
#include <Bridge.h>
#include <YunServer.h>
#include <YunClient.h>
#include <ZumoMotors.h>
#include <ZumoBuzzer.h>


ZumoBuzzer buzzer;
YunServer server;
ZumoMotors motors;
int LeftSpeed=0;
int RightSpeed=0;
int vitesse=0;
int num_bouton=0;
int dif_vitesse=0;

void setup() {
  Serial.begin(9600);      
    // Bridge startup
  pinMode(13,OUTPUT);
  digitalWrite(13, LOW);
  Bridge.begin();                                           
    // Listen for incoming connection only from localhost
  // (no one from the external network could connect)
  server.listenOnLocalhost();
  server.begin();
}

void loop() {              
  // Get clients coming from server  

  YunClient client = server.accept();       
// There is a new client?  
  if (client) {    
 // Process request    
     digitalWrite(13, HIGH);
     delay(100);
     digitalWrite(13, LOW);
    
    zumoCommand(client);      
  // Close connection and free resources.    
    client.stop();
  }
  delay(50);      

}

void zumoCommand(YunClient client) {
   // read the command
  //String command = client.readStringUntil('/');    
      
  
    vitesse = client.parseInt();     
    
  if (client.read() == '/') {
    dif_vitesse = client.parseInt();
    }
  if (client.read() == '/') {
    num_bouton = client.parseInt();
    }

   
   if (num_bouton==1) {
     LeftSpeed=vitesse*dif_vitesse/100;
     RightSpeed=vitesse;}
   else if (num_bouton==2) {
     LeftSpeed=vitesse;
     RightSpeed=vitesse;}
   else if (num_bouton==3) {
     LeftSpeed=vitesse;
     RightSpeed=vitesse*dif_vitesse/100;}
   else if (num_bouton==4) {
     LeftSpeed=-vitesse;
     RightSpeed=vitesse;}
   else if (num_bouton==5) {
     LeftSpeed=0;
     RightSpeed=0;}
   else if (num_bouton==6) {
     LeftSpeed=vitesse;
     RightSpeed=-vitesse;}
   else if (num_bouton==7) {
     LeftSpeed=-vitesse*dif_vitesse/100;
     RightSpeed=-vitesse;}
   else if (num_bouton==8) {
     LeftSpeed=-vitesse;
     RightSpeed=-vitesse;}
   else if (num_bouton==9) {
     LeftSpeed=-vitesse;
     RightSpeed=-vitesse*dif_vitesse/100;}
     
   else if (num_bouton==10) {
     buzzer.playNote(NOTE_A(3),1000,15);
     }
     
    motors.setLeftSpeed(LeftSpeed);
    motors.setRightSpeed(RightSpeed);

                 
    client.print(F("LeftSpeed="));
    client.print(LeftSpeed);
    client.print(F(" et RightSpeed="));
    client.print(RightSpeed);
}


