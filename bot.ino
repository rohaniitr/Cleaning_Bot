//Directions
int right= A1;
int left= A2;
int forward= A3;
int backward= A4;
int stop= A5;

//Store Options
int startRecording= 11;
int stopRecording= 12;

//Store Interrupts
int startStore= 2;
int stopStore= 3;

//Motor Control
int mForwardRight= 5;
int mForwardLeft= 6;
int mBackwardRight= 7;
int mBackwardLeft= 8;

//Data Storage
int ARRAY_LENGTH= 50;
long time[ARRAY_LENGTH];
int direction[ARRAY_LENGTH];

//Control Signals
bool isStoring;
bool isRight;
bool isLeft;
bool isForward;
bool isBackward;
bool isStop;

void setup()
{
	pinMode(right, INPUT);
	pinMode(left, INPUT);
	pinMode(forward, INPUT);
	pinMode(backward, INPUT);
	pinMode(stop, INPUT);
	pinMode(startRecording, INPUT);
	pinMode(stopRecording, INPUT);

	pinMode(mForwardRight, OUTPUT);
	pinMode(mForwardLeft, OUTPUT);
	pinMode(mForwardRight, OUTPUT);
	pinMode(mBackwardLeft, OUTPUT);

	attachInterrupt(startStore, set_isStoring, RISING);
	attachInterrupt(stopStore, stop_isStoring, RISING);

	isStoring= false;
	isRight= false;
	isLeft= false;
	isForward= false;
	isBackward= false;
}

void loop()
{
	if (isStoring==true)
	{
		if(isForward=false && digitalRead(forward)==1)
		{
			moveForward();
		}
		else if(isBackward==false && digitalRead(backward)==1)
		{
			moveBackward();
		}
	}

  digitalWrite(ledPin, HIGH);
  delay(1000);
  digitalWrite(ledPin, LOW);
  delay(1000);
} 

void moveForward()
{
	//Start the motor here
	isRight= false;
	isLeft= false;
	isBackward= false;
}

void set_isStoring()
{
	isStoring= true;
}

void stop_isStoring()
{
	isStoring= false;
}