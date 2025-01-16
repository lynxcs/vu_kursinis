#pragma once

/* All functions are in a separate translation unit to guarantee atleast 1 function call */

#include <span>

void execute_raw_loop(std::span<const int> span, size_t offset, double early_exit);
void execute_find_if(std::span<const int> span, size_t offset, double early_exit);
void execute_view(std::span<const int> span, size_t offset, double early_exit);
void execute_view_lambdas(std::span<const int> span, size_t offset, double early_exit);