#include <stdio.h>
#include <stdlib.h>


typedef enum {
    PlusZero      = 0x00,
    MinusZero     = 0x01,
    PlusInf       = 0xF0,
    MinusInf      = 0xF1,
    PlusRegular   = 0x10,
    MinusRegular  = 0x11,
    PlusDenormal  = 0x20,
    MinusDenormal = 0x21,
    SignalingNaN  = 0x30,
    QuietNaN      = 0x31
} float_class_t;

extern float_class_t
classify(double *value_ptr);

int main() {

	// У нас есть некоторое целое вещественное число, которое хранится в памяти
double a = 3.14159;

// Получаем указатель на это число
double* a_ptr_as_double = &a;

// Теряем информацию о типе, приведением его к типу void*
void* a_ptr_as_void = a_ptr_as_void;

// Указатель void* в языке Си можно присваивать любому указателю
uint64_t* a_ptr_as_uint = a_ptr_as_void;

// Ну а дальше просто разыменовываем указатель
uint64_t b = *a_ptr_as_uint;
	
	printf("%f\n", b);

	return 0;
}