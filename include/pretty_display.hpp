class Pretty_Display{
  private:
    U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C* display;
    Battery* battery;

    bool auto_bat_lvl = true;
  public:
    Pretty_Display(U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C* d, Battery* b){
        this->display = d;
        this->battery = b;
      }
      
    bool get_auto_bat_lvl(){return this->auto_bat_lvl;}
    void set_auto_bat_lvl(bool lvl){this->auto_bat_lvl = lvl;}

    void clear(){
      this->display->clearBuffer();
    }

    void send(){
      if(this->auto_bat_lvl){this->bat_lvl();}

      this->display->sendBuffer();
    }

    void text(int x, int y, const char* text, const unsigned char font[]=u8g2_font_4x6_mf){
      this->display->setFont(font);
      this->display->drawStr(x, y, text);
    }

    void bat_lvl(){
      int p = this->battery->get();
      this->text(100, 10, std::string(std::to_string(p) + "%").c_str());
    }

    ~Pretty_Display(){
      delete this->display;
    }
};