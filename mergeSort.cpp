/*
Assumptions:
	Objects being parsed have overriden the comparison operators to use to their desired comparison
	size is the true length of the array being sorted
Solution Background:
	In college, the simplest solution programmatically seemed to be using recursion. As it abstracts some of the partitioning
	logic from the developer. But I thought that it was extremely wasteful memory wise to add all the funciton calls as well as 
	memory duplication needed to achieve this. This solution would use memory of order n * log(n) which I thought was also wasteful. 
	After plenty of thinking, I realized that I could use an array of the same size and alternate the merges back and forth 
	between the two. This is the inspiration to this solution. In addition, by realizing that the merges occuring would perfectly
	sync with the powers of 2, allowed me to iterate through the array, exactly log(n) times, merging the smaller chunks as I 
	iterated. 
	I did write this about 2 years ago, and don't remember the speeds of it. But would love to see if anyone has any recs or 
	optimizaitons for it. Not to mention, if anyone has a faster solution and would like to test them out :) 
 */

template <class T>
T *Sorter<T>::mergeSort(T *array, int size) {
	T *temp = new T[size];
	T *mergeTo = temp;
	T *mergeFrom = array;
	int i, s, mid, rem, remp, n, l;
	for (i = 2; i < size; i *= 2) {
		mid = i/2;
		n = size / i;
		for (s = 0, l = 0; l < n ; s += i, l++)
			merge(&mergeTo[s], &mergeFrom[s], &mergeFrom[s + mid], mid, mid);
		rem = size % i;
		if (rem > mid) {
			remp = size - rem;
			merge(&mergeTo[remp], &mergeFrom[remp], &mergeFrom[remp + mid], mid, rem - mid);
		}
		swap(mergeTo, mergeFrom);
	}
	mid = i / 2;
	merge(&mergeTo[0], &mergeFrom[0], &mergeFrom[mid], mid, size - mid);
	return mergeTo;
}

template <class T>
void Sorter<T>::merge(T *mergedTo, T *a, T *b, int asize, int bsize) {
	int l = 0, r = 0, c = 0;
	while (l < asize && r < bsize) {
		if (*a[l] < *b[r]) {
			mergedTo[c] = a[l];
			l++;
		} else {
			mergedTo[c] = b[r];
			r++;
		}
		c++;
	}
	if (l < asize) {
		do {
			mergedTo[c] = a[l];
			l++;
			c++;
		} while (l < asize);
	} else {
		do {
			mergedTo[c] = b[r];
			r++;
			c++;
		} while (r < bsize);
	}
}
