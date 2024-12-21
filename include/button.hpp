struct ButtonWrapper{
    int pin;
    std::string name;
};

class Button{
    public:
        int pin;
        std::string public_name;

        Button(int p){
            this->pin = p;
            pinMode(this->pin, INPUT_PULLDOWN);
        }

        Button(int p, std::string n){
            this->pin = p;
            pinMode(this->pin, INPUT_PULLDOWN);
            this->public_name = n;
        }

        bool get(){
            return digitalRead(this->pin) > 0;
        }
};

class Button_Pool{
    private:
        std::vector<Button> buttons;
    public:
        Button_Pool(std::vector<ButtonWrapper> b){
            for(auto& i: b){
                this->buttons.push_back(Button{i.pin, i.name});
            }
        }

        bool get(int pin){
            for(auto& i: this->buttons){
                if(i.pin == pin){return i.get();}
            }
            return false;
        }

        bool get(std::string name){
            for(auto& i: this->buttons){
                if(i.public_name == name){return i.get();}
            }
            return false;
        }
};