#include <classElement.h>

using namespace std;

ClassElement::ClassElement(const QString& classNameInput, const QString& classStartTimeInput, const QString& classTimeDurationInput, const QString& roomInput, const QString& instructorNameInput, const QString& dayOfTheWeekInput, const QString& classTypeInput) {
	this->className = classNameInput;
	this->classType = classTypeInput;

	// Parse class start time from string to integer index
	QStringList startTimeParts = classStartTimeInput.split(":");
	int hour = startTimeParts[0].toInt();
	int minute = startTimeParts[1].toInt();
	this->classStartTime = (hour - 7) * 4 + (minute / 15);

	this->classTimeDuration = classTimeDurationInput.toInt();
	this->room = roomInput;
	this->instructorName = instructorNameInput;

	if (dayOfTheWeekInput == "Monday") {
		this->dayOfTheWeek = 0;
	}
	else if (dayOfTheWeekInput == "Tuesday") {
		this->dayOfTheWeek = 1;
	}
	else if (dayOfTheWeekInput == "Wednesday") {
		this->dayOfTheWeek = 2;
	}
	else if (dayOfTheWeekInput == "Thursday") {
		this->dayOfTheWeek = 3;
	}
	else if (dayOfTheWeekInput == "Friday") {
		this->dayOfTheWeek = 4;
	}
	else {
		// Should never execute, I put it in to avoid a compiler warning
		this->dayOfTheWeek = -1;
	}
}