#include <iostream>
#include <iomanip>
#include <bitset>

using namespace std;

void
printbin(int x)
{
    bitset<8> b(x);
    cout << b;
}

int
hextoint(const char &x)
{
    if ( 'a' <= x && x <= 'f' )     return x - int('a') + 10;
    if ( 'A' <= x && x <= 'F' )     return x - int('A') + 10;
    if ( '0' <= x && x <= '9' )     return x - (int) '0';
                                    return 0;
}

inline int
inttohex(const int &x)
{
    if(0 <= x && x <= 9)    return '0' + x;
    if(10 <= x && x <= 15)  return 'A' + x - 10;
                            return 0;
}

void
proccess_key(__int8 *array, const string &str)
{
    int length = str.size();
    for(int i = 0, k = 0; i < length; i += 2, k++) {
        int a = hextoint(str[i]),
            b = hextoint(str[i + 1]),
            c = a << 4 | b;
        *(array + k) = (__int8) c;
    }
}

void
proccess_text(__int8 *array, const string &str)
{
    int length = str.size();
    memcpy(array, str.data(), length);
}

void
complete_str(__int8* array, int &size, int block_size, char symbol)
{
    while(size % block_size != 0) {
        *(array + size++) = (__int8) symbol;
    }
}

void
feistel_xor(__int8 *left, int left_start,
            __int8 *right, int right_start,
            int length)
{
    for(int i = 0; i < length; i++) {
        __int8 a = left[left_start + i];
        __int8 b = right[right_start + i];
        __int8 c = a ^ b;
        left[left_start + i] = c;
    }
}

void
feistel_assigment(__int8 *left, int left_start,
                  __int8 *right, int right_start,
                  int length)
{
    memcpy(left + left_start, right + right_start, length);
}

void
feistel(__int8 *text, int text_size, __int8 *key,
        int rounds, int block_size)
{
// Phad 1d2R ef00
// [--] [--] [--] - block_size
// [][] [][] [][] - block_size / 2
//
// i_n = (plain_text.size() / block_size)
// i += 1
//
// left:
//      plain_text.substr(i * block_size,  block_size / 2)
// right:
//      plain_text.substr(i * block_size + block_size / 2,  block_size / 2)
//
    const int half_block_size = block_size / 2;
    __int8 *x = (__int8 *) malloc(half_block_size * sizeof(__int8));
    for(int block = 0; block < (text_size / block_size); block++) {
        for(int current_round = 0; current_round < rounds; current_round++) {
            int left = block * block_size;
            int right = left + half_block_size;
            // left xor key
            feistel_xor(text, left,
                        key, current_round * half_block_size,
                        half_block_size);
            // left xor right
            feistel_xor(text, left,
                        text, right,
                        half_block_size);
            // save left
            feistel_assigment(x, 0,
                              text, left,
                              half_block_size);
            // left = right
            feistel_assigment(text, left,
                              text, right,
                              half_block_size);
            // right = x
            feistel_assigment(text, right,
                              x, 0,
                              half_block_size);
        }
    }
    free(x);
}

void
printhex(__int8 *text, int text_size)
{
    string str;
    for(int i = 0; i < text_size; i++) {
        int c = (int) *(text + i);
        if (c < 0) {
            c += 256;
        }
        int a = inttohex(c >> 4);
        int b = inttohex(c & ((1 << 4) - 1));
        str.push_back(a);
        str.push_back(b);
    }
    cout << str;
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n;
    cin >> n;

    string key_str;
    string text_str;

    __int8 key[1024];
    int key_size;
    __int8 text[65536];
    int text_size;

    for(int i = 0; i < n; ++i) {
        int rounds, block_size;
        cin >> rounds >> block_size;
        cin >> key_str >> text_str;

        proccess_key(key, key_str);
        key_size = key_str.size() / 2;

        proccess_text(text, text_str);
        text_size = text_str.size();
        complete_str(text, text_size, block_size, '\0');
        feistel(text, text_size, key, rounds, block_size);
        printhex(text, text_size);
        if(i != n - 1) cout << "\n";
    }
    return 0;
}
