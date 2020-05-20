#pragma once
#include <vector>
#include <chrono>
#include <ctime>
#include <ratio>
#include <type_traits>
#include <thread> 

typedef char i8;
typedef unsigned char u8;
typedef short i16;
typedef unsigned short u16;
typedef int i32;
typedef unsigned int u32;
typedef long long i64;
typedef unsigned long long u64;
typedef float f32;
typedef double f64;



#define _out_
#define _in_

#define VECTOR_SIZE_IN_BYTES(x) x.size() * sizeof(decltype(x)::value_type)

template<class T>
struct enable_if_type_is {

	using integral = typename std::enable_if<
		std::is_same<T, i8>::value ||
		std::is_same<T, u8>::value ||
		std::is_same<T, i16>::value ||
		std::is_same<T, u16>::value ||
		std::is_same<T, i32>::value ||
		std::is_same<T, u32>::value ||
		std::is_same<T, i64>::value ||
		std::is_same<T, u64>::value ||
		std::is_same<T, f64>::value ||
		std::is_same<T, f32>::value,
		int
	>;

	using integer = typename std::enable_if<
		std::is_same<T, i8>::value ||
		std::is_same<T, u8>::value ||
		std::is_same<T, i16>::value ||
		std::is_same<T, u16>::value ||
		std::is_same<T, i32>::value ||
		std::is_same<T, u32>::value ||
		std::is_same<T, i64>::value ||
		std::is_same<T, u64>::value,
		int
	>;

	using floating = typename std::enable_if<
		std::is_same<T, f64>::value ||
		std::is_same<T, f32>::value,
		int
	>;
};

class DeltaTimeValue;

std::chrono::time_point<std::chrono::steady_clock> GetTimeNow();
DeltaTimeValue GetDeltaToNow(const std::chrono::time_point<std::chrono::steady_clock>& past);
DeltaTimeValue GetDeltaTime(const std::chrono::time_point<std::chrono::steady_clock>& future, const std::chrono::time_point<std::chrono::steady_clock>& past);
void SleepThread(const DeltaTimeValue& delta);