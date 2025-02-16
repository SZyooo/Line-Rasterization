#pragma once

template<typename T>
inline int sign(const T& v)
{
	if (v > 0) return 1;
	else if (v < 0) return -1;
	else return 0;
}