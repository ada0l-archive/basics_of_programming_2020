#include <iostream>
#include <vector>

using namespace std;

string get_started(string &s)
{
    int index = s.size();
    for (int i = 0; i < s.size(); ++i)
    {
        if (s[i] == ' ' || s[i] == '-'  || s[i] == '_')
        {
            index = i;
            break;
        }
    }
    return s.substr(0, index);
}

bool lt(string &s_1, string &s_2)
{
    return s_1 < s_2;
}

void insert_sort(std::vector<string> &a, bool (*cmp)(string&, string&))
{
    int n_sorted = 1;
    while (n_sorted < a.size())
    {
        if (cmp(a[n_sorted], a[n_sorted - 1]))
        {
            int new_index = 0;
            while (new_index < n_sorted && cmp(a[new_index], a[n_sorted]))
            {
                ++new_index;
            }
            string tmp = a[new_index];
            a[new_index] = a[n_sorted];
            for (int current = n_sorted; current > new_index; --current)
            {
                a[current] = a[current - 1];
            }
            a[new_index + 1] = tmp;
        }
        ++n_sorted;
    }
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n, m;
    vector<string> files, user_playlist, total_playlist;
    string tmp;
    cin >> n;
    files.resize(n);
    getline(cin, tmp); // TODO
    for (int i = 0; i < n; ++i)
    {
        getline(cin, files[i]);
    }
    cin >> m;
    user_playlist.resize(m);
    getline(cin, tmp);
    for (int i = 0; i < m; ++i)
    {
        getline(cin, user_playlist[i]);
    }
    for (int i = 0; i < m; ++i)
    {
        vector<string> total;
        total.push_back(user_playlist[i]);
        for (int j = 0; j < n; ++j)
        {
            if (get_started(user_playlist[i]) == get_started(files[j]) &&
                user_playlist[i] != files[j])
            {
                total.push_back(files[j]);
            }
        }
        insert_sort(total, lt);
        for (int k = 0; k < total.size(); ++k)
        {
            total_playlist.push_back(total[k]);
        }
    }

    for(int i = 0; i < total_playlist.size(); ++i)
    {
        cout << total_playlist[i];
        if (i != total_playlist.size() - 1)
        {
            cout << "\n";
        }
    }

    return 0;
}
