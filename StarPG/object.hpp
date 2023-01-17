#ifndef OBJECT_HPP
#define OBJECT_HPP
#include <vector>
#include <list>
#include <unordered_map>
#include <memory>
#include <string>
#include "function.hpp"

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

	// returns an iterator pointing at the first child
	iterator begin();

	// returns an iterator pointing one space past the last child
	iterator end();

	// messaging

	// sends a message over a set channel with optional data
	static void send(const std::string& channel, void* data = nullptr);

	// listens for messages over a specific channel
	template<auto MemberFunction, object_type T>
	void subscribe(const std::string& channel, T* obj);

	// unsubscribes specific function from a specific channel if its subscribed
	template<auto MemberFunction, object_type T>
	void unsubscribe(const std::string& channel, T* obj);

private:
	object* m_parent;
	object_list m_children;
	std::unordered_map<std::string, function<void, void*>> m_subscribedChannels;
	static inline std::unordered_map<std::string, std::list<function<void, void*>>> s_channels;
};


inline object::object() : m_parent(nullptr) { }

inline object::~object() {
	// delete children
	for (size_t i = 0; i < m_children.size(); i++) {
		delete m_children[i];
	}
	m_children.clear();
	// remove listeners
	for (auto p : m_subscribedChannels) {
		s_channels[p.first].remove(p.second);
	}
	m_subscribedChannels.clear();
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

inline void object::send(const std::string& channel, void* data) {
	// check if and then ignore if needed
	// no need to alert anything if theres no listeners
	if (!s_channels.contains(channel)) return;
	// invoke
	auto& ls = s_channels[channel];
	for (auto& func : ls) func(data);
}

template<auto MemberFunction, object_type T>
inline void object::subscribe(const std::string& channel, T* obj) { 
	if (obj == nullptr) return;
	// check if already subscribed
	if (m_subscribedChannels.contains(channel)) return;
	// subscribe
	function<void, void*> func = make_function<MemberFunction>(obj);
	m_subscribedChannels.emplace(channel, func);
	s_channels[channel].push_back(func);
}

template<auto MemberFunction, object_type T>
inline void object::unsubscribe(const std::string& channel, T* obj) { 
	if (obj == nullptr) return;
	// check if not subscribed
	if (!m_subscribedChannels.contains(channel)) return;
	// unsubscribe
	function<void, void*> func = make_function<MemberFunction>(obj);
	m_subscribedChannels.erase(channel);
	s_channels[channel].remove(func);

}

//inline void object::subscribe(const std::string& channel, function<void, void*> listenerFunction) {
//	// check if already subscribed
//	if (m_subscribedChannels.contains(channel)) return;
//	// subscribe
//	m_subscribedChannels.emplace(channel, listenerFunction);
//	s_channels[channel] += listenerFunction;
//}
//
//inline void object::unsubscribe(const std::string& channel) { 
//	// check if subscribed
//	if (!m_subscribedChannels.contains(channel)) return;
//	// unsubscribe
//	auto func = m_subscribedChannels[channel];
//	m_subscribedChannels.erase(channel);
//	s_channels[channel] -= func;
//}

#endif // !OBJECT_HPP