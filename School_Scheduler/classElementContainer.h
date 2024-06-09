#pragma once
#include <vector>
#include <QTableWidget>
#include "classElement.h"

using namespace std;

class ClassElementContainer {
private:
	vector<ClassElement*> classesArray;

public:
	bool isEmpty();
	void addElement(ClassElement* newMember);
	void debugPrint();
	void refreshTable(QTableWidget* table);
	void undo();
	void deleteElement(const QString& delItemName, const QString& delItemType);
	void saveContainer(const QString& fileName);
};