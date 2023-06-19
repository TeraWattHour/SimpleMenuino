#include <LiquidCrystal_I2C.h>
#include "SimpleMenu.h"

LiquidCrystal_I2C lcd(0x27, 20, 4);

class MyMenu : public Menu {
  using Menu::Menu;

public:
  void handleSelected(int position) {
    Serial.println("buzzer or sth");
  }
  void setCursor(int x, int y) {
    lcd.setCursor(x, y);
  }
  void print(char *text) {
    lcd.print(text);
  }
};

MyMenu mainMenu = MyMenu(20, 4);

void menuOneHandler() {
  Serial.println("hello from menu 1");
}

void menuTwoHandler() {
  Serial.println("hello from menu 2");
}

void menuThreeHandler() {
  Serial.println("hello from menu 3");
}

void menuFourHandler() {
  mainMenu.renameItem(3, "clicked");
}

void menuFiveHandler() {
  Serial.println("hello from menu 5");
}

void setup() {
  Serial.begin(115200);

  lcd.init();
  lcd.backlight();

  mainMenu.registerItem("Lorem ipsum dolor sit amet tratatata... ", menuOneHandler);
  mainMenu.registerItem("tes2t", menuTwoHandler);
  mainMenu.registerItem("tes3t", menuThreeHandler);
  mainMenu.registerItem("tes4t", menuFourHandler);
  mainMenu.registerItem("tes5t", menuFiveHandler);
}

void loop() {
  // some dummy navigation
  if (Serial.available()) {
    int input = Serial.parseInt();
    if (input == 1) {
      mainMenu.setPosition(mainMenu.position - 1);
    } else if (input == 2) {
      mainMenu.setPosition(mainMenu.position + 1);
    } else if (input == 3) {
      Serial.print("call ");
      mainMenu.select();
    }
  }
  mainMenu.handler();
}

