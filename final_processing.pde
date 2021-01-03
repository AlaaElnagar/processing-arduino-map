 
 
 import processing.serial.*;  

Serial port;                             
int val,x,flag2=1,flag=0,flag3=1,y=680,i=90,v=0,F=0,Z=0;
int f=1200/2,z=700/2;  //f=x axis //z y axis
//.....................................//void setup().....................

void setup(){
port = new Serial(this, "com3", 9600); //<>//
size(1200,700);
rectMode (CENTER);
strokeWeight(20);
fill(142,170,141);
rect (1200/2,700/2,1200,700);
fill(4,29,144);
ellipse(f,z,10,10);
strokeWeight(5);
frameRate(50);
port.bufferUntil('\n');
}
//.........................................//void drow..................

void draw(){

  if ( port.available()>0) {         // If data is available,
   val = port.read();                 // read it and store it in val
x=val;
point(f,z);

if      (x=='H') {flag=1;             }//........continue
else if (x=='T') {ellipse(f,z,20,20); }//drow for metals 
else if (x=='J') {flag=0;             }//stop
else if (x=='R') { i-=(90);flag=0;      }//increment i(rotate)90
else if (x=='L') {i+=(90); flag=0;      }//...//increment i(rotate)90
else if (x=='Y') {i+=(180);flag=0;     }//...//increment i(rotate)180
}
if(i==360||i==-360){i=0;}
if((i==0||i==-360||i==360 )&&flag==1  ){ ++f; point(f,z);}
if((i==90||i==-270)&&flag==1 ){ --z; point(f,z);}
if((i==180||i==-180)&&flag==1){--f ; point(f,z);}
if((i==270||i==-90)&&flag==1){ ++z; point(f,z);}


}
/*if ((F<30||Z>1150||F<30||Z>660)&&flag2==1){Stop();port.write('S');port.write('B'); stroke(f,z,1);flag2=0;flag3=1;v=0;}//size(1200,700);stroke(178,54,1);i+=90;
//if ((f>100||f<900||z>100||z<400)&&flag3==1){flag2=1;flag3=0;}//activate the barrier detection
////println(mouseX,":",mouseY);//grid points  check 
v++;
if (v>10)   {flag2=1;v=0;}*/



//.............................................................................//CODE SUB ROUTINES.......................................................

//directions drowing subroutine

void Forward(){flag=1;z--;}
void Right  (){flag=1;f++;}
void Left   (){flag=1;f--;}
void Down   (){flag=1;z++;}
void Stop   (){flag=0;    }


//target.................................................................................
void checkTarget (){
 if (val=='T'){
ellipse(f,z,20,20);}
}


//recive..................................................................................


//STABILITY...................................................................................................
void  serialEvent(Serial port){//...stability
  val=int (port.readStringUntil('\n'));
}
//key board start and stop...............//computer controll.........................................................................
void keyPressed() {
  if      (key == 'Q' ) { port.write('F'); } //FORWARD
  else if (key == 'W' ) { port.write('S'); } //STOP
}
//STAY IN THE BOX..................................................................................................
void mov_in_only(){ 
if ((f<30||f>1150||z<30||z>660)&&flag2==1){Stop();port.write('S');port.write('B'); stroke(178,54,1);flag2=0;flag3=1;}//size(1200,700);stroke(178,54,1);i+=90;
if ((f>100||f<900||z>100||z<400)&&flag3==1){flag2=1;flag3=0;}//activate the barrier detection
}