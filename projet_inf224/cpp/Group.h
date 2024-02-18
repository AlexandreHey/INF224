#ifndef GROUP_H
#define GROUP_H

#include <list>

#include "Multimedia.h"

class Group : public std::list<DataPtr> {
private:
	// Attribut
	const std::string groupName;

public: 
	// Constructors
	Group() : std::list<DataPtr>() {}
	Group(std::string groupName) : std::list<DataPtr>(), groupName(groupName) { };

	// Getter
	std::string const getGroupName() const { return groupName; };

	void print(std::ostream& os) const {
		std::cout << "Group: [";
		for (DataPtr data : *this) {
			std::cout << " | "; data->print(os);
		}
		std::cout << " ]";
	}
};

#endif // GROUP_H