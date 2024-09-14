import sys
import time #Allows passing parameters from command line

#Used to convert AAAA-BBBB-CCC into ASCII sum
def ascii_sum(s):
    return sum(ord(c) for c in s if c.isalnum())

def merge_sort(arr, L, R):
    if L < R:
        M = (L + R) // 2
        merge_sort(arr, L, M)
        merge_sort(arr, M + 1, R)
        merge(arr, L, M, R)

def merge(arr, left, middle, right):
    n1 = middle - left + 1
    n2 = right - middle

    L = arr[left:left + n1]
    R = arr[middle + 1:middle + 1 + n2]

    i = j = 0
    k = left

    while i < n1 and j < n2:
        if ascii_sum(L[i]) <= ascii_sum(R[j]):  #Minor alteration to OG MergeSort to compare ASCII sum Values
            arr[k] = L[i]
            i += 1
        else:
            arr[k] = R[j]
            j += 1
        k += 1

    while i < n1:
        arr[k] = L[i]
        i += 1
        k += 1

    while j < n2:
        arr[k] = R[j]
        j += 1
        k += 1

#writes sorted array to output_file
def print_array(array_to_print, output_file):
    with open(output_file, 'w') as f:
        for item in array_to_print:
            f.write(f"{item}\n")

def main():
    
    #Checks user input
    if len(sys.argv) != 3:
        print("Invalid input, Use format: python MergeSort.py <file to be sorted> <output file>")
        sys.exit(1)
    #Assigns User input
    dataset_file = sys.argv[1]
    output_file = sys.argv[2]

    #Opens unsorted file and places each line in an array 
    with open(dataset_file, 'r') as f:
        arr = [line.strip() for line in f]

    
    start_time = time.time() #Opens a timer

    #Calls Sorting Algorithm
    merge_sort(arr, 0, len(arr) - 1)
    
    end_time = time.time() #Closes timer
    perform = end_time - start_time #measures performance

    print(f"Time taken to sort: {perform:.6f} seconds")

    #Prints sorted array to specified file
    print_array(arr, output_file)


if __name__ == "__main__":
    main()