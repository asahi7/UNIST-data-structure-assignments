#include <iostream>
#include <typeinfo>

using namespace std;

template<class K, class V>
class MapElem{
    public: 
        K key;
        V value;
        MapElem* next;
        typedef K ktype;
        typedef V vtype;
};

template<class HashMapElemType>
class HashMap{
public:
    typedef typename HashMapElemType::ktype K;
    typedef typename HashMapElemType::vtype V;
    
    K first;
    V second;

    HashMapElemType** ht;

    HashMap() {}
};

int main(){
    HashMap < MapElem<string, string> > h;
    h.first = "hello";
    h.second = "world";
    cout << h.first << " " << h.second << endl;
  //  h.ht = new MapElem<string, string>*[10];
    h.ht = new HashMapElemType*[10];
    h.ht[0] = new MapElem<string, string>;
    h.ht[0]->key = "word";
    h.ht[0]->value = "egg";
    cout << h.ht[0]->key << " : " << h.ht[0]->value << endl;
    //cout << (typeid(h.first).name()) << endl;;  
    //cout << (typeid(string).name()) << endl;
    return 0;
}
