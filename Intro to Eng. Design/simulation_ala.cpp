#include<Servo.h>
//pins set for the sensors as global. Will not change
const int pingPin = 7;
const int pingPin2 = 6;

Servo myservo;
int value;
double angle;

const int MOTOR_NEUT = 2765;       // Neutral             
const int MOTOR_MAX = 3502;        // Full Forward        
const int MOTOR_MIN = 2027;        // Full Reverse        
int MOTOR_PW;                // Current PW

const int SERVO_CENTER = 2765;     // Centered           
const int SERVO_RIGHT = 3871;      // All the way right    
const int SERVO_LEFT = 1659;       // All the way left    
int SERVO_PW;                // Current PW

const int ksteer = 25;
const int kdrive = 15;



void setup() {
  // initialize serial communication:
  Serial.begin(9600);
  myservo.attach(8);
}



void loop() {  
  String r0input = "";
  String r1input = "";
  
  // read input from left bluetooth
  /*long sum = 0;
  for (int i=0; i < 15; i++) {
      sum += (random(30) - 80);
  }
  long RSSI0 = sum/15;*/
  
  while (Serial.available() == 0) {} 
  r0input = Serial.readString();
  r0input = r0input.substring(20);
  long RSSI0 = strtol(r0input.c_str(),0,16) * -1;
  
  // read input from right bluetooth
  /*sum = 0;
  for (int i=0; i < 15; i++) {
      sum += (random(30) - 80);
  }
  long RSSI1 = sum/15;*/
  
  while (Serial.available() == 0) {}
  r1input = Serial.readString();
  r1input = r1input.substring(20);
  long RSSI1 = strtol(r1input.c_str(),0,16)* -1;
  
  // establish variables for duration of the ping, and the distance result
  // in inches and centimeters:
  long duration;

  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);

  // The same pin is used to read the signal from the PING))): a HIGH pulse
  // whose duration is the time (in microseconds) from the sending of the ping
  // to the reception of its echo off of an object.
  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);

  // convert the time into a distance
  long range_front = microsecondsToInches(duration);
  
  
  long duration2;

  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(pingPin2, OUTPUT);
  digitalWrite(pingPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin2, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin2, LOW);

  // The same pin is used to read the signal from the PING))): a HIGH pulse
  // whose duration is the time (in microseconds) from the sending of the ping
  // to the reception of its echo off of an object.
  pinMode(pingPin2, INPUT);
  duration2 = pulseIn(pingPin2, HIGH);

  // convert the time into a distance
  long range_back = microsecondsToInches(duration2);

  Serial.print("Bluetooth Left: ");
  Serial.print(RSSI0);
  Serial.println(" dB");
  Serial.print("Bluetooth Right: ");
  Serial.print(RSSI1); 
  Serial.println(" dB");
  Serial.print("Ultrasonic Back: ");
  Serial.print(range_back); 
  Serial.println(" inches");
  Serial.print("Ultrasonic Front: ");
  Serial.print(range_front); 
  Serial.println(" inches");
  
  // set the speed
  MOTOR_PW = MOTOR_NEUT + kdrive * (range_front - 36);
  if (MOTOR_PW > MOTOR_MAX) {
      MOTOR_PW = MOTOR_MAX;
  }
  else if(MOTOR_PW < MOTOR_MIN) {
      MOTOR_PW = MOTOR_MIN;
  }
  if (MOTOR_PW < MOTOR_NEUT) {
      MOTOR_PW = MOTOR_NEUT;
  }
  
  // set the direction
  RSSI0 = abs(RSSI0);
  RSSI1 = abs(RSSI1);
  float direction_error = RSSI0 - RSSI1;
  SERVO_PW = SERVO_CENTER + direction_error * ksteer;
  if (SERVO_PW > SERVO_RIGHT) {
      SERVO_PW = SERVO_RIGHT;
  } 
  else if(SERVO_PW < SERVO_LEFT) {
      SERVO_PW = SERVO_LEFT;
  }
  
  float speed = 0.00725373 * MOTOR_PW - 20.05657;
  
  //Servo.attach(8);
  
  // print the results
  if (MOTOR_PW > MOTOR_NEUT) {
      Serial.println("Going forward");
  }
  else if (MOTOR_PW < MOTOR_NEUT) {
      Serial.println("Going backward");
  }
  else {
      Serial.println("Remain stable");
  }
  if (SERVO_PW > SERVO_CENTER) {
      Serial.println("Turning right");
  }
  else if (SERVO_PW < SERVO_CENTER) {
      Serial.println("Turning left");
  }
  else {
      Serial.println("Remain straight");
  }
  //value = analogRead(A0);
  //angle = map(value, 0, 1023, 0, 180);
  angle = int(0.081374 * SERVO_PW - 135);
  myservo.write(angle);
  Serial.print("Tuning angle = ");
  Serial.print(angle);
  Serial.println(" degrees");
  
  //if (range_back < 30) {
  //    Serial.println("Warning! Too Close!");
  //}
  Serial.print("Speed = ");
  Serial.print(speed);
  Serial.println(" mph");
  Serial.println();

  delay(15);
}


//assumption is made that devices are connected and 
//wired properly 
//this is a pseudocode but I will mostly the real functions and their real input
//add this to setup
//void setup() {
//    Serial.begin(38400); 
//}

//int getrssi(string master) { 
//    int rssi_received = 0; 
//   vector<int> rssi_val;
//    while(rssi_received <15){
//        int check1 = Serial.write("AT+INQM=1,9,48"); //use the check 1 variable as error detection. 
                                                    //not needed right now
//        int check2 = Serial.write("AT+INQ");
//        char[50] buffer;
//        int check3 = Serial.readBytesUntil('\n', buffer, 50);
        //at this point buffer should be something like : "+INQ:1234:56:0,1F1F,FFC0"
//        string test (buffer); //cast the array as a string
//        string sub (test, 5, 9); //should be equal to "1234:56:0"
//        if(sub == master){
//            string sub2 (test, 20, 4); //should be equal to "FFC0"
//            int rssi = sub2.convertHexInt() //not a real function have to research or do manually
//            rssi_val.pushback(rssi); 
//            rssi_received++;
//        } 
//        else{
//            continue;
//        }
//    }
//    int sum =0; 
//    for (auto& n : rssi_val) {
//        sum += n;
//    }     
//    int avg = sum/(rssi_val.size());
//    int mode = mode(rssi_val); //not a real function. have to research or do manually.
//    if(abs(mode-avg)/float(mode) < 0.1) {
//        return mode; 
//    }
//    else {
//        return -1;
//    }
//}

long microsecondsToInches(long microseconds) {
  // According to Parallax's datasheet for the PING))), there are 73.746
  // microseconds per inch (i.e. sound travels at 1130 feet per second).
  // This gives the distance travelled by the ping, outbound and return,
  // so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the object we
  // take half of the distance travelled.
  return microseconds / 29 / 2;
}