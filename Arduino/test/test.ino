/****************************************
Example Sound Level Sketch for the 
Adafruit Microphone Amplifier
****************************************/
 
const int sampleWindow = 500; // Sample window width in mS (50 mS = 20Hz)
int sample;
//int sample2;
 
void setup() 
{
   Serial.begin(9600);
}
 
 
void loop() 
{
   long startMillis= millis();  // Start of sample window
   int peakToPeak = 0;   // peak-to-peak level
  // int peakToPeak2 = 0;
 
   int signalMax = 0;
   int signalMin = 1024;
 //  int signalMax2 = 0;
  // int signalMin2 = 1024;
 
   // collect data for 50 mS
   while (millis() - startMillis < sampleWindow)
   {
      sample = analogRead(0);
    //  sample2 = analogRead(1);
      
         if (sample > signalMax)
         {
            signalMax = sample;  // save just the max levels
         }
         else if (sample < signalMin)
         {
            signalMin = sample;  // save just the min levels
         }
   
/*
         if (sample2 > signalMax2)
         {
            signalMax2 = sample2;  // save just the max levels
         }
         else if (sample2 < signalMin2)
         {
            signalMin2 = sample2;  // save just the min levels
         }
      */
   }
   peakToPeak = signalMax - signalMin;  // max - min = peak-peak amplitude
   double volts = (peakToPeak * 3.0) / 1024;  // convert to volts

//   peakToPeak2 = signalMax2 - signalMin2;  // max - min = peak-peak amplitude
 //  double volts2 = (peakToPeak2 * 3.0) / 1024;  // convert to volts
   Serial.println(peakToPeak);
}
