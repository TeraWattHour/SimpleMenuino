# SimpleMenu.ino

This library allows for quick and seamless management of LCD menus in Arduino.

## Installation
This library uses only `Arduino.h`, no need for any external dependencies.

- Download this repository.
- Place `SimpleMenu.cpp` and `SimpleMenu.h` files wherever you want in your project but in the same directory.
- Include the header file in your main Arduino sketch (make sure to import it from the right directory).


## Usage
1. Initialize your menu class, implement the handlers
```ino
#include <LiquidCrystal_I2C.h>
#include "SimpleMenu.h"

// this example uses LiquidCrystal_I2C library
LiquidCrystal_I2C lcd(0x27, 20, 4);

// initialize your own Menu class and implement the adapters
class MyMenu : public Menu {
  using Menu::Menu; // this is very important, derived class uses the Menu's constructor

public:
  // required method, you can just omit its body but it has to be defined
  void handleSelected(int position) {
    Serial.println("buzzer or sth");
  }

  // for compatibility across different LCD libraries you set up your handlers by yourself
  void setCursor(int x, int y) {
    lcd.setCursor(x, y);
  }
  void print(char *text) {
    lcd.print(text);
  }
};

```

2. Create a menu object of derived class MyMenu.

```ino
MyMenu mainMenu = MyMenu(20, 4);
```

3. Set up the items

```ino
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
```

4. Display and control your menu
```ino
void loop() {
  // some dummy navigation
  if (Serial.available()) {
    int input = Serial.parseInt();
    if (input == 1) {
      mainMenu.setPosition(mainMenu.position - 1); // sets focus to some absolute position
    } else if (input == 2) {
      mainMenu.setPosition(mainMenu.position + 1);
    } else if (input == 3) {
      Serial.print("call ");
      mainMenu.select(); // calls the handler associated with currently focused item
    }
  }
  mainMenu.handler(); // this method prints the menu
}
```