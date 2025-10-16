/*========================================================================
	Creator: Grimleik $
========================================================================*/
#include "d7.h"

#define INSTRUCTION_TYPE_LIST \
	X(IT_ERROR)               \
	X(IT_SIGNAL)              \
	X(IT_AND)                 \
	X(IT_OR)                  \
	X(IT_LSHIFT)              \
	X(IT_RSHIFT)              \
	X(IT_NOT)

enum instruction_type
{
#define X(a) a,
	INSTRUCTION_TYPE_LIST
#undef X
};

static const char *instruction_type_strings[] = {
#define X(a) #a,
	INSTRUCTION_TYPE_LIST
#undef X
};

struct operand
{
	int literal = -1;
	std::string var;

	std::string print() const
	{
		if (var.size() > 0)
			return var;
		return std::to_string(literal);
	}

	int evaluate(std::map<std::string, unsigned short> &memory) const
	{
		if (var.size() <= 0)
		{
			return literal;
		}
		return memory.find(var) != memory.end() ? memory[var] : -1;
	}
};

struct instruction
{
	instruction_type it;
	operand op1, op2, op3;
	bool executed = {false};

	void print() const;
	void execute(std::map<std::string, unsigned short> &memory);
	bool can_execute(std::map<std::string, unsigned short> &memory, const int idx);
};

// binary/tertiary ops ?
void instruction::print() const
{
	switch (it)
	{
	case IT_AND:
		std::cout << op1.print() << " AND " << op2.print() << " -> " << op3.var
				  << std::endl;
		break;
	case IT_OR:
		std::cout << op1.print() << " OR " << op2.print() << " -> " << op3.var
				  << std::endl;
		break;
	case IT_SIGNAL:
		std::cout << op1.print() << " -> " << op2.print() << std::endl;
		break;
	case IT_LSHIFT:
		std::cout << op1.print() << " LSHIFT " << op2.print() << " -> " << op3.var
				  << std::endl;
		break;
	case IT_RSHIFT:
		std::cout << op1.print() << " RSHIFT " << op2.print() << " -> " << op3.var
				  << std::endl;
		break;
	case IT_NOT:
		std::cout << "NOT " << op1.print() << " -> " << op2.var << std::endl;
		break;
	default:
		std::cerr << "Unknown instruction." << std::endl;
		break;
	}
}

void instruction::execute(std::map<std::string, unsigned short> &memory)
{
	executed = true;
	switch (it)
	{
	case IT_AND:
	{
		// TODO: Fix this instruction so it can execute with literals.
		int lop = op1.evaluate(memory);
		int rop = op2.evaluate(memory);
		if (lop != -1 && rop != -1)
		{
			memory[op3.var] = lop & rop;
#ifdef VERBOSE
			std::cout << op3.var << " : " << memory[op3.var] << std::endl;
#endif
		}
		else
		{
			std::cout << "Gate missing value, not executed: " << lop << " " << rop
					  << std::endl;
		}
	}
	break;
	case IT_OR:
	{
		int lop = op1.evaluate(memory);
		int rop = op2.evaluate(memory);
		if (lop != -1 && rop != -1)
		{
			memory[op3.var] = lop | rop;
#ifdef VERBOSE
			std::cout << op3.var << " : " << memory[op3.var] << std::endl;
#endif
		}
		else
		{
			std::cout << "Gate missing value, not executed: " << lop << " " << rop
					  << std::endl;
		}
	}
	break;
	case IT_SIGNAL:
	{
		int lop = op1.evaluate(memory);
		if (lop != -1)
		{
			memory[op2.var] = lop;
#ifdef VERBOSE
			std::cout << op2.var << " : " << memory[op2.var] << std::endl;
#endif
		}
		else
		{
			std::cout << "Failed to signal value. " << std::endl;
		}
	}
	break;

	case IT_LSHIFT:
	{
		int lop = op1.evaluate(memory);
		int rop = op2.evaluate(memory);
		if (lop != -1 && rop != -1)
		{
			memory[op3.var] = lop << rop;
#ifdef VERBOSE
			std::cout << op3.var << " : " << memory[op3.var] << std::endl;
#endif
		}
		else
		{
			std::cout << "Gate missing value, not executed: " << lop << " " << rop
					  << std::endl;
		}
	}
	break;
	case IT_RSHIFT:
	{
		int lop = op1.evaluate(memory);
		int rop = op2.evaluate(memory);
		if (lop != -1 && rop != -1)
		{
			memory[op3.var] = lop >> rop;
#ifdef VERBOSE
			std::cout << op3.var << " : " << memory[op3.var] << std::endl;
#endif
		}
		else
		{
			std::cout << "Gate missing value, not executed: " << lop << " " << rop
					  << std::endl;
		}
	}
	break;
	case IT_NOT:
	{
		int lop = op1.evaluate(memory);
		if (lop != -1)
		{
			memory[op2.var] = ~lop;
#ifdef VERBOSE
			std::cout << op2.var << " : " << memory[op2.var] << std::endl;
#endif
		}
		else
		{
			std::cout << "Failed to invert." << std::endl;
		}
	}
	break;
	default:
		std::cerr << "Unknown instruction." << std::endl;
		break;
	}
}

bool instruction::can_execute(std::map<std::string, unsigned short> &memory, const int idx)
{
	if (executed)
		return false;

	switch (it)
	{
	case IT_OR:
	case IT_AND:
#ifdef VERBOSE
		if (op1.var.size() && op1.var.size())
		{
			if (memory.find(op1.var) != memory.end() && memory.find(op2.var) == memory.end())
			{
				std::cout << std::format("Unable to execute command {}, op1 ({}) in memory, but op2 ({}) is not.",
										 idx, op1.var, op2.var)
						  << std::endl;
			}

			if (memory.find(op1.var) == memory.end() && memory.find(op2.var) != memory.end())
			{
				std::cout << std::format("Unable to execute command {} , op1 {} in memory, but op2 {} is not.",
										 idx, op1.var, op2.var)
						  << std::endl;
			}
		}
#endif
		return (op1.var.size() <= 0 || memory.find(op1.var) != memory.end()) &&
			   (op2.var.size() <= 0 || memory.find(op2.var) != memory.end());
	case IT_NOT:
	case IT_LSHIFT:
	case IT_RSHIFT:
	case IT_SIGNAL:
#ifdef VERBOSE
		// if (op1.literal <= 0)
		// {
		// 	std::cout << instruction_type_strings[it] << " has no value." << std::endl;
		// }
#endif
		return op1.var.size() <= 0 || memory.find(op1.var) != memory.end();

	default:
		// assert(false && "Unhandled instruction.");
		break;
	}
	return true;
}

void execute_program(std::vector<instruction> instructions,
					 std::map<std::string, unsigned short> &memory)
{
	while (instructions.size() > 0)
	{
		std::optional<instruction> active;
		int idx = 0, executed_instructions = 0;
		for (auto &i : instructions)
		{
			if (i.can_execute(memory, idx + 1))
			{
#ifdef VERBOSE
				std::cout << "Executed instruction: " << idx + 1 << std::endl;
				i.print();
#endif
				i.execute(memory);
				active = i;
#ifdef VERBOSE
				std::cout << " === MEMORY LAYOUT === " << std::endl;
				for (auto [k, v] : memory)
				{
					std::cout << "\t" << k << " : " << v << std::endl;
				}
#endif
				break;
			}
#ifdef VERBOSE
			else if (instructions.size() <= 320 && i.op1.var.size() <= 1)
			{
				std::cout << "Can't execute(" << instructions.size() << "):";
				i.print();
			}
#endif
			else if (i.executed)
			{
				++executed_instructions;
			}
			++idx;
		}
		if (executed_instructions == instructions.size())
		{
			break;
		}
		if (!active.has_value() && executed_instructions < instructions.size())
		{
			std::cout << " === MEMORY LAYOUT === " << std::endl;
			for (auto [k, v] : memory)
			{
				std::cout << "\t" << k << " : " << v << std::endl;
			}
			int is_idx = 0;
			for (auto &i : instructions)
			{
				if (i.executed)
				{
					std::cout << "Already executed: ";
					i.print();
					switch (i.it)
					{
					case IT_AND:
					case IT_OR:
					{
						assert(memory.find(i.op3.var) != memory.end());
						std::cout << std::format("Result is in memory: {} = {}", i.op3.var, memory[i.op3.var]) << std::endl;
					}
					break;
					case IT_NOT:
					case IT_LSHIFT:
					case IT_SIGNAL:
					case IT_RSHIFT:
					{
						assert(memory.find(i.op2.var) != memory.end());
						std::cout << std::format("Result is in memory: {} = {}", i.op2.var, memory[i.op2.var]) << std::endl;
					}
					default:
						break;
					}
					is_idx++;
					continue;
				}
				switch (i.it)
				{
				case IT_AND:
				case IT_OR:
					if (i.op1.var.size() > 0 && i.op2.var.size() > 0)
					{
						std::string err = std::format("Unable to execute command {}, missing one operand: ", is_idx + 1);
						int err_count = 0;
						if (memory.find(i.op1.var) == memory.end())
						{
							err += "op1 (" + i.op1.var + ") not in memory, but op2 (" + i.op2.var + ") is, ";
							++err_count;
						}
						if (memory.find(i.op2.var) == memory.end())
						{
							err += "op2 (" + i.op2.var + ") not in memory, but op1 (" + i.op1.var + ") is, ";
							++err_count;
						}
						if (err_count == 1)
							std::cout << err << std::endl;
					}
					break;
				case IT_NOT:
				case IT_LSHIFT:
				case IT_RSHIFT:
				case IT_SIGNAL:
					if (i.op1.var.size() > 0)
					{
						if (memory.find(i.op1.var) == memory.end())
						{
							std::cout << "Missing: " << i.op1.var << std::format(" for instruction {}: ", is_idx + 1);
							i.print();
						}
					}
					break;
				}
				is_idx++;
			}
			assert(active.has_value());
		}
	}
}

void parse_instructions(const std::string_view &sv, std::vector<instruction> &instructions)
{
	int i = 0;
	std::vector<std::string_view> split = string_view_split(sv);
	instructions.resize(split.size());
	while (i < split.size())
	{
		instruction &instruction = instructions[i];
		const char *digest = split[i].data();
		if ((*digest - '0') >= 0 && (*digest - '0') <= 9)
		{
			instruction.it = IT_SIGNAL;
			instruction.op1.literal = get_number(&digest);
		}
		// is it a variable ?
		else if (!(is_whitespace(*digest) || is_numeric(*digest)))
		{
			if (*digest == 'N')
			{
				// instruction!
				instruction.it = IT_NOT;
				digest += 3;
				instruction.op1.var = get_variable(&digest);
			}
			else
			{
				instruction.it = IT_SIGNAL;
				instruction.op1.var = get_variable(&digest);
			}
		}

		char symb = get_symbol(&digest);
		if (symb == '-') // ->
		{
			instruction.op2.var = get_variable(&digest);
		}
		else if (symb == 'A')
		{
			instruction.it = IT_AND;
			digest += 3;
			instruction.op2.var = get_variable(&digest);
			instruction.op3.var = get_variable(&digest);
		}
		else if (symb == 'O')
		{
			instruction.it = IT_OR;
			digest += 2;
			instruction.op2.var = get_variable(&digest);
			instruction.op3.var = get_variable(&digest);
		}
		else if (symb == 'L')
		{
			digest += 6;
			instruction.it = IT_LSHIFT;
			instruction.op2.literal = get_number(&digest);
			instruction.op3.var = get_variable(&digest);
		}
		else if (symb == 'R')
		{
			instruction.it = IT_RSHIFT;
			digest += 6;
			instruction.op2.literal = get_number(&digest);
			instruction.op3.var = get_variable(&digest);
		}
		else
		{
			assert(false && "Unhandled instruction!");
		}
		++i;
	}
}

std::pair<int, int> d7::solution(const std::string_view &sv, const char *reg_name, const char *override_name)
{
	std::pair<int, int> result;
	std::map<std::string, unsigned short> memory;
	std::vector<instruction> instructions;
	parse_instructions(sv, instructions);
	execute_program(instructions, memory);
	result.first = memory[reg_name];
	unsigned short override_value = memory[reg_name];
	memory.clear();
	for (auto &inst : instructions)
	{
		if (inst.it == instruction_type::IT_SIGNAL && inst.op2.var == override_name)
		{
			inst.op1.literal = override_value;
			break;
		}
	}

	execute_program(instructions, memory);
#ifdef VERBOSE
	std::cout << "\tFinal memory layout:" << std::endl;
	for (auto [k, v] : memory)
	{
		std::cout << "\t\t" << k << " : " << v << std::endl;
	}
#endif

	result.second = memory[reg_name];
	return result;
}

d7::d7()
{
	input_file = read_entire_file("../../../../2015/input/d7.in");
	input.push_back(std::make_pair(input_t{std::string_view(input_file->mem), "a", "b"}, std::make_pair(16076, 2797)));
}

bool d7::run()
{
	for (auto &t : input)
	{
		auto ans = solution(t.first.sv, t.first.reg_output, t.first.reg_override);
		CHECK_VALUE(ans.first, t.second.first);
		CHECK_VALUE(ans.second, t.second.second);
	}
	return true;
}