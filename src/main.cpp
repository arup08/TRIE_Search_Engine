#include <bits/stdc++.h>
#include "trie.h"
#include "utils.h"
using namespace std;

int main(int argc, char **argv)
{
    string filename;
    Trie T;
    vector<string> data;

    if (argc > 1)
    {
        filename = argv[1];
        data = get_array_from_file(filename);
    }
    else
    {
        cout << "Enter File name to load data from. ( music | movies | words ) :\n";
        cin >> filename;
        cerr << "loading ...";
        data = get_array_from_file("../data/" + filename + ".txt");
        cerr << "Done.\n";
    }

    for (string word : data)
        T.insert(word);

    if (argc > 2)
    {
        string pattern = argv[2];
        for (string w : search(data, pattern))
            cout << w << "\n";
        return 0;
    }

    int choice;
    do
    {
        cout << "------------------------\nMENU\n1. Exact Search\n2. Prefix Search\n3. Universal Search\n0. Exit\n";
        cin >> choice;
        getchar();

        string pattern;
        if (choice)
        {
            cout << "Enter Search Text (leave empty to list all): ";
            getline(cin, pattern);
        }

        switch (choice)
        {
        case 1:
            cout << (T.search_exact(pattern) ? "String Exists.\n" : "NOT Found.\n");
            break;
        case 2:
            for (string w : T.search_pre(pattern)) cout << w << "\n";
            break;
        case 3:
            for (string w : search(data, pattern)) cout << w << "\n";
            break;
        }

        cout << "\n\npress Enter to continue.";
        getchar();
        system("clear"); // use "cls" if on Windows
    } while (choice);

    return 0;
}
//g++ main.cpp trie.cpp utils.cpp -o search_app
//./search_app


