/* 
 *  Code for three wheel holonomic drive rc soccerbot. The bot has three omni wheels space equally apart.
 *  Orlando Moya
 */
#include <Adafruit_MotorShield.h>
//#include <math.h>

Adafruit_MotorShield AMFS = Adafruit_MotorShield(); //intialize motorshield object
Adafruit_DCMotor *motor_one = AMFS.getMotor(1); //intialize motors
Adafruit_DCMotor *motor_two = AMFS.getMotor(2);
Adafruit_DCMotor *motor_three = AMFS.getMotor(3);

static float pi = 3.141592;
float control_angle = 0; //polar angle of vector
float control_magnitude = 0; //polar magnitude of vector

int motor_one_speed = 0; //motorspeed variable; 0 no movement, 255 max movment
int motor_two_speed = 0;
int motor_three_speed = 0;
//motorangle in degrees
int motor_one_angle = 0;
int motor_two_angle = 0;
int motor_three_angle = 0;

//motor set angles, determine by placement of wheels on soccerbot
static int angle_one = 150;
static int angle_two = 30;
static int angle_three = 270;

//RC variables
int x_pin =  2;  //Channel 1 on reciever
int y_pin =  3; //Channel 2

int x_input = 0; //value from x_pin 
int y_input = 0; //value from y_pin 

void setup() 
{
AMFS.begin(); 
pinMode(x_pin, INPUT); //set arduino pin as input
pinMode(y_pin, INPUT);

Serial.begin(9600); // Pour a bowl of Serial
}

void loop() 
{
  y_input = (pulseIn(y_pin, HIGH, 35000) - 1500);
  x_input = (pulseIn(x_pin, HIGH, 35000) - 1500);

  if (x_input != 0 ) // check if x input is 0, if 0 set the angle to 90
  {
    control_angle = vector_dir(y_input,x_input);
  }
  else 
{
  control_angle = 90;
}

 control_magnitude = magnitude(y_input, x_input); //vector manitutde, determines speed

//MOTOR ONE
 motor_one_angle = motor_angle(angle_one, control_angle); 
 motor_one_speed = motor_speed(control_magnitude, motor_one_angle);

 if (motor_one_speed < 0){
  motor_one->run(BACKWARD);
}
else if (motor_one_speed == 0){
  motor_one->run(RELEASE);
}
else{
  motor_one->run(FORWARD);
}
motor_one->setSpeed(abs(motor_one_speed));

//MOTOR two
 motor_two_angle = motor_angle(angle_two, control_angle); 
 motor_two_speed = motor_speed(control_magnitude, motor_two_angle);

 if (motor_two_speed < 0){
  motor_two->run(BACKWARD);
}
else if (motor_two_speed == 0){
  motor_two->run(RELEASE);
}
else{
  motor_two->run(FORWARD);
}
motor_two->setSpeed(abs(motor_two_speed));

//MOTOR THREE
 motor_three_angle = motor_angle(angle_three, control_angle); 
 motor_three_speed = motor_speed(control_magnitude, motor_three_angle);

 if (motor_three_speed < 0){
  motor_three->run(BACKWARD);
}
else if (motor_three_speed == 0){
  motor_three->run(RELEASE);
}
else{
  motor_three->run(FORWARD);
}
motor_three->setSpeed(abs(motor_three_speed));
}

int magnitude (int y, int x)
{
 int result;
 result = (sqrt(pow(y, 2) + pow(x, 2))/2.7);
 return result;
}

double vector_dir (double y, double x)
{
  double result;
  result = atan2(y, x) * 57;
  return result;
}

double motor_angle(double set_angle, double vector_angle) //set angle is the angle of a wheel axis from a top down view
{
  double result;
  result = set_angle - vector_angle;
  return result;
}

int motor_speed (int vector_magnitude, int motor_degree)
{
  int result; 
  result = vector_magnitude*sin(motor_degree * (pi/180.0));
  return result;
  
}
