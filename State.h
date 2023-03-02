#ifndef STATE_H
#define STATE_H

#define STATE_RECORD_COUNT 180

class State {
public:
  float temps[STATE_RECORD_COUNT];
  unsigned long timestamps[STATE_RECORD_COUNT];
  unsigned short recordCount = 0;

  void addTemp(const float temp, const unsigned long ts);
  String toString();

  State();

private:
  void shift();
};

State::State() {
};

void State::addTemp(const float temp, const unsigned long ts) {
  Serial.print("record index = "); Serial.println(recordCount);
  if (recordCount >= STATE_RECORD_COUNT) {
    shift();
  }
  temps[recordCount] = temp;
  timestamps[recordCount] = ts;
  ++recordCount;
};

String State::toString() {
  String string = "";
  for (unsigned short i = 0; i < recordCount; ++i) {
    string += timestamps[i];
    string += ":";
    string += temps[i];
    if (i == recordCount - 1) continue; // skip comma at the end of the string
    string += ",";
  }
  return string;
}

void State::shift() {
  for (unsigned long i = 1; i < STATE_RECORD_COUNT; ++i) {
    temps[i - 1] = temps[i];
    timestamps[i - 1] = timestamps[i]; 
  }
  --recordCount;
  Serial.println("did shift records");
}

#endif
