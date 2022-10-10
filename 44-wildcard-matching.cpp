class Solution {
    vector<vector<int>> dp;
public:
    bool isMatch(string &s, string &p, int s_index, int p_index) {
        // If this combination is already handled, return pre computed value.
        if (dp[s_index][p_index] == 1) {
            return true;
        } else if (dp[s_index][p_index] == 0) {
            return false;
        }
        // p_index reached end
        if (p_index == p.size()) {
            if (s_index == s.size()) {
                dp[s_index][p_index] = 1;
                return true;
            } else {
                dp[s_index][p_index] == 0;
                return false;
            }
        }
        // s reached end
        if (s_index == s.size()) {
            // '*' case
            if (p[p_index] == '*') {
                // last character is '*', matching scenario
                if (p_index + 1 == p.size()) {
                    dp[s_index][p_index] = 1;
                    return true;
                } else {
                    // '*' didn't match, move forward p_index
                    return isMatch(s, p, s_index, p_index + 1);
                }
            } else {
                // anything other than '*' in p when s is empty is mismatch
                dp[s_index][p_index] == 0;
                return false;
            }
        }
        // Regular match or '?', skip to next character for p & s
        if (p[p_index] == s[s_index] || p[p_index] == '?') {
            bool ret = isMatch(s, p, s_index + 1, p_index + 1);
            if (ret) {
                dp[s_index][p_index] = 1;
            } else {
                dp[s_index][p_index] = 0;
            }
            return ret;
        } else if (p[p_index] == '*') {
            // 3 cases to be handled
            // '*' matches only current character
            // '*' matches current, matches next character
            // '*' matches none
            bool ret =
                isMatch(s, p, s_index + 1, p_index + 1) ||
                isMatch(s, p, s_index + 1, p_index) ||
                isMatch(s, p, s_index, p_index  + 1);
            if (ret) {
                dp[s_index][p_index] = 1;
            } else {
                dp[s_index][p_index] = 0;
            }
            return ret;
        } else {
            // default case when p point to alphabet and doesn't match with s.
            dp[s_index][p_index] = 0;
            return false;
        }
    }
    bool isMatch(string s, string p) {
        // Allocate size + 1, vector indexes could reach size() during recursion
        dp.resize(s.size() + 1, vector<int>(p.size() + 1, -1));
        return isMatch(s, p, 0, 0);
    }
};