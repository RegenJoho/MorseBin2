#include "Arduino.h"
#include "MorseBin2.h"
void MB2Send0(int sendpin) {
 	digitalWrite(sendpin,HIGH);
 	delayMicroseconds(time0);
 	digitalWrite(sendpin,LOW);
 	delayMicroseconds(time1);
  }
void MB2Send1(int sendpin) {
 	digitalWrite(sendpin,HIGH);
 	delayMicroseconds(time1);
 	digitalWrite(sendpin,LOW);
 	delayMicroseconds(time1);
  }
void MB2SendByte(String input,int sendpin){
	digitalWrite(sendpin,HIGH);
	delayMicroseconds(time0+time1);
	digitalWrite(sendpin,LOW);
	delayMicroseconds(time1);
   	 for (int i=0;i<8;i++){
    		if (input.charAt(i)=='1'){
     		 Send1(sendpin);
      		//Serial.println("gotit1");
      	}
      if (input.charAt(i)=='0'){
      		Send0(sendpin);
      		//Serial.println("gotit0");
      }
    }
  }
String MB2Receive(int respin){
	String buf;
  	int waitTimer = 0;
	int timeouttimer = 0;
	while(digitalRead(respin)==LOW){
		timeouttimer+=8;
    	delayMicroseconds(8);
    	if(timeouttimer>=30000){
      		return "errTimeout";
	  	}
	}
	int microTimer = micros();
	while(digitalRead(respin) == HIGH){
	}
	waitTimer = micros() - microTimer;
 	if(waitTimer>timeForStart){
	} else {
		//Serial.println(waitTimer);
		//Serial.print("StartTime should be: ");
		//Serial.println(timeForStart);
		return "errGrabledMessage";
	}
 	for (int i=0;i<8;i++){
		int timer = 0;
		while (digitalRead(respin)==LOW){
			timer++;
			delayMicroseconds(8);
			if(timer>=10000){
				timer = 0;
				return "errTimeout";
			}
		}
		int microStart = micros();
		while(digitalRead(respin)==HIGH) {
		}
		int t = micros() - microStart;
		if (t > timeMiddle && t < timeForStart) {
			buf += "0";
		}
		else {
			if(t < timeMiddle && t < timeForStart){
				buf += "1";
				} else {
					buf += "n";
				}      	
			}   
    }
    return buf;
  }