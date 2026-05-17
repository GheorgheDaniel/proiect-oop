#pragma once

struct Node{
    Node *left, *right;
    int val;
    int fr;
    Node() : left(nullptr), right(nullptr), val(0), fr(0) {}
    bool operator <(const Node& v) const{
        return this->fr > v.fr;
    }

    Node operator +(const Node& v) const {
        Node ans;
        ans.fr = v.fr + this->fr;
        return ans;
    }
};  
