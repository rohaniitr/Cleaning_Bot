//Directions
int right= A1;
int left= A2;
int forward= A3;
int backward= A4;

//Store Options
int startRecording= 11;
int stopRecording= 12;

//Store Interrupts
int startStore= 2;
int stopStore= 3;

//Motor Control
int mRightHigh= 5;
int mRightLow= 6;
int mLeftHigh= 7;
int mLeftLow= 8;

//Data Storage
int MAX_ARRAY_LENGTH= 50;
unsigned long REFERENCE_TIME
unsigned long time[MAX_ARRAY_LENGTH];
//Have to try storing in char to save memory
int direction[MAX_ARRAY_LENGTH];
int i= 0;

//Control Signals
boolean isStoring;
boolean isRight;
boolean isLeft;
boolean isForward;
boolean isBackward;
boolean isStop;

//Time Required For A Single Turn: Right or Left (in milliseconds)
int TURN_TIME= 5000;

void setup()
{
	pinMode(right, INPUT);
	pinMode(left, INPUT);
	pinMode(forward, INPUT);
	pinMode(backward, INPUT);
	pinMode(stop, INPUT);
	pinMode(startRecording, INPUT);
	pinMode(stopRecording, INPUT);

	pinMode(mRightHigh, OUTPUT);
	pinMode(mLeftHigh, OUTPUT);
	pinMode(mRightLow, OUTPUT);
	pinMode(mLeftLow, OUTPUT);

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
	//STARTING STORE MODE
	if(digitalRead(startRecording)==HIGH)
	{
		i= 0;
		isStoring= true;
		REFERENCE_TIME= millis();
	}

	//STOPPING STORE MODE
	else if(digitalRead(stopRecording)==HIGH)
	{
		isStoring= false;
	}

	//STORING MODE
	else if (isStoring==true)
	{
		if(digitalRead(forward)==HIGH)
		{
			moveForward();
		}
		else if(digitalRead(backward)==HIGH)
		{
			moveBackward();
		}
		else if(digitalRead(right)==HIGH)
		{
			moveRight();
		}
		else if (digitalRead(left)==HIGH)
		{
			moveLeft();
		}
		else
		{
			stopBot();
		}
	}

	//READING MODE
	else //isStoring== false;
	{

	}

} 

void moveForward()
{
	//Start the motor here - forward
	digitalWrite(mRightHigh, HIGH);
	digitalWrite(mRightLow, LOW);
	digitalWrite(mLeftHigh, HIGH);
	digitalWrite(mLeftLow, LOW);

	if(isForward==false)
	{
		time[i]= millis() - REFERENCE_TIME;
		direction[i]= 0;
	}

	//Manage Control Signals Here
	isRight= false;
	isLeft= false;
	isForward= true;
	isBackward= false;
	isStop= false;	
}

void moveBackward()
{
	//Start the motor here - backward
	digitalWrite(mRightHigh, HIGH);
	digitalWrite(mRightLow, LOW);
	digitalWrite(mLeftHigh, HIGH);
	digitalWrite(mLeftLow, LOW);

	if(isBackward==false)
	{
		time[i]= millis() - REFERENCE_TIME;
		direction[i]= 1;
	}

	//Manage Control Signals Here
	isRight= false;
	isLeft= false;
	isForward= false;
	isBackward= true;
	isStop= false;
}

void moveRight()
{
	//Start Right Turn Code Here
	digitalWrite(mRightHigh, HIGH);
	digitalWrite(mRightLow, HIGH);
	digitalWrite(mLeftHigh, HIGH);
	digitalWrite(mLeftLow, LOW);
	delay(TURN_TIME);

	time[i]= millis() - REFERENCE_TIME;
	direction[i]= 2;

	//Manage Control Signals Here
	isRight=true;
	isLeft= false;
	isForward= false;
	isBackward= false;
	isStop= false;
}

void moveLeft()
{
	//Start Right Turn Code Here
	digitalWrite(mRightHigh, HIGH);
	digitalWrite(mRightLow, LOW);
	digitalWrite(mLeftHigh, HIGH);
	digitalWrite(mLeftLow, HIGH);
	delay(TURN_TIME);

	time[i]= millis() - REFERENCE_TIME;
	direction[i]= 3;

	//Manage Control Signals Here
	isRight=false;
	isLeft= true;
	isForward= false;
	isBackward= false;
	isStop= false;
}

void stopBot()
{
	//Stop the bot here
	digitalWrite(mRightHigh, HIGH);
	digitalWrite(mRightLow, HIGH);
	digitalWrite(mLeftHigh, HIGH);
	digitalWrite(mLeftLow, HIGH);

	if(isStop==false)
	{
		time[i]= millis() - REFERENCE_TIME;
		direction[i]= 4;
	}

	//Manage Control Signals Here
	isRight=false;
	isLeft= false;
	isForward= false;
	isBackward= false;
	isStop= true;
}

void set_isStoring()
{
	isStoring= true;
}

void stop_isStoring()
{
	isStoring= false;
}