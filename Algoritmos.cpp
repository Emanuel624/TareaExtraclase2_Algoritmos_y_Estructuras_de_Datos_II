// Implementación Bubble Sort para arreglos de enteros
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Intercambiar los elementos
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

//Implementacion Selection Sort
void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        // Encontrar el índice del elemento mínimo en el arreglo no ordenado
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        // Intercambiar el elemento mínimo con el primer elemento no ordenado
        int temp = arr[minIndex];
        arr[minIndex] = arr[i];
        arr[i] = temp;
    }
}


// Función para combinar dos subarreglos en orden
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Crear arreglos temporales
    int* leftArr = new int[n1];
    int* rightArr = new int[n2];

    // Copiar los datos a los arreglos temporales
    for (int i = 0; i < n1; i++) {
        leftArr[i] = arr[left + i];
    }
    for (int j = 0; j < n2; j++) {
        rightArr[j] = arr[mid + 1 + j];
    }

    // Mezclar los arreglos temporales en el arreglo original
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        } else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    // Copiar los elementos restantes de leftArr
    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    // Copiar los elementos restantes de rightArr
    while (j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }

    // Liberar la memoria de los arreglos temporales
    delete[] leftArr;
    delete[] rightArr;
}

// Función de Merge Sort
void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        // Ordenar la primera mitad
        mergeSort(arr, left, mid);
        // Ordenar la segunda mitad
        mergeSort(arr, mid + 1, right);

        // Combinar las dos mitades
        merge(arr, left, mid, right);
    }
}

