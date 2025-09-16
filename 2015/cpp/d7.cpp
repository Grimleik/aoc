/*
* In the future come back here and do a correct parsing pass.
*/
#include <iostream>
#include <map>
#include <vector>
#include <assert.h>
#include <string>
#include <optional>

// SIGNAL, AND, L/RSHIFT, NOT

static const char *input[] = {
    "lf AND lq -> ls",
    "iu RSHIFT 1 -> jn",
    "bo OR bu -> bv",
    "gj RSHIFT 1 -> hc",
    "et RSHIFT 2 -> eu",
    "bv AND bx -> by",
    "is OR it -> iu",
    "b OR n -> o",
    "gf OR ge -> gg",
    "NOT kt -> ku",
    "ea AND eb -> ed",
    "kl OR kr -> ks",
    "hi AND hk -> hl",
    "au AND av -> ax",
    "lf RSHIFT 2 -> lg",
    "dd RSHIFT 3 -> df",
    "eu AND fa -> fc",
    "df AND dg -> di",
    "ip LSHIFT 15 -> it",
    "NOT el -> em",
    "et OR fe -> ff",
    "fj LSHIFT 15 -> fn",
    "t OR s -> u",
    "ly OR lz -> ma",
    "ko AND kq -> kr",
    "NOT fx -> fy",
    "et RSHIFT 1 -> fm",
    "eu OR fa -> fb",
    "dd RSHIFT 2 -> de",
    "NOT go -> gp",
    "kb AND kd -> ke",
    "hg OR hh -> hi",
    "jm LSHIFT 1 -> kg",
    "NOT cn -> co",
    "jp RSHIFT 2 -> jq",
    "jp RSHIFT 5 -> js",
    "1 AND io -> ip",
    "eo LSHIFT 15 -> es",
    "1 AND jj -> jk",
    "g AND i -> j",
    "ci RSHIFT 3 -> ck",
    "gn AND gp -> gq",
    "fs AND fu -> fv",
    "lj AND ll -> lm",
    "jk LSHIFT 15 -> jo",
    "iu RSHIFT 3 -> iw",
    "NOT ii -> ij",
    "1 AND cc -> cd",
    "bn RSHIFT 3 -> bp",
    "NOT gw -> gx",
    "NOT ft -> fu",
    "jn OR jo -> jp",
    "iv OR jb -> jc",
    "hv OR hu -> hw",
    "19138 -> b",
    "gj RSHIFT 5 -> gm",
    "hq AND hs -> ht",
    "dy RSHIFT 1 -> er",
    "ao OR an -> ap",
    "ld OR le -> lf",
    "bk LSHIFT 1 -> ce",
    "bz AND cb -> cc",
    "bi LSHIFT 15 -> bm",
    "il AND in -> io",
    "af AND ah -> ai",
    "as RSHIFT 1 -> bl",
    "lf RSHIFT 3 -> lh",
    "er OR es -> et",
    "NOT ax -> ay",
    "ci RSHIFT 1 -> db",
    "et AND fe -> fg",
    "lg OR lm -> ln",
    "k AND m -> n",
    "hz RSHIFT 2 -> ia",
    "kh LSHIFT 1 -> lb",
    "NOT ey -> ez",
    "NOT di -> dj",
    "dz OR ef -> eg",
    "lx -> a",
    "NOT iz -> ja",
    "gz LSHIFT 15 -> hd",
    "ce OR cd -> cf",
    "fq AND fr -> ft",
    "at AND az -> bb",
    "ha OR gz -> hb",
    "fp AND fv -> fx",
    "NOT gb -> gc",
    "ia AND ig -> ii",
    "gl OR gm -> gn",
    "0 -> c",
    "NOT ca -> cb",
    "bn RSHIFT 1 -> cg",
    "c LSHIFT 1 -> t",
    "iw OR ix -> iy",
    "kg OR kf -> kh",
    "dy OR ej -> ek",
    "km AND kn -> kp",
    "NOT fc -> fd",
    "hz RSHIFT 3 -> ib",
    "NOT dq -> dr",
    "NOT fg -> fh",
    "dy RSHIFT 2 -> dz",
    "kk RSHIFT 2 -> kl",
    "1 AND fi -> fj",
    "NOT hr -> hs",
    "jp RSHIFT 1 -> ki",
    "bl OR bm -> bn",
    "1 AND gy -> gz",
    "gr AND gt -> gu",
    "db OR dc -> dd",
    "de OR dk -> dl",
    "as RSHIFT 5 -> av",
    "lf RSHIFT 5 -> li",
    "hm AND ho -> hp",
    "cg OR ch -> ci",
    "gj AND gu -> gw",
    "ge LSHIFT 15 -> gi",
    "e OR f -> g",
    "fp OR fv -> fw",
    "fb AND fd -> fe",
    "cd LSHIFT 15 -> ch",
    "b RSHIFT 1 -> v",
    "at OR az -> ba",
    "bn RSHIFT 2 -> bo",
    "lh AND li -> lk",
    "dl AND dn -> do",
    "eg AND ei -> ej",
    "ex AND ez -> fa",
    "NOT kp -> kq",
    "NOT lk -> ll",
    "x AND ai -> ak",
    "jp OR ka -> kb",
    "NOT jd -> je",
    "iy AND ja -> jb",
    "jp RSHIFT 3 -> jr",
    "fo OR fz -> ga",
    "df OR dg -> dh",
    "gj RSHIFT 2 -> gk",
    "gj OR gu -> gv",
    "NOT jh -> ji",
    "ap LSHIFT 1 -> bj",
    "NOT ls -> lt",
    "ir LSHIFT 1 -> jl",
    "bn AND by -> ca",
    "lv LSHIFT 15 -> lz",
    "ba AND bc -> bd",
    "cy LSHIFT 15 -> dc",
    "ln AND lp -> lq",
    "x RSHIFT 1 -> aq",
    "gk OR gq -> gr",
    "NOT kx -> ky",
    "jg AND ji -> jj",
    "bn OR by -> bz",
    "fl LSHIFT 1 -> gf",
    "bp OR bq -> br",
    "he OR hp -> hq",
    "et RSHIFT 5 -> ew",
    "iu RSHIFT 2 -> iv",
    "gl AND gm -> go",
    "x OR ai -> aj",
    "hc OR hd -> he",
    "lg AND lm -> lo",
    "lh OR li -> lj",
    "da LSHIFT 1 -> du",
    "fo RSHIFT 2 -> fp",
    "gk AND gq -> gs",
    "bj OR bi -> bk",
    "lf OR lq -> lr",
    "cj AND cp -> cr",
    "hu LSHIFT 15 -> hy",
    "1 AND bh -> bi",
    "fo RSHIFT 3 -> fq",
    "NOT lo -> lp",
    "hw LSHIFT 1 -> iq",
    "dd RSHIFT 1 -> dw",
    "dt LSHIFT 15 -> dx",
    "dy AND ej -> el",
    "an LSHIFT 15 -> ar",
    "aq OR ar -> as",
    "1 AND r -> s",
    "fw AND fy -> fz",
    "NOT im -> in",
    "et RSHIFT 3 -> ev",
    "1 AND ds -> dt",
    "ec AND ee -> ef",
    "NOT ak -> al",
    "jl OR jk -> jm",
    "1 AND en -> eo",
    "lb OR la -> lc",
    "iu AND jf -> jh",
    "iu RSHIFT 5 -> ix",
    "bo AND bu -> bw",
    "cz OR cy -> da",
    "iv AND jb -> jd",
    "iw AND ix -> iz",
    "lf RSHIFT 1 -> ly",
    "iu OR jf -> jg",
    "NOT dm -> dn",
    "lw OR lv -> lx",
    "gg LSHIFT 1 -> ha",
    "lr AND lt -> lu",
    "fm OR fn -> fo",
    "he RSHIFT 3 -> hg",
    "aj AND al -> am",
    "1 AND kz -> la",
    "dy RSHIFT 5 -> eb",
    "jc AND je -> jf",
    "cm AND co -> cp",
    "gv AND gx -> gy",
    "ev OR ew -> ex",
    "jp AND ka -> kc",
    "fk OR fj -> fl",
    "dy RSHIFT 3 -> ea",
    "NOT bs -> bt",
    "NOT ag -> ah",
    "dz AND ef -> eh",
    "cf LSHIFT 1 -> cz",
    "NOT cv -> cw",
    "1 AND cx -> cy",
    "de AND dk -> dm",
    "ck AND cl -> cn",
    "x RSHIFT 5 -> aa",
    "dv LSHIFT 1 -> ep",
    "he RSHIFT 2 -> hf",
    "NOT bw -> bx",
    "ck OR cl -> cm",
    "bp AND bq -> bs",
    "as OR bd -> be",
    "he AND hp -> hr",
    "ev AND ew -> ey",
    "1 AND lu -> lv",
    "kk RSHIFT 3 -> km",
    "b AND n -> p",
    "NOT kc -> kd",
    "lc LSHIFT 1 -> lw",
    "km OR kn -> ko",
    "id AND if -> ig",
    "ih AND ij -> ik",
    "jr AND js -> ju",
    "ci RSHIFT 5 -> cl",
    "hz RSHIFT 1 -> is",
    "1 AND ke -> kf",
    "NOT gs -> gt",
    "aw AND ay -> az",
    "x RSHIFT 2 -> y",
    "ab AND ad -> ae",
    "ff AND fh -> fi",
    "ci AND ct -> cv",
    "eq LSHIFT 1 -> fk",
    "gj RSHIFT 3 -> gl",
    "u LSHIFT 1 -> ao",
    "NOT bb -> bc",
    "NOT hj -> hk",
    "kw AND ky -> kz",
    "as AND bd -> bf",
    "dw OR dx -> dy",
    "br AND bt -> bu",
    "kk AND kv -> kx",
    "ep OR eo -> eq",
    "he RSHIFT 1 -> hx",
    "ki OR kj -> kk",
    "NOT ju -> jv",
    "ek AND em -> en",
    "kk RSHIFT 5 -> kn",
    "NOT eh -> ei",
    "hx OR hy -> hz",
    "ea OR eb -> ec",
    "s LSHIFT 15 -> w",
    "fo RSHIFT 1 -> gh",
    "kk OR kv -> kw",
    "bn RSHIFT 5 -> bq",
    "NOT ed -> ee",
    "1 AND ht -> hu",
    "cu AND cw -> cx",
    "b RSHIFT 5 -> f",
    "kl AND kr -> kt",
    "iq OR ip -> ir",
    "ci RSHIFT 2 -> cj",
    "cj OR cp -> cq",
    "o AND q -> r",
    "dd RSHIFT 5 -> dg",
    "b RSHIFT 2 -> d",
    "ks AND ku -> kv",
    "b RSHIFT 3 -> e",
    "d OR j -> k",
    "NOT p -> q",
    "NOT cr -> cs",
    "du OR dt -> dv",
    "kf LSHIFT 15 -> kj",
    "NOT ac -> ad",
    "fo RSHIFT 5 -> fr",
    "hz OR ik -> il",
    "jx AND jz -> ka",
    "gh OR gi -> gj",
    "kk RSHIFT 1 -> ld",
    "hz RSHIFT 5 -> ic",
    "as RSHIFT 2 -> at",
    "NOT jy -> jz",
    "1 AND am -> an",
    "ci OR ct -> cu",
    "hg AND hh -> hj",
    "jq OR jw -> jx",
    "v OR w -> x",
    "la LSHIFT 15 -> le",
    "dh AND dj -> dk",
    "dp AND dr -> ds",
    "jq AND jw -> jy",
    "au OR av -> aw",
    "NOT bf -> bg",
    "z OR aa -> ab",
    "ga AND gc -> gd",
    "hz AND ik -> im",
    "jt AND jv -> jw",
    "z AND aa -> ac",
    "jr OR js -> jt",
    "hb LSHIFT 1 -> hv",
    "hf OR hl -> hm",
    "ib OR ic -> id",
    "fq OR fr -> fs",
    "cq AND cs -> ct",
    "ia OR ig -> ih",
    "dd OR do -> dp",
    "d AND j -> l",
    "ib AND ic -> ie",
    "as RSHIFT 3 -> au",
    "be AND bg -> bh",
    "dd AND do -> dq",
    "NOT l -> m",
    "1 AND gd -> ge",
    "y AND ae -> ag",
    "fo AND fz -> gb",
    "NOT ie -> if",
    "e AND f -> h",
    "x RSHIFT 3 -> z",
    "y OR ae -> af",
    "hf AND hl -> hn",
    "NOT h -> i",
    "NOT hn -> ho",
    "he RSHIFT 5 -> hh",
};

const char *instruction_set[] = {
    "123 -> xy",
    "456 -> yx",
    "xy AND yx -> d",
    "xy OR yx -> e",
    "xy LSHIFT 2 -> f",
    "yx RSHIFT 2 -> g",
    "NOT xy -> h",
    "NOT yx -> i"};


enum instruction_type
{
    IT_ERROR,
    IT_SIGNAL,
    IT_AND,
    IT_OR,
    IT_LSHIFT,
    IT_RSHIFT,
    IT_NOT,
};

struct operand
{
    int literal = -1;
    std::string var;

    std::string print()
    {
        if (var.size() > 0)
            return var;
        return std::to_string(literal);
    }

    int evaluate(std::map<std::string, unsigned short> &memory)
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

    void print();
    void execute(std::map<std::string, unsigned short> &memory);
    bool can_execute(std::map<std::string, unsigned short> &memory);
};

// binary/tertiary ops ?
void instruction::print()
{
    switch (it)
    {
    case IT_AND:
        std::cout << op1.print() << " AND " << op2.print() << " -> " << op3.var << std::endl;
        break;
    case IT_OR:
        std::cout << op1.print() << " OR " << op2.print() << " -> " << op3.var << std::endl;
        break;
    case IT_SIGNAL:
        std::cout << op1.print() << " -> " << op2.print() << std::endl;
        break;
    case IT_LSHIFT:
        std::cout << op1.print() << " LSHIFT " << op2.print() << " -> " << op3.var << std::endl;
        break;
    case IT_RSHIFT:
        std::cout << op1.print() << " RSHIFT " << op2.print() << " -> " << op3.var << std::endl;
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
            // std::cout << op3.var << " : " << memory[op3.var] << std::endl;
        }
        else
        {
            std::cout << "Gate missing value, not executed: " << lop << " " << rop << std::endl;
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
            // std::cout << op3.var << " : " << memory[op3.var] << std::endl;
        }
        else
        {
            std::cout << "Gate missing value, not executed: " << lop << " " << rop << std::endl;
        }
    }
    break;
    case IT_SIGNAL:
    {
        int lop = op1.evaluate(memory);
        if (lop != -1)
        {
            memory[op2.var] = lop;
            // std::cout << op2.var << " : " << memory[op2.var] << std::endl;
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
            // std::cout << op3.var << " : " << memory[op3.var] << std::endl;
        }
        else
        {
            std::cout << "Gate missing value, not executed: " << lop << " " << rop << std::endl;
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
            // std::cout << op3.var << " : " << memory[op3.var] << std::endl;
        }
        else
        {
            std::cout << "Gate missing value, not executed: " << lop << " " << rop << std::endl;
        }
    }
    break;
    case IT_NOT:
    {
        int lop = op1.evaluate(memory);
        if (lop != -1)
        {
            memory[op2.var] = ~lop;
            // std::cout << op2.var << " : " << memory[op2.var] << std::endl;
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

bool instruction::can_execute(std::map<std::string, unsigned short> &memory)
{
    switch (it)
    {
    case IT_OR:
    case IT_AND:
        return (op1.var.size() <= 0 || memory.find(op1.var) != memory.end()) &&
               (op2.var.size() <= 0 || memory.find(op2.var) != memory.end());

    case IT_NOT:
    case IT_LSHIFT:
    case IT_RSHIFT:
    case IT_SIGNAL:
        return op1.var.size() <= 0 || memory.find(op1.var) != memory.end();

    default:
        // assert(false && "Unhandled instruction.");
        break;
    }
    return true;
}

void execute_program(std::vector<instruction> instructions, std::map<std::string, unsigned short> &memory)
{
    while (instructions.size() > 0)
    {
        std::optional<instruction> active;
        int idx = 0;
        for (auto &i : instructions)
        {
            if (i.can_execute(memory))
            {
                // i.print();
                i.execute(memory);
                active = i;

                // std::cout << " === MEMORY LAYOUT === " << std::endl;
                // for (auto [k, v] : memory)
                // {
                //     std::cout << "\t" << k << " : " << v << std::endl;
                // }
                break;
            }
            // else if (instructions.size() <= 320 && i.op1.var.size() <= 1)
            // {
            //     std::cout << "Can't execute(" << instructions.size() << "):";
            //     i.print();
            // }
            ++idx;
        }
        assert(active.has_value());
        // NOTE: Why cant we just use the obj ?
        instructions.erase(instructions.begin() + idx);
    }
}

int d7(int, char **)
{
    int i = 0;
    int len = _countof(input);
    std::vector<instruction> instructions(len);
    // TODO: Proper parsing, lexing then program construction.
    while (i < len)
    {
        instruction &instruction = instructions[i];
        const char *digest = input[i];
        // NOTE: Determine first segment. This can be a:
        // signal, variable, start of instruction NOT.
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
                instruction.op2.var = get_variable(&digest);
            }
            else
            {
                instruction.op1.var = get_variable(&digest);
            }
        }

        char symb = get_symbol(&digest);
        if (symb == '-')
        {
            // assert(instruction.it == IT_SIGNAL);
            instruction.it = IT_SIGNAL;
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
        else if (instruction.it == IT_NOT)
        {
            // done!
        }
        else
        {
            assert(false && "Unhandled instruction!");
        }
        ++i;
    }

    std::map<std::string, unsigned short> memory;
    execute_program(instructions, memory);
    std::cout << "A: " << memory["a"] << std::endl;
    unsigned short aVal = memory["a"];
    memory.clear();
    // memory["b"] = aVal;
    instructions[54].op1.literal = aVal;
    // instructions.erase(instructions.begin() + 55);
    execute_program(instructions, memory);
    std::cout << "A: " << memory["a"] << std::endl;
    // std::cout << "Final memory layout:" << std::endl;
    // for (auto [k, v] : memory)
    // {
    //     std::cout << "\t" << k << " : " << v << std::endl;
    // }

    return 0;
}
