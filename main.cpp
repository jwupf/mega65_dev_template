#include "mega65.h"
#include <stdio.h>
#include <conio.h>


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

  gotoxy(0,24);
  myputs("F1 XXXXXXX");  
  myputs("F3 XXXXXXX");
  myputs("F5 XXXXXXX");
  myputs("F7 XXXXXXX");
  myputs("F2 XXXXXXX");
  myputs("F4 XXXXXXX");
  myputs("F6 XXXXXXX");
  myputs("F8 XXXXXXX");
  for(unsigned char i = 0; i<80;i+=10){
    cellcolor(i,24,COLOUR_RED);
    cellcolor(i+1,24,COLOUR_RED);
  }

  while(true){
    switch(Key k; k.Get()){
      case 'a':
      gotoxy(0,0);
      myputs("AAAAAA\n");
      break;
      case '\t':
      gotoxy(0,0);
      myputs("BBBBBB\n");
      break;
      default:
      break;
    }
  };
  return 0;
}