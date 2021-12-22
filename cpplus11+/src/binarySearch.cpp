#include <iostream>
#include <vector>
#include <random>
#include <sstream>
#include <algorithm>
#include <assert.h>
#include <chrono>

using namespace std;

// Pass vector as value
void print(const vector<int>& nums);

// Create random integer within a range
int rand_int(int min, int max);

vector<int> build_nums_int(int size, int min, int max);

int binarySearch(vector<int> nums, int target);

int main() {
  char buffer [50];  
  vector<int> nums = build_nums_int(5, 1, 10);
  int target = 1;

  print(nums);
  
  binarySearch(nums, target) > 0 ? sprintf(buffer, "found: %d", target) : sprintf(buffer, "not found: %d", target);
  cout << buffer << endl;
}

// Pass unmodifiable array by reference to avoid calling the copy constructor
void print(const vector<int>& nums) {
  // Range based for loop
  for (auto it: nums) {
    cout << ' ' << it;
  }
  cout << endl;
}

// Return a random integer value from an inclusive range of [min, max].
int rand_int(int min, int max) {
  // Construct a trivial random generator engine from a time-based seed
  // Static seed and generator are initialized only once
  static unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  static std::default_random_engine generator (seed);

  std::uniform_int_distribution<int> distribution(min, max);
  int num = distribution(generator);
  return num;
}

// Return a random generated number list from a known data range.s
// Cannot return reference of local variables. Can only return a copy
// if using the generator pattern.
vector<int> build_nums_int(int size, int min, int max) {
  assert(size > 0);
  assert(min > 0);
  assert(max > 0);
  assert(min < max);

  // ostringstream has an internal buffer and support different data types
  ostringstream message;
  vector<int> nums;

  for ( auto i = 0; i < size ; i++) {
    nums.push_back(rand_int(min, max));
  }

  sort(nums.begin(), nums.end());
  return nums;
} 

int binarySearch(vector<int> nums, int target) {
  return -1;
}
