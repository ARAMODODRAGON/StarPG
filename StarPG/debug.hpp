#ifndef _CORE_DEBUGGER_HPP
#define _CORE_DEBUGGER_HPP
//#include <glm\glm.hpp>
//#include <glm\gtx\string_cast.hpp>
#include <string>
#include <mutex>

class debug {
	virtual ~debug() final = 0;
public:

	static void log(const std::string& msg, const std::string& file, size_t line);
	static void trace(const std::string& msg, const std::string& file, size_t line);
	static void warning(const std::string& msg, const std::string& file, size_t line);
	static void error(const std::string& msg, const std::string& file, size_t line);
	static void fatal_error(const std::string& msg, const std::string& file, size_t line);

private:

	static inline std::mutex s_lock;
	static inline std::string s_logFilepath = "";
	static const std::string& get_log_path();
};

namespace detail {
	using std::to_string;
	//using glm::to_string;
}

#define DEBUG_LOG(msg) \
	::debug::log(msg, __FILE__, __LINE__)
#define DEBUG_TRACE(msg) \
	::debug::trace(msg, __FILE__, __LINE__)
#define DEBUG_WARNING(msg) \
	::debug::warning(msg, __FILE__, __LINE__)
#define DEBUG_ERROR(msg) \
	::debug::error(msg, __FILE__, __LINE__)
#define DEBUG_FATAL_ERROR(msg) \
	::debug::fatal_error(msg, __FILE__, __LINE__)

#define VTOS(value) \
	::alc::detail::to_string(value)

#endif // !_CORE_DEBUGGER_HPP