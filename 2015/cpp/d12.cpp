/*========================================================================
	Creator: Grimleik $
	NOTE: Essentially a JSON parser.
========================================================================*/
#include "d12.h"
void tokenize(const std::string_view &sv, std::queue<JSONToken> &tokens)
{
	for (size_t i = 0; i < sv.size(); ++i)
	{
		if (is_whitespace(sv[i]))
			continue;
		if (sv[i] == '{')
		{
			tokens.push({JSONTokenType::LBRACE, nullptr});
		}
		else if (sv[i] == '}')
		{
			tokens.push({JSONTokenType::RBRACE, nullptr});
		}
		else if (sv[i] == '[')
		{
			tokens.push({JSONTokenType::LBRACKET, nullptr});
		}
		else if (sv[i] == ']')
		{
			tokens.push({JSONTokenType::RBRACKET, nullptr});
		}
		else if (sv[i] == ':')
		{
			tokens.push({JSONTokenType::COLON, nullptr});
		}
		else if (sv[i] == ',')
		{
			tokens.push({JSONTokenType::COMMA, nullptr});
		}
		else if (sv[i] == 'n') // ull
		{
			tokens.push({JSONTokenType::JNULL_VALUE, nullptr});
			i += 3;
		}
		else if (sv[i] == 'f') // alse
		{
			tokens.push({JSONTokenType::JFALSE, false});
			i += 4;
		}

		else if (sv[i] == 't') // rue
		{
			tokens.push({JSONTokenType::JTRUE, true});
			i += 3;
		}
		else if (sv[i] == '\"')
		{
			std::string str_value = "";
			while (sv[++i] != '\"')
			{
				str_value += sv[i];
			}
			tokens.push({JSONTokenType::STRING, str_value});
		}
		else if (sv[i] == '-')
		{
			++i;
			tokens.push({JSONTokenType::NUMBER, -get_number_d(sv.data() + i, i)});
			--i;
		}
		else if (is_numeric(sv[i]))
		{
			tokens.push({JSONTokenType::NUMBER, get_number_d(sv.data() + i, i)});
			--i;
		}
		else
		{
			std::cout << "Uncaught token in json: " << sv[i] << std::endl;
		}
	}
}

JSONValue *parse_token(std::queue<JSONToken> &tokens)
{
	auto token = tokens.front();
	tokens.pop();
	while (token.type == JSONTokenType::COLON ||
		   token.type == JSONTokenType::COMMA)
	{
		token = tokens.front();
		tokens.pop();
	}

	switch (token.type)
	{
	case JSONTokenType::LBRACE:
	{
		JSONValue *jv = new JSONValue;
		jv->type = JSONObjectType::OBJECT;
		jv->value = JSONObject{};
		auto &obj = std::get<JSONObject>(jv->value);
		while (tokens.front().type != JSONTokenType::RBRACE)
		{
			JSONValue *name = parse_token(tokens);
			JSONValue *value = parse_token(tokens);
			obj.tokens[std::get<std::string>(name->value)] = value;
			delete name;
		}
		tokens.pop(); // pop the rbrace.
		return jv;
	}
	break;

	case JSONTokenType::LBRACKET:
	{
		JSONValue *jv = new JSONValue;
		jv->type = JSONObjectType::ARRAY;
		jv->value = JSONArray{};
		auto &arr = std::get<JSONArray>(jv->value);
		while (tokens.front().type != JSONTokenType::RBRACKET)
		{
			JSONValue *next = parse_token(tokens);
			arr.tokens.push_back(next);
		}
		tokens.pop(); // pop the rbracket.
		return jv;
	}
	break;
	case JSONTokenType::JTRUE:
	case JSONTokenType::JFALSE:
	{
		JSONValue *jv = new JSONValue;
		jv->type = JSONObjectType::VALUE;
		std::get<bool>(jv->value) = std::get<bool>(token.value);
		return jv;
	}
	break;
	case JSONTokenType::JNULL_VALUE:

	{
		JSONValue *jv = new JSONValue;
		jv->type = JSONObjectType::VALUE;
		jv->value = nullptr;
		return jv;
	}
	break;
	case JSONTokenType::NUMBER:
	{
		JSONValue *jv = new JSONValue;
		jv->type = JSONObjectType::VALUE;
		jv->value = std::get<double>(token.value);
		// std::get<double>(jv->value) = std::get<double>(token.value);
		return jv;
	}
	break;
	case JSONTokenType::STRING:
	{
		JSONValue *jv = new JSONValue;
		jv->type = JSONObjectType::VALUE;
		jv->value = std::move(std::get<std::string>(token.value));
		return jv;
	}
	break;
	case JSONTokenType::END:
	{
		return nullptr;
	}
	break;

	default:
		std::cerr << "Fault during JSON Parsing." << std::endl;
		break;
	}

	return nullptr;
}

JSON *parse(std::queue<JSONToken> &tokens)
{
	JSON *result = new JSON();
	result->top = parse_token(tokens);
	return result;
}

d12::d12()
{
	input_file = std::move(read_entire_file("../../../../2015/input/d12.in"));
	input.push_back(std::make_pair(std::string_view(input_file->mem), std::make_pair(119433, 68466)));
}

int d12::solution(const std::string_view &sv, const std::string &filter)
{
	std::queue<JSONToken> tokens;
	tokenize(sv, tokens);
	JSON *json = parse(tokens);
	double result = json->sum(filter);
	return (int)result;
}

bool d12::run()
{
	for (auto &t : input)
		CHECK_TEST(solution, t.first, t.second.first, "");

	for (auto &t : input)
		CHECK_TEST(solution, t.first, t.second.second, "red");
	return true;
}

double JSONObject::sum(const std::string &filter)
{
	double result = 0.0;
	for (auto &[k, v] : tokens)
	{
		if (k == filter)
			return 0.0;
		if (auto p = std::get_if<std::string>(&v->value))
		{
			if (*p == filter)
				return 0.0;
		}
		result += v->sum(filter);
	}
	return result;
}

double JSONArray::sum(const std::string &filter)
{
	double result = 0.0;
	for (auto &el : tokens)
		result += el->sum(filter);
	return result;
}

double JSONValue::sum(const std::string &filter)
{
	if (type == JSONObjectType::OBJECT)
	{
		return std::get<JSONObject>(value).sum(filter);
	}
	else if (type == JSONObjectType::ARRAY)
	{
		return std::get<JSONArray>(value).sum(filter);
	}
	else
	{
		if (auto p = std::get_if<double>(&value))
		{
			return *p;
		}
	}
	return 0.0;
}

double JSON::sum(const std::string &filter)
{
	return top->sum(filter);
}
