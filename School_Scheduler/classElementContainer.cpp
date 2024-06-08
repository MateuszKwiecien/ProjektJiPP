#include "classElementContainer.h"
#include <QDebug>

bool ClassElementContainer::isEmpty() { return classesArray.empty(); } // Checks if the container is empty

void ClassElementContainer::addElement(ClassElement* newMember) {
	if (newMember->classStartTime < 0 || newMember->classStartTime + newMember->classTimeDuration * 3 > 52) {
		// TODO: Implement exception handling
		return;
	}

	for (const auto& elem : classesArray) {
		if (elem->classStartTime + elem->classTimeDuration * 3 <= newMember->classStartTime) {
			// Checks for a collision between newMemeber and existing members of the container
			// TODO: Implement exception handling in the future
			return;
		}
		if (newMember->classStartTime + newMember->classTimeDuration * 3 <= elem->classStartTime) {
			return;
		}
	}

	classesArray.push_back(newMember);
}

void ClassElementContainer::debugPrint() {
	for (const auto& elem : classesArray) {
		qDebug() << "Name: " << elem->className;
		qDebug() << "Start time: " << elem->classStartTime;
		qDebug() << "Duration: " << elem->classTimeDuration;
		qDebug() << "Day: " << elem->dayOfTheWeek;
		qDebug() << "Instructor: " << elem->instructorName;
		qDebug() << "Room: " << elem->room;
	}
}

void ClassElementContainer::refreshTable(QTableWidget* table) {
	for (const auto& elem : classesArray) {
		QTableWidgetItem* item = new QTableWidgetItem(elem->className + "\n" + elem->instructorName + "\n" + elem->room);
		item->setTextAlignment(Qt::AlignCenter);
		table->setSpan(elem->classStartTime, elem->dayOfTheWeek, 3 * elem->classTimeDuration, 1);
		table->setItem(elem->classStartTime, elem->dayOfTheWeek, item);
	}
}