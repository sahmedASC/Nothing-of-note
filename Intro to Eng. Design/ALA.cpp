# include<iostream>

using namespace std;

signed int MOTOR_NEUT = 2765;       // Neutral             
signed int MOTOR_MAX = 3502;        // Full Forward        
signed int MOTOR_MIN = 2027;        // Full Reverse        
signed int MOTOR_PW;                // Current PW

signed int SERVO_CENTER = 2765;     // Centered           
signed int SERVO_RIGHT = 3871;      // All the way right    
signed int SERVO_LEFT = 1659;       // All the way left    
signed int SERVO_PW;                // Current PW

int ksteer = 1;
int kdrive = 1;

/*
//assumption is made that devices are connected and 
//wired properly 
//this is a pseudocode but I will mostly the real functions and their real input
//add this to setup
void setup() {
    Serial.begin(38400); 
}

int getrssi(string master) { 
    int rssi_received = 0; 
    vector<int> rssi_val;
    while(rssi_received <15){
        int check1 = Serial.write("AT+INQM=1,9,48"); //use the check 1 variable as error detection. 
                                                    //not needed right now
        int check2 = Serial.write("AT+INQ");
        char[50] buffer;
        int check3 = Serial.readBytesUntil('\n', buffer, 50);
        //at this point buffer should be something like : "+INQ:1234:56:0,1F1F,FFC0"
        string test (buffer); //cast the array as a string
        string sub (test, 5, 9); //should be equal to "1234:56:0"
        if(sub == master){
            string sub2 (test, 20, 4); //should be equal to "FFC0"
            int rssi = sub2.convertHexInt() //not a real function have to research or do manually
            rssi_val.pushback(rssi); 
            rssi_received++;
        } 
        else{
            continue;
        }
    }
    int sum =0; 
    for (auto& n : rssi_val) {
        sum += n;
    }     
    int avg = sum/(rssi_val.size());
    int mode = mode(rssi_val); //not a real function. have to research or do manually.
    if(abs(mode-avg)/float(mode) < 0.1) {
        return mode; 
    }
    else {
        return -1;
    }
}
*/

float read_ultrasonic_sensor_front() { 
    // read input from front sensor
    return rand() % 10;
}

float read_ultrasonic_sensor_back() {
    // read input from back sensor
    return rand() % 10 + 42;
}

int read_bluetooth_left() {
    // read input from left bluetooth
    int sum = 0;
    for (int i=0; i < 10; i++) {
        sum += (rand() % 10 - 62);
    }
    return sum / 10;
} 

int read_bluetooth_right() {
    // read input from right bluetooth
    int sum = 0;
    for (int i=0; i < 10; i++) {
        sum += (rand() % 10 - 62);
    }
    return sum / 10;
}

void set_motorPW(int range_back, int range_front){
    // set the speed
    MOTOR_PW = MOTOR_NEUT + kdrive * (range_back - 45);
    if (range_front < 3) {
        MOTOR_PW = MOTOR_NEUT;
    } 
    if (MOTOR_PW > MOTOR_MAX) {
        MOTOR_PW = MOTOR_MAX;
    }
    else if(MOTOR_PW < MOTOR_MIN) {
        MOTOR_PW = MOTOR_MIN;
    }
} 

void set_servoPW(int RSSI0, int RSSI1){
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
} 

void device_status() {
    if (MOTOR_PW > MOTOR_NEUT) {
        cout << "Going forward" << endl;
    }
    else if (MOTOR_PW < MOTOR_NEUT) {
        cout << "Going backward" << endl;
    }
    else {
        cout << "Reamain stable" << endl;
    }
    if (SERVO_PW > SERVO_CENTER) {
        cout << "Turning right" << endl;
    }
    else if (SERVO_PW < SERVO_CENTER) {
        cout << "Turning left" << endl;
    }
    else {
        cout << "Remain straight" << endl;
    }
}

int main() {
    for (int i=0; i < 5; i++) {
        cout << i << ":" << endl;
        int RSSI0 = read_bluetooth_left();
        int RSSI1 = read_bluetooth_right(); 
        int range_back = read_ultrasonic_sensor_back();
        int range_front = read_ultrasonic_sensor_front();
        cout << "Bluetooth Left: " << RSSI0 << endl; 
        cout << "Bluetooth Right: " << RSSI1 << endl; 
        cout << "Ultrasonic Back: " << range_back << endl; 
        cout << "Ultrasonic Front: " << range_front << endl; 
        set_motorPW(range_back, range_front);
        set_servoPW(RSSI0, RSSI1);
        device_status();
        cout << endl;
    }
}