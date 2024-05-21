#include "inputContainer.h"

QList<QString> InputContainer::dataContainer;

InputContainer::InputContainer() {
	this->index = this->dataContainer.size();
}

void InputContainer::update() {
	this->index = this->dataContainer.size();
}

void InputContainer::push(const QString element) {
	this->dataContainer.append(element);
	this->index++;
}

QString InputContainer::pop() {
	if (dataContainer.isEmpty()) {
		return QString("");
	}
	this->index--;
	return this->dataContainer.at(this->index);
}

QString InputContainer::get_at_index(int index) const {
	return this->dataContainer.at(index);
}



void InputContainer::clean_container() {
	this->dataContainer.clear();
	this->index = 0;
}


bool InputContainer::empty() const {
	if (this->index == 0)
		return true;
	else
		return false;
}

int InputContainer::get_size() const {
	return this->index;
}