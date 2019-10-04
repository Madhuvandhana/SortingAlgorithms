#include <cstdio>
#include <cstdlib>

#include "sort.h"
#include "timer.h"
#include "random_generator.h"

int main(int argc, char* argv[])
{
  random_generator rg;
  timer t;
  int n, m, d, a;

  if (argc > 1)
    {
      m = atoi(argv[1]);
      m = (m < 1) ? 1 : m;
    }
  else
    {
      cout << "[m] [n] [direction]" << endl;
      cout << "[m]              size of the random integer vector array" << endl;
      cout << "[n]              dimension of integer vector array" << endl;
      cout << "[direction]      0: random" << endl;
      cout << "                 1: sorted" << endl;
      cout << "                 -1: reverse sorted" << endl;
      cout << endl;
      return 0;
    }

  if (argc > 2)
    {
      n = atoi(argv[2]);
      n = (n < 0) ? 0 : n;
    }
  else
    n = 0;

  if (argc > 3)
    d = atoi(argv[3]);
  else
    d = 0;

  int** input_array;
     int** input_array_insertion_sort = new int*[m];
   int** input_array_insertion_sort_im = new int*[m];
   int** input_array_merge_sort = new int*[m];
   int* vector_length_array;
   int* vector_length_array_merge;


/*
 * create input array sorted/reverse sorted/random
 * depending on program argument
 * -> input_array is allocated!
 */
  t.start();
  if (d == 0)
    input_array = create_random_ivector(n, m, true);
  else
    {
      if (d < 0)
	input_array = create_reverse_sorted_ivector(n, m);
      else
	input_array = create_sorted_ivector(n, m);
    }
  t.stop();

  cout << "Timer (generate): " << t << endl;
  vector_length_array = new int[m];
  vector_length_array_merge =  new int[m];



/*
 * output the first 20 elements for debugging purposes
 */
  for (int i = 0; (i < m) && (i < 20); i++)
    {
      cout << "[ ";
      for (int j = 0; j < n; j++)
	cout << input_array[i][j] << " ";
      cout << "]" << endl;
    }
  cout << endl;

  // copy array input_array into input_array_insertion_sort so that the original array doesn't change
   for (int i=0; i<m; i++) {
    input_array_insertion_sort[i] = new int[n];
    for (int j=0; j<n; j++) {
      input_array_insertion_sort[i][j] = input_array[i][j];
    }
  }

  // copy array input_array into input_array_insertion_sort_im so that the original array doesn't change
   for (int i=0; i<m; i++) {
    input_array_insertion_sort_im[i] = new int[n];
    for (int j=0; j<n; j++) {
      input_array_insertion_sort_im[i][j] = input_array[i][j];
    }
  }

  /*
   * Do naiv insertion sort
   */

    cout << "Running insertion sort algorithm: " << endl;
    t.start();
    insertion_sort(input_array_insertion_sort, n, 0, m-1);
    t.stop();

    cout << "Timer (sort): " << t << endl;

  /*
   * check whether or not the algorithm sorted the array
   */
    if (check_sorted(input_array_insertion_sort, n, 0, m-1))
      cout << "The output is sorted!" << endl;
    else
      cout << "ERROR: The output is not sorted!" << endl;

      /*
       * output the first 20 elements for debugging purposes
       */
        for (int i = 0; (i < m) && (i < 20); i++)
          {
            cout << "[ ";
            for (int j = 0; j < n; j++)
      	cout << input_array_insertion_sort[i][j] << " ";
            cout << "]" << endl;
          }
        cout << endl;

  /*
   * precomputation of the length of each vector
   */
int sum=0;
for (int i = 0; i < m; i++)
  {
    sum = ivector_length(input_array[i], n);
    vector_length_array[i] = sum;
    vector_length_array_merge[i] = sum;
    }



/*
 * Do improved insertion sort with precomputation of vector length
 */

  cout << "Running improved insertion sort algorithm: " << endl;
  t.start();
  insertion_sort_im(input_array_insertion_sort_im, n, 0, m-1, vector_length_array);
  t.stop();

  cout << "Timer (sort): " << t << endl;

/*
 * check whether or not the algorithm sorted the array
 */
  if (check_sorted(input_array_insertion_sort_im, n, 0, m-1))
    cout << "The output is sorted!" << endl;
  else
    cout << "ERROR: The output is not sorted!" << endl;

    /*
     * output the first 20 elements for debugging purposes
     */
      for (int i = 0; (i < m) && (i < 20); i++)
        {
          cout << "[ ";
          for (int j = 0; j < n; j++)
    	cout << input_array_insertion_sort_im[i][j] << " ";
          cout << "]" << endl;
        }
      cout << endl;

/**
    Beginning of merge sort
    **/
// input_array_merge_sort = input_array;
      // copy array input_array into input_array_merge_sort so that the original array doesn't change
       for (int i=0; i<m; i++) {
          input_array_merge_sort[i] = new int[n];
        for (int j=0; j<n; j++) {
          input_array_merge_sort[i][j] = input_array[i][j];
        }
      }

    /*
     * Do merge sort with precomputation of vector length
     */

    cout << "Running merge sort algorithm: " << endl;
    t.start();
    merge_sort(input_array_merge_sort, n, 0, m-1, vector_length_array_merge);
    t.stop();

    cout << "Timer (merge sort): " << t << endl;

    if (check_sorted(input_array_merge_sort, n, 0, m-1))
      cout << "The output is sorted!" << endl;
    else
      cout << "ERROR: The output is not sorted!" << endl;

      /*
       * output the first 20 elements for debugging purposes
       */
        for (int i = 0; (i < m) && (i < 20); i++)
          {
            cout << "[ ";
            for (int j = 0; j < n; j++)
      	cout << input_array_merge_sort[i][j] << " ";
            cout << "]" << endl;
          }
        cout << endl;


/*
 * free the allocated storage
 */
  remove_ivector(input_array, m);
  remove_ivector(input_array_insertion_sort, m);
  remove_ivector(input_array_insertion_sort_im, m);
  remove_ivectoreLengthArr(vector_length_array);
  remove_ivector(input_array_merge_sort, m);
  remove_ivectoreLengthArr(vector_length_array_merge);

  return 0;
}
