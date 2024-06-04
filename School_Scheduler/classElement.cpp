#include <classElement.h>

using namespace std;

ClassElement::ClassElement(const QString& classNameInput, const QString& classStartTimeInput, const QString& classTimeDurationInput, const QString& roomInput, const QString& instructorNameInput, const QString& dayOfTheWeekInput) {
	this->className = classNameInput;
	this->classStartTime = classStartTimeInput.toInt();
	this->classTimeDuration = classTimeDurationInput.toInt();
	this->room = roomInput;
	this->instructorName = instructorNameInput;
	this->dayOfTheWeek = dayOfTheWeekInput;
}