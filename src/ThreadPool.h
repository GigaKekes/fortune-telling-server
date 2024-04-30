#include <iostream>
#include <thread>
#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <future>

class ThreadPool {
private:
    // Очередь задач
    std::queue<std::function<void()>> tasks;

    // Мютекс для синхронизации доступа к очереди
    std::mutex queue_mutex;

    // Условная переменная для ожидания новых задач
    std::condition_variable condition;

    // Флаг остановки потоков
    bool stop = false;

    // Вектор потоков
    std::vector<std::thread> threads;

public:
    // Конструктор
    ThreadPool() {
        // Узнаем количество ядер в системе
        int num_threads = std::thread::hardware_concurrency();
        if (num_threads == 0) {
            num_threads = 1;
        }

        // Создаем потоки
        for (int i = 0; i < num_threads; i++) {
            threads.push_back(std::thread(&ThreadPool::worker, this));
        }
    }

    // Деструктор
    ~ThreadPool() {
        // Останавливаем потоки
        stop = true;
        condition.notify_all();
        for (auto& thread : threads) {
            thread.join();
        }
    }

    // Добавление задачи в очередь
    template<class F, class... Args>
    auto enqueue(F&& f, Args&&... args) -> std::future<typename std::result_of<F(Args...)>::type> {
        // Создаем задачу
        using return_type = typename std::result_of<F(Args...)>::type;
        auto task = std::make_shared<std::packaged_task<return_type()>>(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...)
        );

        // Создаем future для получения результата
        std::future<return_type> res = task->get_future();

        // Блокируем мютекс и добавляем задачу в очередь
        std::unique_lock<std::mutex> lock(queue_mutex);
        tasks.emplace([task]() { (*task)(); });
        lock.unlock();

        // Будим один из потоков для выполнения задачи
        condition.notify_one();

        // Возвращаем future
        return res;
    }

private:
    // Функция для выполнения задач
    void worker() {
        while (true) {
            // Блокируем поток, пока не появится новая задача
            std::function<void()> task;
            {
                std::unique_lock<std::mutex> lock(queue_mutex);
                condition.wait(lock, [this] { return stop || !tasks.empty(); });
                if (stop && tasks.empty()) {
                    return;
                }
                task = std::move(tasks.front());
                tasks.pop();
            }

            // Выполняем задачу
            task();
        }
    }

};