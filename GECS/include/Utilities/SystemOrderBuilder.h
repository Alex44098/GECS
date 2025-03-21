#pragma once

#include "Facade.h"
#include "ISystem.h"

namespace GECS {
	namespace Util {

		// Function used for topological sort
		void DFSWithSort(type_id vertex,
			std::vector<bool>& used,
			const std::vector<std::vector<bool>>& graph,
			std::vector<type_id>& output);

		void DFSWithCompNum(type_id vertex,
			u64 compNum,
			std::vector<u64>& comp,
			const std::vector<std::vector<bool>>& graph);

		void DefineSystemGroups(std::vector<std::vector<type_id>>& systemGroups, const std::vector<std::vector<bool>>& systemGraph);

		void DefineGroupPriority(std::vector<std::vector<type_id>>& systemGroups,
			std::vector<u8>& groupPriority,
			std::unordered_map<type_id, ISystem*>& systemsTable);

		void BuildSystemOrder(std::vector<type_id>& systemsOrder,
			std::unordered_map<type_id, ISystem*>& systemsTable,
			const std::vector<std::vector<bool>>& systemGraph);
	}
}