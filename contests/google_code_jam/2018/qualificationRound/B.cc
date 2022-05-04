#include <bits/stdc++.h>
using namespace std;

// dbg
#define DBG_MODE
int64_t DBG_COUNT = 0;
void DBG_OUT() {
    cerr << endl;
    DBG_COUNT++;
}
template <typename Front, typename... Back>
void DBG_OUT(Front K, Back... T) {
    cerr << ' ' << K;
    DBG_OUT(T...);
}
#ifdef DBG_MODE
template <typename T_Ints>
void testList(T_Ints List) {
    cerr << '#' << DBG_COUNT << " __LIST_ARGS__: (";
    DBG_COUNT++;
    for (int i = 0; i < List.size(); i++) {
        cout << List[i] << (i < List.size() - 1 ? ", " : ")\n");
    }
}
#define testArgs(...)                                                     \
    cerr << '#' << DBG_COUNT << " __VA_ARGS__ (" << #__VA_ARGS__ << "):", \
        DBG_OUT(__VA_ARGS__)
#else
template <typename T_Ints>
void testList(T_Ints List) {
    return;
}
#define testArgs(...)
#endif

// MERGE SORT
template <typename T_List>
void merge(T_List &array, int leftIndex, int middleIndex, int rightIndex) {
    // size of left and right sub-arrays
    int nl = middleIndex - leftIndex + 1, nr = rightIndex - middleIndex;
    int leftArray[nl], rightArray[nr];

    // fill left and right sub-arrays
    for (int i = 0; i < nl; i++) leftArray[i] = array[leftIndex + i];

    for (int i = 0; i < nr; i++) rightArray[i] = array[middleIndex + 1 + i];

    int i = 0, j = 0;
    int k = leftIndex;

    // merge temp arrays to real array
    while (i < nl && j < nr) {
        if (leftArray[i] <= rightArray[j]) {
            array[k] = leftArray[i];
            i++;
        } else {
            array[k] = rightArray[j];
            j++;
        }
        k++;
    }

    while (i < nl) {  // extra element in left array
        array[k] = leftArray[i];
        i++;
        k++;
    }

    while (j < nr) {  // extra element in right array
        array[k] = rightArray[j];
        j++;
        k++;
    }
}

template <typename T_List>
void mergeSort(T_List &array, int leftIndex, int rightIndex) {
    if (leftIndex < rightIndex) {
        int middleOfArray = leftIndex + (rightIndex - leftIndex) / 2;

        // Sort first and second arrays
        mergeSort(array, leftIndex, middleOfArray);
        mergeSort(array, middleOfArray + 1, rightIndex);
        merge(array, leftIndex, middleOfArray, rightIndex);
    }
}

void runCase(int tc) {
    int N;
    cin >> N;
    vector<int> even, odd;

    for (int i = 0; i < N; i++) {
        int k;
        if (i % 2 == 0) {
            cin >> k;
            even.push_back(k);
        } else {
            cin >> k;
            odd.push_back(k);
        }
    }

    mergeSort(even, 0, even.size() - 1);
    mergeSort(odd, 0, odd.size() - 1);

    vector<int> a;
    for (int i = 0; i < (N % 2 == 0 ? N / 2 : (N - 1) / 2); i++) {
        a.push_back(even[i]);
        a.push_back(odd[i]);
    }

    if (N % 2 != 0) a.push_back(even[even.size() - 1]);

    for (int i = 0; i < N - 1; i++) {
        if (a[i] > a[i + 1]) {
            cout << "Case #" << tc << ": " << i << '\n';
            return;
        }
    }

    cout << "Case #" << tc << ": OK" << '\n';
}

int main() {
    int test_cases;
    cin >> test_cases;

    for (int tc = 1; tc <= test_cases; tc++) {
        runCase(tc);
        cerr << flush;
    }
}