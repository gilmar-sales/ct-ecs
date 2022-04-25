#ifndef SPARSE_SET_HPP
#define SPARSE_SET_HPP

#include <vector>
#include <algorithm>

template<typename T>
class SparseSet {
public:
    SparseSet(unsigned capacity = 512u) {
        m_dense.reserve(capacity);
        m_sparse.resize(capacity);

        m_sorted = false;
    }

    ~SparseSet() = default;

    CT_ECS_SPEC void insert(T n) {
        if (contains(n))
            return;

        m_sparse[n] = m_dense.size();
        m_dense.push_back(n);

        m_sorted = false;
    }

    CT_ECS_SPEC void remove(T n) {
        if (!contains(n))
            return;

        m_dense[m_sparse[n]] = m_dense[m_dense.size() - 1];
        m_sparse[m_dense[m_dense.size() - 1]] = m_sparse[n];
        m_sparse[n] = 0;
        m_dense.pop_back();

        m_sorted = false;
    }

    CT_ECS_SPEC bool contains(T n) const {
        return m_sparse[n] < m_dense.size() && m_dense[m_sparse[n]] == n;
    }

    CT_ECS_SPEC void clear() {
        m_dense.clear();
    }

    CT_ECS_SPEC void resize(unsigned size) {
        m_dense.reserve(size);
        m_sparse.resize(size);
    }

    CT_ECS_SPEC void sort() {
        if (m_sorted)
            return;

        dense_sort();

        sparse_reorder();

        m_sorted = true;
    }

    T &operator[](int index) {
        return m_dense[index];
    };

    unsigned long size() {
        return m_dense.size();
    }

    auto begin() const {
        return m_dense.rbegin();
    }

    auto end() const {
        return m_dense.rend();
    }

protected:
    CT_ECS_SPEC void dense_sort() {
        std::sort(m_dense.begin(), m_dense.end());
    }

    CT_ECS_SPEC void sparse_reorder() {
        for (T i = 0; i < m_dense.size(); i++) {
            m_sparse[m_dense[i]] = i;
        }
    }
private:
    std::vector<T> m_dense;
    std::vector<T> m_sparse;
    bool m_sorted;
};

#endif
