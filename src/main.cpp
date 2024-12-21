#include <Arduino.h>
#include <WiFi.h>

#include <U8g2lib.h>

#include <vector>
#include <map>

#include "button.hpp"
#include "battery.hpp"
#include "pretty_display.hpp"

Battery sys_battery(GPIO_NUM_15);
U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C d(U8G2_R0);
Pretty_Display display(&d, &sys_battery);

#include "clock.hpp" // user programs.
#include "battery_page.hpp"
#include "buttons_page.hpp"
#include "wifi_page.hpp"

std::map<const char*, void (*)(Pretty_Display *)> entries = {
  {"BUTTONS", buttons_f},
  {"BATTERY", battery_monitoring_f},
  {"CLOCK", clock_f},
  {"WIFI", wifi_f}
};

auto cursor = entries.begin();

Button_Pool b({{16, "L0"}, {4, "L1"}, {5, "R0"}, {17, "R1"}});
std::map<std::string, std::function<void()>> controls_main = {
  {"L0", [&](){
    std::advance(cursor, 1);
    if(cursor == entries.end()){cursor = entries.begin();}
  }},
  
  {"L1", [&](){
    if(cursor == entries.begin()){
      auto last = entries.end();
  
      cursor = last;
    }

    std::advance(cursor, -1);
  }},

  {"R0", [&](){
    cursor->second(&display);
  }},
};

void setup()
{
  Serial.begin(9600);

  d.begin();

  std::string greet_text = "BY TIMUR_SENNIKOV";

  for (int i = 0; i < greet_text.length(); i++)
  {
    display.clear();
    display.text(10, 15, greet_text.substr(0, i).c_str());
    display.send();
    delay(100);
  }

  display.text(10, 30, "USING ESP32");

  display.send();

  delay(1500);
}

uint64_t loops = 0;
void loop()
{
  display.clear();

  for(auto i = controls_main.begin(); i != controls_main.end(); i++){
    if(b.get(i->first)){
      i->second();
      delay(100);
    }
  }

  display.text(20, 20, cursor->first, u8g2_font_logisoso16_tr);
  display.text(10, 30, "L0 - down, L1 - up, R0 - choose");
  display.send();

  delay(10);
}