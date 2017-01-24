void setup() {
  Serial.begin(9600);
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

  sei();//enable interruptsx

}

ISR(ADC_vect) {
  int inputPin = ADCH;
  Serial.println(inputPin);
}

void loop() {
  // put your main code here, to run repeatedly:

}
