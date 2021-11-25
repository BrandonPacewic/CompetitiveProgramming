//MERGE SORT O(N log N)
template<typename T_List>
void merge(T_List &array, int leftIndex, int middleIndex, int rightIndex) {
   
   //size of left and right sub-arrays
   int nl = middleIndex - leftIndex + 1, nr = rightIndex - middleIndex;
   int leftArray[nl], rightArray[nr];

   //fill left and right sub-arrays
   for (int i = 0; i < nl; i++)
      leftArray[i] = array[leftIndex + i];

   for (int i = 0; i < nr; i++)
      rightArray[i] = array[middleIndex + 1 + i];

   int i = 0, j = 0; 
   int k = leftIndex;
   
   //merge temp arrays to real array
   while (i < nl && j < nr) {
        if(leftArray[i] <= rightArray[j]) {
            array[k] = leftArray[i];
            i++;
        } else {
            array[k] = rightArray[j];
            j++;
        }
        k++;
   }
   
    while(i < nl) {       //extra element in left array
        array[k] = leftArray[i];
        i++; 
        k++;
    }
   
    while(j < nr) {     //extra element in right array
        array[k] = rightArray[j];
        j++; 
        k++;
    }
}

template<typename T_List>
void mergeSort(T_List &array, int leftIndex, int rightIndex) {
   if (leftIndex < rightIndex) {
      int middleOfArray = leftIndex + (rightIndex - leftIndex) / 2;
      
      // Sort first and second arrays
      mergeSort(array, leftIndex, middleOfArray);
      mergeSort(array, middleOfArray + 1, rightIndex);
      merge(array, leftIndex, middleOfArray, rightIndex);
   }
}
