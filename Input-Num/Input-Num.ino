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

int InputNum(String msg = "Input [Number]"){
  int Val = 0;                        //Val表示选定的数字
  int InStr = 0;                      //用于存储已输入的数字
  
  while(1){
    display.clearDisplay();

    int valueX = int(analogRead(A1)); //摇杆X轴
    int valueY = int(analogRead(A0)); //摇杆Y轴
    int valueZ = int(digitalRead(11));//摇杆按钮
    
    if(valueY >= 600 && Val < 9 && InStr < 21474836) Val += 1;  //摇杆向下
    else if(valueY <= 50 && Val > 0) Val -= 1;                   //摇杆向上
    else if(valueZ == 0 && Val >= 0){                            //单击摇杆
      InStr = InStr * 10 + Val;
      Val = -1;
      display.setCursor(80, 2);
      display.print("[TYPE]");
    }
    else if(valueX <= 50){                                       //摇杆向左，删除数字最低位
      InStr /= 10;      
      display.setCursor(80, 2);
      display.print("[DEL]");
      Val = -1;
    }
    else if(valueX >= 600) break;                                //摇杆向右，提交

    display.setCursor(2, 2);
    display.print(msg);
    
    display.drawLine(0, 12, 128, 12, WHITE);
    display.setCursor(0, 20);
    display.setTextSize(2);
    if(InStr != 0) display.print(InStr);
    if(Val >= 0) display.print(Val);
    display.display();
    display.setTextSize(1);
    delay(70);
  }
  display.display();
  return InStr;
}

void loop() {
  display.clearDisplay();
  
  int a = InputNum();
  display.setCursor(5, 5);
  display.print("Number: ");
  display.print(a);
  
  display.display();
  delay(5000);
}
