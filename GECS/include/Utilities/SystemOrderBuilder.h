#pragma once

#include "Facade.h"
#include "ISystem.h"

namespace GECS {
	namespace Util {

		// Function used for topological sort
		void DFSWithSort(type_id vertex, std::vector<bool>& used, const std::vector<std::vector<bool>>& graph, std::vector<type_id>& output) {
			used[vertex] = true;

			for (u64 i = 0; i < used.size(); i++)
				if (graph[i][vertex] == true && !used[i])
					DFSWithSort(i, used, graph, output);

			output.push_back(vertex);
		}

		void DFSWithCompNum(type_id vertex, u64 compNum, std::vector<u64>& comp, const std::vector<std::vector<bool>>& graph) {
			comp[vertex] = compNum;

			for (u64 i = 0; i < comp.size(); i++)
				if (comp[i] == 0)
					DFSWithCompNum(i, compNum, comp, graph);
		}

		void DefineSystemGroups(std::vector<std::vector<type_id>>& systemGroups, const std::vector<std::vector<bool>>& systemGraph) {
			u64 groupNum = 1, numSystems = systemGraph.size();
			std::vector<u64> comp(numSystems, 0);

			// define connectivity components in graph
			for (u64 i = 0; i < numSystems; i++)
				if (comp[i] == 0) {
					DFSWithCompNum(i, groupNum, comp, systemGraph);
					groupNum++;
				}

			// create vector of groups
			for (u64 i = 1; i <= groupNum; i++) {
				std::vector<type_id> group;
				for (u64 j = 0; j < numSystems; j++) 
					if (comp[j] == i)
						group.push_back(j);
				systemGroups.push_back(group);
			}
		}

		void DefineGroupPriority(std::vector<std::vector<type_id>>& systemGroups, std::vector<u8>& groupPriority, std::unordered_map<type_id, ISystem*>& systemsTable) {
			for (std::vector<type_id> group : systemGroups) {
				u8 maxGroupPriority = LOWEST_SYSTEM_PRIORITY;
				for (type_id systemId : group) {
					u8 sysPriority = systemsTable[systemId] == nullptr ? LOWEST_SYSTEM_PRIORITY : systemsTable[systemId]->m_priority;
					maxGroupPriority = sysPriority > maxGroupPriority ? sysPriority : maxGroupPriority;
				}
				groupPriority.push_back(maxGroupPriority);
			}
		}

		void BuildSystemOrder(std::vector<type_id>& systemsOrder, std::unordered_map<type_id, ISystem*>& systemsTable, const std::vector<std::vector<bool>>& systemGraph) {
			std::vector<std::vector<type_id>> systemGroups;
			std::vector<u8> groupPriority;

			DefineSystemGroups(systemGroups, systemGraph);
			DefineGroupPriority(systemGroups, groupPriority, systemsTable);

			std::vector<bool> used(systemGraph.size(), false);

			// sorted map with multiple entries (systems group) with the same priority
			// contains pairs of priority and systems' ID
			std::multimap<u8, std::vector<type_id>> sortedSystemsOrder;

			for (int i = 0; i < systemGroups.size(); i++) {
				std::vector<type_id> group = systemGroups[i];
				std::vector<type_id> orderedGroup;

				// topological sorting of systems group
				for (int j = 0; j < group.size(); j++)
					if (used[group[j]] == false)
						DFSWithSort(group[j], used, systemGraph, orderedGroup);

				std::reverse(orderedGroup.begin(), orderedGroup.end());

				// reverse systems' priority for correct sorting (form high priority to low)
				sortedSystemsOrder.insert(std::pair<u8, std::vector<type_id>>(HIGHEST_SYSTEM_PRIORITY - groupPriority[i], orderedGroup));
			}

			systemsOrder.clear();
			for (auto group : sortedSystemsOrder) {
				for (auto systemId : group.second) {
					systemsOrder.push_back(systemId);
				}
			}
		}
	}
}