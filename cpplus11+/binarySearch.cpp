#include <iostream>
#include <vector>

using namespace std;

// Pass vector as value
void print(vector<int> nums);

int main() {
  int nums[] = {16,2,77,29};
  std::vector<int> nums_int (nums, nums + sizeof(nums) / sizeof(int) );
  print(nums_int);
}

void print(vector<int> nums) {
  // Range based for loop
  for (auto it: nums) {
    cout << ' ' << it;
  }
  cout << endl;
}