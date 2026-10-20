#include <hpx/hpx_main.hpp>
#include <hpx/async.hpp>
#include <hpx/future.hpp>
#include <hpx/iostream.hpp>
#include <hpx/runtime_local/get_worker_thread_num.hpp>
#include <hpx/runtime_local/runtime_local_fwd.hpp>
#include <array>
#include <chrono>
#include <cstddef>
#include <cstdint>

namespace {
    struct task_result
    {
        std::size_t task_number;
        std::size_t worker_number;
        std::uint64_t iterations;
    };
}


int main()
{
    constexpr std::size_t task_count = 8;
    constexpr auto task_duration = std::chrono::milliseconds(100);

    hpx::cout << "Hello World desde HPX\n"
              << "Trabajadores disponibles: " << hpx::get_num_worker_threads()
              << "\nTareas: " << task_count << "\n" << std::flush;

    std::array<hpx::future<task_result>, task_count> tasks;
    const auto start = std::chrono::steady_clock::now();

    for (std::size_t i = 0; i < task_count; ++i)
    {
        tasks[i] = hpx::async([i, task_duration]() {
            const auto worker = hpx::get_worker_thread_num();
            const auto deadline = std::chrono::steady_clock::now() + task_duration;
            std::uint64_t iterations = 0;
            while (std::chrono::steady_clock::now() < deadline)
            {
                ++iterations;
            }
            return task_result{i + 1, worker, iterations};
        });
    }

    for (auto& task : tasks)
    {
        const task_result result = task.get();
        hpx::cout << "Tarea " << result.task_number << " ejecutada por el "
                  << "trabajador " << result.worker_number << " ("
                  << result.iterations << " iteraciones)\n";
    }

    const auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::steady_clock::now() - start);
    hpx::cout << "Tiempo total: " << elapsed.count() << " ms\n" << std::flush;

    return 0;
}