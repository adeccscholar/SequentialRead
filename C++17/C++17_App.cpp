// Classic_App.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include "Data.h"
#include <iostream>
#include <iomanip>
#include <chrono>

int main() {
   std::cout.setf(std::ios::fixed);
   TProcesses proc;

   std::cout << "Read Data C++17" << std::endl;

   auto func_start = std::chrono::high_resolution_clock::now();
   proc.Read("D:\\Test\\berlin_infos.dat");
   auto func_ende = std::chrono::high_resolution_clock::now();
   auto time = std::chrono::duration_cast<std::chrono::microseconds>(func_ende - func_start).count();
   std::cout << "Read " << proc.CountOfAddresses() << " rows with C++17" << " in " 
             << std::setprecision(3) << time / 1000.0 << " ms" << std::endl;


   func_start = std::chrono::high_resolution_clock::now();
   proc.Calculate(TGeoLocation(52.520803, 13.40945));
   func_ende = std::chrono::high_resolution_clock::now();
   time = std::chrono::duration_cast<std::chrono::microseconds>(func_ende - func_start).count();
   std::cout << "Calculated " << proc.CountOfAddresses() << " rows with C++17" << " in "
      << std::setprecision(3) << time / 1000.0 << " ms" << std::endl;

   func_start = std::chrono::high_resolution_clock::now();
   size_t cnt = proc.Work(1000.0);
   func_ende = std::chrono::high_resolution_clock::now();
   time = std::chrono::duration_cast<std::chrono::microseconds>(func_ende - func_start).count();
   std::cout << "Partitioned " << cnt << " rows with C++17" << " in "
      << std::setprecision(3) << time / 1000.0 << " ms" << std::endl;
   getchar();
   }
