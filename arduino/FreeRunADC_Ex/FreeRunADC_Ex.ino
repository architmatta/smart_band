//clipping indicator variables
boolean clipping = 0;

//storage variables
byte newData = 0;
byte prevData = 0;
unsigned int time = 0; //keeps time and send value to store in timer[]
int timer[10]; //storage for timing of eb=vents
int slope[10]; //storage for slope of events
unsigned int totalTimer; //used to calculate period
unsigned int period; //storage for period of wave
byte index = 0; //current storage index
float frequency; // storage for frequency calculation
int maxSlope = 0; //used to calculate max slope as trigger point
int newSlope; //storage for incomin slope data

//variables for decided whether you have a match
byte noMatch = 0; //counts how many non matches you've received to reset
//variables if it's been too long
byte slopeTol = 3; //slope tolerance - adjust this if you need
int timerTol = 10; //timer tolerance - adjust this if you need

void setup() {

  Serial.begin(9600);

  pinMode(13, OUTPUT);//led indicator pin
  pinMode(12, OUTPUT);//output pin

  cli();//disable interrupt

  //set up continuous sampling of A0

  //clear ADCSRA and ADCSRB registers
  ADCSRA = 0;
  ADCSRB = 0;

  ADMUX |= (1 << REFS0);//set reference voltage
  ADMUX |= (1 << ADLAR); //left align the ADC value- so we can read
  //highest value from ADCH registers only

  ADCSRA |= (1 << ADPS2) | (1 << ADPS0); //set ADC clock with 32 prescaler-
  //16mHz/32=500kHz
  ADCSRA |= (1 << ADATE); //enable trigger
  ADCSRA |= (1 << ADIE); //enable interrupts when measurement complete
  ADCSRA |= (1 << ADEN); //enable ADC
  ADCSRA |= (1 << ADSC); //start ADC measurements

  sei();//enable interrupts
}

ISR(ADC_vect) { //when new ADC value ready
  PORTB &= B11101111; //set pin 12 low
  prevData = newData; //store previous value
  newData = ADCH; //get value from A0
  if (prevData < 127 && newData >= 127) { //if increasing and crossing midpoint(2.5V)
    newSlope = newData - prevData; //calculate slope
    if (abs(newSlope - maxSlope) < slopeTol) { //if slopes are ==
      //record new data and reset time
      slope[index] = newSlope;
      timer[index] = time;
      time = 0;
      if (index == 0) { //new max slope just reset
        PORTB |= B00010000; //set pin 12 high
        noMatch = 0;
        index++;//increment index
      }
      else if (abs(timer[0] - timer[index]) < timerTol
               && abs(slope[0] - newSlope) < slopeTol)
        //if timer duration and slope matches
      {
        //sum timer values
        totalTimer = 0;
        for (byte i = 0; i < index; i++) {
          totalTimer += timer[i];
        }
        period = totalTimer; //set period
        //reset new zero index values to compare with
        timer[0] = timer[index];
        slope[0] = slope[index];
        index = 1; //set index to 1
        PORTB |= B00010000; //set pin 12 high
        noMatch = 0;
      }
      else { //crossing midpoint but no match
        index++;
        if (index > 9) {
          reset();
        }
      }
    }
    else if (newSlope > maxSlope) { //if new slope is much larger than max slope
      maxSlope  = newSlope;
      time = 0;//reset clock
      noMatch = 0;
      index = 0;//reset index
    }
    else { //slope not steep enough
      noMatch++;//increment to match counter
      if (noMatch > 9) {
        reset();
      }
    }
  }

  if (newData == 0 || newData == 1023) { //if clipping
    PORTB |= B00100000; //set pin 13 high - turn on clipping indicator led
    clipping = 1; //currently clipping
  }

  time++; //increment timer at rate of 38.5kHz
}

void reset() { //clear out some variables
  index = 0; //reset index
  noMatch = 0; //reset match counter
  maxSlope = 0; //reset slope
}

void checkClipping(){//manage clipping indicator LED
  if(clipping){//if currently clipping
    PORTB &= B11011111; //turn off clipping indicator led
    clipping = 0;
  }
}

void loop(){
  checkClipping();

  frequency = 38642/float(period); //calculate frequency timer rate/period

  //print results
  Serial.print(frequency);
  Serial.println("hz");

  //do other stuff here
}

