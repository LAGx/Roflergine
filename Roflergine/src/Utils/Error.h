#pragma once
#include <optional>
#include <string>
#include <vector>



enum class ErrorCode {
	None = 0,
	General = 1,
	FileOpen = 2,
	FileName = 3,
	Compile = 4,
	MemoryUsage,
	Init,
	FileParse,
	Nullptr
};


struct ErrorDescription {
	std::string message;
	ErrorCode code = ErrorCode::General;

	std::string toString() const;
};


typedef std::optional<ErrorDescription> Error;


class ErrorList {
public:

	ErrorList();
	ErrorList(std::initializer_list<Error>);
	ErrorList(const ErrorList&);
	ErrorList(ErrorList&&);

	void add(std::initializer_list<Error>);
	void add(Error&&);
	void add(const Error&);
	void add(ErrorList&&);
	void add(const ErrorList&);

	void clear();

	std::string toString() const;

	bool containsError() const;
	operator bool() const;

	ErrorList& operator=(const ErrorList&);
	ErrorList& operator=(ErrorList&&);
	ErrorList& operator=(std::initializer_list<Error>);


	ErrorList operator+(ErrorList&&) const;
	ErrorList operator+(std::initializer_list<Error>) const;
	ErrorList operator+(const ErrorList&) const;
	ErrorList operator+(const Error&) const;
	ErrorList operator+(Error&&) const;

	void operator+=(Error&&);
	void operator+=(const Error&);
	void operator+=(ErrorList&&);
	void operator+=(std::initializer_list<Error>);
	void operator+=(const ErrorList&);

	std::vector<Error>::const_iterator begin() const;
	std::vector<Error>::const_iterator end() const;

private:
	std::vector<Error> core;
};


ErrorList operator+(Error&&, Error&&);
ErrorList operator+(const Error&, Error&&);
ErrorList operator+(Error&&, const Error&);
ErrorList operator+(const Error&, const Error&);

ErrorList operator+(Error&&, const ErrorList&);
ErrorList operator+(Error&&, ErrorList&&);
ErrorList operator+(const Error&, ErrorList&&);
ErrorList operator+(const Error&, const ErrorList&);

