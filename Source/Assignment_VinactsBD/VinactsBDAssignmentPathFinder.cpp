#include "VinactsBDAssignmentPathFinder.h"
#include "Containers/Array.h"


/// <summary>
/// Return a new path between tow node
/// </summary>
/// <param name="startNode"></param>
/// <param name="goalNode"></param>
/// <returns></returns>
TArray<APathNode*> VinactsBDAssignmentPathFinder::FindPath(const APathNode* startNode, const APathNode* goalNode)
{
	if(startNode == nullptr || goalNode == nullptr || startNode == goalNode)
		return TArray<APathNode*>();

	TArray<APathNode*>* openSet = new TArray<APathNode*>();
	TArray<APathNode*>* closedSet = new TArray<APathNode*>();

	TMap<APathNode*, APathNode*>* cameFrom = new TMap<APathNode*, APathNode*>();
	TMap<APathNode*, float>* gScore = new TMap<APathNode*, float>();
	TMap<APathNode*, float>* fScore = new TMap<APathNode*, float>();

	APathNode* current = const_cast<APathNode*>(startNode);
	openSet->Add(current);
	gScore->Add(current, 0.0f);
	fScore->Add(current, HeuristicCostEstimate(*startNode, *goalNode));

	while (openSet->Num() > 0)
	{
		current = GetNodeWithLowestFScore(*openSet, *fScore);
		if (current == goalNode)
			return ReconstructPath(*cameFrom, current);

		openSet->Remove(current);
		closedSet->Add(current);

		for (APathNode* neighbor : current->neighbors)
		{
			if (closedSet->Contains(neighbor))
				continue;

			float tentativeGScore = *gScore->Find(current) + VinactsBDAssignmentPathFinder::CostToMove(*current, *neighbor);
			if (!openSet->Contains(neighbor) || tentativeGScore < *gScore->Find(neighbor))
			{
				cameFrom->Add(neighbor, current);
				gScore->Add(neighbor, tentativeGScore);
				fScore->Add(neighbor, *gScore->Find(neighbor) + VinactsBDAssignmentPathFinder::HeuristicCostEstimate(*neighbor, *goalNode));

				if (!openSet->Contains(neighbor))
					openSet->Add(neighbor);
			}
		}
	}

	return TArray<APathNode*>();
}


/// <summary>
/// Constructing the path by backtracking.
/// </summary>
/// <param name="cameFrom">collection of path node as a chain from start to current path node</param>
/// <param name="current">Current path node</param>
/// <returns></returns>
TArray<APathNode*> VinactsBDAssignmentPathFinder::ReconstructPath(const TMap<APathNode*, APathNode*>& cameFrom, const APathNode* current)
{
	TArray<APathNode*> path = TArray<APathNode*>();
	while (cameFrom.Contains(current))
	{
		path.Insert(const_cast<APathNode*>(current), 0);
		current = cameFrom.FindRef(current);
	}
	path.Insert(const_cast<APathNode*>(current), 0);
	return path;
}

/// <summary>
/// Returning a Path node pointer which path node has lowest heuristic cost
/// </summary>
/// <param name="openSet"></param>
/// <param name="fScore"></param>
/// <returns></returns>
APathNode* VinactsBDAssignmentPathFinder::GetNodeWithLowestFScore(const TArray<APathNode*>& openSet, const TMap<APathNode*, float>& fScore)
{
	if (openSet.Num() == 0)
		return nullptr;

	APathNode* lowestNode = openSet.Top();
	for (APathNode* node : openSet)
		if (fScore.Find(node) < fScore.Find(lowestNode))
			lowestNode = node;

	return lowestNode;
}


/// <summary>
/// Calculate the heoristic cost value between two path node
/// </summary>
/// <param name="from">From path node</param>
/// <param name="to">To path node</param>
/// <returns></returns>
float VinactsBDAssignmentPathFinder::HeuristicCostEstimate(const APathNode& from, const APathNode& to)
{
	return FVector::Distance(from.GetActorLocation(), to.GetActorLocation());
}

/// <summary>
/// Calculate the movement cost value between two path node
/// </summary>
/// <param name="from">From path node</param>
/// <param name="to">To path node</param>
/// <returns></returns>
float VinactsBDAssignmentPathFinder::CostToMove(const APathNode& from, const APathNode& to)
{
	return VinactsBDAssignmentPathFinder::HeuristicCostEstimate(from, to);
}

