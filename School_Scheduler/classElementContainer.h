#pragma once
#include <vector>
#include "classElement.h"

using namespace std;

class ClassElementContainer {
private:
	const int classStart = 7; // Stores the value of the time the classes start in the timetable
	const int classFinish = 19; // Stores the value of the time the classes finish in the timetable
	vector<ClassElement*> classesArray;

public:
	bool isEmpty();
	void addElement(ClassElement* newMember);
};