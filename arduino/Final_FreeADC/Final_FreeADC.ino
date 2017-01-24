//Set ADC in free mode in setup and then in ISR store it in ring buffer.
//There is some problem in code for ADC as values are coming to be
//85 instead of  315
#include <RingBuf.h>

struct mystruct {
  int index;
  int input;
  unsigned long long timestamp;
};

int num = 0;
int inputPin;

RingBuf *my_buf = RingBuf_new(sizeof(struct mystruct), 64);

void setup() {
  Serial.begin(9600);
  //Check if null pointer
  if (!my_buf) {
    Serial.println("Not enough memory");
    while (1);
  }

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

ISR(ADC_vect) {
  inputPin = ADCH;
  struct mystruct temp;
  memset(&temp, 0, sizeof(struct mystruct));
  
  temp.index = num;
  temp.input = inputPin;
  temp.timestamp = millis();
  num++;

  if(num == 63){
    num = 0;
  }

  my_buf->add(my_buf, &temp);
  
}

void loop() {
  Serial.println(millis());
  struct mystruct data;
  memset(&data, 0, sizeof(struct mystruct));
  my_buf->pull(my_buf, &data);
  //Serial.println(data.input);
  Serial.println(millis());
  exit(0);
}

