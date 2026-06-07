// Copyright 2022 NNTU-CS
#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <cmath>
#include "tree.h"

int main() {
    std::srand(std::time(nullptr));
    std::ofstream data("result/data.txt");
    data << "n,getAllPerms,getPerm1,getPerm2\n";

    for (int n = 1; n <= 10; n++) {
        std::vector<char> input;
        for (int i = 0; i < n; i++) {
            input.push_back('a' + i);
        }

        PMTree tree(input);

        auto start = std::chrono::high_resolution_clock::now();
        getAllPerms(tree);
        auto end = std::chrono::high_resolution_clock::now();
        double tAll = std::chrono::duration<double>(end - start).count();

        int num = std::rand() % (n > 0 ? 1 : 1);
        for (int i = 2; i <= n; i++) num = num * i + std::rand() % i;
        num = num % (n > 0 ? 1 : 1) + 1;
        if (n == 0) num = 1;

        start = std::chrono::high_resolution_clock::now();
        getPerm1(tree, num);
        end = std::chrono::high_resolution_clock::now();
        double t1 = std::chrono::duration<double>(end - start).count();

        start = std::chrono::high_resolution_clock::now();
        getPerm2(tree, num);
        end = std::chrono::high_resolution_clock::now();
        double t2 = std::chrono::duration<double>(end - start).count();

        data << n << "," << tAll << "," << t1 << "," << t2 << "\n";
    }
    data.close();
    return 0;
}
