#pragma once

#include <iostream>

using namespace std;

class clsSearchingAlgorithm
{
public:

	static int linearSearch(int arr[], int n, int key)
	{

		for (int i = 0; i < n; i++)
		{
			if (arr[i] == key)
				return i;
		}
		return-1;
	}

	static int binarySearch(int arr[], int l, int r, int x)
	{
		while (l <= r) {
			int m = l + (r - l) / 2;

			// Check if x is present at mid
			if (arr[m] == x)
				return m;

			// If x greater, ignore left half
			if (arr[m] < x)
				l = m + 1;

			// If x is smaller, ignore right half
			else
				r = m - 1;
		}

		// If we reach here, then element was not present
		return -1;
	}

	static int binarySearchRec(int arr[], int l, int h, int element)
	{
		if (h >= l) {
			int mid = (l + h) / 2;

			if (arr[mid] == element)
				return mid;

			if (arr[mid] > element)
				return binarySearch(arr, l, mid - 1, element);

			return binarySearch(arr, mid + 1, h, element);
		}
		return -1;
	}

	//------------------------------------------------------------------


    static void LinearSearch(int arr[], int size, int target) {
        /*
        Linear Search:
        Searches each element in a list sequentially until the target is found or the list ends.
        Works on unsorted or sorted data.
        Time Complexity: O(n)
        */
        for (int i = 0; i < size; i++) {
            if (arr[i] == target) {
                cout << "Element found at index " << i << endl;
                return;
            }
        }
        cout << "Element not found." << endl;
    }

    static int binarySearch(int arr[], int size, int target) {
        /*
        Binary Search:
        Searches in a sorted array by repeatedly dividing the search space in half.
        Requires sorted data.
        Time Complexity: O(log n)
        */
        int low = 0, high = size - 1;
        while (low <= high) {
            int mid = (low + high) / 2;
            if (arr[mid] == target) return mid;
            else if (arr[mid] < target) low = mid + 1;
            else high = mid - 1;
        }
        return -1;
    }

    static void JumpSearch(int arr[], int size, int target) {
        /*
        Jump Search:
        Searches in a sorted array by jumping fixed steps (usually sqrt(n)),
        then performing linear search within the block.
        Time Complexity: O(√n)
        */
        int step = sqrt(size);
        int prev = 0;
        while (arr[min(step, size) - 1] < target) {
            prev = step;
            step += sqrt(size);
            if (prev >= size) {
                cout << "Element not found." << endl;
                return;
            }
        }
    }

    static void InterpolationSearch(int arr[], int size, int target) {
        /*
        Interpolation Search:
        Estimates the probable position of the target using interpolation formula,
        then searches accordingly.
        Best used for uniformly distributed sorted data.
        Time Complexity: O(log log n) best, O(n) worst.
        */
            int low = 0, high = size - 1;
            while (low <= high && target >= arr[low] && target <= arr[high]) {
                int pos = low + ((target - arr[low]) * (high - low)) / (arr[high] - arr[low]);
                if (arr[pos] == target) {
                    cout << "Element found at index " << pos << endl;
                    return;
                }
                if (arr[pos] < target)
                    low = pos + 1;
                else
                    high = pos - 1;
            }
            cout << "Element not found." << endl;
    }

    static void ExponentialSearch(int arr[], int size, int target) {
        /*
        Exponential Search:
        Expands the search range exponentially until the target is likely within range,
        then performs binary search.
        Useful for unbounded or large sorted arrays.
        Time Complexity: O(log n)
        */
            if (arr[0] == target) {
                cout << "Element found at index 0" << endl;
                return;
            }
            int i = 1;
            while (i < size && arr[i] <= target)
                i *= 2;
            int left = i / 2, right = min(i, size - 1);
            while (left <= right) {
                int mid = (left + right) / 2;
                if (arr[mid] == target) {
                    cout << "Element found at index " << mid << endl;
                    return;
                }
                else if (arr[mid] < target)
                    left = mid + 1;
                else
                    right = mid - 1;
            }
            cout << "Element not found." << endl;

    }
    template<typename T>
    static int LinearSearch(T arr[], int size, T target) {
        for (int i = 0; i < size; i++) {
            if (arr[i] == target)
                return i;
        }
        return -1;
    }

    template<typename T>
    static int BinarySearch(T arr[], int size, T target) {
        int low = 0, high = size - 1;
        while (low <= high) {
            int mid = (low + high) / 2;
            if (arr[mid] == target) return mid;
            else if (arr[mid] < target) low = mid + 1;
            else high = mid - 1;
        }
        return -1;
    }

    template<typename T>
    static int BinarySearchRec(T arr[], int low, int high, T target) {
        if (high >= low) {
            int mid = (low + high) / 2;
            if (arr[mid] == target) return mid;
            if (arr[mid] > target)
                return BinarySearchRec(arr, low, mid - 1, target);
            return BinarySearchRec(arr, mid + 1, high, target);
        }
        return -1;
    }

    template<typename T>
    static int JumpSearch(T arr[], int size, T target) {
        int step = sqrt(size);
        int prev = 0;
        while (arr[min(step, size) - 1] < target) {
            prev = step;
            step += sqrt(size);
            if (prev >= size)
                return -1;
        }
        for (int i = prev; i < min(step, size); i++) {
            if (arr[i] == target)
                return i;
        }
        return -1;
    }

    template<typename T>
    static int InterpolationSearch(T arr[], int size, T target) {
        int low = 0, high = size - 1;
        while (low <= high && target >= arr[low] && target <= arr[high]) {
            int pos = low + ((target - arr[low]) * (high - low)) / (arr[high] - arr[low]);
            if (arr[pos] == target)
                return pos;
            if (arr[pos] < target)
                low = pos + 1;
            else
                high = pos - 1;
        }
        return -1;
    }

    template<typename T>
    static int ExponentialSearch(T arr[], int size, T target) {
        if (arr[0] == target)
            return 0;
        int i = 1;
        while (i < size && arr[i] <= target)
            i *= 2;
        return BinarySearch(arr + i / 2, min(i, size - i / 2), target);
    }

    static void DFS_Tree() {
        /*
        Depth-First Search (DFS - Tree):
        Explores as deep as possible down a branch before backtracking.
        Typically implemented using recursion or a stack.
        Used in trees and graphs.
        Time Complexity: O(n)
        */
    }

    static void BFS_Tree() {
        /*
        Breadth-First Search (BFS - Tree):
        Explores all nodes at the current depth level before moving to the next.
        Typically implemented using a queue.
        Used in trees and graphs.
        Time Complexity: O(n)
        */
    }

    static void BST_Search() {
        /*
        Binary Search Tree (BST) Search:
        Navigates left or right in a binary search tree depending on key comparison.
        Time Complexity: O(log n) average, O(n) worst (unbalanced tree).
        */
    }

    static void AVL_Tree_Search() {
        /*
        AVL Tree Search:
        Searches within an AVL Tree — a self-balancing binary search tree.
        Guarantees O(log n) search time.
        */
    }

    static void RedBlack_Tree_Search() {
        /*
        Red-Black Tree Search:
        Performs search on a balanced binary search tree using color-based balancing rules.
        Guarantees O(log n) search time.
        */
    }

    static void DFS_Graph() {
        /*
        Depth-First Search (Graph):
        Explores nodes and paths deeply in a graph before backtracking.
        Can detect cycles, connected components, etc.
        Time Complexity: O(V + E)
        */
    }

    static void BFS_Graph() {
        /*
        Breadth-First Search (Graph):
        Explores all neighbors level by level.
        Useful for finding shortest path in unweighted graphs.
        Time Complexity: O(V + E)
        */
    }

    static void Dijkstra() {
        /*
        Dijkstra's Algorithm:
        Finds the shortest path from a source node to all other nodes in a graph with non-negative weights.
        Time Complexity: O(V^2) or O(E + V log V) with priority queue.
        */


    }

    static void A_Star() {
        /*
        A* Search Algorithm:
        Combines Dijkstra's algorithm with heuristics to guide the search.
        Used in pathfinding and AI.
        */
    }

    static void BellmanFord() {
        /*
        Bellman-Ford Algorithm:
        Calculates shortest paths from a source, even with negative edge weights.
        Can detect negative cycles.
        Time Complexity: O(V * E)
        */
    }

    static void FloydWarshall() {
        /*
        Floyd-Warshall Algorithm:
        Computes shortest paths between all pairs of nodes in a weighted graph.
        Time Complexity: O(V^3)
        */
    }

    static void GreedyBestFirstSearch() {
        /*
        Greedy Best-First Search:
        Uses a heuristic to explore paths that seem best at each step.
        Does not guarantee optimal path.
        */
    }

    static void HashSearch() {
        /*
        Hash-Based Search:
        Uses a hash function to directly map keys to values.
        Average Time Complexity: O(1)
        */
    }

    static void TernarySearch() {
        /*
        Ternary Search:
        A divide-and-conquer search method that splits the range into three parts.
        Used on unimodal functions.
        Time Complexity: O(log n)
        */
    }

    static void FibonacciSearch() {
        /*
        Fibonacci Search:
        Uses Fibonacci numbers to divide the search range.
        Works on sorted arrays.
        Time Complexity: O(log n)
        */
    }

    static void SubsequenceSearch() {
        /*
        Subsequence Search:
        Searches whether a smaller sequence appears in order inside a larger sequence (not necessarily consecutive).
        */
    }

    static void KMP_Search() {
        /*
        Knuth-Morris-Pratt (KMP) Algorithm:
        Efficient string-matching algorithm that avoids re-checking matched characters.
        Time Complexity: O(n + m)
        */
    }

    static void RabinKarp_Search() {
        /*
        Rabin-Karp Algorithm:
        Uses hashing to search for multiple pattern matches in a string.
        Time Complexity: O(n + m) average, O(nm) worst.
        */
    }

    static void BoyerMoore_Search() {
        /*
        Boyer-Moore Algorithm:
        Efficient string search algorithm that skips sections of the text.
        Performs very well on long texts.
        */
    }

    static void TrieSearch() {
        /*
        Trie Search:
        Uses a prefix tree (trie) to search for words or prefixes efficiently.
        Time Complexity: O(L), where L is the length of the word.
        */
    }

    static void SuffixTreeSearch() {
        /*
        Suffix Tree / Suffix Array Search:
        Specialized data structures for efficient substring search and string processing.
        Used in bioinformatics, text editors, and data compression.
        */
    }


};

