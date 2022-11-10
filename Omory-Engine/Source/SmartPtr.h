#pragma once

#include <memory>
#include <cassert>

/**
* @file			SmartPtr.h
* @namespace	
* @brief		各スマートポインタをラップしたクラス。主にweak_ptrを利用しやすくするために。
* @author		大森 健司
*/


	template<typename T>
	using UniquePtr = std::unique_ptr<T>;

	template<typename T>
	using SharedPtr = std::shared_ptr<T>;


	template<typename T>
	struct TWrapper : public T{
		template<typename... Param>
		TWrapper(Param&&... param) :
			T(std::forward<Param>(param)...) {

		}
	};

	template<typename T, typename... Param>
	UniquePtr<T> makeUnique(Param&&... param){
		return std::move(std::make_unique<TWrapper<T>>(std::forward<Param>(param)...));
	}

	template<typename T, typename...Param>
	SharedPtr<T> makeShared(Param&&... param){
		return std::move(std::make_shared< TWrapper<T>>(std::forward<Param>(param)...));
	}

	template<typename T>
	struct WeakPtr {

		WeakPtr() : m_pPtr() {}

		WeakPtr(const SharedPtr<T>& ptr) : m_pPtr(ptr) {}

		void swap(WeakPtr<T>* ptr) {
			m_pPtr.swap( ptr->m_pPtr );
		}

		void reset() {
			m_pPtr.reset();
		}

		unsigned int useCount() const {
			return m_pPtr.use_count();
		}

		bool expired() const {
			return m_pPtr.expired();
		}

		bool ownerBefore(const SharedPtr<T>& ptr) const {
			return m_pPtr.owner_before(ptr);
		}

		bool ownerBefore(const WeakPtr<T>& ptr) const {
			return m_pPtr.owner_before(ptr);
		}

		util::SharedPtr<T> lock() {
			return util::SharedPtr<T>(m_pPtr.lock());
		}

		WeakPtr<T>& operator=(const SharedPtr<T>& ptr) {
			assert(ptr.get() != nullptr && "メモリが確保されていません");
			m_pPtr = ptr;
			return *this;
		}

		WeakPtr<T>& operator=(const WeakPtr<T>& ptr) {
			m_pPtr = ptr.m_pPtr;
			return *this;
		}

		bool operator==(const WeakPtr<T>& ptr) const {
			return m_pPtr.lock().get() == ptr.m_pPtr.lock().get();
		}

		std::shared_ptr<T> operator->() const {
			return m_pPtr.lock();
		}

		T&	operator*() const {
			return *m_pPtr.lock().get();
		}

		std::weak_ptr<T> m_pPtr;
	};

