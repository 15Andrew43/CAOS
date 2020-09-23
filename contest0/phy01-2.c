#include <stdio.h>
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

typedef union {
    double value;
    struct {
       unsigned long long int mantissa : 52;
       unsigned long long int exponent : 11;
       unsigned long long int sign : 1;
   } raw;
} unFloat;


float_class_t classify(double *value_ptr) {
    unFloat var;
    var.value = *value_ptr;
    if (!(var.raw.sign ^ 0)) {
        if (!(var.raw.exponent ^ 0)) {
            if (!(var.raw.mantissa ^ 0)) {
                return PlusZero;
            } else {
                return PlusDenormal;
            }
        } else {
            if (!(var.raw.exponent ^ 0x7FF)) {
                if (!(var.raw.mantissa ^ 0)) {
                    return PlusInf;
                } else {
                    if (!(var.raw.mantissa & 0x8000000000000)) {
                        return SignalingNaN;
                    } else {
                        return QuietNaN;
                    }
                }
            } else {
                return PlusRegular;
            }
        }
    } else {
        if (!(var.raw.exponent ^ 0)) {
            if (!(var.raw.mantissa ^ 0)) {
                return MinusZero;
            } else {
                return MinusDenormal;
            }
        } else {
            if (!(var.raw.exponent ^ 0x7FF)) {
                if (!(var.raw.mantissa ^ 0)) {
                    return MinusInf;
                } else {
                    if (!(var.raw.mantissa & 0x8000000000000)) {
                        return SignalingNaN;
                    } else {
                        return QuietNaN;
                    }

                }
            } else {
                return MinusRegular;
            }
        }

    }

}

// int main() {
//     return 0;
// }