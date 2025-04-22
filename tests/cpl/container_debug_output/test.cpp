// Copyright (c) Brandon Pacewic
// SPDX-License-Identifier: MIT

#include <cassert>
#include <iostream>
#include <list>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include "container.h"

int main() {
    using namespace std;
    using namespace cpl;
    {
        vector<int>  v{1, 2, 3};
        stringstream ss;
        ss << v;
        assert(ss.str() == "{1, 2, 3}");
    }
    {
        list<string> l{"foo", "bar"};
        stringstream ss;
        ss << l;
        assert(ss.str() == "{foo, bar}");
    }
    {
        set<char>    s{'a', 'b'};
        stringstream ss;
        ss << s;
        assert(ss.str() == "{a, b}");
    }
    {
        pair<int, string> p{42, "answer"};
        stringstream      ss;
        ss << p;
        assert(ss.str() == "(42, answer)");
    }
    {
        map<string, int> m{{"x", 1}, {"y", 2}};
        stringstream     ss;
        ss << m;
        // Note: map is ordered by key, so this will be {(x, 1), (y, 2)}
        assert(ss.str() == "{(x, 1), (y, 2)}");
    }
#if DBG_MODE || CPL
    {
        stringstream errbuf;
        auto         old = cerr.rdbuf(errbuf.rdbuf());

        int    a = 10;
        string b = "hi";
        test(a, b);

        cerr.rdbuf(old);

        auto out = errbuf.str();
        assert(out.find("[a, b]:") != string::npos);
        assert(out.find("10") != string::npos);
        assert(out.find("hi") != string::npos);
    }
#endif
    return 0;
}
