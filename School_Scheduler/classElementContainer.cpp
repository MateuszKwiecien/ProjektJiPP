#include "classElementContainer.h"

bool ClassElementContainer::isEmpty() { return classesArray.empty(); } // Checks if the container is empty

void ClassElementContainer::addElement(ClassElement* newMember) {
	if (newMember->classStartTime < classStart || newMember->classStartTime + newMember->classTimeDuration > classFinish) {
		// If new element's hours are outside of the schedule newMember is not added into the container
		// TODO: Implement exception handling in the future
		return;
	}

	if (classesArray.empty()) {	// Early return in case classesArray has no existing members, therefore no conflicts
		classesArray.push_back(newMember);
		return;
	}

	for (const auto& elem : classesArray) {
		if (elem->classStartTime + elem->classTimeDuration <= newMember->classStartTime) {
			// Checks for a collision between newMemeber and existing members of the container
			// TODO: Implement exception handling in the future
			return;
		}
	}

	classesArray.push_back(newMember);
}