#ifndef ARRAYUTILS_H
#define ARRAYUTILS_H



//  Add to the end
//  - Assumes that we have a separate integer (size) indicating how
//     many elements are in the array
//  - and that the "true" size of the array is at least one larger 
//      than the current value of that counter
template <typename T>
void addToEnd (T* array, int& size, T value)
{
   array[size] = value;
   ++size;
}



// Add value into array[index], shifting all elements already in positions
//    index..size-1 up one, to make room.
//  - Assumes that we have a separate integer (size) indicating how
//     many elements are in the array
//  - and that the "true" size of the array is at least one larger 
//      than the current value of that counter

template <typename T>
void addElement (T* array, int& size, int index, T value)
{
  // Make room for the insertion
  int toBeMoved = size - 1;
  while (toBeMoved >= index) {
    array[toBeMoved+1] = array[toBeMoved];
    --toBeMoved;
  }
  // Insert the new value
  array[index] = value;
  ++size;
}


// Assume the elements of the array are already in order
// Find the position where value could be added to keep
//    everything in order, and insert it there.
// Return the position where it was inserted
//  - Assumes that we have a separate integer (size) indicating how
//     many elements are in the array
//  - and that the "true" size of the array is at least one larger 
//      than the current value of that counter

template <typename T>
int addInOrder (T* array, int& size, T value)
{
  // Make room for the insertion
  int toBeMoved = size - 1;
  while (toBeMoved >= 0 && value < array[toBeMoved]) {
    array[toBeMoved+1] = array[toBeMoved];
    --toBeMoved;
  }
  // Insert the new value
  array[toBeMoved+1] = value;
  ++size;
  return toBeMoved+1;
}


// Search an array for a given value, returning the index where 
//    found or -1 if not found.
template <typename T>
int seqSearch(const T list[], int listLength, T searchItem)
{
    int loc;

    for (loc = 0; loc < listLength; loc++)
        if (list[loc] == searchItem)
            return loc;

    return -1;
}


// Search an ordered array for a given value, returning the index where 
//    found or -1 if not found.
template <typename T>
int seqOrderedSearch(const T list[], int listLength, T searchItem)
{
    int loc = 0;

    while (loc < listLength && list[loc] < searchItem)
      {
       ++loc;
      }
    if (loc < listLength && list[loc] == searchItem)
       return loc;
    else
       return -1;
}


// Removes an element from the indicated position in the array, moving
// all elements in higher positions down one to fill in the gap.
template <typename T>
void removeElement (T* array, int& size, int index)
{
  int toBeMoved = index + 1;
  while (toBeMoved < size) {
    array[toBeMoved] = array[toBeMoved+1];
    ++toBeMoved;
  }
  --size;
}



// Search an ordered array for a given value, returning the index where 
//    found or -1 if not found.
template <typename T>
int binarySearch(const T list[], int listLength, T searchItem)
{
    int first = 0;
    int last = listLength - 1;
    int mid;

    bool found = false;

    while (first <= last && !found)
    {
        mid = (first + last) / 2;

        if (list[mid] == searchItem)
            found = true;
        else 
            if (searchItem < list[mid])
                last = mid - 1;
            else
                first = mid + 1;
    }

    if (found) 
        return mid;
    else
        return -1;
}





#endif
