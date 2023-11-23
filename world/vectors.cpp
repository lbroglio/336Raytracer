#include "vectors.hpp"

Color& Color::operator=(Color&& c){
    r = c.r;
    g = c.g;
    b = c.b;

    return *this;
}

Color& Color::operator=(const Color& c){
    r = c.r;
    g = c.g;
    b = c.b;

    return *this;
}
