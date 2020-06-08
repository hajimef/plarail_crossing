#ifndef __RAIL_SWITCH_H__
#define __RAIL_SWITCH_H__
class RailSwitch {
  protected:
    bool pushed;
    unsigned long delay;
    unsigned long t;

  public:
    RailSwitch(void);
    RailSwitch(unsigned long _delay);
    void set_pushed(void);
    void reset_pushed(void);
    bool is_pushed(void);
};
#endif
