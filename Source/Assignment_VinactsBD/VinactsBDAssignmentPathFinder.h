#pragma once

#include "PathNode.h"
#include "Containers/Array.h"

class ASSIGNMENT_VINACTSBD_API VinactsBDAssignmentPathFinder 
{
public:	
	static TArray<APathNode*> FindPath(const APathNode* startNode, const APathNode* goalNode);
	
private:
	static TArray<APathNode*> ReconstructPath(const TMap<APathNode*, APathNode*>& cameFrom, const APathNode* current);
	static APathNode* GetNodeWithLowestFScore(const TArray<APathNode*>& openSet, const TMap<APathNode*, float>& fScore);
 	static float HeuristicCostEstimate(const APathNode& from, const APathNode& to);
	static float CostToMove(const APathNode& from, const APathNode& to);
};
