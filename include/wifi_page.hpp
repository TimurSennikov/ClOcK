void wifi_f(Pretty_Display* d){
    Button_Pool b({{16, "L0"}, {4, "L1"}, {5, "R0"}, {17, "R1"}});
    bool running = true;

    d->clear();
    d->text(0, 15, "PERFORMING NET SCAN...");
    d->send();

    WiFi.mode(WIFI_STA);
    WiFi.disconnect();

    int n = WiFi.scanNetworks();

    int current = 0;

    std::map<std::string, std::function<void()>> commands = {
        {"L0", [&](){
            if(--current < 0){current = n-1;}
        }},

        {"L1", [&](){
            if(++current >= n){current = 0;}
        }},

        {"R1", [&](){
            WiFi.begin(WiFi.SSID(current));

            auto m = millis();
            while(WiFi.status() != WL_CONNECTED){
                d->clear();
                d->text(0, 15, "Connecting...");
                d->send();

                if(millis() - m > 5000){
                    d->clear();
                    d->text(0, 15, "Aborting after 5S");
                    d->send();

                    delay(1000);
                }
            }
        }},

        {"R2", [&](){
            running = false;
        }}
    };

    while(running){
        d->clear();
        if(n <= 0){d->text(0, 15, "NO DATA", u8g2_font_logisoso16_tr);}

        d->text(0, 15, WiFi.SSID(current).c_str());
    }
}