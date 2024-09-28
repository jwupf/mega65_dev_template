#include <stdio.h>
#include <conio.h>
#include <hal.h>

typedef unsigned char uint8_t;
// typedef unsigned short uint16_t;

union frequency_control
{
  uint16_t raw;
  struct
  {
    uint8_t lower;
    uint8_t higher;
  };
};

union pulse_width_config
{
  uint16_t raw; // bytes are in reverse order!
  struct access
  {
    uint8_t lower : 8;
    uint8_t : 4;
    uint8_t higher : 4;
  };
};

union voice_ctrl
{
  uint8_t raw;
  struct
  {
    uint8_t noise : 1;
    uint8_t pulse : 1;
    uint8_t sawtooth : 1;
    uint8_t triangle : 1;
    uint8_t disable_osc : 1;
    uint8_t ring_mod_osc : 1;
    uint8_t sync_osc : 1;
    uint8_t gate : 1;
  };
};

union decay_attack
{
  uint8_t raw;
  struct
  {
    uint8_t decay : 4;
    uint8_t attack : 4;
  };
};

union release_sustain
{
  uint8_t raw;
  struct
  {
    uint8_t release : 4;
    uint8_t sustain : 4;
  };
};

union voice
{
  uint8_t memory[0x7];
  struct
  {
    frequency_control frequency_control;
    pulse_width_config pulse_width;
    voice_ctrl ctrl_bits;
    decay_attack da_reg;
    release_sustain rs_reg;
  };
};

// D400
union Sid
{
  uint8_t memory[0x1d];
  struct
  {
    union
    {
      struct
      {
        voice voice1;
        voice voice2;
        voice voice3;

        uint8_t filter_freq_lo;
        uint8_t filter_freq_hi;
        uint8_t filter_reso_ctrl;
        uint8_t filter_mode_volume;
        uint8_t paddle_1;
        uint8_t paddle_2;
        uint8_t osc_RNG3;
        uint8_t envelop_gen3_out;
      };
    };
  };
};

// void myputs(const char *str)
// {
//   cputs((unsigned char *)str);
// }

// 80x25 Zeichen
int main(void)
{

  // conioinit();
  // clrscr();

  // gotoxy(0, 24);
  // myputs("F1 XXXXXXX");
  // myputs("F3 XXXXXXX");
  // myputs("F5 XXXXXXX");
  // myputs("F7 XXXXXXX");
  // myputs("F2 XXXXXXX");
  // myputs("F4 XXXXXXX");
  // myputs("F6 XXXXXXX");
  // myputs("F8 XXXXXXX");

  // for (unsigned char i = 0; i < 80; i += 10)
  // {
  //   cellcolor(i, 24, COLOUR_RED);
  //   cellcolor(i + 1, 24, COLOUR_RED);
  // }

  Sid* sid = (Sid *)0xd400;
  for (uint8_t i = 0; i < sizeof(sid->memory); i++)
  {
    sid->memory[i] = 0;
  }

  //sid->memory[5] = 0x96; 
  sid->voice1.da_reg = {.decay=6,.attack=2};
  //sid->memory[6] = 0x92; 
  sid->voice1.rs_reg = {.release = 10,.sustain=9};
  //sid->memory[24] = 15; 
  sid->filter_mode_volume = 0x15; // max vol, no filter

  // sid->memory[1] = 15;  
  //sid->voice1.frequency_control.higher = 15;
  // sid->memory[0] = 177;
  //sid->voice1.frequency_control.lower = 177;
  sid->voice1.frequency_control.raw = 0x0600;//f3f;
  while (true)
  {
    //sid->memory[4] = 0x21; // sid.voice1.ctrl_bits.raw = 33; // gate + sawtooth
    //sid->voice1.ctrl_bits = 
    voice_ctrl t = { .noise = 0, .pulse = 0, .sawtooth =1 ,.triangle=0,.disable_osc =0, .ring_mod_osc=0,.sync_osc=0,.gate = 1};
    sid->voice1.ctrl_bits.raw = 0x21;
    usleep(1000000);
    sid->voice1.ctrl_bits.raw = 0x20;// = {.sawtooth=1, .gate=0}; //sid->memory[4] = 0x20; // sid.voice1.ctrl_bits.raw = 32; // gate + sawtooth
    usleep(1000000);
  }
  return 0;
}