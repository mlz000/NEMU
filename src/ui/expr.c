#include "common.h"
#include "nemu.h"
#include "cpu/reg.h"
/* We use the POSIX regex functions to process regular expressions.
 * Type 'man regex' for more information about POSIX regex functions.
 */
#include <sys/types.h>
#include <regex.h>

extern swaddr_t find_var(char *);
enum {
	NOTYPE = 256, EQ, NE, LE, GE, AND, OR, NOT, SAL, SAR, NUM,
	HNUM, REG, NEG, DEREFER, VAR
	/* TODO: Add more token types */
};
static struct rule {
	char *regex;
	int token_type;
} rules[] = {
	/* TODO: Add more rules.
	 * Pay attention to the precedence level of different rules.
	 */
	{" +",	NOTYPE},				// white space
	{"\\+", '+'},					// plus
	{"-", '-'},
	{"\\*", '*'},
	{"/", '/'},
	{"%", '%'},
	{"<=", LE},
	{"==", EQ},						// equal
	{">=", GE},
	{"!=", NE},
	{"<", '<'},
	{">", '>'},
	{"<<", SAL},	//bitwise
	{">>", SAR},
	{"&&", AND},
	{"\\|\\|", OR},
	{"!", NOT},		//logic
	{"&", '&'},
	{"\\|", '|'},
	{"\\^", '^'},
	{"~", '~'},
	{"\\(", '('},
	{"\\)", ')'},
	{"0x[[:xdigit:]]+", HNUM},
	{"[[:digit:]]+", NUM},	//or [0-9]  These are always used inside square brackets in the form [[:alnum:]] or combined as [[:digit:]a-d]
	{"\\$[[:alpha:]]+", REG},
	{"[[:alpha:]][[:alpha:][:digit:]_]*", VAR}
};
#define NR_REGEX (sizeof(rules) / sizeof(rules[0]) )
static regex_t re[NR_REGEX];
/* Rules are used for more times.
 * Therefore we compile them only once before any usage.
 */
void init_regex() {
	int i;
	char error_msg[128];
	int ret;
	for(i = 0; i < NR_REGEX; i ++) {
		ret = regcomp(&re[i], rules[i].regex, REG_EXTENDED);
		if(ret != 0) {
			regerror(ret, &re[i], error_msg, 128);
			test(0, "regex compilation failed: %s\n%s\n", error_msg, rules[i].regex);
		}
	}
}
typedef struct token {
	int type;
	char str[32];
} Token;
Token tokens[105];
int nr_token;
int level(int type) {
	int t = 100;
	switch (type) {
		case NEG: case '~': case DEREFER: case NOT:
			t = 11;
			break;
		case '/': case '*': case '%':
			t = 10;
			break;
		case '+': case '-':
			t = 9;
			break;
		case SAL: case SAR:
			t = 8;
			break;
		case '>': case '<': case LE: case GE:
			t = 7;
			break;
		case EQ: case NE:
			t = 6;
			break;
		case '&':
			t = 5;
			break;
		case '^':
			t = 4;
			break;
		case '|':
			t = 3;
			break;
		case AND:
			t = 2;
			break;
		case OR:	
			t = 1;
			break;
	}
	return t;
}
int dominant(int l, int r) {
	int i, cnt = 0, pos = -1;
	//printf("WOW\n");	//debug
	for (i = l; i <= r; ++i) {
		switch (tokens[i].type) {
			case '(':
				++cnt;
				break;
			case ')':
				--cnt;
				break;
			case NUM: case HNUM: case REG: break;
			default:
				if (cnt == 0) {				//out of parentheses
					if (pos == -1)	pos = i;
					if (level(tokens[i].type) == level(tokens[pos].type)) {
						switch (tokens[i].type) {
							case '~': case NOT: case NEG: case DEREFER:	break;
							default: pos = i;
						}
					}
					else if (level(tokens[i].type) < level(tokens[pos].type))	pos = i;
				}
		}
	}
	return pos;
}
static bool make_token(char *e) {
	int position = 0;
	int i;
	regmatch_t pmatch;
	nr_token = 0;
	while(e[position] != '\0') {
		/* Try all rules one by one. */
		for(i = 0; i < NR_REGEX; i ++) {
			if(regexec(&re[i], e + position, 1, &pmatch, 0) == 0 && pmatch.rm_so == 0) {
				char *substr_start = e + position;
				int substr_len = pmatch.rm_eo;
				//Log("match regex[%d] at position %d with len %d: %.*s", i, position, substr_len, substr_len, substr_start);
				position += substr_len;
				/* TODO: Now a new token is recognized with rules[i]. 
				 * Add codes to perform some actions with this token.
				 */
				switch(rules[i].token_type) {
					case NOTYPE:	break;
					case NUM: case HNUM: case REG: case VAR:
						tokens[nr_token].type = rules[i].token_type;
						strncpy(tokens[nr_token].str, substr_start, substr_len);
						tokens[nr_token].str[substr_len] = '\0';
						++nr_token;
						break;
					default: 
						tokens[nr_token].type = rules[i].token_type;
						++nr_token;
				}
				break;
			}
		}
		//printf("%d\n", i);//debug
		if(i == NR_REGEX) {
			printf("no match at position %d\n%s\n%*.s^\n", position, e, position, "");
			return false;
		}
	}
	return true; 
}
bool check(int type) {
	return (type == NUM || type == HNUM || type == REG || type == ')' || type == VAR);
}
bool check_parentheses(int l, int r, bool *f) {
	int i, cnt = 0;
	bool right = (tokens[l].type == '(' && tokens[r].type == ')'); 
	for (i = l; i <= r; ++i) {
		if (tokens[i].type == '(')	++cnt;
		else if (tokens[i].type == ')')	--cnt;
		if (cnt < 0)	*f = 0;
		if (cnt == 0 && i != r) right = 0;
	}
	//printf("f:%d\n",*f);		//debug
	if (cnt != 0)	*f = 0, right = 0;
	return right;
}
bool checkunary(int type) {
	return (type == '~' || type == NOT || type == NEG || type == DEREFER);
}
uint32_t eval(int l, int r, bool *f) {
    if (l > r) {
		*f = 0;
		return 0;
		/* Bad expression */
	}
    else if (l == r) {
		uint32_t x = 0;
		bool can = 0;
		int i;
		switch (tokens[l].type) {
			case NUM:
				sscanf(tokens[l].str, "%d", &x);
				break;
			case HNUM:
				sscanf(tokens[l].str, "%x", &x);
				break;
			case REG:				//register
				for (i = 0; i < 8; ++i) {
					if (strcmp(regsl[i], tokens[l].str + 1) == 0) {
						x = reg_l(i);
						can = 1;
					}
				}
				for (i = 0; i < 8; ++i) {
					if (strcmp(regsw[i], tokens[l].str + 1) == 0) {
						x = reg_w(i);
						can = 1;
					}
				}
				for (i = 0; i < 8; ++i) {
					if (strcmp(regsb[i], tokens[l].str + 1) == 0) {
						x = reg_b(i);
						can = 1;
					}
				}
				if (strcmp("eip", tokens[l].str + 1) == 0) {
					x = cpu.eip;
					can = 1;
				}
				if (!can)	*f = 0;
				break;
			case VAR: { 
				swaddr_t addr = find_var(tokens[l].str + 1);
				if (addr != 0) {
					printf("0x%x\n", addr);//debug
					return addr;
				}
				else	*f = 0;
			}
			default : *f = 0;
		}
		return x;
	}
	else if(check_parentheses(l, r, f)) {
		/* The expression is surrounded by a matched pair of parentheses. 
		 * If that is the case, just throw away the parentheses.
		 */
		//printf("parentheses!\n");		//debug
		return eval(l + 1, r - 1, f); 
	}
    else {
		if (!(*f))	return 0;
		int op = dominant(l, r);
		uint32_t val1;
		if (op == l)	val1 = 0;
		else val1 = eval(l, op - 1, f);
		uint32_t val2 = eval(op + 1, r, f);
		//unary operator
		if (op != l && checkunary(tokens[op].type)) {
			*f = 0;
			return 0;
		}
		//binary operator
		if (op == l && !checkunary(tokens[op].type)) {
			*f = 0;
			return 0;
		}
		switch(tokens[op].type) {
		    case '+': return val1 + val2;
	  	    case '-': return val1 - val2;
	  	    case '*': return val1 * val2;
	  	    case '/': return val1 / val2;
			case '%': return val1 % val2;
			case '<': return val1 < val2;
			case '>': return val1 > val2;
			case LE: return val1 <= val2;
			case GE: return val1 >= val2;
			case EQ: return val1 == val2;
			case NE: return val1 != val2;
			case AND: return val1 && val2;
			case OR: return val1 || val2;
			case SAL: return val1 << val2;
			case SAR: return val1 >> val2;
			case '&': return val1 & val2;
			case '|': return val1 | val2;
			case '^': return val1 ^ val2;
			case NOT: return !val2;
			case '~': return ~val2;
			case DEREFER: return swaddr_read(val2, 4);
			case NEG: return -val2;
			default: *f = 0;return 0;
	 	} 
	}
}
uint32_t expr(char *e, bool *f) {
	if(!make_token(e)) {
		*f = 0;
		//printf("WRONG\n");			//debug
		return 0;
	}
	//puts(e);		//debug
	int i;
	for (i = 0; i < nr_token; ++i) {
		if(!i || !check(tokens[i-1].type)) {	//judge NEG and DEREFER
			if (tokens[i].type == '-')	tokens[i].type = NEG;
			else if (tokens[i].type == '*')	tokens[i].type = DEREFER;
		}
	}
	//debug
	//for (i = 0; i < nr_token; ++i)	printf("%c\n", tokens[i].type);
	/* TODO: Implement code to evaluate the expression. */
	return eval(0, nr_token-1, f);
}

