const int pinMorseOutLed = 13;

const char* possibleInput = "!\"$&'()+,-./0123456789:;=?@abcdefghijklmnopqrstuvwxyz";
const char inputMappedToMorse[][16] =
{
	"-.-.--", ".-..-.", "...-..-", ".-...", ".----.", "-.--.", "-.--.-", ".-.-.",
	"--..--", "-....-", ".-.-.-", "-..-.", "-----", ".----", "..---", "...--",
	"....-", ".....", "-....", "--...", "---..", "----.", "---...", "-.-.-.",
	"-...-", "..--..", ".--.-.", ".-", "-...", "-.-.", "-..", ".", "..-.", "--.",
	"....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.",
	"...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.."
};

// Delays
const int charDelimiterTimeDelay = 3000;
const int invalidInputTimeDelay = 5000;
const int morseLowTimeDelay = 500;
const int morseHighTimeDelay = 1000;
const int moreSignalTimeDelay = 100;


void setup()
{
	pinMode(pinMorseOutLed, OUTPUT);
	Serial.begin(9600);
}

void loop()
{
	if (!Serial.available())
		return;

	const char inputChar = Serial.read();
	if (inputChar == ' ')
	{
		onDelimiterInput();
		return;
	}

	const char* morseCode = toMorseCode(inputChar);
	if (morseCode == NULL)
	{
		onInvalidInput();
		return;
	}

	Serial.write(inputChar);
	interpretMorseCode(morseCode);
	Serial.write('\n');
}

void onDelimiterInput()
{
	Serial.write('\n');
	delay(charDelimiterTimeDelay);
}

void onInvalidInput()
{
	Serial.write("Invalid input");
	delay(invalidInputTimeDelay);
}

void interpretMorseCode(const char* morseCode)
{
	while (*morseCode)
	{
		digitalWrite(pinMorseOutLed, HIGH);
		if (*morseCode == '.')
			interpretLowMorseSignal();
		else if (*morseCode == '-')
			interpretHighMorseSignal();
		else
		{
			Serial.write("Internal error");
			return;
		}

		digitalWrite(pinMorseOutLed, LOW);
		
		// Delay if next char is not the end
		if (morseCode[1])
			delay(moreSignalTimeDelay);

		morseCode++;
	}

	delay(charDelimiterTimeDelay);
}

void interpretLowMorseSignal()
{
	Serial.write('.');
	delay(morseLowTimeDelay);
}

void interpretHighMorseSignal()
{
	Serial.write('-');
	delay(morseHighTimeDelay);
}

const char* toMorseCode(const char c)
{
	const int inputIndex = getIndexOfInput(c);

	if (inputIndex == -1)
		return NULL;

	return inputMappedToMorse[inputIndex];
}

int getIndexOfInput(const char inputChar)
{
	int i = 0;

	while (possibleInput[i])
	{
		if (inputChar == possibleInput[i])
			return i;
		i++;
	}

	return -1;
}