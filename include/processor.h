#ifndef PROCESSOR_H
#define PROCESSOR_H

class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp

  // TODO: Declare any necessary private members
 private:
    float prev_usertime      ;
    float prev_nicetime      ;
    float prev_systemtime    ;
    float prev_idletime      ;
    float prev_ioWait        ;
    float prev_irq           ;
    float prev_softirq       ;
    float prev_steal         ;
    float prev_guest         ;
    float prev_guest_nice    ;
    float PrevIdle ;
    float PrevNonIdle  ;
    float PrevTotal  ;

};

#endif