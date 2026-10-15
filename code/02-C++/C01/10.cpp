#include <cstdio>
int main() {
    int* p = new int(42);
    int* arr = new int[5]{};
    arr[2] = 7;
    std::printf("%d %d %d\n", *p, arr[2], arr[4]);
    delete p;
    delete[] arr;
    return 0;
}