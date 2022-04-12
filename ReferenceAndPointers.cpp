//training reference and pointer
#include<iostream>
#include<vector>
#include<algorithm>
using std::vector;
using std::sort;
using std::cout;

void AddOne(int* j)
{
    // Dereference the pointer and increment the int being pointed to.
    (*j)++;
}


int main(){

    int i = 5;
    int* pointer_to_i = &i;
    
    // Print the memory addresses of i and j
    cout << "The value of the variable i is                     : " << i << "\n";
    cout << "The address of i is:          " << &i << "\n";
    cout << "The variable pointer_to_i is: " << pointer_to_i << "\n";
    cout << "The value of the variable pointed to by pointer_to_i is: " << *pointer_to_i << "\n";
   
    i = 7;
    cout << "The new value of the variable i is                     : " << i << "\n";
    cout << "The address of i is:          " << &i << "\n";
    cout << "The value of the variable pointed to by pointer_to_i is: " << *pointer_to_i << "\n";
    cout << "The variable pointer_to_i is: " << pointer_to_i << "\n";

    // Declare a pointer to i:
    int* pi = &i;
    AddOne(pi);
    cout << "The value of i is now: " << i << "\n";
     //memo
    // int* xx = &yy;   //& address off,   int*, address for int type
    // cout <<value where xx is pointing to is << *xx << "\n”    //*xx,  the value of from the address at xx   dereferencing
    vector<int> v {1, 2, 3};
    vector<int> *pointer_to_v = &v;
    for (int a: v) {
        cout << a << "\n";
    }
    cout << "The first element of v is: " << (*pointer_to_v)[0] << "\n";

}