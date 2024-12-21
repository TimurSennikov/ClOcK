void buttons_f(Pretty_Display* d){
    Button_Pool b({{16, "L0"}, {4, "L1"}, {5, "R0"}, {17, "R1"}});

    bool running = true;

    std::map<std::string, std::function<void()>> commands = {
        {"L0", [&](){d->text(10, 10, "L0");}},
        {"L1", [&](){d->text(20, 10, "L1");}},
        {"R0", [&](){d->text(10, 20, "R0");}},
        {"R1", [&](){d->text(20, 20, "R1"); running = false;}}
    };

    while(running){
        d->clear();

        d->text(0, 30, "PRESS L0, L1, R1 (R2 to leave)");

        for(auto i = commands.begin(); i != commands.end(); i++){
            if(b.get(i->first)){i->second();}
        }

        d->send();
    }
}