#include "numlist.h"

// Partitioning functions
// Serial partition
unsigned int NumList::partition(vector<int>& keys, unsigned int low, 
                                unsigned int high)
{ //using basic quicksort algorithm from CRSL book
    // Use the last element as the pivot
    int pivot = keys[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
	    if (keys[j] <= pivot) {
		    i++;
		    int temp = keys[i];
		    keys[i] = keys[j];
		    keys[j] = temp;
	    }
    }
    int temp = keys[i + 1];
    keys[i + 1] = keys[high];
    keys[high] = temp;
    return (i + 1);
    // TODO: Implement the serial partitioning method
}

// Parallel partition
unsigned int NumList:: partition_par(vector<int>& keys, unsigned int low,
                                     unsigned int high)
{
	//help from stackoverflow
    // Use the last element as the pivot
    int pivot = keys[high];
    int lt[high-low];
    int gt[high-low];
    int i;
    int j; //establish all the variables to be used later
    int lt_n = 0;
    int gt_n = 0;
#pragma omp parralel for  //parralle for loop
    {
    for (i = low; i < high; i++) {
	    if (keys[i] < keys[high]) { //use the three different arrays to store the keys
		    lt[lt_n++] = keys[i];
	    }else{
		    gt[gt_n++] = keys[i];
	    }
    }
    }
    for (i = 0; i < lt_n; i++) { //put the rearranged keys back into array half on one then half on another
	    keys[low + i] = lt[i];
    }
    keys[low + lt_n] = pivot;
#pragma omp parralel for
    {
    for (j = 0; j < gt_n; j++) {
	    keys[low + lt_n + j + 1] = gt[j];
    }
    }
    return low + lt_n;
}

    // TODO: Implement the parallel partitioning method
    // There should be two #pragmas to parallelize the loop
    // First loop is calculating the lt and gt arrays
    // Second is when the integers are copied to the correct position (i.e.,
    // left or right side of the pivot

// Actual qsort that recursively calls itself with particular partitioning
// strategy to sort the list
void NumList::qsort(vector<int>& keys, int low, int high, ImplType opt)
{
    if(low < high) {
        unsigned int pi;
        if(opt == serial) {
            pi = partition(keys, low, high);
        } else {
            pi = partition_par(keys, low, high);
        }
        qsort(keys, low, pi - 1, opt);
        qsort(keys, pi + 1, high, opt);
    }
}

// wrapper for calling qsort
void NumList::my_qsort(ImplType opt)
{
    /* Initiate the quick sort from this function */
    qsort(list, 0, list.size() - 1, opt);
}
// Default constructor
// This should "create" an empty list
NumList::NumList() {
    /* do nothing */
    /* you will have an empty vector */
}
// Contructor
// Pass in a vector and the partitioning strategy to use
NumList::NumList(vector<int> in, ImplType opt) {
    list = in;
    my_qsort(opt);
}
// Destructor
NumList::~NumList() {
    /* do nothing */
    /* vector will be cleaned up automatically by its destructor */
}
// Get the element at index
int NumList::get_elem(unsigned int index)
{
    return list[index];
}
// Print the list
void NumList::print(ostream& os)
{
    for(unsigned int i = 0; i < list.size(); i++) {
        os << i << ":\t" << list[i] << endl;
    }
}
