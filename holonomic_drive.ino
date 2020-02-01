#include <Adafruit_MotorShield.h>
//#include <math.h>

Adafruit_MotorShield AMFS = Adafruit_MotorShield(); //intialize motorshield object
Adafruit_DCMotor *motor_one = AMFS.getMotor(1); //intialize motors
Adafruit_DCMotor *motor_two = AMFS.getMotor(2);
Adafruit_DCMotor *motor_three = AMFS.getMotor(3);

int motor_one_speed = 0; //motorspeed variable; 0 no movement, 255 max movment
int motor_two_speed = 0;
int motor_three_speed = 0;

int vector_direction;
double vector_magnitude;

//RC variables
int ch1_value =  0;  //y channel
int ch2_value =  0; //x channel
int ch3_value =  0;  //rotation

int ch1_pin = 5; 
int ch2_pin = 6; 
int ch3_pin = 7; 

void setup() 
{
AMFS.begin(); 
pinMode(ch1_pin, INPUT); //set arduino pin as input
pinMode(ch2_pin, INPUT);
pinMode(ch3_pin, INPUT);

Serial.begin(9600); // Pour a bowl of Serial
}

void loop() 
{
  int x = 1200;
  int y = 1700;
  vector_direction = vector_dir(y,x);
  vector_magnitude = magnitude(y, x);
  Serial.print("direction in rads is \n");
  Serial.print(vector_direction);
  Serial.print("magnitude is \n");
  Serial.print(vector_magnitude); 
}

int magnitude (int y, int x)
{
 int result;
 result = sqrt(pow(y, 2) + pow(x, 2));
 return result;
}

double vector_dir (double y, double x)
{
  double result;
  result = atan2(y, x);
  return result;
}
