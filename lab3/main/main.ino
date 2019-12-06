  
#define RELAYPIN 7
#define WATERLEVEL A0

const int threshold = 50;

void setup()
{
    Serial.begin(9600);
    pinMode(RELAYPIN, OUTPUT);
}


void loop()
{
    auto water = analogRead(WATERLEVEL);
    Serial.println(water);

    if (water >= threshold) {
        digitalWrite(RELAYPIN, LOW);
    } else {
        digitalWrite(RELAYPIN, HIGH);
    }    
}