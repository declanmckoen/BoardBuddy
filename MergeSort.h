void Merge(vector<ChessGame*>& vec, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    vector<ChessGame*> X(n1);
    vector<ChessGame*> Y(n2);

    for (int i = 0; i < n1; ++i) {
        X[i] = vec[left + i];
    }
    for (int i = 0; i < n2; ++i) {
        Y[i] = vec[mid + 1 + i];
    }

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (*(X[i]) >= *(Y[j])) {
            vec[k] = X[i++];
        }
        else {
            vec[k] = Y[j++];
        }
        k++;
    }

    while (i < n1) {
        vec[k] = X[i++];
        k++;
    }
    while (j < n2) {
        vec[k] = Y[j++];
        k++;
    }
}

void MergeSort(vector<ChessGame*>& vec, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        MergeSort(vec, left, mid);
        MergeSort(vec, mid+1, right);

        Merge(vec, left, mid, right);
    }
}
