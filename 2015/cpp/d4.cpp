/*========================================================================
	Creator: Grimleik $

	NOTE: TODO: Replace with your own MD5 implementation, this is just
	to get things going.
========================================================================*/
#include "d4.h"
#define OPENSSL_API_COMPAT 0x10100000L // Need this to avoid deprecation warnings.
#include <openssl/md5.h>
#include <thread>
#include <mutex>
#include <vector>
#include <iostream>

struct shared_state_t
{
	const std::string_view &sv;
	const std::function<bool(const unsigned char *)> &predicate;
	std::atomic<int> work_item = {0};
	std::atomic<int> keep_working = {1};
	std::atomic<int> answer = {INT_MAX};
};

int md5_zeros_hash_mt(const std::string_view sv, const std::function<bool(const unsigned char *)> &predicate)
{
	shared_state_t shared_state(sv, predicate);
	parallelize_function(std::thread::hardware_concurrency(), [](shared_state_t *ss)
						 {
			std::string input;
			input.reserve(ss->sv.size() + 32);
			unsigned char md[MD5_DIGEST_LENGTH];
			while(ss->keep_working.load())
			{
				input.assign(ss->sv);
				int nbr = ss->work_item.fetch_add(1);
				input += std::to_string(nbr);
				MD5((const unsigned char *)(input.c_str()), input.size(), md);
				if (ss->predicate(md))
				{
#ifdef VERBOSE
					std::cout << std::dec << "MD5(" << ss->sv << " + " << nbr << ") = ";
					for (int i = 0; i < MD5_DIGEST_LENGTH; ++i)
					{
						std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)md[i];
					}
					std::cout << std::endl;
#endif
					ss->keep_working.store(0);
					int old = ss->answer.load();
					while(nbr < old && !ss->answer.compare_exchange_strong(old, nbr));
					break;
				}
			} }, &shared_state);
	return shared_state.answer;
}

// Original single threaded implementation.
int md5_zeros_hash_st(const std::string_view sv, const std::function<bool(const unsigned char *)> &predicate)
{
	int nbr = 0;
	std::string input;
	input.reserve(sv.size() + 32);
	unsigned char md[MD5_DIGEST_LENGTH];
	// nbr = 609043;
	while (nbr < INT_MAX)
	{
		input.assign(sv);
		input += std::to_string(nbr);
		MD5((const unsigned char *)(input.c_str()), input.size(), md);
		if (predicate(md))
		{
#ifdef VERBOSE
			std::cout << std::dec << "MD5(" << sv << " + " << nbr << ") = ";
			for (int i = 0; i < MD5_DIGEST_LENGTH; ++i)
			{
				std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)md[i];
			}
			std::cout << std::endl;
#endif
			break;
		}
		++nbr;
	}
	return nbr;
}

d4::d4()
{
	input_file = read_entire_file("../../../../2015/input/d4.in");
	input.push_back(std::make_pair(std::string_view(input_file->mem, input_file->sz), std::make_pair(346386, 9958218)));
}

bool d4::run()
{
	for (auto &el : input)
		CHECK_TEST(md5_zeros_hash_mt, el.first, el.second.first, [](const unsigned char *md)
				   { return ((unsigned int)md[0] == 0 && (unsigned int)md[1] == 0 && ((unsigned int)md[2] >> 4) == 0); });

	for (auto &el : input)
		CHECK_TEST(md5_zeros_hash_mt, el.first, el.second.second, [](const unsigned char *md)
				   { return ((unsigned int)md[0] == 0 && (unsigned int)md[1] == 0 && ((unsigned int)md[2]) == 0); });

	return true;
}
