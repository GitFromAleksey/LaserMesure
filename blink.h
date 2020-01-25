#ifndef BLINK_H
#define BLINK_H

class Blink
{

public:
	Blink():state(false)
	{
		pinMode(LED_BUILTIN, OUTPUT);
	}
	~Blink(){}

	void run(void)
	{
		if(state)
		{digitalWrite(LED_BUILTIN, HIGH); state = false;}
		else
		{digitalWrite(LED_BUILTIN, LOW); state = true;}
	}
private:
	bool state;
};

#endif

