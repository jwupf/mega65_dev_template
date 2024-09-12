#include <stdio.h>
#include <conio.h>


void myputs(const char* str){
  cputs((unsigned char *)str);
}

int main(){
  conioinit();
  clrscr();
  gotoxy(20,20);  
  myputs("HIYA(20,20)");
  return 0;
}