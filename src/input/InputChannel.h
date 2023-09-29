#ifndef INPUT_INPUTCHANNEL_H
#define INPUT_INPUTCHANNEL_H

namespace input {

  class InputChannel {
    public:
      virtual void read() = 0;
  };

}

#endif // INPUT_INPUTCHANNEL_H