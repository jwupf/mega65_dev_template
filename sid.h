#pragma once

#pragma pack(push, 1)

typedef unsigned char uint8_t;
// typedef unsigned short uint16_t;

struct double_register
{
    uint8_t lower;
    uint8_t higher;
};

union pulse_wave_form
{
    uint16_t raw; // bytes are in reverse order!
    struct access
    {
        uint8_t lower : 8;
        uint8_t higher : 4;
    };
};

union voice_ctrl
{
    uint8_t raw;
    struct{
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

union decay_attack{
    uint8_t raw;
    struct{
        uint8_t decay : 4;
        uint8_t attack : 4;
    };
};

union release_sustain{
    uint8_t raw;
    struct{
        uint8_t release : 4;
        uint8_t sustain : 4;
    };
};

union voice
{
    uint8_t memory[7];
    struct
    {
        uint8_t freq_lo;
        uint8_t freq_hi;
        uint8_t pw_lo;
        uint8_t : 4;
        uint8_t pw_hi : 4;
        union
        {
            voice_ctrl ctrl_bits;
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
        union {
            decay_attack da_reg;
            struct{
                uint8_t decay : 4;
                uint8_t attack : 4;
            };
        };
        union{
            release_sustain rs_reg;
            struct{
                uint8_t release : 4;
                uint8_t sustain : 4;
            };
        };
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
            };
            struct
            {
                uint8_t voice1_freq_lo;
                uint8_t voice1_freq_hi;
                uint8_t voice1_pw_lo;
                uint8_t voice1_pw_hi;
                uint8_t voice1_ctrl;
                uint8_t voice1_att_dec; // attack, decay
                uint8_t voice1_sus_rel; // sustain, release

                uint8_t voice2_freq_lo;
                uint8_t voice2_freq_hi;
                uint8_t voice2_pw_lo;
                uint8_t voice2_pw_hi;
                uint8_t voice2_ctrl;
                uint8_t voice2_att_dur;
                uint8_t voice2_sus_rel;

                uint8_t voice3_freq_lo;
                uint8_t voice3_freq_hi;
                uint8_t voice3_pw_lo;
                uint8_t voice3_pw_hi;
                uint8_t voice3_ctrl;
                uint8_t voice3_att_dec;
                uint8_t voice3_sus_rel;
            };
        };

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

#pragma pack(pop)
