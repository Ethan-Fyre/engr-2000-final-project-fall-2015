#include <Servo.h>
#include <math.h>
Servo leftwheel;
Servo rightwheel;
Servo pen;
const int RL = 277;
const int L = 195;
const float V = .248;
float xbot = 0;
float ybot = 0;
float thetabot = PI / 2;
int lpin = 12;
int rpin = 11;
int ppin = 10;
void turnto(int x, int y) {
  float angle = atan2(y - ybot, x - xbot);
  float deltang = thetabot - angle;
  float deltaT = (fabs(deltang) * L) / (2 * V);
  if (deltang < 0) {
    leftwheel.writeMicroseconds(1300); //turning left
    rightwheel.writeMicroseconds(1300);
    Serial.println("left");
    delay(deltaT + 45);
    leftwheel.writeMicroseconds(1500);
    rightwheel.writeMicroseconds(1500);
  }
  else if (deltang > 0) {
    leftwheel.writeMicroseconds(1700);  //turning right
    rightwheel.writeMicroseconds(1700);
    Serial.println("right");
    delay(deltaT+55);
    leftwheel.writeMicroseconds(1500);
    rightwheel.writeMicroseconds(1500);}
  thetabot = thetabot - deltang;}
void driveto(int x, int y) {
  float distance = sqrt((x - xbot) * (x - xbot) + (y - ybot) * (y - ybot));
  float deltaT = distance / V;
  leftwheel.writeMicroseconds(1300);
  rightwheel.writeMicroseconds(1700);
  delay(deltaT);
  leftwheel.writeMicroseconds(1500);
  rightwheel.writeMicroseconds(1500);
  xbot = xbot + (distance * (cos(thetabot)));
  ybot = ybot + (distance * (sin(thetabot)));

}

void droppen() {
  pen.write(1790);
}
void liftpen() {
  pen.write(2000);
}
void center() {
  //move forwards center to pen.
  float t = RL / V;
  leftwheel.writeMicroseconds(1300);
  rightwheel.writeMicroseconds(1700);
  delay(t);
  rightwheel.writeMicroseconds(1500);
  leftwheel.writeMicroseconds(1500);
  xbot = xbot + (RL * (cos(thetabot))) ;
  ybot = ybot + (RL * (sin(thetabot)));
}
void reset() {
  //lift pent, then move backwards center to pen.
  liftpen();
  float t = RL / V;
  leftwheel.writeMicroseconds(1700);
  rightwheel.writeMicroseconds(1300);
  delay(t);
  rightwheel.writeMicroseconds(1500);
  leftwheel.writeMicroseconds(1500);
  xbot = xbot - (RL * (cos(thetabot))) ;
  ybot = ybot - (RL * (sin(thetabot)));
}
void debug(int ste) {
  Serial.println(ste);
  Serial.print(xbot);
  Serial.println(" xbot");
  Serial.print(ybot);
  Serial.println(" ybot");
  Serial.print(thetabot * 180 / PI);
  Serial.println(" thetabot");
  Serial.println("");
}
void line(int x, int y, int x2, int y2) {
  turnto(x, y);
  delay(500);
  debug(1);
  driveto(x, y);
  delay(500);
  debug(2);
  turnto(x2, y2);
  delay(500);
  debug(3);
  center();
  droppen();
  delay(500);
  debug(4);
  driveto(x2, y2);
  delay(500);
  debug(5);
  center();
  delay(500);
  debug(6);
  reset();
  delay(500);
  debug(7);
  

}
void parktest() {
  line(400, 0, 0, -400);
  line(-200, -200, 200, 200);
  line(0, 400, -400, 0);
  line(-600, 200, -200, 600);
  line(-400, 400, 600, -600);
}
void turntest() {
  turnto(10, 10);
  delay(500);
  debug(1);
  turnto(0, 10);
  delay(500);
  debug(2);
  turnto(10, 0); delay(500);
  debug(3);
  turnto(0, 10);
  delay(500);
  debug(4);
  turnto(10, -10);
  delay(500);
  debug(5);
  turnto(0, 10);
  delay(500);
  debug(6);
  turnto(0, -10);
  delay(500);
  debug(7);
}
void parkreal() {
  line(200, -200, 200, -400);
  line(50, -250, 50, -50);
  line(-100, 100, -100, -100);
  line(-300, 100, 200, -400);
  line(400, 0, 600, 0);
  line(450, 150, 250, 150);
  line(100, 300, 300, 300);
  line(100, 500, 600, 0);
}
void calibrateV() {
  droppen();
  delay(500);
  leftwheel.writeMicroseconds(1300);
  rightwheel.writeMicroseconds(1700);
  delay(1000);
  rightwheel.writeMicroseconds(1500);
  leftwheel.writeMicroseconds(1500);
  liftpen();
}
void setup() {
  leftwheel.attach(lpin);
  rightwheel.attach(rpin);
  pen.attach(ppin);
  pen.write(2000);
  Serial.begin(9600);
  delay(2000);
  //line(-200,-200,200,200);
  parkreal();
  //calibrateV();
  //turntest();

}
void loop() {



}



