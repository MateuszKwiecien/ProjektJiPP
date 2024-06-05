#pragma once
#include <QString>

using namespace std;

class ClassElement {
private:
	QString className;
	int classStartTime;
	int classTimeDuration;
	QString room;
	QString instructorName;
	QString dayOfTheWeek;

public:
	ClassElement(const QString& classNameInput, const QString& classStartTimeInput, const QString& classTimeDurationInput, const QString& roomInput, const QString& instructorNameInput, const QString& dayOfTheWeekInput);
};