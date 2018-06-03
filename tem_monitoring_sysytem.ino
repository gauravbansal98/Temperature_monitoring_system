#include <SPI.h>
#include <SD.h>
#include <TimerOne.h>
int mm=0,hh=0,sec=0,d=1,m=1,y=2017;
const int chipSelect = 8;
void setup() {
   Serial.begin(9600);
    Timer1.initialize(1000000);
  Timer1.attachInterrupt(update_data,1000000);
  while (!Serial);
  Serial.print("Initializing SD card...");
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    return;
  }
  Serial.println("card initialized.");
  String dataString="date,time,tem";
   File dataFile = SD.open("datalog.csv", FILE_WRITE);
     if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
    Serial.println(dataString);
  }
  else {
    Serial.println("error opening datalog.txt");
  }
}
void loop(){
  
}
void data_write() {
 String dataString = "";
 String date=String(d)+"/"+String(m)+"/"+String(y);
 String timer=String(hh)+":"+String(mm);
 String combind_string="";
    int sensor = analogRead(A0);
    float tem=float(sensor)*500.0/1024.0;
    dataString += String(tem);
 combind_string=date+","+timer+","+dataString;
    File dataFile = SD.open("datalog.csv", FILE_WRITE);
     if (dataFile) {
    dataFile.println(combind_string);
    dataFile.close();
    Serial.println(combind_string);
  }
  else {
    Serial.println("error opening datalog.txt");
  }
}
void update_data(){
  sec++;
  if(sec==59){mm++,sec=0;}
  if(mm==59){hh++;mm=0;}
  if(hh==24){date_change();hh=0;}
  data_write();
}
void date_change(){
  if(m==1 || m==3 || m==5 || m==7 || m==8 || m==10 || m==12)
    {
      if(d==31){m++;d=1;}
      else d++;
    }
   else if(m==2){
   if(y%4==0){
    if(d==29){d=1;m++;}
    else d++;
   }
   else {
    if(d==28){d=1;m++;}
    else d++;
   }
   }
   else {
    if(d==30){m++;d=1;}
      else d++;
   }
}

