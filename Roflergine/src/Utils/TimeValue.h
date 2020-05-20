#pragma once
#include "System.h"

class DeltaTimeValue {
public:
	DeltaTimeValue() {
	}

	static DeltaTimeValue Zero() {
		return DeltaTimeValue(0);
	}

	template<class T>
	static DeltaTimeValue Seconds(T value) {
		DeltaTimeValue delta;
		delta.SetSeconds<T>(value);
		return delta;
	}

	template<class T>
	static DeltaTimeValue Miliseconds(T value) {
		DeltaTimeValue delta;
		delta.SetMiliseconds<T>(value);
		return delta;
	}

	template<class T>
	static DeltaTimeValue Microseconds(T value) {
		DeltaTimeValue delta;
		delta.SetMicroseconds<T>(value);
		return delta;
	}

	// Seconds region 
	template<class T, typename enable_if_type_is<T>::integer::type = 0>
	void SetSeconds(T value) {
		microseconds = static_cast<i64>(value) * i64(1000000);
	}

	template<class T, typename enable_if_type_is<T>::floating::type = 0>
	void SetSeconds(T value) {
		T intpart;
		T fractpart = modf32f64<T>(value, &intpart);

		i64 intMicroseconds = i64(intpart) * i64(1000000);
		i64 fractMicroseconds = fractpart * 1000000;

		microseconds = intMicroseconds + fractMicroseconds;
	}

	template<class T, typename enable_if_type_is<T>::integer::type = 0>
	T GetSeconds() const{
		return static_cast<T>(microseconds / 1000000);
	}

	template<class T, typename enable_if_type_is<T>::floating::type = 0>
	T GetSeconds() const{
		i64 intPart = microseconds / 1000000;
		i64 fractPart = microseconds % 1000000;
		T floatFractPart = T(fractPart) / 1000000.0;

		return (T)intPart + floatFractPart;
	}

	// Miliseconds region
	template<class T, typename enable_if_type_is<T>::integer::type = 0>
	void SetMiliseconds(T value) {
		microseconds = static_cast<i64>(value) * i64(1000);
	}

	template<class T, typename enable_if_type_is<T>::floating::type = 0>
	void SetMiliseconds(T value) {
		T intpart;
		T fractpart = modf32f64<T>(value, &intpart);

		i64 intMicroseconds = i64(intpart) * i64(1000);
		i64 fractMicroseconds = fractpart * 1000;

		microseconds = intMicroseconds + fractMicroseconds;
	}

	template<class T, typename enable_if_type_is<T>::integer::type = 0>
	T GetMiliseconds() const{
		return static_cast<T>(microseconds / 1000);
	}

	template<class T, typename enable_if_type_is<T>::floating::type = 0>
	T GetMiliseconds() const{
		i64 intPart = microseconds / 1000;
		i64 fractPart = microseconds % 1000;
		T floatFractPart = T(fractPart) / 1000.0;

		return (T)intPart + floatFractPart;
	}

	// Microseconds region
	template<class T>
	void SetMicroseconds(T value) {
		microseconds = static_cast<i64>(value);
	}

	template<class T>
	T GetMicroseconds() const{
		return static_cast<T>(microseconds);
	}

	// Operator region
	DeltaTimeValue operator+(const DeltaTimeValue& a) const{
		return DeltaTimeValue(this->microseconds + a.microseconds);
	}

	DeltaTimeValue operator-(const DeltaTimeValue& a) const {
		return DeltaTimeValue(this->microseconds - a.microseconds);
	}

	void operator+=(const DeltaTimeValue& a){
		this->microseconds += a.microseconds;
	}

	void operator-=(const DeltaTimeValue& a) {
		this->microseconds -= a.microseconds;
	}

	template<class T>
	DeltaTimeValue operator/(T value) const{
		return DeltaTimeValue(this->microseconds/value);
	}

	template<class T>
	DeltaTimeValue operator*(T value) const {
		return DeltaTimeValue(this->microseconds * value);
	}

	bool operator>(const DeltaTimeValue& a) const {
		return this->microseconds > a.microseconds;
	}

	bool operator<(const DeltaTimeValue& a) const {
		return this->microseconds < a.microseconds;
	}

	bool operator>=(const DeltaTimeValue& a) const {
		return this->microseconds >= a.microseconds;
	}

	bool operator<=(const DeltaTimeValue& a) const {
		return this->microseconds <= a.microseconds;
	}

	bool operator==(const DeltaTimeValue& a) const {
		return this->microseconds == a.microseconds;
	}

	bool operator!=(const DeltaTimeValue& a) const {
		return this->microseconds != a.microseconds;
	}

private:

	template<class T>
	T modf32f64(T x, T* y);

	template<>
	f32 modf32f64<f32>(f32 x, f32* y) {
		return modff(x, y);
	}

	template<>
	f64 modf32f64<f64>(f64 x, f64* y) {
		return modf(x, y);
	}

	DeltaTimeValue(i64 mc): microseconds(mc) {
	}

private:
	i64 microseconds = 0;
};