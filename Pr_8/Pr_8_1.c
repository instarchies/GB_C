void sort_array(int size, int a[]){
    for(int i = 0; i < size - 1; i++){
        for(int j = i + 1; j < size; j++){
            if(a[i] > a[j]){
                int _arr = a[i];
                a[i] = a[j];
                a[j] = _arr;
            }
        }
    }
}
