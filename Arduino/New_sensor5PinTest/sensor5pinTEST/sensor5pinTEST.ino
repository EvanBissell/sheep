#include <NewPing.h>

#define TRIGGER_PIN_CENTER  9  // Arduino pin tied to trigger pin on ping sensor.
#define ECHO_PIN_CENTER   10  // Arduino pin tied to echo pin on ping sensor.

#define MAX_DISTANCE 20




NewPing sonarC(TRIGGER_PIN_CENTER, ECHO_PIN_CENTER, MAX_DISTANCE);

unsigned int pingSpeed = 50; // How frequently are we going to send out a ping (in milliseconds). 50ms would be 20 times a second.
unsigned long pingTimer;     // Holds the next ping time.

void setup() {
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
  pingTimer = millis(); // Start now.
}

void loop() {
  // Notice how there's no delays in this sketch to allow you to do other processing in-line while doing distance pings.
  if (millis() >= pingTimer) {   // pingSpeed milliseconds since last ping, do another ping.
    pingTimer += pingSpeed;      // Set the next ping time.
 // Send out the ping, calls "echoCheck" function every 24uS where you can check the ping status.
    sonarC.ping_timer(echoCheck);

  }
  // Do other stuff here, really. Think of it as multi-tasking.
}

void echoCheck() { // Timer2 interrupt calls this function every 24uS where you can check the ping status.
  // Don't do anything here!

    if (sonarC.check_timer()) { // This is how you check to see if the ping was received.
    // Here's where you can add code.
    Serial.print("Center Ping: ");
    Serial.print(sonarC.ping_result / US_ROUNDTRIP_CM); // Ping returned, uS result in ping_result, convert to cm with US_ROUNDTRIP_CM.
    Serial.println("cm");

  // Don't do anything here!
}
}

