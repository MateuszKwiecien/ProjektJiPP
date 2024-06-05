#pragma once
#include <QString>

using namespace std;

class ClassElement {
public:
	QString className;
	int classStartTime;
	int classTimeDuration;
	QString room;
	QString instructorName;
	QString dayOfTheWeek;

	ClassElement(const QString& classNameInput, const QString& classStartTimeInput, const QString& classTimeDurationInput, const QString& roomInput, const QString& instructorNameInput, const QString& dayOfTheWeekInput);
};