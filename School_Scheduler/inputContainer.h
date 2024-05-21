#ifndef __input_container_h__
#define __input_container_h__

#include <QList>
#include <QString>
#include <iostream>

class InputContainer {
	private:
		static QList<QString> dataContainer;
		int index = 0;
	public:
		InputContainer();
		void update();
		void push(const QString element);
		QString pop();
		QString get_at_index(int index) const;
		void clean_container();
		bool empty() const;

		int get_size() const;
};


#endif // !__input_container_h__