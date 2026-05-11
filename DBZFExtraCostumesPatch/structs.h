typedef int8_t s8;
typedef uint8_t u8;
typedef int16_t s16;
typedef uint16_t u16;
typedef int32_t s32;
typedef uint32_t u32;
typedef int64_t s64;
typedef uint64_t u64;
typedef float f32;
typedef double f64;

typedef struct
{
	u8 Select;
	u8 Start;
	u8 DPadUp;
	u8 DPadRight;
	u8 DPadDown;
	u8 DPadLeft;
	u8 L1;
	u8 R1;
	u8 L2;
	u8 R2;
	u8 L3;
	u8 R3;
	u8 Circle;
	u8 Cross;
	u8 Square;
	u8 Triangle;
	u8 RightStickUp;
	u8 RightStickRight;
	u8 RightStickDown;
	u8 RightStickLeft;
	f32 LeftStickXPos;
	f32 LeftStickYPos;
	f32 RightStickXPos;
	f32 RightStickYPos;
	f32 LeftTriggerDepth;
	f32 RightTriggerDepth;
}UE4PlayerInput;

typedef struct
{
	u8 KeyNum_1;
	u8 KeyNum_2;
	u8 KeyNum_3;
	u8 KeyNum_4;
	u8 KeyNum_5;
	u8 KeyNum_6;
	u8 KeyNum_7;
	u8 KeyNum_8;
	u8 KeyNum_9;
	u8 KeyNum_0;
}UE4PlayerInput_Keyboard;

// commence shitty ghidra copypasta

typedef struct char_info 
{
	short costume_ID;
	short color_ID;
};

typedef struct char_info_struct
{
	u64 new_troll[4];
	u64 field0_0x0[77];
	u32 field1_0x268;
	u16 field2_0x26c;
	short field3_0x26e;
	short field4_0x270;
	u32 field5_0x272;
	u16 field6_0x276;
	u64 field7_0x278;
	int field8_0x280;
	u8 field9_0x284;
	u8 field9_0x285;
	u8 costume_id;
	u8 field11_0x287;
	u8 color_id;
	u8 field13_0x289;
};

typedef struct css_info_struct_sub {
	u64 field0_0x0[70];
	u64 new_troll[4];
	struct char_info_struct* ptr2[6];
};

typedef struct css_info_struct {
	u64 new_troll[4];
	u64 field_00[70];
	css_info_struct_sub* ptr1;
	u64 field_238[22];
	char_info ptr_final[3];
};

typedef struct color_select_mini_struct
{
	u32 field00;
	u32 field04;
	u32 field08;
	u32 field0c;
	u32 field10;
	u32 color_id;
	u32 color_id_next;
} color_select_mini_struct;