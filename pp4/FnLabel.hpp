#ifndef FN_LABEL_H
#define FN_LABEL_H
class FnLabel{
public:
    const int offset;
    const char * label;
    FnLabel(const int i, const char * l) : offset(i), label(l){};
};

struct CompareFn{
    bool operator ()(const FnLabel * l, const FnLabel * r){
        return l->offset < r->offset;
    }
};
#endif
