# CSES-Solutions
This repository contains the solutions of [cses](https://cses.fi/problemset/list/) problemset in C++. There are also Java solutions available for Introductory section.  
Each solution file also contains the explanations, prerequisites, useful tutorials and references.

## C++ STL quick references  
  
  
### Pair
There is an already implemented class for pairs in C++ which can be declared as `pair<T, T> mypair`. For example, you can have a pair of integers `pair<int, int> mypair`, or doubles `pair<double, double> mypair` or something mixed `pair<int, string> mypair`. The elements can then be accessed with `mypair.first` or `mypair.second`.  
Nice thing about `pair` is that when you want to sort an array of pairs, you can simply do `sort(array, array+size)` insted of defining your own comparator for ordering. By default, `pair<T, T>` sorts by the first value, and then by the second.  
```C++
pair<double, int> mypair = make_pair(4.20, 69);
cout << mypair.first << " " << mypair.second << endl;
pair<int, int> arr[10];
for(int i=5; i>=0; i--){
  arr[i].first = i%2;
  arr[i].second = i;
  cout << arr[i].first << " " << arr[i].second << endl;
}
sort(arr, arr+6);
for(int i=0; i<6; i++){
  cout << arr[i].first << " " << arr[i].second << endl;
}
```
The output is
```
4.2 69

1 5
0 4
1 3
0 2
1 1
0 0

0 0
0 2
0 4
1 1
1 3
1 5
```

### Vector
C++ vector is just like Arraylists in Java but better, because you can access the `i'th` element as you would with an array `myvector[i]`. Vectors are declared as `vector<T> myvector` where `T` is any defined type.  
You can push an element in the vector with `myvector.push_back(element)` and pop with `myvector.pop_back()`. The size can be accessed with `myvector.size()` and the vector can be cleared with `myvector.clear()`.  
You can initialize vectors to any size and any element with `vector<T> myvector(n, initial_element)`. For example, `vector<int> myvector(n, 0)` will initialize a vector of `n` zeros.  
It is also possible to do 'foreach' loops on vectors:
```C++
vector<int> myvector(n, 1);
for(int i : myvector)
  cout << i << " ";
```
This outputs `n` ones onto standard output.

### Stack  
Stack has a really nice implementation in STL which can be accessed with `stack<T> mystack`. You can get the topmost element of the stack with `mystack.top()` and pop it with `mystack.pop()`. Pushing to the top of the stack is as aeasy as `mystack.push(element)`.  
The size is accessed with `mystack.size()` and can be checked for emptiness `mystack.empty()` (returns true if it is).  
For example:
```C++
stack<pair<int, int>> mystack;
mystack.push({1, 3});
mystack.push({(int)-1e9, 0});
mystack.push({6, 4});
cout << mystack.top().first << " " << mystack.top().second << endl;
mystack.pop();
cout << mystack.top().first << " " << mystack.top().second << endl;
```
This outputs
```
6 4
-1000000000 0
```

### Queue
Queue can be declared as `queue<T> myqueue`. You can push into the queue by `myqueue.push(element)`, get the first element in the queue by `myqueue.front()` and pop it with `myqueue.pop()`.  
For example:
```C++
queue<pair<int, int>> myqueue;
myqueue.push({1, 3});
myqueue.push({(int)-1e9, 0});
myqueue.push({6, 4});
cout << myqueue.front().first << " " << myqueue.front().second << endl;
myqueue.pop();
cout << myqueue.front().first << " " << myqueue.front().second << endl;
```
This outputs
```
1 3
-1000000000 0
```

# Map
