
const int trigPin1 = 11; // the number of the trigger output pin ( sensor 1 )
const int echoPin1 = 10; // the number of the echo input pin ( sensor 1 )     
const int trigPin2 = 6;  // the number of the trigger output pin ( sensor 2 ) 
const int echoPin2 = 5;  // the number of the echo input pin ( sensor 2 ) 

/*variables used for distance calculation*/
long duration;                               
int distance1, distance2; 
float r;
unsigned long temp=0;
int temp1=0;
int l=0;


void find_distance (void);

/*Distance Calculation*/
void find_distance (void)                   
{ 
  /*Distance Calculation Left sensor*/
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);

  duration = pulseIn(echoPin1, HIGH, 5000);// here this pulsein function wont wait more then 5000us for the ultrasonic sound to came back. (due to this it wont measure more than 60cm)
                                          
  r = 3.4 * duration / 2;                  // calculation to get the measurement in cm using the time returned by the pulsein function.     
  distance1 = r / 100.00;

  /*Distance Calculation Right sensor*/
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);

  duration = pulseIn(echoPin2, HIGH, 5000);
  r = 3.4 * duration / 2;     
  distance2 = r / 100.00;
  delay(100);
}

void setup() 
{
  Serial.begin(9600);
  /*initilize tiger & echo pin as input or output pin*/
  pinMode(trigPin1, OUTPUT); 
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  delay (1000);
    
}

void loop()
{
  /*Call Distance calculation function and store distances in global varible*/
  find_distance();
   
  if(distance2<=35 && distance2>=15) /*object detection in Right sensor*/
  { 
    temp=millis();                   
    while(millis()<=(temp+300))     /*makes some delay*/
     
    find_distance();                /*call distance calcultion funcion*/
    if(distance2<=35 && distance2>=15) /*detect object for right sensor in range 15 to 35 cm */
    {
     temp=distance2;                        
     while(distance2<=50 || distance2==0)    
     {
       find_distance();                      
       if((temp+6)<distance2)                /*if distance increases in right sensor*/
       {
       Serial.println("down");               /*send 'down' massage*/
       }
       else if((temp-6)>distance2)           /*if distance decreases in right sensor*/
       {
        Serial.println("up");                /*send "up" massage*/
       }
     }
    }
    else                                      
    {
      Serial.println("next");                /* send "next" massage */
    }
  }

  else if(distance1<=35 && distance1>=15) /*detect object for left sensor in range 15 to 35 cm */
  { 
    temp=millis();                   
    while(millis()<=(temp+300))          /*makes some delay*/
    
    find_distance();
    if(distance1<=35 && distance1>=15)  
    {
     temp=distance1;                         
     while(distance1<=50 || distance1==0)    
     {
       find_distance();                      
       if((temp+6)<distance1)                
       {
        Serial.println("zoomIn");               /* send 'Zoom In' seriall massage */
       }
       else if((temp-6)>distance1)           
       {
        Serial.println("zoomOut");                /* send "Zoom out" seriall massage. */
       }
     }
    }
    else                                     
    {
      Serial.println("previous");                /* send "previous" seriall massage */
    }
  }

  else if((distance1<=10 && distance1>=5)|| (distance2<=10 && distance2>=5)) /*Object detection for both left and right sensor in range 5 to 10 cm*/
  { 
    temp=millis();                   
    while(millis()<=(temp+300))   /* makes some delay*/   
    find_distance();
    if((distance1<=10 && distance1>=5)|| (distance2<=10 && distance2>=5)) 
    {
      Serial.println("play/pause"); /*send 'play/pause' serial message*/
    }
    delay(500);                     /*make delay of 500 ms*/
    
  } 
} 
