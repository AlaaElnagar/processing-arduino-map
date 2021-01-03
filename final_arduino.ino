int DIR1=5,DIR2=6;
int pwm1=9,pwm2=10,pwm3=4;//pwm1,2 back motor&pwm3 front
int trigPin=3,echoPin1=12,echoPin2=11,echoPin3=13;
int metal_detector=A0;//eco1 FORWARD,eco2 R,Eco3 L
long duration;int distance;
int val,x=0,a=0,flag2=1,M=0,i=1;
int F,R,L;


void setup(){
pinMode (DIR1,OUTPUT);pinMode (DIR2,OUTPUT);
pinMode (pwm1,OUTPUT);pinMode (pwm2,OUTPUT);pinMode (pwm3,OUTPUT);
pinMode(trigPin,OUTPUT); 
pinMode(echoPin1, INPUT);pinMode(echoPin2, INPUT);pinMode(echoPin3, INPUT);
pinMode (metal_detector,INPUT);
Serial.begin(9600);
 while (!Serial) {} // wait for serial port to connect. Needed for native USB port only
   
}


void loop(){
if (Serial.available()>0){
  val=Serial.read();
  if      (val=='F'){Mov_Forward();x=1;    }//robot move only...flag already activated in processing
  else if (val=='S'){ Stop(); x=0;flag2=1; i=1;}
//  else if (val=='B'&&flag2==1){ Turn_Back();x=1;flag2=0;a=1;i=0;}//calling from processing that this is the border of page
}

//detection and ultrasonic recalling
if(x==1){
 Ultrasonic_Alg();
 Detect();    }
   
}


//...........................................................................MOTOR DIRECTION

//............................................................................Mov_Forward()
void Mov_Forward(){
digitalWrite(DIR1,HIGH);analogWrite(pwm1,50);
digitalWrite(DIR2,LOW);analogWrite(pwm2,50);
analogWrite(pwm3,150); Serial.write('H');
}
//.............................................................................Turn_Right().................................
void Turn_Right(){
rover_stop();
digitalWrite(DIR1,LOW);analogWrite(pwm1,200);
digitalWrite(DIR2,LOW);analogWrite(pwm2,200);
analogWrite(pwm3,250);delay(500);
Serial.write('R');

}

//.............................................................................Turn_Left()..................................

void Turn_Left(){
rover_stop();
digitalWrite(DIR1,HIGH);analogWrite(pwm1,200);
digitalWrite(DIR2,HIGH);analogWrite(pwm2,200);
analogWrite(pwm3,250);Serial.write('L');
delay(500);
}

//.............................................................................Turn_Back()..............................

void Turn_Back(){
rover_stop();
digitalWrite(DIR1,LOW);analogWrite(pwm1,200);
digitalWrite(DIR2,LOW);analogWrite(pwm2,200);
analogWrite(pwm3,250);
delay(2000);
Serial.write('Y');
}
//.............................................................................Mov_Reverese()...............................
void Mov_Reverese(){rover_stop();
digitalWrite(DIR1,LOW);analogWrite(pwm1,70);
digitalWrite(DIR2,HIGH);analogWrite(pwm2,70);
analogWrite(pwm3,100);
Serial.write('Y');delay(100);
}

//..............................................................................void Stop()................................

void Stop(){
Serial.write('J');
analogWrite(pwm1,0);analogWrite(pwm2,0);analogWrite(pwm3,0);
delay(500);                       //inertia delay
}
void rover_stop(){
analogWrite(pwm1,0);analogWrite(pwm2,0);analogWrite(pwm3,0);delay(500);  
}

//..............................................................................metal detection................................

void Detect (){
M= analogRead (metal_detector);delay(150);
  if(M>500){
Serial.write ('T'); }
}

//............................................................................ULTRASONIC DISTANCE READING...........................

int ultrasonic_Read(int echoPin){
digitalWrite(trigPin, LOW);// Clears the trigPin
delayMicroseconds(2);
digitalWrite (trigPin,HIGH);   
delayMicroseconds(10);
digitalWrite(trigPin,LOW);
duration=pulseIn(echoPin,HIGH);
distance=duration*0.034/2;
return (distance);delay(150);
}

//................................................................................ULTRASONIC ALGORITHM............................

void Ultrasonic_Alg(){       
F=ultrasonic_Read(echoPin1);
if (F<=35){ Stop();i==1;
R=ultrasonic_Read(echoPin2);
L=ultrasonic_Read(echoPin3);

if    (R>=40){Turn_Right();rover_stop();i=1;}

else if(L>=40){Turn_Left(); rover_stop(); i=1;}
else if (R>40&&L>40){Mov_Reverese();i=1; }
i=1;
}
  

 F=ultrasonic_Read(echoPin1);
 if(F>35&&i==1){ Mov_Forward(); i=0;}

}





