/*When this code is uploaded to arduino it will recognise knocks like 1 2 _ 4   where at each second a knock occurs
 * 
 * Pins:5 led negative
 *      7 led positive
 *      10 sond detector data pin
 *      others pins of sound detector are attached to ground and vcc respectively
 *      
 * when correct knock sequence occurs led will light up.
 */
int soundpin=10;
int sound=HIGH;
unsigned long last,last1;

void setup() 
{   // put your setup code here, to run once:
    pinMode(soundpin,INPUT);  //input from sound detector
    Serial.begin(9600);
    pinMode(5,OUTPUT);        //led ports
    pinMode(7,OUTPUT);
}

void loop() 
{   // put your main code here, to run repeatedly:
    x:sound=digitalRead(soundpin);
    
    if(sound == LOW)
    {
         Serial.print("yes");
         last=millis();
         delay(150);
         sound=digitalRead(soundpin);
         while(sound!=LOW)
            sound=digitalRead(soundpin);
         
         if( millis()-last > 500 && millis()-last < 1500)        //checks time difference between knock1 and knock 2
         {  
             last1=millis();
             delay(100);
             sound=digitalRead(soundpin);
             while(sound!=LOW)
                 sound=digitalRead(soundpin);
             
             if( millis()-last1 > 1000 && millis()-last < 2500) //checks time difference between knock2 and knock 3
             {  
                Serial.write("code accepted");
                digitalWrite(5,LOW);
                digitalWrite(7,HIGH);
                delay(5000);
             }
             else
             { 
                goto x;
                delay(100);
             }
         }
         else
         {
            goto x;
            delay(100);
         }          
    }
    else
    {
         digitalWrite(5,LOW);
         digitalWrite(7,LOW);
    }
}
