///////////////////////////////////////////////////////////////////////////////
// project2.hh
//
// The three algorithms specified in the project 1 requirements
// document, plus helper functions.
//
///////////////////////////////////////////////////////////////////////////////

#include "project2.hh"

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
#include <vector>




using namespace std;


//-----------------------------------------------------------------------------
// Randomize the order of all items in the list
//-----------------------------------------------------------------------------
void randomize_list(string_vector & strings) {
	
	int vectorsize = strings.size();
	
	for (int i = 0; i <= vectorsize; i++)
	{
	
		int r = rand() % strings.size();
		swap(strings[i], strings[r]);
	}
  return;
}

//-----------------------------------------------------------------------------
void merge(string_vector & strings, size_t start, size_t mid, size_t end) {

	
	std::string left[1000];

	for (int l = 0; l < mid - start; l++)
	{
		left[l] = strings[start + l];
	}
	left[mid - start] = numeric_limits<int>::max();

	std::string right[1000];

	for (int r = 0; r < end - mid; r++)
	{
		right[r] = strings[mid + r];
	}
	right[end - mid + 1] = numeric_limits<int>::max();
	
	int i = 0;
	int j = 0;

	for (int k = start; k <= end; k++)
	{
		if (left[i] < right[j])
		{
			strings[k] = left[i];
			i++;
		}
		else
		{
			strings[k] = right[j];
			j++;
		}
	}
	
  return;
}


//-----------------------------------------------------------------------------
// Sort the given list using the merge sort algorithm.
// This is a recursive method which splits the list into two
// parts, recursively calls itself on the two parts and then merges 
// the two parts together using the merge() method.
//-----------------------------------------------------------------------------
void mergesort(string_vector & strings, size_t start, size_t end) {
	if (start < end)
	{
		int middle = int((end + start) / 2);
		mergesort(strings, start, middle);
		mergesort(strings, middle + 1, end);
		merge(strings, start, middle + 1, end);
	}
  return;
}

//-----------------------------------------------------------------------------
// Implementation of the Hoare Partition.
// This partition uses the first element of the list as a partition
// and divides the list into less than and greater than the pivot value
// It returns the index of the final position of the pivot value.
//-----------------------------------------------------------------------------
int hoare_partition(string_vector & strings, int start, int end) {

	std::string pivot = strings[start];
	int i = start - 1;
	int j = end + 1;
	
	while (true)
	{
		do
		{
			i++;
		} while (strings[i] < pivot);

		do
		{
			j--;
		} while (strings[j] > pivot);

		if (i >= j)
		{
			return j;
		}

		swap(strings[i], strings[j]);
	}

  return 0;
}

//-----------------------------------------------------------------------------
// Sort the given list using the quicksort algorithm.
// This is a recursive method which splits the list into two
// parts, recursively calls itself on the two parts and then merges 
// the two parts together using the merge() method.
//-----------------------------------------------------------------------------
void quicksort(string_vector & strings, int start, int end) {


	if (start < end)
	{
		int s = hoare_partition(strings, start, end);

		quicksort(strings, start, s - 1);
		quicksort(strings, s + 1, end);
	}
  return;
}


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// ALREADY IMPLEMENTED 
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Load words from the file at the given path. The words vector is
// cleared, and then each word from the file is added to the
// vector. Returns true on success or fale on I/O error.
//-----------------------------------------------------------------------------
bool load_words(string_vector& words, const std::string& path) 
{
  //std::cout << "Loading words from [" << path << "]" << std::endl;
  words.clear();
  std::ifstream ifs(path.c_str());
  if (!ifs.is_open() || !ifs.good()) {
    //cout << "Failed to open [" << path << "]" << std::endl;
    return false;
  }
  int countWordsLoaded = 0;
  while (!ifs.eof()) {
    std::string lineBuffer;
    std::getline(ifs, lineBuffer);
    if (ifs.eof()) {
      break;
    }
    words.push_back(lineBuffer);
    countWordsLoaded++;
  }
  //std::cout << "Loaded " << countWordsLoaded << " words from [" << path << "]" << std::endl;;
  return true;
}

//-----------------------------------------------------------------------------
// Sort the given list using the merge sort algorithm.
// This method is simply a helper to make the initial 
// call the recursive mergesort() method below that requires
// first and last indexes for sorting range
//-----------------------------------------------------------------------------
void mergesort(string_vector & strings) {
  if (strings.size() == 0) {
    return;
  }
  mergesort(strings, 0, strings.size() - 1);
  return;
}

//-----------------------------------------------------------------------------
// Sort the given list using the quicksort algorithm.
// This method is simply a helper to make the initial 
// call the recursive mergesort() method below that requires
// first and last indexes for sorting range
//-----------------------------------------------------------------------------
void quicksort(string_vector & strings) {
  if (strings.size() == 0) {
    return;
  }
  quicksort(strings, 0, strings.size() - 1);
  return;
}

