#include <stdio.h>
#include <conio.h>


void myputs(const char* str){
  cputs((unsigned char *)str);
}

// 80x25 Zeichen
int main(void) {

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

  return 0;
}