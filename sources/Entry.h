#ifndef ENTRY_H_
#define ENTRY_H_

namespace AwesomeLibrary {

namespace Private {

template<class T> class Entry {
/*
 * Класс, реализующий запись в хэш-таблицу
 */
public:
	Entry (const T& newData): data_(newData), next_(nullptr), deleted_(false) {}
	~Entry () {}

	/*
	 * установить следующую запись
	 */
	void setNextEntry(const Entry* entry) noexcept {
		next_ = entry;
	}

	/*
	 * получить следующую запись
	 */
	const Entry* getNextEntry() const noexcept {
		return next_;
	}

	/*
	 * запись помечена как удаленная?
	 */
	bool isMarkAsDeleted() const noexcept {
		return deleted_;
	}

	/*
	 * пометить как удаленный
	 */
	void markAsDeleted() noexcept {
		deleted_ = true;
	}

	/*
	 * получить данные
	 */
	const T& getData() const noexcept {
		return data_;
	}

private:
	T data_;
	Entry* next_;
	bool deleted_;
};//end of declaration class Entry

} /* Private */ 

} /* AwesomeLibrary */ 

#endif /* end of include guard: ENTRY_H_ */

