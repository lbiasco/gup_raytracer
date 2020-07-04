#ifndef UTILITIES_MATHS_H_
#define UTILITIES_MATHS_H_

template <typename T> int 
Sign(T val) {
    return (T(0) < val) - (val < T(0));
}

inline double
Max(double x0, double x1);

inline double
Max(double x0, double x1) {
	return ((x0 > x1) ? x0 : x1);
}

#endif  // UTILITIES_MATHS_H_
