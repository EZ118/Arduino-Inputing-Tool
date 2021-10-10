#include <SPI.h>
#include <Wire.h> 
#include <string.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display = Adafruit_SSD1306(128, 64, &Wire);

void setup() { 
  display.begin(SSD1306_SWITCHCAPVCC, 0x3c);  //屏幕
  pinMode(11, INPUT_PULLUP);                  //摇杆上的按钮，接在引脚D11
  
  display.setTextSize(1);                     //文本大小
  display.setTextColor(SSD1306_WHITE);        //文本颜色（只有白色）
} 

int Mode = 0;                       //Mode表示快捷跳转到字符模式的计数器
char Val = 65;                      //Val表示选定的字符
String InStr = "Input Tool Test.";  //用于存储已输入的字符串

void loop() {
  display.clearDisplay();

  int valueX = int(analogRead(A1)); //摇杆X轴
  int valueY = int(analogRead(A0)); //摇杆Y轴
  int valueZ = int(digitalRead(11));//摇杆按钮
  
  if(valueY >= 600){                //摇杆向上拨动时，选择上一个字符
    Val += 1;
  } else if(valueY <= 50){          //摇杆向下拨动时，选择下一个字符
    Val -= 1;
  } else if(valueZ == 0){           //点击摇杆时，将选定的字符添加到已输入的字符串
    InStr += Val;
  } else if(valueX <= 50){          //左滑摇杆时，清空所有已输入的字符串
    InStr = "";
    display.setCursor(50, 52);
    display.print("[ DEL ]");
  } else if(valueX >= 600){         //快捷跳转到字符
    Mode += 1;
    if(Mode == 1) Val = 97;         //跳转到a
    else if(Mode == 2) Val = 65;    //跳转到A
    else if(Mode == 3) Val = 48;    //跳转到1
    else if(Mode == 4) Val = 33;    //跳转到!
    else if(Mode == 5) Val = 1;     //跳转到特殊符号
    else if(Mode == 6) Mode = 0;    //避免超出可选模式范围
  }

  
  display.setCursor(0, 2);
  display.print(InStr);
  
  display.drawLine(0, 50, 128, 50, WHITE);

  display.setCursor(0, 52);
  display.print("[ ");
  display.print(Val);
  display.print(" ]");
  
  display.display();
  delay(70);
} 

/*
int value = 0; 
void setup() { 
 pinMode(11, INPUT_PULLUP);
 Serial.begin(9600); 
} 
void loop() { 
 value = analogRead(A0); 
 Serial.print("X:"); 
 Serial.print(int(value)); 
 value = analogRead(A1); 
 Serial.print(" | Y:"); 
 Serial.print(int(value)); 
 value = digitalRead(11); 
 Serial.print(" | Z: "); 
 Serial.println(int(value)); 
 delay(500); 
}*/
