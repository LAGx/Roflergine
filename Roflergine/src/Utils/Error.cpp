#include "Error.h"



ErrorList::ErrorList() {
}


ErrorList::ErrorList(std::initializer_list<Error> init){
	add(init);
}


ErrorList::ErrorList(const ErrorList& init) 
	: core(init.core){
}


ErrorList::ErrorList(ErrorList&& init)
	: core(std::move(init.core)){
}


void ErrorList::add(std::initializer_list<Error> element) {
	for (const auto& error : element) {
		if (error)
			core.push_back(error);
	}
}


void ErrorList::add(Error&& element) {
	if(element)
		core.emplace_back(element);
}


void ErrorList::add(const Error& element) {
	if(element)
		core.push_back(element);
}


void ErrorList::add(ErrorList&& element) {
	core.insert(core.end(), element.core.begin(), element.core.end());
}


void ErrorList::add(const ErrorList& element) {
	core.insert(core.end(), element.core.begin(), element.core.end());
}


void ErrorList::clear() {
	core.clear();
}


std::string ErrorList::toString() const {
	std::string result;

	for (const auto& error : core) 
		result += " -- ERRROR -- \n" + error->toString() + "\n";

	return result.empty() ? "empty" : result;
}


bool ErrorList::containsError() const {
	return !core.empty();
}


ErrorList::operator bool() const {
	return containsError();
}


ErrorList& ErrorList::operator=(const ErrorList& another) {
	core = another.core;
	return *this;
}


ErrorList& ErrorList::operator=(ErrorList&& another) {
	core = std::move(another.core);
	return *this;
}


ErrorList& ErrorList::operator=(std::initializer_list<Error> another) {
	clear();
	add(another);
	return *this;
}


ErrorList ErrorList::operator+(ErrorList&& second) const {
	ErrorList result(*this);
	result.add(second);
	return result;
}


ErrorList ErrorList::operator+(std::initializer_list<Error> second) const {
	ErrorList result(*this);
	result.add(second);
	return result;
}


ErrorList ErrorList::operator+(const ErrorList& second) const {
	ErrorList result(*this);
	result.add(second);
	return result;
}


ErrorList ErrorList::operator+(const Error& second) const{
	ErrorList result(*this);
	result.add(second);
	return result;
}


ErrorList ErrorList::operator+(Error&& second) const{
	ErrorList result(*this);
	result.add(second);
	return result;
}


void ErrorList::operator+=(Error&& another){
	add(another);
}


void ErrorList::operator+=(const Error& another){
	add(another);
}


void ErrorList::operator+=(ErrorList&& another) {
	add(another);
}



void ErrorList::operator+=(std::initializer_list<Error> another) {
	add(another);
}



void ErrorList::operator+=(const ErrorList& another) {
	add(another);
}



std::vector<Error>::const_iterator ErrorList::begin() const {
	return core.begin();
}


std::vector<Error>::const_iterator ErrorList::end() const {
	return core.end();
}


ErrorList operator+(Error&& first, Error&& second){
	return ErrorList({ first, second });
}


ErrorList operator+(const Error& first, Error&& second){
	return ErrorList({first, second});
}


ErrorList operator+(Error&& first, const Error& second){
	return ErrorList({ first, second });
}


ErrorList operator+(const Error& first, const Error& second){
	return ErrorList({ first, second });
}


ErrorList operator+(Error&& error, const ErrorList& lst){
	ErrorList result(lst);
	result.add(error);
	return result;
}


ErrorList operator+(Error&& error, ErrorList&& lst){
	ErrorList result(lst);
	result.add(error);
	return result;
}


ErrorList operator+(const Error& error, ErrorList&& lst){
	ErrorList result(lst);
	result.add(error);
	return result;
}


ErrorList operator+(const Error& error, const ErrorList& lst){
	ErrorList result(lst);
	result.add(error);
	return result;
}

std::string ErrorDescription::toString() const
{
	return std::string() + 
		"Error code: `" + std::to_string(static_cast<int>(code)) + "`.\n" + 
		"Error message: " + message;
}
