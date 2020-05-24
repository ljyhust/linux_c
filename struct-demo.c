#include<stdio.h>
#include<math.h>
//enum type polar type
enum coordinate_type {RECTANGULAR = 1, POLAR};
struct complex_struct {
    enum coordinate_type t;
    double a, b;
};

// polar to rectangular
struct complex_struct make_from_real_img(double x, double y)
{
    struct complex_struct z;
    z.t = RECTANGULAR;
    z.a = x;
    z.b = y;
    return z;
}
// polar struct init
struct complex_struct make_from_mag_ang(double r, double A)
{
    struct complex_struct z;
    z.t = POLAR;
    z.a = r;
    z.b = A;
    return z;
}

double real_part(struct complex_struct input) {
    if (input.t == POLAR) {
        return input.a * cos(input.b);
    }
    return input.a;
}

double img_part(struct complex_struct input) {
    if (input.t == POLAR) {
        return input.a * sin(input.b);
    }
    return input.b;
}

double magnitude(struct complex_struct input) {
    if (input.t == POLAR) {
        return input.a;
    }
    return sqrt(input.a * input.a + input.b * input.b);
}

double angle(struct complex_struct input) {
    if (input.t == POLAR) {
        return input.b;
    }
    return acos(input.a / magnitude(input));
}

main()
{
    struct complex_struct test;
    test.a = 3.0;
    test.b = 4.0;
    test.t = RECTANGULAR;
    printf("====> r= %f\n", magnitude(test));
    printf("====> angle= %f\n", angle(test));
    printf("====> real_part= %f\n", real_part(test));
    printf("====> img_part= %f\n", img_part(test));
    
    int RECTANGULAR;
    printf("%d %d\n", RECTANGULAR, POLAR);
    return 0;
}

