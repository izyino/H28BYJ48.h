#ifndef H28BYJ48_H
#define H28BYJ48_H

#include "Arduino.h"

class H28BYJ48 {

  public:

  H28BYJ48(uint8_t t0);
  void begin();
  void runStep(uint32_t steps, uint8_t velstep, boolean cwstep);
  void runDC(uint8_t n, uint32_t time, uint8_t veldc, boolean cwdc);
  void beep(int xbnum, int xbdur, int xbfreq, int xbinter);
  void led(int xlnum, int xldur, int xlinter);
  void setms(uint32_t yms);
  void stopStep();
  void stopDC(uint8_t n);
  void stopBeep();
  void stopLed();

  uint32_t getms();
  uint32_t stepstogo();
  uint32_t timetogo(uint8_t n);

  volatile int bdur=0, binter=0, bfreq=0, bnum=0;
  volatile int ldur=0, linter=0, lnum=0;
  volatile uint32_t xms=0;

  volatile uint8_t xtipostep=2;
  volatile uint32_t   xsteps=0;
  volatile uint32_t xvelstep=10;
  volatile boolean   xcwstep=1;
  volatile int         xfase=0;
  volatile uint32_t  xvelnow=0;

  volatile uint32_t    xtime[2]={0,0};
  volatile uint32_t   xveldc[2]={50,50};
  volatile boolean     xcwdc[2]={1,1};



  private:

  void onTimer100us();
  void go();
  void move1();
  void move2();
  void move3();
  void writ(uint8_t px1, uint8_t px2, uint8_t px3, uint8_t px4);
  static H28BYJ48 *isrTable[];
  using isrFunct = void (*)();
  template<uint8_t NUM_INTERRUPTS = SOC_TIMER_GROUP_TOTAL_TIMERS>
  static isrFunct getIsr(uint8_t timerNumber);

  //variaveis de controle do beep
  volatile bool bxpausa=false, bxpri=true;
  volatile int bxinter=0, bxdur=0;

  //variaveis de controle do led
  volatile bool lxpausa=false, lxpri=true;
  volatile int lxinter=0, lxdur=0;
  uint8_t k;

  //variaveis de controle dos step motors
  uint16_t passos[4]={ 0, 2048, 2048, 4096};
  int      ajuste[4]={ 0,   28,   28,   28};

  //pinos associados aos motores DC (1s, 2s, enable)
  uint8_t pinosdc[2][3]={ {0,1,20}, {2,3,21} };
};


template<uint8_t NUM_INTERRUPTS>
H28BYJ48::isrFunct H28BYJ48::getIsr(uint8_t timerNumber) {
  if (timerNumber == (NUM_INTERRUPTS - 1)) {
    return [] {
      isrTable[NUM_INTERRUPTS - 1]->onTimer100us();
    };
  }
  return getIsr < NUM_INTERRUPTS - 1 > (timerNumber);
}

template<>
inline H28BYJ48::isrFunct H28BYJ48::getIsr<0>(uint8_t timerNumber) {
  (void) timerNumber;
  return nullptr;
}

#endif
