#pragma once

struct Node{
    Node *left, *right;
    int val = 0;
    int fr = 0;
    Node() {
        fr = 0;
        left = nullptr; right = nullptr;
    }
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
