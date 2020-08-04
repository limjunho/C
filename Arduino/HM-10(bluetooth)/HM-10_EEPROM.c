/* 센서의 ID값을 블루투스로 송신받아 EEPROM에 저장하는 예제소스 */
#define NCLR 1
#include <SoftwareSerial.h> //시리얼통신 라이브러리 호출
#include <EEPROM.h> // EEPROM을 사용하기위한 라이브러리 호출
 
int blueTx=2;   //Tx (보내는핀 설정)at
int blueRx=3;   //Rx (받는핀 설정)
SoftwareSerial mySerial(blueTx, blueRx);  //시리얼 통신을 위한 객체선언

void setup() 
{
  Serial.begin(9600);   //시리얼모니터
  mySerial.begin(9600); //블루투스 시리얼
  EEPROM.write(1, 's');
}

void loop()
{
  int i = 0;
  char ch;
  unsigned int data;
  char str[20];
  memset(str, '\0', 20);
  if (mySerial.available()) {       
    while(1){
      data = mySerial.read();

      if(i >= 20){
        Serial.println("buffer over-flow!!");
        memset(str, 0, 20);
        break;
      }else{
        if(!isdigit(data)){
        //if(data == -1){   // buffer가 비어있다면
          i = 0;
          break;
        }else{
          Serial.write(data);
          str[i] = char(data);  
          i++;
          delay(100);
        }
      }
    }
    //Serial.print("str : ");
    //Serial.println(str);
    
    data = atoi(str);   // char[]타입을 int타입으로 형변환
    //Serial.print("data : ");
    //Serial.println(data);
    
    EEPROM.write(0, data); // EEPROM에 저장

    Serial.println();
    data = EEPROM.read(0);
    Serial.print("EEPROM Address : 0\t Value : ");
    Serial.println(data);
    
    ch = EEPROM.read(1);
    Serial.print("EEPROM Address : 1\t Value : ");
    Serial.println(ch);
    delay(200);
  }
  if (Serial.available()) {         
    mySerial.write(Serial.read());  //시리얼 모니터 내용을 블루추스 측에 WRITE
  }
}