#include <cstdio>
#include <cstdlib>

#include "sort.h"


int ivector_length(int* v, int n)
{
  int sum;

  sum = 0;
  for (int i = 0; i < n; i++)
    sum += (v[i] < 0) ? -v[i] : v[i];

  return sum;
}

/*
 * insertion sort
 */

void insertion_sort(int** A, int n, int l, int r)
{
  int i;
  int* key;

  for (int j = l+1; j <= r; j++)
    {
      key = A[j];
      i = j - 1;

      while ((i >= l) && (ivector_length(A[i], n) > ivector_length(key, n)))
        {
	  A[i+1] = A[i];
	  i = i - 1;
	}

      A[i+1] = key;
    }
}

/*
 * improved insertion sort with precomputed vector length
 * l is for left index and r is right index of the integer vector array to be sorted
 * n is the dimension of integer vector array
 * vl is an array of precomputed vector length
 */

void insertion_sort_im(int** A, int n, int l, int r, int* vl)
{
  int i;
  int* key;
  int keyLen;


  for (int j = l+1; j <= r; j++)
    {
      key = A[j];
      keyLen = vl[j];
      i = j - 1;
      while ((i >= l) && (vl[i] > keyLen))
        {
	  A[i+1] = A[i];
    vl[i+1]= vl[i];
	  i = i - 1;
	}

      A[i+1] = key;
      vl[i+1] = keyLen;

    }
}

/** Merges two subarrays of A[].
 First subarray is A[l..m]
 Second subarray is A[m+1..r]
 **/

void merge(int** A, int n, int l, int m, int r, int* vl){
int n1 = m-l+1;
int n2 = r-m;
 int x, y, k;

/* create temp arrays
* L[] contains left subarray of array A
* R[] contains right subarray of array A
* VL[] contains left subarray of array vl
* VR[] contains right subarray of array vl
*/

int** L = new int*[n1];
int** R = new int*[n2];
int* VL = new int[n1];
int* VR = new int[n2];

 /* Copy data to temp arrays */
for(int i=0; i<n1; i++){
  L[i] = new int[n];
  L[i] = A[l+i];
 VL[i] = vl[l+i];
}
for(int j=0; j<n2; j++){
  R[j] = new int[n];
  R[j] = A[m+1+j];
  VR[j] = vl[m+1+j];
}

 /* Merge the temp arrays back into A[l..r] & vl[l..r]*/
  x = 0; // Initial index of first subarray
  y = 0; // Initial index of second subarray
  k = l; // Initial index of merged subarray
   while (x < n1 && y < n2)  {
       if (VL[x] <= VR[y]) {
         A[k] = L[x];
         vl[k] = VL[x];
         x++;
       }
       else {
         A[k] = R[y];
         vl[k] = VR[y];
         y++;
       }
       k++;
   }

   /* Copy the remaining elements of L[] & VL[], if there
      are any */
   while (x < n1) {
     A[k] = L[x];
     vl[k] = VL[x];
     x++;
     k++;
   }

   /* Copy the remaining elements of R[] & VR[], if there
      are any */
   while (y < n2)    {
     A[k] = R[y];
     vl[k] = VR[y];
     y++;
     k++;
   }

}

/*
 * merge sort with precomputed vector length
 * l is for left index and r is right index of the
   sub-array of integer vector array to be sorted
 * n is the dimension of integer vector array
* vl is an array of precomputed vector length
 */

void merge_sort(int** A, int n, int l, int r, int* vl)
{
  int mid;
  if(l < r){
    mid = l+(r-l)/2;  // Same as (l+r)/2, but avoids overflow for large l and r values
    merge_sort(A, n, l, mid, vl); //sort first half
    merge_sort(A, n, mid+1, r, vl);// sort second half
    merge(A, n, l, mid, r, vl);
  }
}


/*
 * Simple function to check that our sorting algorithm did work
 * -> problem, if we find position, where the (i-1)-th element is
 *    greater than the i-th element.
 */
bool check_sorted(int** A, int n, int l, int r)
{
  for (int i = l+1; i <= r; i++)
    if (ivector_length(A[i-1], n) > ivector_length(A[i], n))
      return false;
  return true;
}


/*
 * generate sorted/reverse/random arrays of type hw1type
 */
int** create_ivector(int n, int m)
{
  int** iv_array;

  iv_array = new int*[m];
  for (int i = 0; i < m; i++)
    iv_array[i] = new int[n];

  return iv_array;
}

void remove_ivector(int** iv_array, int m)
{
  for (int i = 0; i < m; i++)
    delete[] iv_array[i];
  delete[] iv_array;
}
void remove_ivectoreLengthArr(int* array)
{
  delete[] array;
}

int** create_sorted_ivector(int n, int m)
{
  int** iv_array;

  iv_array = create_ivector(n, m);
  for (int i = 0; i < m; i++)
    for (int j = 0; j < n; j++)
      iv_array[i][j] = (i+j)/n;

  return iv_array;
}

int** create_reverse_sorted_ivector(int n, int m)
{
  int** iv_array;

  iv_array = create_ivector(n, m);
  for (int i = 0; i < m; i++)
    for (int j = 0; j < n; j++)
      iv_array[i][j] = ((m-i)+j)/n;

  return iv_array;
}

int** create_random_ivector(int n, int m, bool small)
{
  random_generator rg;
  int** iv_array;

  iv_array = create_ivector(n, m);
  for (int i = 0; i < m; i++)
    for (int j = 0; j < n; j++)
      {
	rg >> iv_array[i][j];
	if (small)
	  iv_array[i][j] %= 100;
	else
	  iv_array[i][j] %= 65536;
      }

  return iv_array;
}
