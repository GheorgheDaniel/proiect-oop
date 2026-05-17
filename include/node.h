#pragma once

struct Node{
    Node *left, *right;
    int val;
    int fr;
    Node() : left(nullptr), right(nullptr), val(0), fr(0) {}
    bool operator <(const Node& v) const{
        return this->fr > v.fr;
    }

    Node operator +(Node& v) {
        Node ans;
        ans.fr = v.fr + this->fr;
        ans.left = this;  
        ans.right = &v;
        return ans;
    }
};  
