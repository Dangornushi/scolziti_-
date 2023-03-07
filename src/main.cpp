#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>


#define END -1
#define NUM 0
#define OP_PM 1
#define OP_MD 2

using namespace std;

char src[1024];
int pos = 0;
int len = 0;

typedef struct {
    string t_data;
    int t_num;
} Token;

typedef struct Node {
    string token_data;
    int token_id ;
    Node *next_node;
    Token *token;

    Node *lhs;
    Node *rhs;
} Node;

void out_label(char *str) {
    int len;
    len = strlen(str);
    write(1, str, len);
    write(1, "\n", 1);
}

void out(char *str) {
    write(1, "\t", 1);
    out_label(str);
}

int program;

void parse(auto token);

class Parse {
    private:
        vector<Token>::iterator token;
        void expect(int code);
        Node* Num();
        Node* PlusMin();
        Node* add_Node();
        Node* end_Node();
    public:
        Node* parse();
        Parse(auto token);
        ~Parse();
};

void  Parse::expect(int code) {
    if (this->token->t_num != END);
}

Node* Parse::add_Node(Node* node) {
    return new Node {
       .lhs = node,
       .rhs = PlusMin()
    };
}

Node* Parse::end_Node() {
    Node* node = new Node {
        .token_data = this->token->t_data,
        .token_id = this->token->t_num
    };
    return node;
}

Node* Parse::Num() {
    //cout << "num: " << this->token->t_data << endl;
    Node *node = end_Node();
    this->token++;

    return node;
}

Node* Parse::PlusMin() {
    Node* node;
    Node* next_node = Num();
    if (this->token->t_num == OP_PM || this->token->t_num == OP_MD) {
    //cout << "p m: " << this->token->t_data << endl;
        node = new Node{this->token->t_data, this->token++->t_num, next_node};
    }
    return node;
}

Node* Parse::parse() {
    while (1) { 
        Node* node =new add_Node(node);
        if ((token-1)->t_num == -1) break;
    }
}

Parse::Parse(auto token) {
    this->token = token;
}

Parse::~Parse() {
}

void emit() {
    char buf[1024];
    sprintf(buf, "movq $%d, %%rax", program);
    out(buf);
}

vector<Token> tokenize(string data) {
    vector<Token>Tokens;
    const char *c_data = data.c_str();
    int len = 0;

    for (;len < data.size();) {
        switch (*c_data) {
            case '+':
            case '-': {
                char char_to_str[] = {*c_data};
                string char_to_str_str = string(char_to_str);
                Tokens.push_back({char_to_str_str, OP_PM}); 
                len++;
                c_data++;
                break;
            }

            case '*':
            case '/':{
                char char_to_str[] = {*c_data};
                string char_to_str_str = string(char_to_str);
                Tokens.push_back({char_to_str_str, OP_MD}); 
                len++;
                c_data++;
                break;
            }
            case ' ': {
                len++;
                c_data++;
                break;
            }
            default: {
                int num = 0;
                for (;;) { 
                    if (*c_data >= '0' && *c_data <= '9') {
                        num *= 10;
                        num += ((char)*c_data - '0');
                    }
                    else break;
                    c_data++;
                    len++;
                }
                Tokens.push_back({to_string(num), NUM}); 
                break;
            }
        }
    }
    Tokens.push_back({"", END});
    return Tokens;
}

int main() {
    string data = "10 + 2 - 12 + 46 + 56 - 100";
    vector<Token>Tokens = tokenize(data);
    vector<Token>::iterator t = Tokens.begin();

    out(".file \"main.c\"");
    out(".text");
    out(".globl main");
    out(".type main, @function");
    out_label("main:");

    Parse *parse  = new Parse(t);
    parse->parse();
    delete parse;

    out("pushq  %rbp");
    out("movq   %rsp, %rbp");
    //out("ret");
    /*
    out("pushq  %rbp");
    out("movq   %rsp, %rbp");
    */

    len = read(0, src, 1024);

    emit();

    out("leave");
    out("ret");
}
