#if !defined(UTILS_H)
/*========================================================================
	Creator: Grimleik $
	STUDY: Move some of the inline functions into .cpp file?
========================================================================*/
#define UTILS_H
#include "pch.h"
// #define VERBOSE

typedef uint8_t u8;
typedef int32_t i32;
typedef int64_t i64;
typedef uint32_t u32;
typedef uint64_t u64;
typedef float f32;
typedef double f64;

#define ARRAY_COUNT(x) ((sizeof(x)) / (sizeof(x[0])))

#define CHECK_VALUE(x, y)                                                      \
	do                                                                         \
	{                                                                          \
		if (x != y)                                                            \
		{                                                                      \
			std::cout << "Value is: " << x << " expected: " << y << std::endl; \
			return false;                                                      \
		}                                                                      \
	} while (false);

#ifdef VERBOSE
#define CHECK_TEST(func, input, output, ...)                                                                  \
	{                                                                                                         \
		auto check_output = func(input, __VA_ARGS__);                                                         \
		if (check_output != output)                                                                           \
		{                                                                                                     \
			std::cout << std::format("\tFAILED. Input({}) != Output({})", check_output, output) << std::endl; \
			return false;                                                                                     \
		}                                                                                                     \
		else                                                                                                  \
		{                                                                                                     \
			std::cout << std::format("\tPASSED. Input({}) == Output({})", check_output, output) << std::endl; \
		}                                                                                                     \
	}
#else
#define CHECK_TEST(func, input, output, ...)                                                                  \
	{                                                                                                         \
		auto check_output = func(input, __VA_ARGS__);                                                         \
		if (check_output != output)                                                                           \
		{                                                                                                     \
			std::cout << std::format("\tFAILED. Input({}) != Output({})", check_output, output) << std::endl; \
			return false;                                                                                     \
		}                                                                                                     \
	}
#endif

struct file_contents
{
	~file_contents() { delete[] mem; }
	char *mem;
	size_t sz;
};

inline std::unique_ptr<file_contents> read_entire_file(const char *filename)
{
	std::unique_ptr<file_contents> result = std::unique_ptr<file_contents>(new file_contents());
	std::ifstream file(filename, std::ios::in | std::ios::ate);
	if (file.is_open())
	{
		result->sz = file.tellg();
		file.seekg(0, std::ios::beg);
		result->mem = new char[result->sz + 1];
		file.read(result->mem, result->sz);
		result->mem[result->sz] = '\0';
	}
	file.close();
	return result;
}

inline bool is_hexadecimal(const char *in)
{
	return in[0] != '\0' && in[0] == '\\' && in[1] == 'x' && in[2] != '\0' &&
		   in[3] != '\0';
}

inline void save_bmp(const char *filename, int width, int height, u32 *buffer)
{
	int filesize = 54 + width * 4 * height;
	u8 bmpheader[14] = {'B',
						'M',
						(u8)filesize,
						(u8)(filesize >> 8),
						(u8)(filesize >> 16),
						(u8)(filesize >> 24),
						0,
						0,
						0,
						0,
						54,
						0,
						0,
						0};

	u8 bmpinfoheader[40] = {40,
							0,
							0,
							0,
							(u8)(width),
							(u8)(width >> 8),
							(u8)(width >> 16),
							(u8)(width >> 24),
							(u8)(height),
							(u8)(height >> 8),
							(u8)(height >> 16),
							(u8)(height >> 24),
							1,
							0,
							32,
							0};

	std::ofstream out(filename, std::ios::binary);
	out.write((char *)bmpheader, ARRAY_COUNT(bmpheader));
	out.write((char *)bmpinfoheader, ARRAY_COUNT(bmpinfoheader));

	for (int y = height - 1; y >= 0; --y)
	{
		for (int x = 0; x < width; ++x)
		{
			u32 color = buffer[(y * width + x)];
			char A = /*color >> 24*/ 127, R = (color >> 16) & 255,
				 G = (color >> 8) & 255, B = (color) & 255;
			out.write(&B, 1);
			out.write(&G, 1);
			out.write(&R, 1);
			out.write(&A, 1);
		}
	}
}

inline bool is_whitespace(const char c) { return c == ' ' || c == '\n' || c == '\t'; }

inline bool is_numeric(const char c)
{
	int result = (c - '0');
	return result >= 0 && result <= 9;
}

inline int get_number(const char **c)
{
	int result = 0;
	while (!is_numeric(**c))
		(*c)++;

	while (**c >= '0' && **c <= '9')
	{
		result = result * 10 + (int)(**c - '0');
		++*c;
	}
	return result;
}

inline double get_number_d(const char *c, size_t &steps)
{
	const char *orig = c;
	double result = 0;
	while (!is_numeric(*c))
		c++;

	while (*c >= '0' && *c <= '9')
	{
		result = result * 10 + (int)(*c - '0');
		++c;
	}

	if (*c == '.')
		while (*c >= '0' && *c <= '9')
		{
			result = result * .1 + (int)(*c - '0');
			++c;
		}
	steps += c - orig;
	return result;
}

inline char get_symbol(const char **c)
{
	while (is_whitespace(**c) || is_numeric(**c))
		(*c)++;
	return **c;
}

inline char is_alpha(const char c)
{
	return (((c) >= 'a' && (c) <= 'z') || ((c) >= 'A' && (c) <= 'Z'));
}

inline std::string get_variable(const char **c)
{
	std::string result;
	while (is_whitespace(**c) || is_numeric(**c) || !is_alpha((**c)))
		(*c)++;
	while (is_alpha(**c))
	{
		result += **c;
		(*c)++;
	}
	return result;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &vec)
{
	os << "[";
	for (size_t i = 0; i < vec.size(); ++i)
	{
		os << vec[i];
		if (i != vec.size() - 1)
			os << ", ";
	}
	os << "]";
	return os;
}

template <typename WorkerFunc, typename... Args>
void parallelize_function(size_t nbr_threads, WorkerFunc worker, Args &&...args)
{
	std::vector<std::thread> threads;
	for (size_t i = 0; i < nbr_threads; ++i)
		threads.emplace_back(worker, std::forward<Args>(args)...);
	for (auto &t : threads)
		t.join();
}

inline std::vector<std::string_view> split_string_view(const std::string_view &sv, char delim = '\n')
{
	std::vector<std::string_view> result;
	size_t start = 0;
	while (start < sv.size())
	{
		size_t end = sv.find(delim, start);
		if (end == std::string_view::npos)
		{
			// result.emplace_back(sv.substr(start));
			break;
		}
		result.emplace_back(sv.substr(start, end - start));
		start = end + 1;
	}
	return result;
}

#endif
