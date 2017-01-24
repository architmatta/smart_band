#include <RingBuf.h>

struct mystruct {
  int index;
  int input;
  unsigned long long timestamp;
};

int num = 0;

RingBuf *my_buf = RingBuf_new(sizeof(struct mystruct), 64);

void setup() {
  Serial.begin(9600);
  //Check if null pointer
  if (!my_buf) {
    Serial.println("Not enough memory");
    while (1);
  }
}
void loop() {
  struct mystruct data, temp;
  memset(&temp, 0, sizeof(struct mystruct));
  memset(&data, 0, sizeof(struct mystruct));

  int inputPin = analogRead(A0);

  temp.index = num;
  temp.input = inputPin;
  temp.timestamp = millis();
  num++;

  my_buf->add(my_buf, &temp);

  my_buf->pull(my_buf, &data);
  Serial.println(data.input);
}

