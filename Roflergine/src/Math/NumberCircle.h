#pragma once

template<class T, int N>
class NumberCircle {
public:

	NumberCircle() {
		for (int i = 0; i < N; ++i)
			circle[i] = 0;
	}

	NumberCircle(T init) {
		for (int i = 0; i < N; ++i)
			circle[i] = init;
	}

	void setNext(const T& value) {
		movePointerNext();
		circle[pointer] = value;
	}

	T getMean() const {
		T sum = 0;

		for (int i = 0; i < N; ++i)
			sum += circle[i];

		return sum / N;
	}

private:

	void movePointerNext() {
		++pointer;

		if (pointer == N)
			pointer = 0;
	}

	T circle[N];
	int pointer = 0;
};