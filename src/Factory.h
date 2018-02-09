#pragma once

#include <unordered_map>
#include <functional>
#include "Instruction.h"



class Factory {
public:
	using creatorFunction = std::function<Instruction*(const InstructionData&) >;


	static Factory* getInstance() {
		static Factory f;
		return &f;
	}


	Instruction* create(const std::string& id, const InstructionData& idata) {
		return creators[id](idata);
	}


	bool registerFunction(const std::string &id, creatorFunction creator) {
		creators.emplace(std::make_pair(id, creator));
		return true;
	}


private:
	std::unordered_map<std::string, creatorFunction> creators;
};

