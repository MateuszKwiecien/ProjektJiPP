#include "classElementContainer.h"
#include <QDebug>
#include <QFile>
#include <QTextStream>

bool ClassElementContainer::isEmpty() { return classesArray.empty(); } // Checks if the container is empty

void ClassElementContainer::addElement(ClassElement* newMember) {
	if (newMember->classStartTime < 0 || newMember->classStartTime + newMember->classTimeDuration * 3 > 52) {
		// TODO: Implement exception handling
		return;
	}

	for (const auto& elem : classesArray) {
		if (elem->classStartTime + elem->classTimeDuration * 3 < newMember->classStartTime) {
			// Checks for a collision between newMemeber and existing members of the container
			// TODO: Implement exception handling in the future
			return;
		}
		if (newMember->classStartTime + newMember->classTimeDuration * 3 < elem->classStartTime) {
			return;
		}
	}

	classesArray.push_back(newMember);
}

void ClassElementContainer::debugPrint() {
	for (const auto& elem : classesArray) {
		qDebug() << "Type: " << elem->classType;
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
		QTableWidgetItem* item = new QTableWidgetItem(elem->classType + "\n" + elem->className + " - " + elem->room + "\n" + elem->instructorName);
		item->setTextAlignment(Qt::AlignCenter);
		if (elem->classType == "LECTURE") {
			item->setBackground(QColor(Qt::red));
		}
		else if (elem->classType == "CLASSICAL") {
			item->setBackground(QColor(Qt::yellow));
		}
		else {
			item->setBackground(QColor(173, 216, 230));
		}
		table->setSpan(elem->classStartTime, elem->dayOfTheWeek, 3 * elem->classTimeDuration, 1);
		table->setItem(elem->classStartTime, elem->dayOfTheWeek, item);
	}
}

void ClassElementContainer::undo() {
	if (!classesArray.empty()) {
		delete classesArray.back();
		classesArray.pop_back();
	}
}

void ClassElementContainer::deleteElement(const QString& delItemName, const QString& delItemType){
	for (auto it = classesArray.begin(); it != classesArray.end(); ++it) {
		if ((*it)->className == delItemName && (*it)->classType == delItemType) {
			delete (*it);
			classesArray.erase(it);
		}
	}
}

void ClassElementContainer::saveContainer(const QString& fileName){
	QFile file(fileName);
	
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
		qDebug() << "This happens";
		return;
	}
		

	QTextStream out(&file);
	for (const auto& elem : classesArray) {
		qDebug() << "This happens 2";
		out << elem->className << "\n";
		out << elem->classStartTime << "\n";
		out << elem->classTimeDuration << "\n";
		out << elem->classType << "\n";
		out << elem->dayOfTheWeek << "\n";
		out << elem->instructorName << "\n";
		out << elem->room << "\n";
	}
	file.close();
}
