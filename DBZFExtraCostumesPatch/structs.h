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

// the game's FString has an extra field compared to stock UE4
typedef struct
{
	wchar_t* Data;
	u64 AllocatorFlags;
	s32 Num;
	s32 Max;
}UE4String;
