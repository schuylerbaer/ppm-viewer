#include "ActionData.h"
#include "MenuData.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>

MenuData::MenuData(){}

void MenuData::addAction(const std::string& name, ActionFunctionType func, const std::string& description) {
	mCommands.push_back(name);
	mActionMap[name] = func;
	mDescriptionMap[name] = description;
}

const std::vector<std::string>& MenuData::getNames() const {
	return mCommands;
}

ActionFunctionType MenuData::getFunction(const std::string& name) {
	if((mActionMap.find(name)) != mActionMap.end()) {
		return mActionMap[name];
	} else {
		return 0;
	}
}

const std::string& MenuData::getDescription(const std::string& name) {
	if((mDescriptionMap.find(name)) != mDescriptionMap.end()) {
		return mDescriptionMap[name];
	} else {
		static std::string empty;
		return empty;
	}
}


