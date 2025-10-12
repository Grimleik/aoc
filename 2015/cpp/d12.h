#if !defined(D12_H)
/*========================================================================
	Creator: Grimleik $
========================================================================*/
#define D12_H
#include "utils.h"
#include "aoc_day.h"

class d12 : public aoc_day
{
public:
	d12();
	bool run() override;

	constexpr int day() override { return 12; }

protected:
	void pre_benchmark() override {}
	void post_benchmark() override {}
	int solution(const std::string_view &sv, const std::string &filter);

private:
	std::unique_ptr<file_contents> input_file;
	std::vector<std::pair<std::string_view, std::pair<int, int>>> input = {
		std::make_pair("[1,2,3]", std::make_pair(6, 6)),
		std::make_pair(" {\" a \":2,\" b \":4}", std::make_pair(6, 6)),
		std::make_pair("[[[3, \"red\"]]]", std::make_pair(3, 3)),
		std::make_pair("{\"red\":{\" b \":4},\" c \":-1}", std::make_pair(3, 0)),
		std::make_pair("{\"a\":[-1,1]}", std::make_pair(0, 0)),
		std::make_pair("[-1,{\"red\":1}]", std::make_pair(0, -1)),
		std::make_pair("{}", std::make_pair(0, 0)),
		std::make_pair("[]", std::make_pair(0, 0))};
};

enum class JSONTokenType
{
	LBRACE,
	RBRACE,
	LBRACKET,
	RBRACKET,
	COLON,
	COMMA,
	STRING,
	NUMBER,
	TRUE,
	FALSE,
	NULL_VALUE,
	END
};

struct JSONValue;

struct JSONToken
{
	JSONTokenType type;
	std::variant<bool, double, std::string, nullptr_t> value;
};

struct JSONObject
{
	std::unordered_map<std::string, JSONValue *> tokens;
	double sum(const std::string &filter);
};

struct JSONArray
{
	std::vector<JSONValue *> tokens;
	double sum(const std::string &filter);
};

enum class JSONObjectType
{
	OBJECT,
	ARRAY,
	VALUE,
};

struct JSONValue
{
	JSONObjectType type;
	std::variant<bool, double, std::string, nullptr_t, JSONObject, JSONArray> value;

	double sum(const std::string &filter);
};

struct JSON
{
	JSONValue *top;
	double sum(const std::string &filter);
};

#endif
