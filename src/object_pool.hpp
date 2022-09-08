#pragma once

#ifndef OBJECT_POOL_H
#define OBJECT_POOL_H

#include <iostream>
#include <cstring>
#include <assert.h>

namespace loli {
	template <class T>
	class object_pool {
		private:
			T* m_block;
			unsigned int* m_allocs;
			
			unsigned int m_block_size;
			unsigned int m_ptr = 0;
			
			unsigned int m_len = 0;
			
		public:
			object_pool() { }
			
			~object_pool() { delete[] m_block; delete[] m_allocs; }
			
			inline void alloc_block(unsigned int block_size) {
				m_block_size = block_size;
				m_block = (T*) malloc(block_size * sizeof(T));
				m_allocs = (unsigned int*) malloc(block_size * sizeof(unsigned int));
				
				memset(m_allocs, 0, block_size * sizeof(unsigned int));
			}
			
			inline void remove(unsigned int ptr) {
				m_block[ptr].~T();
				
				if (ptr == m_len - 1) {
					if (m_ptr == m_len)
						m_ptr -= 1;
					
					m_len -= 1;
				} else {
					m_allocs[ptr] = m_ptr;
					m_ptr = ptr;
				}
			}
			
			inline void remove(T* t) {
				remove(t - m_block);
			}
			
			inline T* alloc() {
				unsigned int ptr = m_ptr;
				
				if (ptr == m_len) {
					assert(ptr < m_block_size && "exceeding size object pool size");
					
					m_ptr += 1;
					m_len += 1;
				} else {
					if (m_allocs[ptr] > m_len) {
						assert(ptr < m_block_size && "exceeding size object pool size");
						m_ptr = m_len;
					} else
						m_ptr = m_allocs[ptr];
					
					m_allocs[ptr] = 0;
				}
				
				return &m_block[ptr];
			}
			
			inline T* add(T obj) {
				T* ptr = alloc();
				*ptr = obj;
				
				return ptr;
			}
			
			inline bool is_alloc(unsigned int ptr) {
				return (ptr < m_len && m_allocs[ptr] == 0);
			}
			
			inline void set(unsigned int ptr, T obj) {
				if (ptr == m_len) {
					m_len = ptr + 1;
					m_ptr++;
				}
				
				m_block[ptr] = obj;
			}
			
			inline T* get(unsigned int ptr) {
				return &m_block[ptr];
			}
			
			inline unsigned int len() {
				return m_len;
			}
	};
}

#endif