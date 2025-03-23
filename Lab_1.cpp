//Данилов Артём Лабораторная работа №1 Вариант №1
//№1
#include <iostream>
#include <boost/thread.hpp>
#include <chrono>
#include <vector>

int fibonacci(int n) {
    if (n <= 1) return n;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

void task(int m, int i) {
    int fib = fibonacci(m);
    std::cout << "Поток " << i << " вычисляет число Фибоначчи №" << m << " = " << fib << std::endl;
}

int main() {
    int N = 4;
    int M = 40;

    // Многопоточное вычисление
    auto start_time = std::chrono::high_resolution_clock::now();
    std::vector<boost::thread> threads;
    for (int i = 0; i < N; ++i) {
    	threads.emplace_back(task, M, i);
    }
    for (auto &t : threads) t.join();
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
    std::cout << "Многопоточное вычисление занимает " << duration << " миллисекунд." << std::endl;

    // Последовательное вычисление
    start_time = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < N; ++i) {
        int fib = fibonacci(M);
        std::cout << "Рабский труд одного потока: число Фибоначчи №" << M << " = " << fib << std::endl;
    }
    end_time = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
    std::cout <<"Последовательное вычисление занимает " << duration << " миллисекунд." << std::endl;
    return 0;
}

//№2
/*#include <iostream>
#include <atomic>
#include <mutex>
#include <boost/thread.hpp>
#include <chrono>
#include <vector>

const int iterations = 1000000;

//Без синхронизации
void counter_1(int& counter) {
    for (int i = 0; i < iterations; ++i) {
        ++counter;
    }
}

//С использованием std::atomic<int>
void counter_2(std::atomic<int>& counter) {
    for (int i = 0; i < iterations; ++i) {
        ++counter;
    }
}

//С использованием std::mutex
void counter_3(int& counter, std::mutex& mtx) {
    for (int i = 0; i < iterations; ++i) {
        std::lock_guard<std::mutex> lock(mtx);
        ++counter;
    }
}

int main() {

	int N = 2;

    //Без синхронизации
    int c1 = 0;
    auto start_time = std::chrono::high_resolution_clock::now();
    std::vector<boost::thread> threads;
    for (int i = 0; i < N; ++i) {
    	threads.emplace_back(counter_1, std::ref(c1));
    }
    for (auto &t : threads) t.join();

    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
    std::cout << "Счётчик без синхронизации: " << c1 << ", время: " << duration << " мс" << std::endl;

    //С использованием std::atomic<int>
    std::atomic<int> c2{0};
    start_time = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < N; ++i) {
    	threads.emplace_back(counter_2, std::ref(c2));
    }
    for (auto &t : threads) t.join();
    end_time = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
    std::cout << "Atomic счётчик: " << c2 << ", время: " << duration << " мс" << std::endl;

    //С использованием std::mutex
    int c3 = 0;
    std::mutex mtx;
    start_time = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < N; ++i) {
    	threads.emplace_back(counter_3, std::ref(c3), std::ref(mtx));
    }
    for (auto &t : threads) t.join();
    end_time = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
    std::cout << "Mutex счётчик: " << c3 << ", время: " << duration << " мс" << std::endl;

    return 0;
}*/
