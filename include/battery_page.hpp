void battery_monitoring_f(Pretty_Display* d){
    Button_Pool bpool({{17, "R1"}});

    bool running = true;

    std::map<std::string, std::function<void()>> commands = {
        {"R1", [&](){running = false;}}
    };

    Battery& b = sys_battery;
    
    d->set_auto_bat_lvl(false);
    
    int last = b.get();

    while(running){
        for(auto i = commands.begin(); i != commands.end(); i++){
            if(bpool.get(i->first)){i->second();}
        }

        int now = b.get();

        d->clear();
        d->text(10, 30, std::string(std::to_string(last) + "%").c_str(), u8g2_font_logisoso16_tr);
        d->text(55, 30, std::string(std::to_string(b.voltage()) + "V").c_str());
        d->send();

        last = now;
    }

    d->set_auto_bat_lvl(true);
}