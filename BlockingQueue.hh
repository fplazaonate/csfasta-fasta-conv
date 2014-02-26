#ifndef BLOCKING_QUEUE_HH
#define BLOCKING_QUEUE_HH
 
/*
 * (C) Copyright 2014 Enterome
 * 
 * This file is part of csfasta-fasta-conv.
 * 
 * csfasta-fasta-conv is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * csfasta-fasta-conv is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with csfasta-fasta-conv.  If not, see <http://www.gnu.org/licenses/>.
 */ 

#include <queue>
#include <mutex>
#include <condition_variable>

template <typename T>
class BlockingQueue
{
private:
	std::queue<T> queue_;
	const unsigned max_size_;
	std::mutex mutex_;
	std::condition_variable not_empty_;
	std::condition_variable not_full_;

public:
	BlockingQueue<T>(unsigned max_size);
	void enqueue(const T& val);
	T dequeue();
};

template <typename T>
BlockingQueue<T>::BlockingQueue(unsigned max_size)
	: queue_(), max_size_(max_size), mutex_(), not_empty_(), not_full_()

{};

template <typename T>
void BlockingQueue<T>::enqueue(const T& val)
{
    std::unique_lock<std::mutex> lock(mutex_);
	not_full_.wait(lock, [&](){return queue_.size() < max_size_;});
	queue_.push(val);
	not_empty_.notify_one();
}

template <typename T>
T BlockingQueue<T>::dequeue()
{
	std::unique_lock<std::mutex> lock(mutex_);
	not_empty_.wait(lock, [&](){return !queue_.empty();});
	T val = queue_.front();
	queue_.pop();
	not_full_.notify_one();

	return val;
}

#endif // BLOCKING_QUEUE_HH
