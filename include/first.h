#pragma once

#include "include.h"
#include "matrix_io.h"
#include "qr_eigenvalues.h"

void Example(const std::string file)
{
    Matrix A;

    std::cout << file << ": \n";

    switch (read_Matrix(A, "./examples/" + file))
    {
    case io_Code::FileNotFound:
        std::cout << "ERROR: File not found!";
        return;
    case io_Code::NoData:
        std::cout << "ERROR: No data!";
        return;
    case io_Code::NotEnoughData:
        std::cout << "ERROR: Not enough data!";
        return;
    default:
        break;
    };

    auto [eigenvalues, iterations, duration] = Solve(A);

    std::cout << "iterations: " << iterations << '\n';
    std::cout << "time(ms): " << duration << '\n';
    std::cout << "eigenvalues: \n";
    for(auto i : eigenvalues){
        std::cout << std::fixed << std::setprecision(6) << i.first;
        if(std::abs(i.second) < 1e-12){
            std::cout << "           ";
        }
        else{
            if(i.second > 0)
                std::cout << " + ";
            else
                std::cout << " - ";
            std::cout << std::abs(i.second) << 'i';
        }
        std::cout << "\t ( abs = " << std::sqrt(i.first * i.first + i.second * i.second) << " )\n";
    }
        
}

void First_task()
{
    std::cout << "first task: \n";
    Example("A1.txt");
    std::cout << "\n\n\n\n";
    std::cout << "first task: \n";
    Example("A2.txt");
    std::cout << "\n\n\n\n";
    std::cout << "first task: \n";
    Example("A3.txt");
    std::cout << "\n\n\n\n";
}