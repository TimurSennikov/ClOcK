class Battery{
    private:
        int pin;
        float max = 2250.0f;
    public:
        Battery(int p){
            this->pin = p;
            pinMode(this->pin, INPUT);
        }
        
        float get(){
            float p = analogRead(this->pin);
            float l = (float)(p / this->max) * 100.0f;

            return l > 100 ? 100 : l; // percentage
        }
        
        float voltage(){
            float p = analogRead(this->pin);
            return (4.2f / 100) * ((p / this->max) * 100);
        }
};