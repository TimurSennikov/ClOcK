/*
 * clock subprogram, can be selected from the main menu.
*/

#include <RtcDS1302.h>

ThreeWire w(GPIO_NUM_25, GPIO_NUM_33, GPIO_NUM_32);
RtcDS1302<ThreeWire> rtc_mod(w);

void clock_f(Pretty_Display* d){
    Button_Pool bpool({{17, "R1"}});

    bool running = true;

    std::map<std::string, std::function<void()>> commands = {
        {"R1", [&](){running = false;}}
    };

    rtc_mod.Begin();

    rtc_mod.SetDateTime(RtcDateTime{2024, 12, 20, 17, 11, 15});

    while(running){
        for(auto i = commands.begin(); i != commands.end(); i++){if(bpool.get(i->first)){i->second();}}

        d->clear();

        if(!rtc_mod.IsDateTimeValid()){
            d->text(32, 23, "ERROR", u8g2_font_logisoso16_tr);
            d->send();

            continue;
        }

        RtcDateTime now = rtc_mod.GetDateTime();

        std::string text = std::to_string(now.Hour()) + ":" + std::to_string(now.Minute()) + ":" + std::to_string(now.Second());

        d->text(32, 30, text.c_str(), u8g2_font_logisoso16_tr);
        d->send();
    }
}