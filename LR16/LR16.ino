#include <Servo.h>
 
#define POT_MAX_ANGLE 270.0 // макс. угол поворота потенциометра
Servo myServo;
 
void setup()
{
  myServo.attach(13);
}
 
void loop()
{
  int val = analogRead(A0);
  int angle = int(val / 1023.0 * POT_MAX_ANGLE);
  angle = constrain(angle, 0, 180);
  myServo.write(angle);
}

