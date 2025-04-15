
# Exercises on vectors

## Insert and Erase:

- Extend your vector implementation to include:
    - `insert(index, element)`: Insert an element at a specific index.
    - `erase(index)`: Remove the element at a specific index.
- Analyze the time complexity of these operations.
- Consider the following program to test your implementations. Be careful, it just tests some functionalities and is not intended to be extensive.
```c++
Vector<int> myVector;

// Test push_back
myVector.push_back(10);
myVector.push_back(20);
myVector.push_back(30);

cout << myVector.size() << endl; // Expected: 3
cout << myVector.capacity() << endl; // Expected: Initial capacity, e.g., 4 or 8

// Test pop_back
myVector.pop_back();
cout << myVector.size() << endl; // Expected: 2

// Test at with valid and invalid indices
cout << myVector.at(0) << endl; // Expected: 10
cout << myVector.at(1) << endl; // Expected: 20

// Border case: Accessing an out-of-bounds index
cout << myVector.at(2) << endl; // Should crash!

// Border case: pop_back on empty vector
Vector<int> emptyVector;
emptyVector.pop_back(); // should crash!
```
## Removing Duplicates:

- Write a function that takes a vector of integers and removes all duplicate elements, preserving the original order of the remaining elements.
- Analyze the time complexity of your solution.
- Consider the following non-extensive program to test your implementation:
```c++
Vector<int> numbers = {1, 2, 2, 3, 4, 4, 5};
Vector<int> uniqueNumbers = removeDuplicates(numbers);

uniqueNumbers.print(); // Expected: {1, 2, 3, 4, 5}

Vector<int> numbers2 = {1,1,1,1,1,1};
Vector<int> uniqueNumbers2 = removeDuplicates(numbers2);
uniqueNumbers2.print(); // Expected: {1}

Vector<int> numbers3 = {};
Vector<int> uniqueNumbers3 = removeDuplicates(numbers3);
uniqueNumbers3.print(); // Expected: {}

Vector<int> numbers4 = {1};
Vector<int> uniqueNumbers4 = removeDuplicates(numbers4);
uniqueNumbers4.print(); // Expected: {1}
```
## Dynamic Array Resizing Analysis:

- Write a program that pushes a large amount of random numbers into your vector implementation. Display the size and capacity of the vector after every 1000 insertions. Graph the results, and analyze the growth of the capacity. Perform this experiment with the growth policies considered in class.
## Implementing a Stack Using a Vector:

- We have not discussed the Stack data structure. However, you are very curious and have a lot of resources at your disposal to study it. After you have done that present an implementation of it using a vector.
## Merge sorted vectors

- Given two sorted vectors, write the method `merge` to merge them into a single sorted vector.
- Consider the following non extensive program to test your implementation.
```c++
Vector<int> vector1 = {1, 3, 5};
Vector<int> vector2 = {2, 4, 6};
Vector<int> mergedVector = mergeSortedVectors(vector1, vector2);

mergedVector.print(); // Expected: {1, 2, 3, 4, 5, 6}

Vector<int> vector3 = {1, 2, 3};
Vector<int> vector4 = {};
Vector<int> mergedVector2 = mergeSortedVectors(vector3, vector4);
mergedVector2.print(); // Expected: {1, 2, 3}

Vector<int> vector5 = {};
Vector<int> vector6 = {4,5,6};
Vector<int> mergedVector3 = mergeSortedVectors(vector5, vector6);
mergedVector3.print(); // Expected: {4, 5, 6}

Vector<int> vector7 = {1,1,1,1};
Vector<int> vector8 = {1,1,1,1};
Vector<int> mergedVector4 = mergeSortedVectors(vector7, vector8);
mergedVector4.print(); // Expected: {1,1,1,1,1,1,1,1}
```