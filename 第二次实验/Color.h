//
// Created by 81406 on 2020/6/9.
//

#ifndef CG_COLOR_H
#define CG_COLOR_H

class Color {
public:
    double r_, g_, b_;

    Color(double r = 0, double g = 0, double b = 0) : r_{r}, g_{g}, b_{b} {};

    Color operator+(const Color &c)   { return {r_ + c.r_, g_ + c.g_, b_ + c.b_}; };
    Color operator-(const Color &c)   { return {r_ - c.r_, g_ - c.g_, b_ - c.b_}; };

    Color operator*(const Color &c) const  { return {r_ * c.r_, g_ * c.g_, b_ * c.b_}; };

    Color operator*(const double c) const  { return {r_ * c, g_ * c, b_ * c}; };

    Color operator==(const Color &c) const  { return r_ == c.r_ && g_ == c.g_ && b_ == c.b_; };

    void operator+=(const Color &c)   {
        r_ += c.r_;
        g_ += c.g_;
        b_ += c.b_;
    };
};

#endif //CG_COLOR_H
