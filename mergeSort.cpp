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