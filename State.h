#ifndef STATE_H
#define STATE_H

#define STATE_RECORD_COUNT 60

class State {
  short temps[STATE_RECORD_COUNT];
  unsigned long timestamps[STATE_RECORD_COUNT];
  unsigned short recordCount = 0;

  void addTemp(const short temp, const unsigned long ts);

  State();

private:
  void shift();
};

State::State() {
};

void State::addTemp(const short temp, const unsigned long ts) {
  if (recordCount >= STATE_RECORD_COUNT) {
    shift();
  }
  temps[recordCount] = temp;
  timestamps[recordCount] = ts;
  ++recordCount;
};

void State::shift() {
  for (unsigned long i = 1; i < STATE_RECORD_COUNT; ++i) {
    temps[i - 1] = temps[i];
    timestamps[i - 1] = temps[i]; 
  }
  --recordCount;
}

#endif
