#pragma once

#include <memory>
#include <cassert>

/**
* @file			SmartPtr.h
* @namespace	
* @brief		各スマートポインタをラップしたクラス。主にweak_ptrを利用しやすくするために。
* @author		大森 健司
*/

/// <summary>
/// ユニークポインタのエイリアス
/// </summary>
/// <typeparam name="T">ユニークポインタ化したいクラス</typeparam>
template<typename T>
using UniquePtr = std::unique_ptr<T>;

/// <summary>
/// シェアドポインタのエイリアス
/// </summary>
/// <typeparam name="T">シェアドポインタ化したいクラス</typeparam>
template<typename T>
using SharedPtr = std::shared_ptr<T>;

/// <summary>
/// 
/// </summary>
/// <typeparam name="T"></typeparam>
template<typename T>
struct TWrapper : public T{
	template<typename... Param>
	TWrapper(Param&&... param) :
		T(std::forward<Param>(param)...) {}
};

/// <summary>
/// 
/// </summary>
/// <typeparam name="T"></typeparam>
/// <typeparam name="...Param"></typeparam>
/// <param name="...param"></param>
/// <returns></returns>
template<typename T, typename... Param>
UniquePtr<T> MakeUnique(Param&&... param){
	return std::move(std::make_unique<TWrapper<T>>(std::forward<Param>(param)...));
}

template<typename T, typename...Param>
SharedPtr<T> MakeShared(Param&&... param){
	return std::move(std::make_shared< TWrapper<T>>(std::forward<Param>(param)...));
}

template<typename T>
struct WeakPtr {

	WeakPtr() : m_pPtr() {}

	WeakPtr(const SharedPtr<T>& ptr) : m_pPtr(ptr) {}
	WeakPtr(const UniquePtr<T>& ptr) { m_pPtr = ptr; }

	//void Swap(WeakPtr<T>* ptr) {
	//	m_pPtr.swap( ptr->m_pPtr );
	//}

	/// <summary>
	/// 監視を終了する
	/// </summary>
	void Reset() {
		m_pPtr.reset();
	}

	/// <summary>
	/// 監視しているポインタの参照数を取得する
	/// </summary>
	/// <returns>参照数</returns>
	unsigned int UseCount() const {
		return m_pPtr.use_count();
	}

	/// <summary>
	/// 監視しているポインタが有効か否かを確認する
	/// </summary>
	/// <returns>有効か否か</returns>
	bool Expired() const {
		return m_pPtr.expired();
	}

	/// <summary>
	/// 
	/// </summary>
	/// <param name="ptr"></param>
	/// <returns></returns>
	bool OwnerBefore(const SharedPtr<T>& ptr) const {
		return m_pPtr.owner_before(ptr);
	}

	bool OwnerBefore(const WeakPtr<T>& ptr) const {
		return m_pPtr.owner_before(ptr);
	}

	SharedPtr<T> Lock() {
		return SharedPtr<T>(m_pPtr.lock());
	}

	//std::weak_ptr<T>& operator=(const SharedPtr<T>& ptr)
	//{
	//	m_pPtr = ptr;
	//	return *this;
	//}

	WeakPtr<T>& operator=(const SharedPtr<T>& ptr) {
		assert(ptr.get() != nullptr && "メモリが確保されていません");
		m_pPtr = ptr;
		return *this;
	}

	//std::weak_ptr<T>& operator=(const UniquePtr<T>& ptr) {
	//	m_pPtr = ptr;
	//	return *this;
	//}

	WeakPtr<T>& operator=(const UniquePtr<T>& ptr) {
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

