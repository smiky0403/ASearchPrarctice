//POC in A* Search Lecture
#include<iostream>
#include<vector>
#include<algorithm>
using std::vector;
using std::sort;

bool Compare1(vector<int> a, vector<int> b){
  int f1 = a[0] + a[1]; // f1 = g1 + h1
  int f2 = b[0] + b[1]; // f2 = g2 + h2
  return f1 > f2; 
}

void CellSort1(vector<vector<int>> *v) {
  sort(v->begin(), v->end(), Compare1);
}


int sum(const std::vector<int> &v)
{
    int sum = 0;
    for(int i : v)
        sum += i;
   // v.push_back(5);
    return sum;
}



int main(){
vector<vector<int>> open = {{7, 8}, {1, 2}, {3,4}, {5,6}};
   
  CellSort1(&open);
  std::cout << open.size()<<"\n";
  vector<int> x = open.back();
  std::cout << x[0]<<"\n";

  open.pop_back();
  
  x = open.back();
  std::cout << x[0]<<"\n";

   int i; 
  std::cout << "Enter an integer value for i: "; 
  std::cin >> i; const int j = i * 2; 
  // "j can only be evaluated at run time." // "But I promise not to change it after it is initialized."

  constexpr int k = 3;  // "k, in contrast, can be evaluated at compile time."

  std::cout << "j = " << j << "\n";
  std::cout << "k = " << k << "\n";

  std::vector<int> v {0, 1, 2, 3, 4};
  std::cout << sum(v) << "\n";

};

