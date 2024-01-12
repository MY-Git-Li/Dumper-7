#pragma once
#include <unordered_set>
#include <unordered_map>
#include <iostream>
#include <format>
#include <functional>

#include "Enums.h"


class DependencyManager
{
public:
	using IncludeFunctionType = std::function<void(int32 Index)>;

private:
	struct IndexDependencyInfo
	{
		/* Counter incremented every time this element is hit during iteration, **if** the counter is less than the CurrentIterationIndex */
		mutable uint8 IterationHitCounter = 0x0;

		/* Indices of Objects required by this Object */
		std::unordered_set<int32> DependencyIndices;
	};

private:
	/* List of Objects and their Dependencies */
	std::unordered_map<int32, IndexDependencyInfo> AllDependencies;

	/* Count to track how often the Dependency-List was iterated. Allows for up to 255 iterations of this list. */
	mutable uint8 CurrentIterationHitCount = 0x0;

public:
	DependencyManager() = default;

	DependencyManager(int32 ObjectToTrack);

private:
	void VisitIndexAndDependencies(int32 Index, IncludeFunctionType Callback) const;

public:
	void SetExists(const int32 DepedantIdx);

	void AddDependency(const int32 DepedantIdx, int32 DependencyIndex);

	void SetDependencies(const int32 DepedantIdx, std::unordered_set<int32>&& Dependencies);

	size_t GetNumEntries() const;

	void VisitIndexAndDependenciesWithCallback(int32 Index, IncludeFunctionType Callback) const;
	void VisitAllNodesWithCallback(IncludeFunctionType Callback) const;

public:
	const auto DEBUG_DependencyMap() const
	{
		return AllDependencies;
	}
};
