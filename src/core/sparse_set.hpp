#pragma once

#include <vector>
#include <algorithm>

namespace ecs
{
	template<typename T>
	class sparse_set
	{
	public:
		sparse_set(unsigned capacity = 512u) 
		{
			m_dense.resize(capacity);
			m_sparse.resize(capacity);
		}
		~sparse_set() = default;

		void insert(T n)
		{
			if (contains(n)) return;

			m_sparse[n] = m_dense.size();
			m_dense.push_back(n);

			m_sorted = false;
		}
		void remove(T n)
		{
			m_dense[m_sparse[n]] = m_dense[m_dense.size() - 1];
			m_sparse[m_dense[m_dense.size() - 1]] = m_sparse[n];
			m_dense.pop_back();

			m_sorted = false;
		}

		inline bool contains(T n) const
		{
			return m_sparse[n] < m_dense.size() && m_dense[m_sparse[n]] == n;
		}

		inline void clear()
		{
			m_dense.clear();
		}
		
		void resize(unsigned size)
		{
			m_dense.resize(size);
			m_sparse.resize(size);
		}

		void sort()
		{
			if (m_sorted) return;

			std::sort(m_dense.begin(), m_dense.end());
			
			for (T i = 0; i < m_dense.size(); i++)
			{
				m_sparse[m_dense[i]] = i;
			}

			m_sorted = true;
		}

		auto begin() const {
			return m_dense.begin();
		}

		auto end() const {
			return m_dense.end();
		}

	private:
		std::vector<T> m_dense;
		std::vector<T> m_sparse;
		bool m_sorted;
	};
}