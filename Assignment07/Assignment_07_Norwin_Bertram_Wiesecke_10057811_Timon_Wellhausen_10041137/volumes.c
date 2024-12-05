#include "base.h"

#ifndef M_PI
#define M_PI 3.141592653589793
#endif

/*
Die enum TypTag definiert die Körper, die dargestellt werden können und bietet eine Möglichkeit, diese zu unterscheiden.
*/

typedef enum typetag_e {
    CYLINDER,
    CUBOID,
    SPHERE,
} TypeTag;

typedef struct cylinder_s {
    double r, h;
} Cylinder;

typedef struct cuboid_s {
    double a, b, c;
} Cuboid;

typedef struct sphere_s {
    double r;
} Sphere;

typedef struct body_s {
    enum typetag_e tag;
    union {
        Cylinder cylinder;
        Cuboid cuboid;
        Sphere sphere;
    };
} Body;

Body make_cylinder(double r, double h) {
    if (r < 0 || h < 0) {
        fprintf(stderr, "make_cylinder: invalid input\n");
        exit(1);
    }
    struct body_s body;
    body.tag = CYLINDER;
    body.cylinder.r = r;
    body.cylinder.h = h;
    return body;
}

Body make_cuboid(double a, double b, double c) {
    if (a < 0 || b < 0 || c < 0) {
        fprintf(stderr, "make_cubiod: invalid input\n");
        exit(1);
    }
    struct body_s body;
    body.tag = CUBOID;
    body.cuboid.a = a;
    body.cuboid.b = b;
    body.cuboid.c = c;
    return body;
}

Body make_sphere(double r) {
    if (r < 0) {
        fprintf(stderr, "make_sphere: invalid input\n");
        exit(1);
    }
    struct body_s body;
    body.tag = SPHERE;
    body.sphere.r = r;
    return body;
}

double volume(Body body) {
    switch (body.tag) {
        case CYLINDER:
            return M_PI * body.cylinder.r * body.cylinder.r * body.cylinder.h;
        case CUBOID:
            return body.cuboid.a * body.cuboid.b * body.cuboid.c;
        case SPHERE:
            return (4.0 / 3.0) * M_PI * body.sphere.r * body.sphere.r * body.sphere.r;
    }
    return 0;
}

void volume_test(void) {
    test_within_d(volume(make_sphere(2)), 4 /3.0 * M_PI * 2 * 2 * 2, 1e-6);
    test_within_d(volume(make_cuboid(2, 3, 4)), 2 * 3 * 4, 1e-6);
    test_within_d(volume(make_cylinder(3, 4)), 4 * M_PI * 3 * 3 , 1e-6);
}

int main(void) {
    volume_test();
    return 0;
}

