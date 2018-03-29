
/*  PulseSensor™ Starter Project and Signal Tester
 *  The Best Way to Get Started  With, or See the Raw Signal of, your PulseSensor™ & Arduino.
 *
 *  Here is a link to the tutorial
 *  https://pulsesensor.com/pages/code-and-guide
 *
 *  WATCH ME (Tutorial Video):
 *  https://www.youtube.com/watch?v=82T_zBZQkOE
 *
 *
-------------------------------------------------------------
1) This shows a live human Heartbeat Pulse.
2) Live visualization in Arduino's Cool "Serial Plotter".
3) Blink an LED on each Heartbeat.
4) This is the direct Pulse Sensor's Signal.
5) A great first-step in troubleshooting your circuit and connections.
6) "Human-readable" code that is newbie friendly."

*/

IntervalTimer myTimer;

//  Variables
int PulseSensorPurplePin = 0;        // Pulse Sensor PURPLE WIRE connected to ANALOG PIN 0
int LED13 = 13;   //  The on-board Arduion LED


int Signal;                // holds the incoming raw data. Signal value can range from 0-1024
int Threshold = 550; // Determine which Signal to "count as a beat", and which to ingore.
//int numBeats = 1;
int numBeats[10] = {1,1,1,1,1,1,1,1,1,1};
int beats = 0;
int sec = 1;
double BPM;
bool check1 = true;



void countBPM(){
//  BPM = (numBeats / sec) * 60;
//  if(sec > 10){
//    sec = 1;
//    numBeats = 1;
//  }
//  sec++;
  for (int i = 0; i < 10; i++) {                
    numBeats[i+1] = numBeats[i];
  }
  numBeats[0] = beats;
  beats = 0;

  int sum = 0 ;  
  for (int ii = 0 ; ii < 10 ; ii++){
    sum += numBeats[ii] ;
  }

  BPM = (sum / 10) * 60;
}


// The SetUp Function:
void setup() {
  pinMode(LED13,OUTPUT);         // pin that will blink to your heartbeat!
   Serial.begin(9600); 
   myTimer.begin(countBPM, 1000000);

}

// The Main Loop Function
void loop() {
  
  
  Signal = analogRead(PulseSensorPurplePin);  // Read the PulseSensor's value.
                                              // Assign this value to the "Signal" variable.

   Serial.println(Signal);  
   //Serial.println(beats); // Send the Signal value to Serial Plotter.

   
   if(Signal > Threshold){                          // If the signal is above "550", then "turn-on" Arduino's on-Board LED.
     digitalWrite(LED13,HIGH);
     if(check1){
      beats++;
      check1 = false;
     }
   } else {
     digitalWrite(LED13,LOW);
     check1 = true; //  Else, the sigal must be below "550", so "turn-off" this LED.
   }


delay(30);


}
