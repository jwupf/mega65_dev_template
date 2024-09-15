#include "mega65.h"
#include <stdio.h>
#include <conio.h>
#include "hal.h"
#include "sid.h"


void myputs(const char* str){
  cputs((unsigned char *)str);
}

/* Return the key modifiers state, where bits:

    Bit           Meaning
    -----------------------------------------
    0             Right SHIFT state
    1             Left  SHIFT state
    2             CTRL state
    3             MEGA/C= state
    4             ALT state
    5             NOSCRL state
    6             CAPSLOCK state
    7             Reserved
*/
//unsigned char getkeymodstate(void);

class Key {
public:
  Key(){
    key = kbhit();    
  }
  ~Key(){
    if(key!=0)
      flushkeybuf();
  };
  unsigned char Get(){
    return key;
  }
private:
  unsigned char key;
};

// 80x25 Zeichen
int main(void) {
  // const char *cur = "HELLO, PUTCHAR!\n";
  // while (*cur)
  //   putchar(*cur++);
  conioinit();
  clrscr();

  // gotoxy(0,24);
  // myputs("F1 XXXXXXX");  
  // myputs("F3 XXXXXXX");
  // myputs("F5 XXXXXXX");
  // myputs("F7 XXXXXXX");
  // myputs("F2 XXXXXXX");
  // myputs("F4 XXXXXXX");
  // myputs("F6 XXXXXXX");
  // myputs("F8 XXXXXXX");
  // for(unsigned char i = 0; i<80;i+=10){
  //   cellcolor(i,24,COLOUR_RED);
  //   cellcolor(i+1,24,COLOUR_RED);
  // }

  // voice v;
  // v.freq_lo = 0x01;
  // v.freq_hi = 0x02;
  // v.pw_lo = 0x03;
  // v.pw_hi = 0x04;
  // v.ctrl = 0x05;
  // v.attack = 0x06;
  // v.decay = 0x07;
  // v.sustain = 0x08;
  // v.release = 0x09;
  
  // for(unsigned char i = 0; i<7;i++){
  //   gotoxy(0,i);
  //   cputhex(v.memory[i],2);
  // }
  //gotoxy(0,0);cputhex(v.memory[0],2);

  // volatile Sid sid = *(Sid*)0xd400;
  // for(unsigned char i = 0; i<0x1d;i++){
  //    sid.memory[i] = 0;
  // }
  // // sid->voice1.pw_lo = 0x0;
  // // sid->voice1.pw_hi = 0x4;
  // sid.voice1.freq_hi = 42;
  // sid.voice1.attack = 0xf;
  // sid.voice1.decay = 0x5;
  // sid.voice1.sustain = 0xf;
  // sid.voice1.release = 0x2;

  // sid.voice1.sawtooth = 1;
  // sid.voice1.gate = 1;
  // sid.filter_mode_volume = 0xf;

  // while(true){
    

  

  //   switch(Key k; k.Get()){
  //     case 'a':
  //     gotoxy(0,0);
  //     myputs("AAAAAA\n");
  //     break;
  //     case '\t':
  //     gotoxy(0,0);
  //     myputs("BBBBBB\n");
  //     break;
  //     default:
  //     break;
  //   }
  // };



  // uint8_t* S = (uint8_t*)54272; //0xd400
  // uint8_t W = 17; //: ON INT(RND(TI)*4)+1 GOTO 12,13,14,15
  // // W = 33: GOTO 15
  // // W = 65: GOTO 15
  // // W = 129
  
  // S[ 0] = 0;
  // S[ 1] = 0x1f;
  // S[ 5] = 97;
  // S[ 6] = 200;
  // S[ 4] = 17;
  // S[24] = 15;


  Sid* sid = (Sid*)0xd400;
  sid->voice1.freq_lo=0;
  sid->voice1.freq_hi=0x1f;
  // split stufff is not working correctly ... attack/decay need to be combined ...
  sid->voice1.attack = 6;
  sid->voice1.decay = 1;
  sid->voice1.sustain=0xC;
  sid->voice1.release=0x8;
  //sid->voice1.gate = 1; // 0x11 -> 17
  //sid->voice1.triangle = 1;
  sid->voice1.ctrl_bits = voice_ctrl{
    .noise = 0,
    .pulse=0,
    .sawtooth = 0,
    .triangle = 1,
    .disable_osc=0,
    .ring_mod_osc=0,
    .sync_osc=0,
    .gate = 1};
  sid->voice1.ctrl = 0x11;
  //sid->memory[ 4] = 17;
  sid->filter_mode_volume = 0x0f;

  // for(unsigned char i = 0; i<25;i++){
  //   gotoxy(0,i);
  //   cputhex(sid.memory[i],2);
  //   gotoxy(10,i);
  //   cputdec(sid.memory[i],0,0);
  // }

  return 0;
}