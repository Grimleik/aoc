/*========================================================================
	Creator: Grimleik $
========================================================================*/
// #define VERBOSE
#include "d23.h"

d23::d23()
{
	// input_file = read_entire_file("d23_test.in");
	input_file = read_entire_file("d23.in");
	input.emplace_back(std::make_pair(std::string_view(input_file->mem),
									  std::make_pair(255, 334)));
}

bool d23::run()
{
	auto ans = solution(input[0].first);
	CHECK_VALUE(ans.first, input[0].second.first);
	CHECK_VALUE(ans.second, input[0].second.second);
	return true;
}

struct instruction_t
{
	enum OP
	{
		HLF, // UNARY
		TPL, // UNARY
		INC, // UNARY
		JMP, // UNARY
		JIE, // BINARY
		JIO	 // BINARY
	};
	OP op;
	union
	{
		struct
		{
			int a;
		} u;

		struct
		{
			int a;
			int b;
		} b;
	};

	int execute(std::vector<int> &registers, int pc)
	{
#ifdef VERBOSE
		std::cout << "PC: " << pc << " ";
#endif
		switch (op)
		{
		case HLF:
#ifdef VERBOSE
			std::cout << "HALF Reg: " << u.a << " from " << registers[u.a] << " -> ";
			registers[u.a] /= 2;
			std::cout << registers[u.a] << std::endl;
#else
			registers[u.a] /= 2;
#endif
			return 1;

		case TPL:

#ifdef VERBOSE
			std::cout << "TPL Reg: " << u.a << " from " << registers[u.a] << " -> ";
			registers[u.a] *= 3;
			std::cout << registers[u.a] << std::endl;
#else
			registers[u.a] *= 3;
#endif
			return 1;

		case INC:
#ifdef VERBOSE
			std::cout << "INC Reg: " << u.a << " from " << registers[u.a] << " -> ";
			registers[u.a]++;
			std::cout << registers[u.a] << std::endl;
#else
			registers[u.a]++;
#endif
			return 1;

		case JMP:
#ifdef VERBOSE
			std::cout << "JMP " << pc << " -> " << pc + u.a << std::endl;
#endif
			return u.a;

		case JIE:
			if (registers[b.a] % 2 == 0)
			{
#ifdef VERBOSE
				std::cout << "JIE " << pc << " -> " << pc + b.b << std::endl;
#endif
				return b.b;
			}
			else
			{
#ifdef VERBOSE
				std::cout << "JIE " << pc << " -> " << pc + 1 << std::endl;
#endif
				return 1;
			}

		case JIO:
			if (registers[b.a] == 1)
			{
#ifdef VERBOSE
				std::cout << "JIO " << pc << " -> " << pc + b.b << std::endl;
#endif
				return b.b;
			}
			else
			{
#ifdef VERBOSE
				std::cout << "JIO " << pc << " -> " << pc + 1 << std::endl;
#endif
				return 1;
			}

		default:
			return 0; // should not reach here
		}
	}
};

void execute(std::vector<instruction_t> &memory, std::vector<int> &registers, int pc)
{
	while (pc >= 0 && pc < memory.size())
	{
		auto &it = memory[pc];
		pc += it.execute(registers, pc);
	}
}

std::pair<d23::ans_t, d23::ans_t> d23::solution(const std::string_view &sv)
{
	std::pair<ans_t, ans_t> result;
	std::unordered_map<std::string_view, int> tlb;
	tlb.insert(std::make_pair("a", 0));
	tlb.insert(std::make_pair("b", 1));
	std::vector<instruction_t> memory;
	std::vector<int> registers;
	registers.push_back(0); // a
	registers.push_back(0); // b
	for (auto &i : string_view_split(sv))
	{
		auto parts = string_view_split(i, ' ', true, true);
		// todo code parsing.
		switch (parts[0][0])
		{
		case 'h':
		{
			memory.push_back({instruction_t::HLF, tlb[parts[1]]});
		}
		break;

		case 't':
		{
			memory.push_back({instruction_t::TPL, tlb[parts[1]]});
		}
		break;

		case 'i':
		{
			memory.push_back({instruction_t::INC, tlb[parts[1]]});
		}
		break;

		case 'j':
		{
			if (parts[0][1] == 'm')
			{
				int offset = 0;
				if (parts[1][0] == '-')
				{
					parts[1].remove_prefix(1);
					offset = -string_view_to_int(parts[1]);
				}
				else
				{
					parts[1].remove_prefix(1);
					offset = string_view_to_int(parts[1]);
				}
				memory.push_back({instruction_t::JMP, offset});
			}
			else if (parts[0][1] == 'i' && parts[0][2] == 'e')
			{
				parts[1].remove_suffix(1);
				instruction_t i;
				i.op = instruction_t::JIE;
				i.b.a = tlb[parts[1]];
				if (parts[2][0] == '-')
				{
					parts[2].remove_prefix(1);
					i.b.b = -string_view_to_int(parts[2]);
				}
				else
				{
					parts[2].remove_prefix(1);
					i.b.b = string_view_to_int(parts[2]);
				}
				memory.push_back(i);
			}
			else if (parts[0][1] == 'i' && parts[0][2] == 'o')
			{
				parts[1].remove_suffix(1);
				instruction_t i;
				i.op = instruction_t::JIO;
				i.b.a = tlb[parts[1]];
				if (parts[2][0] == '-')
				{
					parts[2].remove_prefix(1);
					i.b.b = -string_view_to_int(parts[2]);
				}
				else
				{
					parts[2].remove_prefix(1);
					i.b.b = string_view_to_int(parts[2]);
				}
				memory.push_back(i);
			}
		}
		break;
		default:
			assert(false && "Unchaught instruction.");
			break;
		}
	}

	execute(memory, registers, 0);
	result.first = registers[1];
	registers[0] = 1; // a
	registers[1] = 0; // b
	execute(memory, registers, 0);
	result.second = registers[1];
	return result;
}
