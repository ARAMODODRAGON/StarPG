#ifndef OBJECT_HPP
#define OBJECT_HPP
#include <vector>
#include <memory>
#include <string>

class object;

template<typename T>
concept object_type = std::is_base_of_v<object, T>;

// object class that all objects and levels derive from
// kills its own children
class object {
	using object_list = std::vector<object*>;
public:
	using iterator = object_list::iterator;

	object();
	~object();

	// creates a new object attached to this one
	template<object_type T>
	T* create_object();

	// deletes this object and any children
	// (returns this object within a unique_ptr to handle immediate deletion)
	std::unique_ptr<object> delete_this();

	// returns this objects parent
	object* get_parent() const;

	// changes this objects parent
	void set_parent(object* new_parent);

	// iteration
	iterator begin();
	iterator end();

private:
	object* m_parent;
	object_list m_children;
};


inline object::object() : m_parent(nullptr) { }

inline object::~object() {
	for (size_t i = 0; i < m_children.size(); i++) {
		delete m_children[i];
	}
	m_children.clear();
}

template<object_type T>
inline T* object::create_object() {
	T* obj = new T();
	m_children.emplace_back(obj);
	return obj;
}

inline std::unique_ptr<object> object::delete_this() { 
	set_parent(nullptr);
	return std::unique_ptr<object>(this);
}

inline object* object::get_parent() const {
	return m_parent;
}

inline void object::set_parent(object* new_parent) {
	if (m_parent == new_parent) return;
	if (m_parent) for (size_t i = 0; i < m_parent->m_children.size(); i++) {
		if (m_parent->m_children[i] == this) {
			m_parent->m_children.erase(m_parent->m_children.begin() + i);
			break;
		}
	}
	if (new_parent) new_parent->m_children.emplace_back(this);
	m_parent = new_parent;
}

inline object::iterator object::begin() {
	return m_children.begin();
}

inline object::iterator object::end() {
	return m_children.end();
}

#endif // !OBJECT_HPP