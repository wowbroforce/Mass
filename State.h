#ifndef STATE_H
#define STATE_H

#define STATE_RECORD_COUNT 180

class State {
public:
  float temps[STATE_RECORD_COUNT];
  uint32_t timestamps[STATE_RECORD_COUNT];
  uint16_t recordCount = 0;

  void addTemp(const float temp, const uint32_t ts);
  String toString();

  State();

private:
  void shift();
};

State::State() {
};

void State::addTemp(const float temp, const uint32_t ts) {
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
  for (uint16_t i = 0; i < recordCount; ++i) {
    string += timestamps[i];
    string += ":";
    string += temps[i];
    if (i == recordCount - 1) continue; // skip comma at the end of the string
    string += ",";
  }
  return string;
}

void State::shift() {
  for (uint16_t i = 1; i < STATE_RECORD_COUNT; ++i) {
    temps[i - 1] = temps[i];
    timestamps[i - 1] = timestamps[i]; 
  }
  --recordCount;
  Serial.println("did shift records");
}

#endif
